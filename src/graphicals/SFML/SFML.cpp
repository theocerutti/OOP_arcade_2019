/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML() : _window(), _music(), _sound(), _buffer()
{
}

SFML::~SFML()
{
}

void SFML::drawWindow()
{
    _window.display();
}

void SFML::clear()
{
    _window.clear();
}

void SFML::drawRect(const Arcade::IRect &rect)
{
    sf::RectangleShape rectShape(sf::Vector2f(rect.getWidth(), rect.getHeight()));
    Arcade::Color color = rect.getColor();

    rectShape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    rectShape.setPosition(rect.getPosition().x, rect.getPosition().y);
    rectShape.setOrigin(rect.getOrigin().x, rect.getOrigin().y);
    rectShape.setRotation(rect.getRotation());
    _window.draw(rectShape);
}

void SFML::drawText(const Arcade::IText &text)
{
    sf::Text textObj;
    sf::Font font;

    if (!font.loadFromFile(text.getPathFont()))
        throw LibError("SFML: drawText: Can't load font -> '" + text.getPathFont() + "' !");
    textObj.setFont(font);
    textObj.setString(text.getText());
    textObj.setCharacterSize(text.getTextSize());
    textObj.setOrigin(text.getOrigin().x, text.getOrigin().y);
    textObj.setPosition(text.getPosition().x, text.getPosition().y);
    Arcade::Color color = text.getColor();
    textObj.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    textObj.setRotation(text.getRotation());
    _window.draw(textObj);
}

void SFML::drawCircle(const Arcade::ICircle &circle)
{
    sf::CircleShape circleShape(circle.getRadius());

    Arcade::Color color = circle.getColor();
    circleShape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    circleShape.setPosition(circle.getPosition().x, circle.getPosition().y);
    circleShape.setOrigin(circle.getOrigin().x, circle.getOrigin().y);
    circleShape.setRotation(circleShape.getRotation());
    _window.draw(circleShape);
}

void SFML::drawImage(const Arcade::IImage &image)
{
    Arcade::Vector2f origin = image.getOrigin();
    Arcade::Vector2f pos = image.getPosition();
    Arcade::Vector2i dim = image.getDimension();
    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(dim.x, dim.y);
    texture.update(image.getBufferRGBA());
    sprite.setTexture(texture);
    sprite.setPosition(pos.x, pos.y);
    sprite.setOrigin(origin.x, origin.y);
    sprite.setRotation(image.getRotation());
    _window.draw(sprite);
}

const Arcade::Event SFML::pollEvent()
{
    Arcade::Event event{Arcade::EventType::TYPE_UNKNOWN, Arcade::EventKey::KEY_UNKNOWN, 0, {0, 0}};
    sf::Event sfmlEvent;

    while (_window.pollEvent(sfmlEvent)) {
        if (sfmlEvent.type == sf::Event::Closed)
            event.type = Arcade::EventType::CLOSE;
        if (sfmlEvent.type == sf::Event::KeyPressed)
            event.type = Arcade::EventType::KEY_PRESS;
        if (sfmlEvent.type == sf::Event::KeyReleased)
            event.type = Arcade::EventType::KEY_RELEASE;
        if (sfmlEvent.type == sf::Event::TextEntered) {
            event.type = Arcade::EventType::TEXT_ENTERED;
            event.unicode = sfmlEvent.text.unicode;
        }
        if (sfmlEvent.type == sf::Event::MouseMoved) {
            event.type = Arcade::EventType::MOUSE_MOVE;
            event.mouse.x = sf::Mouse::getPosition(_window).x;
            event.mouse.y = sf::Mouse::getPosition(_window).y;
        }
        if (sfmlEvent.type == sf::Event::KeyReleased || sfmlEvent.type == sf::Event::KeyPressed) {
            switch (sfmlEvent.key.code) {
                case sf::Keyboard::Q: event.key = Arcade::EventKey::Q; break;
                case sf::Keyboard::Z: event.key = Arcade::EventKey::Z; break;
                case sf::Keyboard::D: event.key = Arcade::EventKey::D; break;
                case sf::Keyboard::S: event.key = Arcade::EventKey::S; break;
                case sf::Keyboard::Up: event.key = Arcade::EventKey::UP; break;
                case sf::Keyboard::Down: event.key = Arcade::EventKey::DOWN; break;
                case sf::Keyboard::Right: event.key = Arcade::EventKey::RIGHT; break;
                case sf::Keyboard::Left: event.key = Arcade::EventKey::LEFT; break;
                case sf::Keyboard::Escape: event.key = Arcade::EventKey::ECHAP; break;
                case sf::Keyboard::Return: event.key = Arcade::EventKey::ENTER; break;
                case sf::Keyboard::Space: event.key = Arcade::EventKey::SPACE; break;
                default: break;
            }
        }
    }
    return (event);
}

bool SFML::isOpen() const
{
    return (_window.isOpen());
}

void SFML::closeWindow()
{
    _window.close();
}

void SFML::createWindow(int x, int y, const std::string &title)
{
    _window.create(sf::VideoMode(x, y), title);
}

void SFML::initMusic(const Arcade::IMusic &music)
{
    _music.openFromFile(music.getMusic());
    _music.setLoop(music.isLooping());
    _music.setVolume(music.getVolume());
    _music.play();
}

void SFML::closeMusic()
{
    _sound.stop();
    _music.stop();
}

void SFML::playSound(const Arcade::ISound &sound)
{
    if (!_buffer.loadFromFile(sound.getSound()))
        throw LibError("SFML: playSound: can't open '" + sound.getSound() + "!");
    _sound.setBuffer(_buffer);
    _sound.setVolume(sound.getVolume());
    _sound.play();
}