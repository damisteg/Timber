// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object
    sf::VideoMode vm(1920, 1080);

    // Create and open a window for the game
    sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    // Make background sprite
    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Make tree sprite
    sf::Texture treeTexture;
    treeTexture.loadFromFile("graphics/tree.png");
    sf::Sprite treeSprite;
    treeSprite.setTexture(treeTexture);
    treeSprite.setPosition(810, 0); // 1920/2 - 300/2 = 810

    // Make bee sprite
    sf::Texture beeTexture;
    beeTexture.loadFromFile("graphics/bee.png");
    sf::Sprite beeSprite;
    beeSprite.setTexture(beeTexture);
    beeSprite.setPosition(0, 800);
    // Does the bee move?
    bool beeActive = false;
    // Bee's velocity
    float beeSpeed = 0.0f;

    // Cloud sprites
    sf::Texture cloudTexture;
    cloudTexture.loadFromFile("graphics/cloud.png");
    sf::Sprite cloudSprite1;
    sf::Sprite cloudSprite2;
    sf::Sprite cloudSprite3;
    cloudSprite1.setTexture(cloudTexture);
    cloudSprite2.setTexture(cloudTexture);
    cloudSprite3.setTexture(cloudTexture);
    cloudSprite1.setPosition(0, 0);
    cloudSprite2.setPosition(0, 250);
    cloudSprite3.setPosition(0, 500);
    // Clouds moving or not
    bool cloudActive1 = false;
    bool cloudActive2 = false;
    bool cloudActive3 = false;
    // Clouds speed
    float cloudSpeed1 = 0.0f;
    float cloudSpeed2 = 0.0f;
    float cloudSpeed3 = 0.0f;

    // Clock
    sf::Clock clock;

    bool paused = true;



    while (window.isOpen())
    {
        /*
        *********************************************
        Handle player's input
        *********************************************
        */

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            paused = false;
        }

        /*
        *********************************************
        Update scene
        *********************************************
        */
        if (!paused)
        {
            // Measure time
            sf::Time dt = clock.restart();

            // Bee setup and drawing
            if (!beeActive)
            {
                // Bee speed
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                // Bee height
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                beeSprite.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                beeSprite.setPosition(beeSprite.getPosition().x
                    - (dt.asSeconds() * beeSpeed), beeSprite.getPosition().y);

                if (beeSprite.getPosition().x <= -100)
                {
                    beeActive = false;
                }
            }

            // Cloud 1 setup and drawing
            if (!cloudActive1)
            {
                // Cloud speed 
                srand((int)time(0) * 10);
                cloudSpeed1 = (rand() % 200) + 200;
                //Cloud position
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                cloudSprite1.setPosition(-200, height);
                cloudActive1 = true;
            }
            else
            {
                cloudSprite1.setPosition(cloudSprite1.getPosition().x +
                    dt.asSeconds() * cloudSpeed1, cloudSprite1.getPosition().y);
                if (cloudSprite1.getPosition().x > 1920)
                {
                    cloudActive1 = false;
                }

            }

            // Cloud 2 setup and drawing
            if (!cloudActive2)
            {
                // Cloud speed 
                srand((int)time(0) * 20);
                cloudSpeed2 = (rand() % 200) + 200;
                //Cloud position
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                cloudSprite2.setPosition(-200, height);
                cloudActive2 = true;
            }
            else
            {
                cloudSprite2.setPosition(cloudSprite2.getPosition().x +
                    dt.asSeconds() * cloudSpeed2, cloudSprite2.getPosition().y);
                if (cloudSprite2.getPosition().x > 1920)
                {
                    cloudActive2 = false;
                }

            }

            // Cloud 3 setup and drawing
            if (!cloudActive3)
            {
                // Cloud speed 
                srand((int)time(0) * 30);
                cloudSpeed3 = (rand() % 200) + 200;
                //Cloud position
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                cloudSprite3.setPosition(-200, height);
                cloudActive3 = true;
            }
            else
            {
                cloudSprite3.setPosition(cloudSprite3.getPosition().x +
                    dt.asSeconds() * cloudSpeed3, cloudSprite3.getPosition().y);
                if (cloudSprite3.getPosition().x > 1920)
                {
                    cloudActive3 = false;
                }

            }
        }
        /*
        *********************************************
        Draw scene
        *********************************************
        */

        //Clear everything from last frame
        window.clear();

        // Draw background
        window.draw(spriteBackground);
        // Draw clouds
        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);
        // Draw Tree
        window.draw(treeSprite);
        // Draw bee
        window.draw(beeSprite);

        //Show on screen what we draw
        window.display();
    }
    return 0;
}