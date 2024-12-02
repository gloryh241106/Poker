#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "graphics/button.hpp"

enum class GameState { MAIN_MENU, GAME_CONFIG, GAME, TUTORIAL };
const unsigned int WINDOW_WIDTH = 1000;
const unsigned int WINDOW_HEIGHT = 800;

void horizontalCenterText(sf::Text& text, sf::RenderWindow& window) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(static_cast<int>(textRect.left + textRect.width / 2.0f),
                   static_cast<int>(textRect.top + textRect.height / 2.0f));
    text.setPosition(sf::Vector2f(static_cast<int>(window.getSize().x / 2.0f),
                                  text.getPosition().y));
}

int main() {
    //-------------------------------------------------------------------------
    // Init
    //-------------------------------------------------------------------------

    auto window =
        sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "CMake SFML Project");
    window.setFramerateLimit(144);

    // Change window background color
    sf::Color windowBackground = sf::Color(0x064800FF);
    window.clear(windowBackground);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/unscii-16.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Load speaker on image
    sf::Texture speakerOnTexture;
    if (!speakerOnTexture.loadFromFile("assets/images/speaker.png")) {
        std::cerr << "Error loading speaker on image\n";
        return -1;
    }

    // Load speaker off image
    sf::Texture speakerOffTexture;
    if (!speakerOffTexture.loadFromFile("assets/images/speaker-off.png")) {
        std::cerr << "Error loading speaker off image\n";
        return -1;
    }

    // Load home image
    sf::Texture homeTexture;
    if (!homeTexture.loadFromFile("assets/images/home.png")) {
        std::cerr << "Error loading home image\n";
        return -1;
    }

    // Load player images
    sf::Texture playerTextures[8];
    for (int i = 0; i < 8; i++) {
        if (!playerTextures[i].loadFromFile("assets/images/player" +
                                            std::to_string(i) + ".png")) {
            std::cerr << "Error loading player " << i + 1 << " image\n";
            return -1;
        }
    }

    //-------------------------------------------------------------------------
    // Main menu init
    //-------------------------------------------------------------------------

    // Game title
    sf::Text gameTitle;
    gameTitle.setFont(font);
    gameTitle.setString("Poker");
    gameTitle.setCharacterSize(60);
    gameTitle.setFillColor(sf::Color::White);

    // Center the game title text horizontally
    gameTitle.setPosition(0, 100);
    horizontalCenterText(gameTitle, window);

    // New Game Button
    Button newGameButton(WINDOW_WIDTH / 2 - 100.f, 400.f, 200.f, 50.f,
                         "New Game", font);
    newGameButton.setButtonColor(sf::Color::Black);
    newGameButton.setTextColor(sf::Color::White);

    // Tutorial Button
    Button tutorialButton(WINDOW_WIDTH / 2 - 100.f, 475.f, 200.f, 50.f,
                          "Tutorial", font);
    tutorialButton.setButtonColor(sf::Color::Black);
    tutorialButton.setTextColor(sf::Color::White);

    // Credit Button
    // TODO: Add credit button

    // Speaker Button
    ImageButton speakerButton(930.f, 20.f, 50.f, 50.f, "", font,
                              speakerOnTexture);
    speakerButton.setButtonColor(sf::Color::Transparent);

    // Home Button
    ImageButton homeButton(20.f, 20.f, 45.f, 45.f, "", font, homeTexture);
    homeButton.setButtonColor(sf::Color::Transparent);

    // Create a triangle button using the TriangleButton class
    // TriangleButton triangleButton(400.f, 500.f, 50.f, 50.f, "Triangle", font,
    //                               TriangleButton::Direction::UP);

    //-------------------------------------------------------------------------
    // Tutorial init
    //-------------------------------------------------------------------------

    sf::Text tutorialTitle;
    tutorialTitle.setFont(font);
    tutorialTitle.setString("Tutorial");
    tutorialTitle.setCharacterSize(40);
    tutorialTitle.setFillColor(sf::Color::White);

    // Center the game title text horizontally
    tutorialTitle.setPosition(0, 100);
    horizontalCenterText(tutorialTitle, window);

    sf::Text tutorialText;
    tutorialText.setFont(font);
    tutorialText.setString(
        "This is a tutorial\n"
        "Press the back button to return to the main menu");
    tutorialText.setCharacterSize(18);
    tutorialText.setFillColor(sf::Color::White);
    tutorialText.setPosition(50, 180);

    Button tutorialBackButton(50.f, 500.f, 100.f, 50.f, "Back", font);
    tutorialBackButton.setButtonColor(sf::Color::Black);
    tutorialBackButton.setTextColor(sf::Color::White);

    //-------------------------------------------------------------------------
    // Game config init
    //-------------------------------------------------------------------------

    std::string gameModeText[] = {"Basic", "5-card stud"};
    int gameMode = 0;

    sf::Text gameModeSelectLabel;
    gameModeSelectLabel.setFont(font);
    gameModeSelectLabel.setString("Select game mode:");
    gameModeSelectLabel.setCharacterSize(24);
    gameModeSelectLabel.setFillColor(sf::Color::White);
    gameModeSelectLabel.setPosition(50, 150);

    sf::Text gameModeSelect;
    gameModeSelect.setFont(font);
    gameModeSelect.setString(gameModeText[gameMode]);
    gameModeSelect.setCharacterSize(20);
    gameModeSelect.setFillColor(sf::Color::White);
    gameModeSelect.setPosition(0, 200);
    horizontalCenterText(gameModeSelect, window);

    TriangleButton gameModeLeftButton(WINDOW_WIDTH / 2 - 100.f, 185.f, 20.f,
                                      30.f, "", font,
                                      TriangleButton::Direction::LEFT);
    gameModeLeftButton.setButtonColor(sf::Color::Black);

    TriangleButton gameModeRightButton(WINDOW_WIDTH / 2 + 80.f, 185.f, 20.f,
                                       30.f, "", font,
                                       TriangleButton::Direction::RIGHT);
    gameModeRightButton.setButtonColor(sf::Color::Black);

    int playerCount = 2;

    sf::Text gamePlayerCountSelectLabel;
    gamePlayerCountSelectLabel.setFont(font);
    gamePlayerCountSelectLabel.setString("Number of players (2-8):");
    gamePlayerCountSelectLabel.setCharacterSize(24);
    gamePlayerCountSelectLabel.setFillColor(sf::Color::White);
    gamePlayerCountSelectLabel.setPosition(50, 300);

    sf::Text gamePlayerCountSelect;
    gamePlayerCountSelect.setFont(font);
    gamePlayerCountSelect.setString(std::to_string(playerCount));
    gamePlayerCountSelect.setCharacterSize(20);
    gamePlayerCountSelect.setFillColor(sf::Color::White);
    gamePlayerCountSelect.setPosition(0, 350);
    horizontalCenterText(gamePlayerCountSelect, window);

    TriangleButton gamePlayerCountLeftButton(WINDOW_WIDTH / 2 - 100.f, 335.f,
                                             20.f, 30.f, "", font,
                                             TriangleButton::Direction::LEFT);
    gamePlayerCountLeftButton.setButtonColor(sf::Color::Black);

    TriangleButton gamePlayerCountRightButton(WINDOW_WIDTH / 2 + 80.f, 335.f,
                                              20.f, 30.f, "", font,
                                              TriangleButton::Direction::RIGHT);
    gamePlayerCountRightButton.setButtonColor(sf::Color::Black);

    Button startGameButton(WINDOW_WIDTH / 2 - 100.f, 450.f, 200.f, 50.f,
                           "Start Game", font);
    startGameButton.setButtonColor(sf::Color::Black);
    startGameButton.setTextColor(sf::Color::White);

    //-------------------------------------------------------------------------
    // Game init
    //-------------------------------------------------------------------------

    sf::Vector2f playerPositions[8] = {
        {475.f, 350.f}, {475.f, 50.f}, {50.f, 200.f},  {900.f, 200.f},
        {200.f, 50.f},  {750.f, 50.f}, {200.f, 350.f}, {750.f, 350.f}};

    sf::Sprite playerSprites[8];
    for (int i = 0; i < 8; i++) {
        playerSprites[i].setTexture(playerTextures[i]);
        playerSprites[i].setPosition(playerPositions[i]);
        playerSprites[i].setScale(0.5f, 0.5f);
    }

    Button foldButton(WINDOW_WIDTH / 2 - 200.f, 700.f, 100.f, 50.f, "Fold",
                      font);
    foldButton.setButtonColor(sf::Color::Black);
    foldButton.setTextColor(sf::Color::White);

    Button callButton(WINDOW_WIDTH / 2 - 50.f, 700.f, 100.f, 50.f, "Call",
                      font);
    callButton.setButtonColor(sf::Color::Black);
    callButton.setTextColor(sf::Color::White);

    Button raiseButton(WINDOW_WIDTH / 2 + 100.f, 700.f, 100.f, 50.f, "Raise",
                       font);
    raiseButton.setButtonColor(sf::Color::Black);
    raiseButton.setTextColor(sf::Color::White);

    //-------------------------------------------------------------------------
    // Main loop
    //-------------------------------------------------------------------------

    // Play background music
    sf::Music bgm;
    if (!bgm.openFromFile("assets/audio/bgm.wav")) {
        std::cerr << "Error loading background music\n";
        return -1;
    }
    bgm.setLoop(true);
    bgm.play();
    bool isSpeakerOn = true;

    // Initialize the game state
    GameState gameState = GameState::MAIN_MENU;

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Handle left mouse button click
                    if (speakerButton.isMouseOver(window)) {
                        if (isSpeakerOn) {
                            speakerButton.setTexture(speakerOffTexture);
                            bgm.setVolume(0);
                            isSpeakerOn = false;
                        } else {
                            speakerButton.setTexture(speakerOnTexture);
                            bgm.setVolume(100);
                            isSpeakerOn = true;
                        }
                    } else if (homeButton.isMouseOver(window)) {
                        // TODO: Reset everything before going back to main menu
                        gameState = GameState::MAIN_MENU;
                    } else if (gameState == GameState::MAIN_MENU) {
                        if (newGameButton.isMouseOver(window)) {
                            gameState = GameState::GAME_CONFIG;
                        } else if (tutorialButton.isMouseOver(window)) {
                            gameState = GameState::TUTORIAL;
                        }
                    } else if (gameState == GameState::TUTORIAL) {
                        if (tutorialBackButton.isMouseOver(window)) {
                            gameState = GameState::MAIN_MENU;
                        }
                    } else if (gameState == GameState::GAME_CONFIG) {
                        if (gameModeLeftButton.isMouseOver(
                                window)) {  // Change game mode
                            gameMode = (gameMode - 1 + 2) % 2;
                            gameModeSelect.setString(gameModeText[gameMode]);
                            horizontalCenterText(gameModeSelect, window);
                        } else if (gameModeRightButton.isMouseOver(
                                       window)) {  // Change game mode
                            gameMode = (gameMode + 1) % 2;
                            gameModeSelect.setString(gameModeText[gameMode]);
                            horizontalCenterText(gameModeSelect, window);
                        } else if (gamePlayerCountLeftButton.isMouseOver(
                                       window)) {  // Decrease player count
                            playerCount =
                                std::max(2, (playerCount - 2 - 1 + 7) % 7 + 2);
                            gamePlayerCountSelect.setString(
                                std::to_string(playerCount));
                            horizontalCenterText(gamePlayerCountSelect, window);
                        } else if (gamePlayerCountRightButton.isMouseOver(
                                       window)) {  // Increase player count
                            playerCount =
                                std::min(8, (playerCount - 2 + 1) % 7 + 2);
                            gamePlayerCountSelect.setString(
                                std::to_string(playerCount));
                            horizontalCenterText(gamePlayerCountSelect, window);
                        } else if (startGameButton.isMouseOver(window)) {
                            gameState = GameState::GAME;
                        }
                    } else if (gameState == GameState::GAME) {
                    }
                }
            }
        }

        // Clear the window
        window.clear(windowBackground);

        // Speaker button is always drawn
        speakerButton.draw(window);

        // Home button is always drawn except in the main menu
        if (gameState != GameState::MAIN_MENU) {
            homeButton.draw(window);
        }

        // Draw the appropriate game state
        if (gameState == GameState::MAIN_MENU) {
            // Draw the main menu
            window.draw(gameTitle);
            newGameButton.draw(window);
            tutorialButton.draw(window);
        } else if (gameState == GameState::GAME_CONFIG) {
            // Draw the game config menu
            window.draw(gameModeSelectLabel);
            window.draw(gameModeSelect);
            gameModeLeftButton.draw(window);
            gameModeRightButton.draw(window);

            window.draw(gamePlayerCountSelectLabel);
            window.draw(gamePlayerCountSelect);
            gamePlayerCountLeftButton.draw(window);
            gamePlayerCountRightButton.draw(window);

            startGameButton.draw(window);
        } else if (gameState == GameState::GAME) {
            // Draw the game
            for (int i = 0; i < playerCount; i++) {
                window.draw(playerSprites[i]);
            }
            foldButton.draw(window);
            callButton.draw(window);
            raiseButton.draw(window);
        } else if (gameState == GameState::TUTORIAL) {
            // Draw the tutorial
            window.draw(tutorialTitle);
            window.draw(tutorialText);
            tutorialBackButton.draw(window);
        }

        // Display the window
        window.display();
    }
    return 0;
}