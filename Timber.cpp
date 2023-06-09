// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>



// BRANCHES position
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPosition[NUM_BRANCHES];





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

    // Time bar
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(1920 / 2.0f - timeBarStartWidth / 2.0f, 980);
    // Time bar time
    sf::Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Tracking if the game is running ot not
    bool paused = true;

    // Text for Heads Up Display (HUD)
    int score = 0;
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    // Create text objects
    sf::Text messageText;
    sf::Text scoreText;
    // Assign font object to text objects
    messageText.setFont(font);
    scoreText.setFont(font);
    //Assign acutal message to text objects:
    messageText.setString("Press Enter to Start!");
    scoreText.setString("Score = 0");
    //Set size of text
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    //Assign color to message
    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    //POSITION texts
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, 
        textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // Prepare 6 branches
    sf::Texture branchTexture;
    branchTexture.loadFromFile("Graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(branchTexture);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 40); //Set the origin at the center of the image
    }

    // Prepare the player
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // Players position
    side playerSide = side::LEFT;

    // Prepare gravestone
    sf::Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    sf::Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(2000, 860);

    // Prepare axe
    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // Axe lined up with tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Flying log, after having cut it
    sf::Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    sf::Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Control player input
    bool acceptInput = false;



    while (window.isOpen())
    {
        /*
        *********************************************
        Handle player's input
        *********************************************
        */

        sf::Event event; 
        
        while (window.pollEvent(event)) // Registers OS events and puts them into the event object
        {
            if (event.type == sf::Event::KeyReleased && !paused)
            {
                // Get inputs again
                acceptInput = true;
                // Hide the axe again
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            paused = false;
            score = 0;
            timeRemaining = 6;

            // Make all branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPosition[i] = side::NONE;
            }

            // Hid gravestone
            spriteLog.setPosition(5000, 5000);
            // Move player into position
            spritePlayer.setPosition(675, 660);
            spriteRIP.setPosition(2000, 660);
            acceptInput = true;

            
        }

        if (acceptInput) {
            //some shit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerSide = side::RIGHT;
                score++;
                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_RIGHT,
                    spriteAxe.getPosition().y);

                spritePlayer.setPosition(1200, 720);

                // Update branches
                updateBranches(score); // We use as seed of the function the current score

                // Set log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;

                acceptInput = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT,
                    spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                updateBranches(score);
                spriteLog.setPosition(580, 720);
                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;


            }
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

            // REsize time bar according to elapsed time
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining,
                timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                // Pause the game
                paused = true;
                //Change message shown to player
                messageText.setString("Out of time!");
                //Repositon text based on its new size
                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

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

            // Update score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            // Update the branches position
            for (int i = 0; i < NUM_BRANCHES; i++) {
                int height = i * 150;

                if (branchPosition[i] == side::LEFT)
                {
                    branches[i].setPosition(590, height);
                    branches[i].setRotation(180);
                }
                else if (branchPosition[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(-3000, -3000);
                }
            }

            if (logActive)
            {
                spriteLog.setPosition(logSpeedX* dt.asSeconds() + spriteLog.getPosition().x,
                    logSpeedY* dt.asSeconds() + spriteLog.getPosition().y);
                
                if (spriteLog.getPosition().x < -300 || spriteLog.getPosition().x > 2000)
                {
                    logActive = false;
                }



            }
            // Is the player on the same side of the last log?
            if (branchPosition[5] == playerSide)
            {
                // Player dies
                paused = true;
                acceptInput = false;

                spriteRIP.setPosition(525, 760);

                // Player hidden
                spritePlayer.setPosition(2000, 660);

                // Change text message
                messageText.setString("DEAD!");
                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
              
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
        // Draw branches
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        // Draw Tree
        window.draw(treeSprite);

        // Draw player
        window.draw(spritePlayer);

        // Axe
        window.draw(spriteAxe);

        // Flying log
        window.draw(spriteLog);

        // Gravestone
        window.draw(spriteRIP);

        // Draw bee
        window.draw(beeSprite);

        // Draw Text
        window.draw(scoreText);

        // Draw time bar
        window.draw(timeBar);

        if (paused)
        {
            window.draw(messageText);
        }

        //Show on screen what we draw
        window.display();
    }
    return 0;
}

void updateBranches(int seed)
{
    for (int i = NUM_BRANCHES-1; i > 0; i--)
    {
        branchPosition[i] = branchPosition[i - 1];
    }

    srand((int)time(0) + seed);
    int r = rand() % 5;
    
    switch (r) {
    case 0:
        branchPosition[0] = side::LEFT;
        break;
    case 1:
        branchPosition[0] = side::RIGHT;
        break;
    default:
        branchPosition[0] = side::NONE;
    }

}