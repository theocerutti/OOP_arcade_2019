/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#include "NCurses.hpp"

NCurses::NCurses() : _window(nullptr), _sizeRatio({3, 7})
{
}

NCurses::~NCurses()
{
}

void NCurses::drawWindow()
{
    refresh();
}

void NCurses::clear()
{
    erase();
}

void NCurses::drawRect(const Arcade::IRect &rect)
{
    Arcade::Vector2f pos = rect.getPosition();

    attron(COLOR_PAIR(getColorIdFromColor(rect.getColor())));
    for (int y = 0; y < rect.getHeight() / _sizeRatio.y; y++)
        mvprintw((pos.y / _sizeRatio.y) + y, pos.x / _sizeRatio.x, std::string(rect.getWidth() / _sizeRatio.x, ' ').c_str());
    attroff(COLOR_PAIR(COLOR_BLACK));
}

void NCurses::drawText(const Arcade::IText &text)
{
    Arcade::Vector2f pos = text.getPosition();

    attron(COLOR_PAIR(TEXT_MODE(getColorIdFromColor(text.getColor()))));
    mvprintw(pos.y / _sizeRatio.y, pos.x / _sizeRatio.x, text.getText().c_str());
    attroff(COLOR_PAIR(COLOR_BLACK));
}

void NCurses::drawCircle(const Arcade::ICircle &circle)
{
    int r = 0;
    Arcade::Vector2f pos = circle.getPosition();
    int radius = circle.getRadius();

    attron(COLOR_PAIR(getColorIdFromColor(circle.getColor())));
    for (int y = -radius; y < radius; y++) {
        r = sqrt(radius * radius - y * y);
        for (int x = -r; x < r; x++) {
            mvprintw((pos.y + y) / _sizeRatio.y, (pos.x + x) / _sizeRatio.y, " ");
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
}

void NCurses::drawImage(const Arcade::IImage &image)
{
    /*const unsigned char *buf = image.getBuffer();
    Arcade::Vector2f pos = image.getPosition();
    Arcade::Vector2i dim = image.getDimension();
    int colorId = 0;

    for (int y = 0; y < dim.y; y++) {
        for (int x = 0; x < dim.x; x++) {
            colorId = buf[x + (y * dim.x)];
            if ((colorId >= 'A' && colorId <= 'Z') || (colorId >= '0' && colorId <= '9')) {
                colorId -= (colorId >= '0' && colorId <= '9') ? '0' : 'A' - 10;
                attron(COLOR_PAIR(colorId));
                mvprintw((y / _sizeRatio.y) + pos.y, (x / _sizeRatio.x) + pos.x, " ");
                attroff(COLOR_PAIR(COLOR_BLACK));
            }
        }
    }*/
}

void NCurses::init_colors() const
{
    Arcade::Color color;

    start_color();
    for (int colorId = 0; colorId <= Arcade::BWHITE * 2; colorId++) {
        color = Arcade::getColor(colorId);
        if (colorId < Arcade::BWHITE)
            init_pair(colorId, colorId, colorId);
        else
            init_pair(colorId, colorId - Arcade::BWHITE, COLOR_BLACK);
    }
    wbkgd(_window, COLOR_PAIR(Arcade::BLACK));
}

void NCurses::createWindow(int x, int y, const std::string &title)
{
    _window = initscr();
    init_colors();
    keypad(_window, TRUE);
    nodelay(_window, TRUE);
    curs_set(0);    // removes cursor
    cbreak();       // displays character without pressing ENTER
    noecho();       // remove multi displays of pressed character
}

void NCurses::closeWindow()
{
    if (_window != nullptr)
        endwin();
}

const Arcade::Event NCurses::pollEvent()
{
    Arcade::Event event{Arcade::EventType::KEY_RELEASE,
                        Arcade::EventKey::KEY_UNKNOWN, 0};
    int ncurseEvent = getch();

    event.unicode = ncurseEvent;
    if (ncurseEvent != ERR) {
        switch (ncurseEvent) {
            case 'q': event.key = Arcade::EventKey::Q; break;
            case 'z': event.key = Arcade::EventKey::Z; break;
            case 'd': event.key = Arcade::EventKey::D; break;
            case 's': event.key = Arcade::EventKey::S; break;
            case KEY_UP: event.key = Arcade::EventKey::UP; break;
            case KEY_DOWN: event.key = Arcade::EventKey::DOWN; break;
            case KEY_RIGHT: event.key = Arcade::EventKey::RIGHT; break;
            case KEY_LEFT: event.key = Arcade::EventKey::LEFT; break;
            case 27: event.key = Arcade::EventKey::ECHAP; break;
            case 10: event.key = Arcade::EventKey::ENTER; break;
            case ' ': event.key = Arcade::EventKey::SPACE; break;
            default: break;
        }
    }
    return (event);
}

bool NCurses::isOpen() const
{
    return (stdscr != nullptr);
}

Arcade::Colors NCurses::getColorIdFromColor(const Arcade::Color &color)
{
    Arcade::Color tmp;

    for (int colorId = 0; colorId <= Arcade::Colors::NONE; colorId++) {
        tmp = Arcade::getColor(colorId);
        if (color.r == tmp.r && color.g == tmp.g && color.b == tmp.b && color.a == tmp.a)
            return (static_cast<Arcade::Colors>(colorId));
    }
    return (Arcade::NONE);
}

void NCurses::initMusic(const Arcade::IMusic &music)
{
}

void NCurses::closeMusic()
{
}

void NCurses::playSound(const Arcade::ISound &sound)
{
}