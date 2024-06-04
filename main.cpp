#include <SFML/Graphics.hpp>
#include "AreaShowText.h"
#include "InputArea.h"
#include <random>
#define POLE    10

void toFit_cellSize(const float& width_MainArea, const float& height_MainArea, float& cellSizeX, float& cellSizeY);

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Graph!");
    sf::Vector2i mousPosition = sf::Mouse::getPosition(window);

    RectangleShape backgraund;
    float x = window.getSize().x;
    float y = window.getSize().y;
    float cell_size = x*0.0156, 
        width_MainArea = x*2.5/12,
        height_MainArea = x * 2.5 / 12,
        AreaTextX_size = cell_size * 8,
        AreaTextY_size = cell_size * 3,
        Adjacency_coordX = x / 12,
        Adjacency_coordY = (y / 2) - cell_size * POLE / 2,
        Reachability_coordX = ((x * 11) / 12) - cell_size * POLE,
        Reachability_coordY = Adjacency_coordY,
        CountVertix_coordX = Adjacency_coordX+ AreaTextX_size/2,
        CountVertix_coordY = (y / 9) + (AreaTextY_size / 2),
        CountArrow_coordX = Adjacency_coordX * 5 + AreaTextX_size/2,
        CountArrow_coordY = CountVertix_coordY,
        Start_coordX = Adjacency_coordX*9+ AreaTextX_size/2,
        Start_coordY = CountArrow_coordY;

    backgraund.setSize(Vector2f(x, y));
    Texture texture;
    texture.loadFromFile("image/backgraund.jpg");
    backgraund.setTexture(&texture);

    Font font;
    if (!font.loadFromFile("font/ofont.ru_1 Shelley Volante.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    std::vector<std::vector<AreaShowText>> board_1(POLE, std::vector<AreaShowText>(POLE));
    std::vector<std::vector<AreaShowText>> board_2(POLE, std::vector<AreaShowText>(POLE));

    std::vector<std::vector<bool>> AdjacencyMatrix(POLE, std::vector<bool>(POLE));//матрица смежности
    AreaShowText cell;
    AreaShowText Start;

    InputArea CountVertix(Vector2f(AreaTextX_size, AreaTextY_size));
    CountVertix.setLength(2);
    CountVertix.setPosition(CountVertix_coordX, CountVertix_coordY);
    CountVertix.setAreaColor(Color(255, 225, 0));
    CountVertix.setOutlineThickness(AreaTextY_size * 0.1);
    CountVertix.setOutlineColor(Color(255, 200, 0));
    CountVertix.setFont(font);
    CountVertix.setTextColor(Color::Black);
    CountVertix.setString(std::to_string(POLE));

    InputArea CountArrow(Vector2f(AreaTextX_size, AreaTextY_size));
    CountArrow.setLength(2);
    CountArrow.setPosition(CountArrow_coordX, CountArrow_coordY);
    CountArrow.setAreaColor(Color(255, 225, 0));
    CountArrow.setOutlineThickness(AreaTextY_size * 0.1);
    CountArrow.setOutlineColor(Color(255, 200, 0));
    CountArrow.setFont(font);
    CountArrow.setTextColor(Color::Black);
    CountArrow.setString(std::to_string(0));

    Start.setCellSpecifications(Vector2f(AreaTextX_size, AreaTextY_size), Color(255, 248, 202),
        Vector2f(AreaTextX_size / 2, AreaTextY_size / 2), 3, Color::Black, Start_coordX,
        Start_coordY, true);
    Start.setFont(font);
    Start.setTextColor(Color::Black);
    Start.setString("<start>");

    // Генерация случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    for (int i = 0; i < POLE; i++) {
        for (int j = 0; j < POLE; j++) {
            cell.setCellSpecifications(Vector2f(cell_size, cell_size), Color(255, 248, 202),
                Vector2f(cell_size / 2, cell_size / 2), 3, Color::Black, i * cell_size + Adjacency_coordX,
                j * cell_size + Adjacency_coordY, true);
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
    std::vector<std::vector<bool>> ReachabilityMatrix = AdjacencyMatrix;//матрица достижимости

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ReachabilityMatrix[i][j] = ReachabilityMatrix[i][j] || (ReachabilityMatrix[i][k] && ReachabilityMatrix[k][j]);
            }
        }
    }

    for (int i = 0; i < POLE; i++) {
        for (int j = 0; j < POLE; j++) {
            cell.setCellSpecifications(Vector2f(cell_size, cell_size), Color(255, 248, 202),
                Vector2f(cell_size / 2, cell_size / 2), 3, Color::Black, i * cell_size + Reachability_coordX,
                j * cell_size + Adjacency_coordY, true);
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

            if (event.type == sf::Event::KeyPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (Start.MousePressedArea(mousPosition.x, mousPosition.y)) {
                        std::vector<std::vector<bool>> newAdjacencyMatrix;
                        // Очистка старого вектора
                        AdjacencyMatrix.clear();
                        AdjacencyMatrix.shrink_to_fit(); // Опционально, для деалокации памяти

                        AdjacencyMatrix = newAdjacencyMatrix;

                    }
                    if (CountVertix.MousePressedArea(mousPosition.x, mousPosition.y))
                    {
                        CountArrow.setCondition(false);
                        CountVertix.setCondition(true);
                    }
                    else if (CountArrow.MousePressedArea(mousPosition.x, mousPosition.y))
                    {
                        CountVertix.setCondition(false);
                        CountArrow.setCondition(true);
                    }
                    else
                    {
                        CountVertix.setCondition(false);
                        CountArrow.setCondition(false);
                    }
                }
            }
        }

        window.clear();
        window.draw(backgraund);
        for (int i = 0; i < POLE; i++) {
            for (int j = 0; j < POLE; j++) {
                board_1[i][j].draw(window);
                board_2[i][j].draw(window);
            }
        }
        CountVertix.draw(window);
        CountArrow.draw(window);
        Start.draw(window);

        window.display();
    }

    return 0;
}

void toFit_cellSize(const float& width_MainArea, const float& height_MainArea, float& cellSizeX, float& cellSizeY)
{
    if (cellSizeX > 20 && cellSizeY > 20 && (POLE * cellSizeY > height_MainArea || POLE * cellSizeX > width_MainArea))
    {
        cellSizeX -= 1;
        cellSizeY -= 1;
        toFit_cellSize(width_MainArea, height_MainArea, cellSizeX, cellSizeY);
    }
    else if (cellSizeX < 81 && cellSizeY < 81 && (POLE * cellSizeY < height_MainArea - 81 && POLE * cellSizeX < width_MainArea - 81))
    {
        cellSizeX += 1;
        cellSizeY += 1;
        toFit_cellSize(width_MainArea, height_MainArea, cellSizeX, cellSizeY);
    }
    return;
}