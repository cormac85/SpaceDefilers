#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window & initialise global settings
    sf::Vector2f screenSize(800,600);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "My window");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.setFramerateLimit(120);
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

    // create  empty shapes
    sf::ConvexShape player;
    sf::ConvexShape bullet;
    sf::ConvexShape defiler;

    // resize it to required number of points
    player.setPointCount(8);
    bullet.setPointCount(4);
    defiler.setPointCount(6);

    // define the points & set color
    player.setPoint(0, sf::Vector2f(0, 30));
    player.setPoint(1, sf::Vector2f(15, 30));
    player.setPoint(2, sf::Vector2f(15, 20));
    player.setPoint(3, sf::Vector2f(35, 20));
    player.setPoint(4, sf::Vector2f(35, 30));
    player.setPoint(5, sf::Vector2f(50, 30));
    player.setPoint(6, sf::Vector2f(50, 50));
    player.setPoint(7, sf::Vector2f(0, 50));
    player.setFillColor(sf::Color(255, 255, 255));

    defiler.setPoint(0, sf::Vector2f(0, 15));
    defiler.setPoint(1, sf::Vector2f(15, 0));
    defiler.setPoint(2, sf::Vector2f(35, 0));
    defiler.setPoint(3, sf::Vector2f(50, 15));
    defiler.setPoint(4, sf::Vector2f(35, 30));
    defiler.setPoint(5, sf::Vector2f(15, 30));
    defiler.setFillColor(sf::Color(255, 255, 255));
    defiler.setOrigin(sf::Vector2f(25, 15));
    defiler.setPosition((screenSize.x * 0.5), screenSize.y * 0.25 );

    bullet.setPoint(0, sf::Vector2f(0, 0));
    bullet.setPoint(1, sf::Vector2f(10, 0));
    bullet.setPoint(2, sf::Vector2f(10, 20));
    bullet.setPoint(3, sf::Vector2f(0, 20));
    bullet.setFillColor(sf::Color(255, 255, 255));
    bullet.setOrigin(sf::Vector2f(5, 10));
    bool bulletExists = false;



    sf::FloatRect bulletBoxSize = bullet.getGlobalBounds();
    sf::FloatRect playerBoxSize = player.getGlobalBounds();
    sf::FloatRect defilerBoxSize = defiler.getGlobalBounds();


    //define a sprite and texture.
    sf::Sprite sprite;
    sf::Texture texture;

    //load texture, check for errors.
    if (!texture.loadFromFile("sprite1.png", sf::IntRect(0, 0, 32, 32)))
    {
        std::cerr << "Error";
    }
    //give the texture to the sprite and then move the sprite initial position.
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(16, 16));
    sprite.setPosition(sf::Vector2f(screenSize.x/2, screenSize.y*0.9));

    //move origin of player shape to its centre and initialise to bottom of screen with
    player.setOrigin( sf::Vector2f(25,25));
    player.setPosition(sf::Vector2f(screenSize.x/2, screenSize.y*0.9));

    sf::Vector2f playerSpeed(0, 0);
    sf::Vector2f playerPos = player.getPosition();


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
            playerSpeed.x = -3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            std::cout << "right" << std::endl;
            playerSpeed.x = 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (bulletExists == false) )
        {
            bulletExists = true;
            bullet.setPosition(sf::Vector2f(playerPos.x, (playerPos.y - 35)));
        }


        // clear the window with black color
        window.clear(sf::Color::Black);

        /*do calculations here for
        all the text and sprites*/

        playerPos = player.getPosition();

        //stop player going out of bounds.
        if( playerPos.x > screenSize.x - 16 )
        {
            player.setPosition((screenSize.x - 16),playerPos.y);
        }
        else if (playerPos.x < 16)
        {
            player.setPosition(16,playerPos.y);
        }
        player.setPosition((playerPos.x + playerSpeed.x), playerPos.y );//move the player
        playerSpeed.x = 0;//stop player moving until keyboard input confirmed on next loop.

        //move the bullet
        sf::Vector2f bulletPos = bullet.getPosition();
        bullet.setPosition(bulletPos.x, (bulletPos.y - 3));

        //check bullet is out of bounds and remove
        if (bulletPos.y > -20)
        {
            window.draw(bullet);
        }
        else if (bulletPos.y < -20)
        {
            bulletExists = false;
        }

        if (bullet.getGlobalBounds().intersects(defiler.getGlobalBounds()))
        {
            bulletExists = false;
            std::cout << "Collision!" << std::endl;
            bullet.setPosition(-100, -100);
            defiler.setPosition(-200, -200);

        }
        else
        {
            window.draw(defiler);
        }
        //draw text and sprites
        elapsed = clock.getElapsedTime();
        if( elapsed.asSeconds() < 3)
        {
            window.draw(text);
        }
        //switched to shape, not using sprite now.
        //window.draw(sprite);
        window.draw(player);


        // display the frame we just drew.
        window.display();
    }

    return 0;
}
