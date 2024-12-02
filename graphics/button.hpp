#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
   public:
    Button(float x, float y, float width, float height, const std::string& text,
           const sf::Font& font);

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setText(const std::string& text);
    void setFont(const sf::Font& font);
    void setTextColor(const sf::Color& color);
    void setButtonColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

    bool isMouseOver(const sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;

   protected:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};

class ImageButton : public Button {
   public:
    ImageButton(float x, float y, float width, float height,
                const std::string& text, const sf::Font& font,
                const sf::Texture& texture);

    void setTexture(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;

   private:
    sf::Sprite buttonSprite;
};

class TriangleButton : public Button {
   private:
    sf::ConvexShape buttonShape;

   public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };
    Direction direction;
    TriangleButton(float x, float y, float width, float height,
                   const std::string& text, const sf::Font& font,
                   Direction direction);

    void draw(sf::RenderWindow& window) const;
};

#endif  // BUTTON_HPP