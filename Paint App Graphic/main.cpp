#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SIDEBAR_WIDTH = 100;

struct ToolButton {
    sf::RectangleShape shape;
    sf::Color color;
    std::string label;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simplified Paint");
    window.setFramerateLimit(60);

    sf::RenderTexture canvasTexture;
    canvasTexture.create(WINDOW_WIDTH - SIDEBAR_WIDTH, WINDOW_HEIGHT);
    canvasTexture.clear(sf::Color::White);

    sf::Sprite canvasSprite(canvasTexture.getTexture());
    canvasSprite.setPosition(SIDEBAR_WIDTH, 0);

    sf::Font emojiFont;
    emojiFont.loadFromFile("/System/Library/Fonts/Apple Color Emoji.ttc");

    std::vector<sf::Color> colors = {sf::Color::Black, sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
    std::vector<ToolButton> colorButtons;
    std::vector<ToolButton> toolButtons;

    int y_offset = 20;
    for (auto& col : colors) {
        ToolButton btn;
        btn.shape.setSize(sf::Vector2f(30, 30));
        btn.shape.setPosition(30, y_offset);
        btn.shape.setFillColor(col);
        btn.color = col;
        btn.label = "color";
        colorButtons.push_back(btn);
        y_offset += 50;
    }

    std::vector<std::pair<std::string, sf::Color>> toolbarItems = {
        {"🧽", sf::Color(200, 200, 200)},
        {"↩️", sf::Color(255, 255, 150)},
        {"↪️", sf::Color(150, 255, 255)}
    };

    for (const auto& item : toolbarItems) {
        ToolButton btn;
        btn.shape.setSize(sf::Vector2f(40, 40));
        btn.shape.setPosition(30, y_offset);
        btn.shape.setFillColor(item.second);
        btn.label = item.first;
        toolButtons.push_back(btn);
        y_offset += 50;
    }

    sf::Color brushColor = sf::Color::Black;
    bool isEraser = false;
    int brushSize = 4;
    std::stack<sf::Image> undoStack;
    std::stack<sf::Image> redoStack;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                for (auto& btn : colorButtons) {
                    if (btn.shape.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        brushColor = btn.color;
                        isEraser = false;
                    }
                }
                for (auto& btn : toolButtons) {
                    if (btn.shape.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        if (btn.label == "🧽") {
                            isEraser = true;
                        } else if (btn.label == "↩️") {
                            if (!undoStack.empty()) {
                                redoStack.push(canvasTexture.getTexture().copyToImage());
                                sf::Image img = undoStack.top(); undoStack.pop();
                                sf::Texture t; t.loadFromImage(img);
                                canvasTexture.clear(sf::Color::White);
                                canvasTexture.draw(sf::Sprite(t));
                            }
                        } else if (btn.label == "↪️") {
                            if (!redoStack.empty()) {
                                undoStack.push(canvasTexture.getTexture().copyToImage());
                                sf::Image img = redoStack.top(); redoStack.pop();
                                sf::Texture t; t.loadFromImage(img);
                                canvasTexture.clear(sf::Color::White);
                                canvasTexture.draw(sf::Sprite(t));
                            }
                        }
                    }
                }

                if (mouse.x > SIDEBAR_WIDTH) {
                    undoStack.push(canvasTexture.getTexture().copyToImage());
                    while (!redoStack.empty()) redoStack.pop();
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            if (mouse.x > SIDEBAR_WIDTH) {
                sf::CircleShape dot(brushSize);
                dot.setFillColor(isEraser ? sf::Color::White : brushColor);
                dot.setPosition(mouse.x - brushSize - SIDEBAR_WIDTH, mouse.y - brushSize);
                canvasTexture.draw(dot);
            }
        }

        canvasTexture.display();
        canvasSprite.setTexture(canvasTexture.getTexture());

        window.clear(sf::Color::White);

        for (auto& btn : colorButtons) window.draw(btn.shape);
        for (auto& btn : toolButtons) {
            window.draw(btn.shape);
            sf::Text label(btn.label, emojiFont, 18);
            label.setPosition(btn.shape.getPosition().x + 5, btn.shape.getPosition().y + 5);
            label.setFillColor(sf::Color::Black);
            window.draw(label);
        }

        window.draw(canvasSprite);
        window.display();
    }

    return 0;
}





/***
 #include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BRUSH_SIZE = 4;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graphical Paint");
    window.setFramerateLimit(60);

    // Create off-screen drawing surface
    sf::RenderTexture canvasTexture;
    if (!canvasTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Error: Failed to create canvas texture." << std::endl;
        return -1;
    }
    canvasTexture.clear(sf::Color::White);

    sf::Sprite canvasSprite(canvasTexture.getTexture());
    sf::Color brushColor = sf::Color::Black;
    bool isDrawing = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window
            if (event.type == sf::Event::Closed)
                window.close();

            // Save canvas to file
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                canvasTexture.display();  // Ensure latest drawing is applied
                sf::Image screenshot = canvasTexture.getTexture().copyToImage();

                std::string savePath = "canvas.png";  // Or set to full path for testing
                if (screenshot.saveToFile(savePath)) {
                    std::cout << "✅ Canvas saved to " << savePath << std::endl;
                } else {
                    std::cerr << "❌ Failed to save canvas!" << std::endl;
                }
            }

            // Mouse press starts drawing
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isDrawing = true;
            } else {
                isDrawing = false;
            }
        }

        if (isDrawing) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < WINDOW_WIDTH &&
                mousePos.y >= 0 && mousePos.y < WINDOW_HEIGHT) {
                sf::CircleShape dot(BRUSH_SIZE);
                dot.setFillColor(brushColor);
                dot.setPosition(mousePos.x - BRUSH_SIZE, mousePos.y - BRUSH_SIZE);
                canvasTexture.draw(dot);
            }
        }

        canvasTexture.display();

        window.clear(sf::Color::White);
        window.draw(canvasSprite);
        window.display();
    }

    return 0;
}
***/