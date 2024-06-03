#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "AreaShowText.h"
#include <random>
#define POLE    10

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Graph!");

    RectangleShape backgraund;
    float x = window.getSize().x;
    float y = window.getSize().y;
    backgraund.setSize(Vector2f(x, y));
    Texture texture;
    texture.loadFromFile("image/backgraund.jpg");
    backgraund.setTexture(&texture);

    std::vector<std::vector<AreaShowText>> board_1(POLE, std::vector<AreaShowText>(POLE));
    std::vector<std::vector<AreaShowText>> board_2(POLE, std::vector<AreaShowText>(POLE));

    std::vector<std::vector<bool>> AdjacencyMatrix(POLE, std::vector<bool>(POLE));//матрица смежноссти
    AreaShowText cell;

    Font font;
    if (!font.loadFromFile("font/ofont.ru_1 Shelley Volante.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Генерация случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    for (int i = 0; i < POLE; i++) {
        for (int j = 0; j < POLE; j++) {
            cell.setCellSpecifications(Vector2f(50, 50), Color::Blue, Vector2f(25, 25), 3, Color::Black, i * 50 + 100, j * 50 + 600, true);
            if (i == 0 || j == 0) {
                std::string s = (i == 0) ? std::to_string(j) : std::to_string(i);
                cell.setFont(font);
                cell.setTextColor(Color::Black);
                cell.setString(s);
            }
            else if (i > j) { // Заполняем поля выше главной диагонали случайными нулями и единицами
                cell.setFont(font);
                cell.setTextColor(Color::Black);
                //AdjacencyMatrix[i][j] = rand() % 2;
                AdjacencyMatrix[i][j] = dis(gen);
                std::string s = std::to_string(AdjacencyMatrix[i][j]);
                cell.setString(s);
            }
            if (i <= j && i != 0) {
                cell.setFont(font);
                cell.setTextColor(Color::Black);
                std::string s = std::to_string(AdjacencyMatrix[i][j] = 0);
                cell.setString(s);
            }
            board_1[i][j] = cell;
        }
    }

    int n = AdjacencyMatrix.size();
    std::vector<std::vector<bool>> ReachabilityMatrix = AdjacencyMatrix;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ReachabilityMatrix[i][j] = ReachabilityMatrix[i][j] || (ReachabilityMatrix[i][k] && ReachabilityMatrix[k][j]);
            }
        }
    }

    for (int i = 0; i < POLE; i++) {
        for (int j = 0; j < POLE; j++) {
            cell.setCellSpecifications(Vector2f(50, 50), Color::Blue, Vector2f(25, 25), 3, Color::Black, i * 50 + 2000, j * 50 + 600, true);
            if (i == 0 || j == 0) {
                std::string s = (i == 0) ? std::to_string(j) : std::to_string(i);
                cell.setFont(font);
                cell.setTextColor(Color::Black);
                cell.setString(s);
            }
            if (i != 0 && j != 0) {
                cell.setFont(font);
                cell.setTextColor(Color::Black);
                std::string s = std::to_string(ReachabilityMatrix[i][j]);
                cell.setString(s);
            }
            board_2[i][j] = cell;
        }
    }



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();
        window.draw(backgraund);
        for (int i = 0; i < POLE; i++) {
            for (int j = 0; j < POLE; j++) {
                board_1[i][j].draw(window);
                board_2[i][j].draw(window);
            }
        }
        window.display();
    }

    return 0;
}