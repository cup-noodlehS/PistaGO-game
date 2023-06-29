#include <SFML/Graphics.hpp>

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Individual Card Flip");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("public/aboutBackground.png"))
    {
        // Handle error if the image cannot be loaded
        return 1;
    }

    // Create a sprite for the background image
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Load card textures
    sf::Texture backTexture1;
    backTexture1.loadFromFile("public/developer.png");

    sf::Texture backTexture2;
    backTexture2.loadFromFile("public/developer.png");

    sf::Texture backTexture3;
    backTexture3.loadFromFile("public/developer.png");

    sf::Texture frontTexture1;
    frontTexture1.loadFromFile("public/creator4.png");

    sf::Texture frontTexture2;
    frontTexture2.loadFromFile("public/creator5.png");

    sf::Texture frontTexture3;
    frontTexture3.loadFromFile("public/creator6.png");

    // Create sprite objects for the cards
    sf::Sprite cardSprite1(backTexture1);
    sf::Sprite cardSprite2(backTexture2);
    sf::Sprite cardSprite3(backTexture3);

    // Set initial positions for the cards
    cardSprite1.setPosition(180.0f, 250.0f);
    cardSprite1.setScale(0.4f, 0.4f);
    cardSprite2.setPosition(730.0f, 250.0f);
    cardSprite2.setScale(0.4f, 0.4f);
    cardSprite3.setPosition(1280.0f, 250.0f);
    cardSprite3.setScale(0.4f, 0.4f);

    // Define variables
    bool isFlipping1 = false;
    bool isFlipping2 = false;
    bool isFlipping3 = false;
    bool isBack1 = true;
    bool isBack2 = true;
    bool isBack3 = true;

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Check if the click is within any card's bounds
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (cardSprite1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        isFlipping1 = true;
                        isBack1 = !isBack1;
                    }
                    else if (cardSprite2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        isFlipping2 = true;
                        isBack2 = !isBack2;
                    }
                    else if (cardSprite3.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        isFlipping3 = true;
                        isBack3 = !isBack3;
                    }
                }
            }
        }

        // Update
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Card 1
        if (cardSprite1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            cardSprite1.setScale(0.43f, 0.43f);
            if (isFlipping1)
            {
                if (isBack1)
                    cardSprite1.setTexture(frontTexture1);
                else
                    cardSprite1.setTexture(backTexture1);
                isFlipping1 = false;
            }
        }
        else
        {
            cardSprite1.setScale(0.4f, 0.4f);
        }

        // Card 2
        if (cardSprite2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            cardSprite2.setScale(0.43f, 0.43f);
            if (isFlipping2)
            {
                if (isBack2)
                    cardSprite2.setTexture(frontTexture2);
                else
                    cardSprite2.setTexture(backTexture2);
                isFlipping2 = false;
            }
        }
        else
        {
            cardSprite2.setScale(0.4f, 0.4f);
        }

        // Card 3
        if (cardSprite3.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            cardSprite3.setScale(0.43f, 0.43f);
            if (isFlipping3)
            {
                if (isBack3)
                    cardSprite3.setTexture(frontTexture3);
                else
                    cardSprite3.setTexture(backTexture3);
                isFlipping3 = false;
            }
        }
        else
        {
            cardSprite3.setScale(0.4f, 0.4f);
        }

        // Render
        window.clear();
        window.draw(backgroundSprite);
        window.draw(cardSprite1);
        window.draw(cardSprite2);
        window.draw(cardSprite3);
        window.display();
    }

    return 0;
}
