/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#include "SDL.hpp"

SDL::SDL() : _window(nullptr), _renderer(nullptr)
{
}

SDL::~SDL()
{
}

void SDL::drawWindow()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    SDL_UpdateWindowSurface(_window);
}

void SDL::clear()
{
    SDL_RenderClear(_renderer);
}

void SDL::drawRect(const Arcade::IRect &rect)
{
    SDL_Rect r{static_cast<int>(rect.getPosition().x - rect.getOrigin().x),
               static_cast<int>(rect.getPosition().y - rect.getOrigin().y),
               static_cast<int>(rect.getWidth()),
               static_cast<int>(rect.getHeight())};
    Arcade::Color color = rect.getColor();
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &r);
}

void SDL::drawText(const Arcade::IText &text)
{
    if (!text.getText().empty()) {
        std::string fontPath = text.getPathFont();
        std::string fontName = fontPath.substr(fontPath.find_last_of("/\\") + 1);

        TTF_Font *font = TTF_OpenFont(text.getPathFont().c_str(), text.getTextSize());
        if (!font)
            throw LibError("SDL: SDL_Text: Can't load font -> '" + fontPath + "'!");
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.getText().c_str(), getColorFromArcadeColor(text.getColor()));
        if (!surface)
            throw LibError("SDL: SDL_Text: Can't create surface");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture)
            throw LibError("SDL: SDL_Text: Can't create texture");
        SDL_Rect rect{static_cast<int>(text.getPosition().x - text.getOrigin().x),
                static_cast<int>(text.getPosition().y - text.getOrigin().y + surface->h / 2),
                static_cast<int>(surface->w),
                static_cast<int>(surface->h)};
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
}

void SDL::drawCircle(const Arcade::ICircle &circle)
{
    float radius = circle.getRadius();
    Arcade::Color color = circle.getColor();

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
                SDL_RenderDrawPoint(_renderer,
                circle.getPosition().x + dx + radius - circle.getOrigin().x,
                circle.getPosition().y + dy + radius - circle.getOrigin().y);
        }
    }
}

void SDL::drawImage(const Arcade::IImage &image)
{
    const unsigned char *buf = image.getBufferRGBA();
    Arcade::Vector2f pos = image.getPosition();
    Arcade::Vector2i dim = image.getDimension();
    int x = 0;
    int y = 0;
    int w = image.getDimension().y;

    for (int i = 0; i < dim.x * dim.y * 4; i += 4) {
        SDL_SetRenderDrawColor(_renderer, buf[i],
                                          buf[i + 1],
                                          buf[i + 2],
                                          buf[i + 3]);
        SDL_RenderDrawPoint(_renderer,  x + (pos.x - image.getOrigin().x),
                                        y + (pos.y - image.getOrigin().y));
        x++;
        if (x >= w) {
            x = 0;
            y++;
        }
    }
}

const Arcade::Event SDL::pollEvent()
{
    Arcade::Event event{Arcade::EventType::TYPE_UNKNOWN, Arcade::EventKey::KEY_UNKNOWN, 0};
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT)
            event.type = Arcade::EventType::CLOSE;
        if (sdlEvent.type == SDL_KEYUP)
            event.type = Arcade::EventType::KEY_RELEASE;
        if (sdlEvent.type == SDL_KEYDOWN) {
            event.type = Arcade::EventType::KEY_PRESS;
            if (sdlEvent.key.keysym.sym == SDLK_BACKSPACE) {
                event.type = Arcade::EventType::TEXT_ENTERED;
                event.unicode = 8;
            }
        }
        if (sdlEvent.type == SDL_TEXTINPUT) {
            event.type = Arcade::EventType::TEXT_ENTERED;
            event.unicode = sdlEvent.text.text[0];
        }
        if (sdlEvent.type == SDL_MOUSEMOTION) {
            event.type = Arcade::EventType::MOUSE_MOVE;
            SDL_GetMouseState(&event.mouse.x, &event.mouse.y);
        }
        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_q: event.key = Arcade::EventKey::Q; break;
                case SDLK_z: event.key = Arcade::EventKey::Z; break;
                case SDLK_d: event.key = Arcade::EventKey::D; break;
                case SDLK_s: event.key = Arcade::EventKey::S; break;
                case SDLK_UP: event.key = Arcade::EventKey::UP; break;
                case SDLK_DOWN: event.key = Arcade::EventKey::DOWN; break;
                case SDLK_RIGHT: event.key = Arcade::EventKey::RIGHT; break;
                case SDLK_LEFT: event.key = Arcade::EventKey::LEFT; break;
                case SDLK_ESCAPE: event.key = Arcade::EventKey::ECHAP; break;
                case SDLK_RETURN: event.key = Arcade::EventKey::ENTER; break;
                case SDLK_SPACE: event.key = Arcade::EventKey::SPACE; break;
                default: break;
            }
        }
    }
    return (event);
}

bool SDL::isOpen() const
{
    return (true);
}

void SDL::createWindow(int x, int y, const std::string &title)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        throw LibError("SDL: Init Video Error -> " + std::string(SDL_GetError()));
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!_window)
        throw LibError("SDL: Error creating SDL Window");
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!_renderer)
        throw LibError("SDL: Error creating Renderer");
    if (TTF_Init() != 0)
        throw LibError("SDL: Init TTF Error : " + std::string(TTF_GetError()));
}

void SDL::closeWindow()
{
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

SDL_Color SDL::getColorFromArcadeColor(const Arcade::Color &color) const
{
    return (SDL_Color{static_cast<Uint8>(color.r),
                      static_cast<Uint8>(color.g),
                      static_cast<Uint8>(color.b),
                      static_cast<Uint8>(color.a)});
}

void SDL::initMusic(const Arcade::IMusic &music)
{
}

void SDL::closeMusic()
{
}

void SDL::playSound(const Arcade::ISound &sound)
{
}