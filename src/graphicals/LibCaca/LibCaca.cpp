/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibCaca
*/

#include "LibCaca.hpp"

LibCaca::LibCaca() : _sizeRatio(5, 10)
{
    uint32_t const tmp = 0x12345678;
    unsigned int order[4] = {0xff0000, 0xff00, 0xff, 0xff000000};

    if(*(uint8_t const *)&tmp != 0x12) {
        order[0] = 0xff00;
        order[1] = 0xff0000;
        order[2] = 0xff000000;
        order[3] = 0xff;
    }
    _bmp = std::make_unique<Dither>(32, 256, 256, 4 * 256, order[0], order[1], order[2], order[3]);
}

LibCaca::~LibCaca()
{
}

void LibCaca::drawWindow()
{
    _caca->Display();
}

void LibCaca::clear()
{
    _window->Clear();
}

void LibCaca::drawRect(const Arcade::IRect &rect)
{
    Arcade::Vector2f pos = rect.getPosition();
    Arcade::Vector2f dim = rect.getDimension();
    int colorId = from32To16Bits(rect.getColor());

    if (dim.x > 0 && dim.y > 0) {
        _window->setColorARGB(colorId, colorId);
        _window->fillBox(pos.x / _sizeRatio.x, pos.y / _sizeRatio.y, dim.x / _sizeRatio.x, dim.y / _sizeRatio.y, ' ');
        _window->setColorANSI(CACA_BLACK, CACA_BLACK);
    }
}

void LibCaca::drawText(const Arcade::IText &text)
{
    Arcade::Vector2f pos = text.getPosition();
    int colorId = from32To16Bits(text.getColor());

    _window->setColorARGB(colorId, CACA_BLACK);
    _window->putStr(pos.x / _sizeRatio.x, pos.y / _sizeRatio.y, const_cast<char *>(text.getText().c_str()));
    _window->setColorANSI(CACA_TRANSPARENT, CACA_TRANSPARENT);
}

void LibCaca::drawCircle(const Arcade::ICircle &circle)
{
    Arcade::Vector2f pos = circle.getPosition();
    int colorId = from32To16Bits(circle.getColor());

    if (circle.getRadius() > 0) {
        _window->setColorARGB(colorId, colorId);
        _window->fillEllipse(pos.x / _sizeRatio.x, pos.y / _sizeRatio.y, circle.getRadius() / _sizeRatio.x, circle.getRadius() / _sizeRatio.y, '*');
        _window->setColorANSI(CACA_BLACK, CACA_BLACK);
    }
}

void LibCaca::drawImage(const Arcade::IImage &image)
{
    Arcade::Vector2f pos = image.getPosition();
    Arcade::Vector2i dim = image.getDimension();
    uint32_t const tmp = 0x12345678;
    unsigned int order[4] = {0xff0000, 0xff00, 0xff, 0xff000000};

    if(*(uint8_t const *)&tmp != 0x12) {
        order[2] = 0xff0000;
        order[1] = 0xff00;
        order[0] = 0xff;
        order[3] = 0xff000000;
    }
    Dither bmp(32, dim.x, dim.y, 4 * dim.x, order[0], order[1], order[2], order[3]);
    bmp.Bitmap(_window.get(),
                 pos.x / _sizeRatio.x,
                 pos.y / _sizeRatio.y,
                 dim.x / _sizeRatio.x,
                 dim.y / _sizeRatio.y,
                 const_cast<unsigned char *>(image.getBufferRGBA()));
}

void LibCaca::createWindow(int x, int y, const std::string &title)
{
    _window = std::make_unique<Canvas>(x / _sizeRatio.x, y / _sizeRatio.y);
    _caca = std::make_unique<Caca>(_window.get());
    _caca->setTitle(title.c_str());
}

void LibCaca::closeWindow()
{
    _caca.~unique_ptr();
    _window.~unique_ptr();
}

const Arcade::Event LibCaca::pollEvent()
{
    static int last = 0;
    Arcade::Event event{Arcade::EventType::TYPE_UNKNOWN, Arcade::EventKey::KEY_UNKNOWN, 0};
    caca_event_t cacaEvent;
    MyCaca *_myCaca = reinterpret_cast<MyCaca *>(_caca.get());

    while (caca_get_event(_myCaca->dp, CACA_EVENT_ANY, &cacaEvent, 0)) {
        if (caca_get_event_type(&cacaEvent) & CACA_EVENT_QUIT)
            event.type = Arcade::EventType::CLOSE;
        if (caca_get_event_key_ch(&cacaEvent) != last && caca_get_event_type(&cacaEvent) & CACA_EVENT_KEY_PRESS) {
            event.type = Arcade::EventType::TEXT_ENTERED;
            event.unicode = caca_get_event_key_ch(&cacaEvent);
            last = event.unicode;
        } else if (caca_get_event_type(&cacaEvent) & CACA_EVENT_KEY_PRESS) {
            event.type = Arcade::EventType::KEY_PRESS;
        } else if (caca_get_event_type(&cacaEvent) & CACA_EVENT_KEY_RELEASE) {
            last = 0;
            event.type = Arcade::EventType::KEY_RELEASE;
        }
        if (caca_get_event_type(&cacaEvent) & CACA_EVENT_KEY_PRESS || caca_get_event_type(&cacaEvent) & CACA_EVENT_KEY_RELEASE) {
            switch (caca_get_event_key_ch(&cacaEvent)) {
                case 'q': event.key = Arcade::EventKey::Q; break;
                case 'z': event.key = Arcade::EventKey::Z; break;
                case 'd': event.key = Arcade::EventKey::D; break;
                case 's': event.key = Arcade::EventKey::S; break;
                case CACA_KEY_UP: event.key = Arcade::EventKey::UP; break;
                case CACA_KEY_DOWN: event.key = Arcade::EventKey::DOWN; break;
                case CACA_KEY_RIGHT: event.key = Arcade::EventKey::RIGHT; break;
                case CACA_KEY_LEFT: event.key = Arcade::EventKey::LEFT; break;
                case CACA_KEY_ESCAPE: event.key = Arcade::EventKey::ECHAP; break;
                case CACA_KEY_RETURN: event.key = Arcade::EventKey::ENTER; break;
                case ' ': event.key = Arcade::EventKey::SPACE; break;
                default: break;
            }
        }
    }
    return (event);
}

bool LibCaca::isOpen() const
{
    return (true);
}

Arcade::Colors LibCaca::getColorIdFromColor(const Arcade::Color &color)
{
    Arcade::Color tmp;

    for (int colorId = 0; colorId <= Arcade::Colors::NONE; colorId++) {
        tmp = Arcade::getColor(colorId);
        if (color.r == tmp.r && color.g == tmp.g && color.b == tmp.b && color.a == tmp.a)
            return (static_cast<Arcade::Colors>(_colorsCaca[colorId][1]));
    }
    return (Arcade::NONE);
}

std::uint16_t LibCaca::from32To16Bits(const Arcade::Color &color) {
    int r = (color.r >> 4) & 0xf;
    int g = (color.g >> 4) & 0xf;
    int b = (color.b >> 4) & 0xf;
    int a = (color.a >> 4) & 0xf;

    return (b << 0) | (g << 4) | (r << 8) | (a << 12);
}

void LibCaca::initMusic(const Arcade::IMusic &music)
{
}

void LibCaca::closeMusic()
{
}

void LibCaca::playSound(const Arcade::ISound &sound)
{
}