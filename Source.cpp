#include <SFML/Graphics.hpp>
#include <ctime>
#include<SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include "C:\Users\muhammadzuhair\source\repos\OOP_Project\OOP_Project\OOP_Project\Zombie1.h"

using namespace sf;
using namespace std;



struct coordinats {
	int x;
	int y;
};
VideoMode desktop = VideoMode::getDesktopMode(); //getting the desktop charectristics
unsigned int resolutionX = 1280;//desktop.width; //getting desktop width
unsigned int resolutionY = 720;// desktop.height; //getting desktop height



//Drawing the background
void createBack(RenderWindow& window) {
	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("C:/Users/muhammadzuhair/source/repos/OOP_Project/OOP_Project/Images/backwindow.png");
	backgroundSprite.setTexture(backgroundTexture);
	Vector2u backgroundSize = backgroundTexture.getSize();
	float backWidth = static_cast<float>(backgroundSize.x);
	float backHeight = static_cast<float>(backgroundSize.y);
	backgroundSprite.setTextureRect(IntRect(0, 0, backWidth, backHeight));
	float scaleX = static_cast<float>(resolutionX) / (backWidth - 370);
	float scaleY = static_cast<float>(resolutionY) / backHeight;//backHeight;
	backgroundSprite.setScale(scaleX, scaleY);
	backgroundSprite.setPosition(0, 0);
	//Drawing the background
	/*Image map_image;
	map_image.loadFromFile("Images/backwindow.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);*/
	window.draw(backgroundSprite);
}
void createPlant(RenderWindow& window, float xx, float yy, int rectX) {
	Texture plantTexture;
	Sprite plantSprite;
	plantTexture.loadFromFile("C:/Users/muhammadzuhair/source/repos/OOP_Project/OOP_Project/Images/peaShooter.png");
	plantSprite.setTexture(plantTexture);
	//Vector2u plantSize = plantTexture.getSize();
	float plantWidth = static_cast<float>(71);
	float plantHeight = static_cast<float>(71);
	plantSprite.setTextureRect(IntRect(rectX, 0, 71, 71));
	float scaleX = static_cast<float>(80) / plantWidth;
	float scaleY = static_cast<float>(100) / plantHeight;
	plantSprite.setScale(scaleX, scaleY);
	plantSprite.setPosition(xx, yy);
	window.draw(plantSprite);
}
void createPlant1(RenderWindow& window, float xx, float yy, int rectX) {
	Texture plantTexture;
	Sprite plantSprite;
	plantTexture.loadFromFile("C:/Users/muhammadzuhair/source/repos/OOP_Project/OOP_Project/Images/Peashooter_0.png");
	plantSprite.setTexture(plantTexture);
	//Vector2u plantSize = plantTexture.getSize();
	float plantWidth = static_cast<float>(71);
	float plantHeight = static_cast<float>(71);
	plantSprite.setTextureRect(IntRect(rectX, 0, 71, 71));
	float scaleX = static_cast<float>(100) / plantWidth;
	float scaleY = static_cast<float>(120) / plantHeight;
	plantSprite.setScale(scaleX, scaleY);
	plantSprite.setPosition(xx, yy);
	window.draw(plantSprite);
}


std::vector<sf::Vector2f> plantPositions;

void handleMouseClick(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Add the position of the click to the plantPositions vector
                plantPositions.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                std::cout << "Mouse clicked at: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
            }
        }
    }
}

//Drawing the map
void createMap(RenderWindow& window) {
	//Drawing a map
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("C:/Users/muhammadzuhair/source/repos/OOP_Project/OOP_Project/Images//grid.png");//load the file for the map
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(300, 160);

	window.draw(s_map);
}
//grid x start = 320;
//grid x end = 1220;
//grid y start = 100;
//grid y end = 600;
//block width = 100;
//block height = 120;

int main() {
    SimpleZombie* zombies[5] = { nullptr };

    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Plants Vs Zombies");

    const int ROWS = 5;
    const int COLS = 9;
    bool FIELD_GAME_STATUS[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            FIELD_GAME_STATUS[i][j] = true;
        }
    }

    sf::Clock timeMoney;
    sf::Clock clock;

    sf::View view(sf::FloatRect(0, 0, resolutionX, resolutionY));
    sf::Vector2f startVeiwPosition(370, 0);
    sf::Vector2f endVeiwPosition(0, 0);
    float duration = 5.0;
    float delayDuration = 20.0;
    float elapsed = 0.0;
    sf::Clock delayTimer;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        elapsed += deltaTime;
        float progress = std::min(elapsed / duration, 1.0f);
        sf::Vector2f currentPosition = startVeiwPosition + progress * (endVeiwPosition - startVeiwPosition);
        view.setCenter(currentPosition + sf::Vector2f(640, 360));
        window.setView(view);
        if (progress >= 1.0) {
            break;
        }

        window.clear();
        createBack(window);
        window.display();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        createBack(window);

        float pos_x = 0;
        float pos_y = 0;
        int rect_X = 0;
        handleMouseClick(window, pos_x, pos_y);

        if (pos_x != 0) {
            createPlant(window, pos_x, pos_y, rect_X);
            if (rect_X >= 852) {
                rect_X = 0;
            }
            else {
                rect_X += 71;
            }
        }

        if (delayTimer.getElapsedTime().asSeconds() >= delayDuration) {
            // Generate a random row for the zombie
            int randomRow = rand() % 5;
            float y = 70 + randomRow * 110;

            // Delete the existing zombie in the row, if any
            if (zombies[randomRow] != nullptr) {
                delete zombies[randomRow];
            }

            // Create a new zombie in the row
            zombies[randomRow] = new SimpleZombie(1220, y, 2, 1);
            std::cout << "Zombie " << randomRow + 1 << " generated at position: X = " << zombies[randomRow]->getPositionX() << ", Y = " << zombies[randomRow]->getPositionY() << std::endl;

            delayTimer.restart(); // Restart the delay timer for the next zombie
        }


        // Update and display each zombie
        for (int row = 0; row < 5; ++row) {
            if (zombies[row] != nullptr) {
                zombies[row]->move();
                zombies[row]->updateAnimation(); // Update the animation frame
                zombies[row]->display(window);
            }
        }

        // Display the window
        window.display();
    }

    // Delete the zombies
    for (int row = 0; row < 5; ++row) {
        if (zombies[row] != nullptr) {
            delete zombies[row];
            zombies[row] = nullptr;
        }
    }

    return 0;
}





