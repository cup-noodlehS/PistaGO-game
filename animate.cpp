#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Card Flip Animation", sf::Style::Fullscreen);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("public/background.PNG"))
    {
        // Handle error if the image cannot be loaded
        return 1;
    }

    // Create a sprite for the background image
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the screen without stretching
    float scaleRatioX = static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width;
    float scaleRatioY = static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scaleRatioX, scaleRatioY);


    // Load card textures
    sf::Texture backTexture;
    backTexture.loadFromFile("public/backCard.png");

    sf::Texture frontTexture1;
    frontTexture1.loadFromFile("public/frontcard1.png");
    sf::Texture frontTexture2;
    frontTexture2.loadFromFile("public/frontcard2.png");
    sf::Texture frontTexture3;
    frontTexture3.loadFromFile("public/frontcard3.png");
    sf::Texture frontTexture4;
    frontTexture4.loadFromFile("public/frontcard4.png");

    // Create sprite objects
    sf::Sprite cardSprite1(backTexture);
    sf::Sprite cardSprite2(backTexture);
    sf::Sprite cardSprite3(backTexture);
    sf::Sprite cardSprite4(backTexture);

    // Set initial positions
    float cardWidth = 337.0f;
    float cardHeight = 472.0f;
    float spacing = 0.5f * 1920.0f / 96.0f; // 0.5 inch margin (assuming 96 pixels per inch)
    float startX = (1920.0f - 4.0f * cardWidth - 3.0f * spacing) / 2.0f;
    float startY = 1080.0f - cardHeight - spacing;

    cardSprite1.setPosition(startX + 30.0f, startY + 100.0f);
    cardSprite2.setPosition(startX + cardWidth + spacing + 120.0f, startY + 100.0f);
    cardSprite3.setPosition(startX + 2.0f * (cardWidth + spacing) + 210.0f, startY + 100.0f);
    cardSprite4.setPosition(startX + 3.0f * (cardWidth + spacing) + 300.0f, startY + 100.0f);

    // Define variables
    float currentAngle = 0.0f;
    float flipSpeed = 2.5f;
    float flipAngle = 180.0f;
    bool isFlipping = false;
    bool isBack = true;

    // Store original sizes
    sf::Vector2f backTextureSize(backTexture.getSize().x, backTexture.getSize().y);
    sf::Vector2f frontTextureSize1(frontTexture1.getSize().x, frontTexture1.getSize().y);
    sf::Vector2f frontTextureSize2(frontTexture2.getSize().x, frontTexture2.getSize().y);
    sf::Vector2f frontTextureSize3(frontTexture3.getSize().x, frontTexture3.getSize().y);
    sf::Vector2f frontTextureSize4(frontTexture4.getSize().x, frontTexture4.getSize().y);
    // Timer variables
    sf::Clock timer;
    float animationDelay = 0.0f; // Delay in seconds before the animation starts

    // Animation counter
    int animationCounter = 0;
    const int maxAnimationCount = 2;


    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if the animation delay has passed
        if (!isFlipping && timer.getElapsedTime().asSeconds() >= animationDelay)
        {
            isFlipping = true;
            currentAngle = 0.0f;
            if (isBack)
            {
                cardSprite1.setTexture(backTexture);
                cardSprite2.setTexture(backTexture);
                cardSprite3.setTexture(backTexture);
                cardSprite4.setTexture(backTexture);
                
            }
            else {
                cardSprite1.setTexture(frontTexture1);
                cardSprite2.setTexture(frontTexture2);
                cardSprite3.setTexture(frontTexture3);
                cardSprite4.setTexture(frontTexture4);
            }
            isBack = !isBack;
        }

        // Update
        if (isFlipping)
        {
            currentAngle += flipSpeed;
            if (currentAngle >= flipAngle)
            {
                isFlipping = false;
                currentAngle = flipAngle;
                if (isBack)
                {
                    cardSprite1.setTexture(frontTexture1);
                    cardSprite2.setTexture(frontTexture2);
                    cardSprite3.setTexture(frontTexture3);
                    cardSprite4.setTexture(frontTexture4);
                }
                else {
                    cardSprite1.setTexture(backTexture);
                    cardSprite2.setTexture(backTexture);
                    cardSprite3.setTexture(backTexture);
                    cardSprite4.setTexture(backTexture);
                }

                // Increment the animation counter
                animationCounter++;
                animationDelay = 2.0f;

                // Check if the maximum animation count has been reached
                if (animationCounter >= maxAnimationCount)
                {
                    isFlipping = true;
                }
            }
        }

        // Render
        window.clear();
        window.draw(backgroundSprite);
        if (isBack)
        {
            cardSprite1.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite2.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite3.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite4.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite1.setOrigin(backTextureSize.x * cardSprite1.getScale().x / 2.0f,
                backTextureSize.y * cardSprite1.getScale().y / 2.0f);
            cardSprite2.setOrigin(backTextureSize.x * cardSprite2.getScale().x / 2.0f,
                backTextureSize.y * cardSprite2.getScale().y / 2.0f);
            cardSprite3.setOrigin(backTextureSize.x * cardSprite3.getScale().x / 2.0f,
                backTextureSize.y * cardSprite3.getScale().y / 2.0f);
            cardSprite4.setOrigin(backTextureSize.x * cardSprite4.getScale().x / 2.0f,
                backTextureSize.y * cardSprite4.getScale().y / 2.0f);
        }
        else
        {
            cardSprite1.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite2.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite3.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite4.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
            cardSprite1.setOrigin(frontTextureSize1.x * cardSprite1.getScale().x / 2.0f,
                frontTextureSize1.y * cardSprite1.getScale().y / 2.0f);
            cardSprite2.setOrigin(frontTextureSize2.x * cardSprite2.getScale().x / 2.0f,
                frontTextureSize2.y * cardSprite2.getScale().y / 2.0f);
            cardSprite3.setOrigin(frontTextureSize3.x * cardSprite3.getScale().x / 2.0f,
                frontTextureSize3.y * cardSprite3.getScale().y / 2.0f);
            cardSprite4.setOrigin(frontTextureSize4.x * cardSprite4.getScale().x / 2.0f,
                frontTextureSize4.y * cardSprite4.getScale().y / 2.0f);
        }
        window.draw(cardSprite1);
        window.draw(cardSprite2);
        window.draw(cardSprite3);
        window.draw(cardSprite4);
        window.display();
    }

    return 0;
}
