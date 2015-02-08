#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window & initialise global settings
    sf::Vector2f screenSize(800,600);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "My window");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.setFramerateLimit(60);
   //window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    sf::Time elapsed;
    sf::Clock bulletClock;
    sf::Time bulletTime;

    //load the font & check error
    sf::Font font;
    if (!font.loadFromFile("terminat.ttf"))
    {
        std::cerr << "Oh shit, font file didn't load!" << std::endl;
    }
    //declare a text variable and set it's font, then initialise content, size, colour etc.
    sf::Text text;
    text.setFont(font);
    text.setString("Space Defilers");
    text.setCharacterSize(48);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    //initialise position of text
    sf::FloatRect textBoxSize = text.getGlobalBounds();
    text.setPosition((screenSize.x/2 - (textBoxSize.width/2)), 50);



    //define a sprite and texture.
    sf::Sprite playerSprite;
    sf::Texture texture;

    //load texture, check for errors.
    if (!texture.loadFromFile("sprite1.png", sf::IntRect(0, 0, 31, 19)))
    {
        std::cerr << "Error loading player texture" << std::endl;
    }
    //give the texture to the sprite and then move the sprite initial position.
    playerSprite.setTexture(texture);
    playerSprite.setOrigin(sf::Vector2f(15, 15));
    playerSprite.setPosition(sf::Vector2f(screenSize.x/2, screenSize.y*0.9));

    sf::Vector2f playerSpeed(0, 0);
    sf::Vector2f playerMovementSpeed(5,0);
    sf::Vector2f playerPos = playerSprite.getPosition();


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //check all keyboard inputs since last iteration
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            std::cout << "the escape key was pressed, exiting..." << std::endl;
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            std::cout << "left" << std::endl;
            playerSpeed.x = -playerMovementSpeed.x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            std::cout << "right" << std::endl;
            playerSpeed.x = playerMovementSpeed.x;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        /*do calculations here for
        all the text and sprites*/

        playerPos = playerSprite.getPosition();

        //stop player going out of bounds.
        if( playerPos.x > screenSize.x)
        {
            playerSprite.setPosition((screenSize.x - 100),playerPos.y);
        }
        else if (playerPos.x < 16)
        {
            playerSpeed.x=0;
        }
        playerSprite.setPosition((playerPos.x + playerSpeed.x), playerPos.y );//move the player
        playerSpeed.x = 0;//stop player moving until keyboard input confirmed on next loop.





        //draw text and sprites
        elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() < 3)
        {
            window.draw(text);
        }

        window.draw(playerSprite);

        // display the frame we just drew.
        window.display();
    }

    return 0;
}
