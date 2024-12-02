#include "button.hpp"

Button::Button(float x, float y, float width, float height,
               const std::string& text, const sf::Font& font) {
    buttonShape.setPosition(x, y);
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);            // Default character size
    buttonText.setFillColor(sf::Color::Black);  // Default text color
    buttonText.setPosition(
        static_cast<int>(x + (width - buttonText.getLocalBounds().width) / 2),
        static_cast<int>(y +
                         (height - buttonText.getLocalBounds().height) / 2));
}

void Button::setPosition(float x, float y) {
    buttonShape.setPosition(x, y);
    buttonText.setPosition(
        x + (buttonShape.getSize().x - buttonText.getLocalBounds().width) / 2,
        y + (buttonShape.getSize().y - buttonText.getLocalBounds().height) / 2);
}

void Button::setSize(float width, float height) {
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonText.setPosition(
        buttonShape.getPosition().x +
            (width - buttonText.getLocalBounds().width) / 2,
        buttonShape.getPosition().y +
            (height - buttonText.getLocalBounds().height) / 2);
}

void Button::setText(const std::string& text) {
    buttonText.setString(text);
    buttonText.setPosition(
        buttonShape.getPosition().x +
            (buttonShape.getSize().x - buttonText.getLocalBounds().width) / 2,
        buttonShape.getPosition().y +
            (buttonShape.getSize().y - buttonText.getLocalBounds().height) / 2);
}

void Button::setFont(const sf::Font& font) { buttonText.setFont(font); }

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}

void Button::setButtonColor(const sf::Color& color) {
    buttonShape.setFillColor(color);
}

void Button::setOutlineColor(const sf::Color& color) {
    buttonShape.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    buttonShape.setOutlineThickness(thickness);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonRect = buttonShape.getGlobalBounds();
    return buttonRect.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(buttonShape);
    window.draw(buttonText);
}

ImageButton::ImageButton(float x, float y, float width, float height,
                         const std::string& text, const sf::Font& font,
                         const sf::Texture& texture)
    : Button(x, y, width, height, text, font) {
    buttonSprite.setTexture(texture);
    buttonSprite.setPosition(x, y);
    buttonSprite.setScale(width / buttonSprite.getLocalBounds().width,
                          height / buttonSprite.getLocalBounds().height);
}

void ImageButton::setTexture(const sf::Texture& texture) {
    buttonSprite.setTexture(texture);
    buttonSprite.setScale(
        buttonShape.getSize().x / buttonSprite.getLocalBounds().width,
        buttonShape.getSize().y / buttonSprite.getLocalBounds().height);
}

void ImageButton::draw(sf::RenderWindow& window) const {
    window.draw(buttonSprite);
    Button::draw(window);
}

TriangleButton::TriangleButton(float x, float y, float width, float height,
                               const std::string& text, const sf::Font& font,
                               Direction direction)
    : Button(x, y, width, height, text, font), direction(direction) {
    buttonShape.setPointCount(3);
    if (direction == Direction::UP) {
        buttonShape.setPoint(0, sf::Vector2f(width / 2 + x, 0 + y));
        buttonShape.setPoint(1, sf::Vector2f(0 + x, height + y));
        buttonShape.setPoint(2, sf::Vector2f(width + x, height + y));
    } else if (direction == Direction::DOWN) {
        buttonShape.setPoint(0 + x, sf::Vector2f(0 + x, 0 + y));
        buttonShape.setPoint(1, sf::Vector2f(width + x, 0 + y));
        buttonShape.setPoint(2, sf::Vector2f(width / 2 + x, height + y));
    } else if (direction == Direction::LEFT) {
        buttonShape.setPoint(0, sf::Vector2f(width + x, 0 + y));
        buttonShape.setPoint(1, sf::Vector2f(width + x, height + y));
        buttonShape.setPoint(2, sf::Vector2f(0 + x, height / 2 + y));
    } else if (direction == Direction::RIGHT) {
        buttonShape.setPoint(0, sf::Vector2f(0 + x, 0 + y));
        buttonShape.setPoint(1, sf::Vector2f(width + x, height / 2 + y));
        buttonShape.setPoint(2, sf::Vector2f(0 + x, height + y));
    }
}

void TriangleButton::draw(sf::RenderWindow& window) const {
    window.draw(buttonShape);
    window.draw(buttonText);
}