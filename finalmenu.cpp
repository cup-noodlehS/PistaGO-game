#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class MenuState { Main, Play, About, Rules, Exit, Home };

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pista Go!", sf::Style::Fullscreen);

    sf::Texture menuBG, menuBG1, menuRS, playButton, rulesButton, aboutButton, logo, nextButton, prevButton, homeButton;
    sf::Texture rulePage1, rulePage2, rulePage3, rulePage4;

    if (!menuBG.loadFromFile("public/MAINBG.png") ||
        !menuBG1.loadFromFile("public/BG MENU 1.png") ||
        !menuRS.loadFromFile("public/BG MENU 2.png") ||
        !playButton.loadFromFile("public/BUTTON PLAY.png") ||
        !rulesButton.loadFromFile("public/BUTTON RULES.png") ||
        !aboutButton.loadFromFile("public/BUTTON ABOUT.png") ||
        !logo.loadFromFile("public/LOGO.png") ||
        !rulePage1.loadFromFile("public/RULE1.png") ||
        !rulePage2.loadFromFile("public/RULE2.png") ||
        !rulePage3.loadFromFile("public/RULE3.png") ||
        !rulePage4.loadFromFile("public/RULE4.png") ||
        !nextButton.loadFromFile("public/BUTTON NEXT.png") ||
        !prevButton.loadFromFile("public/BUTTON PREV.png") ||
        !homeButton.loadFromFile("public/BUTTON HOME.png")) {
        return EXIT_FAILURE;
    }

    float scaleButton = 0.43f;

    sf::Sprite menuBackground(menuBG), menuBackground1(menuBG1), menuRays(menuRS);
    menuBackground.setPosition(0, 0);
    menuRays.setOrigin(menuRays.getGlobalBounds().width / 2, menuRays.getGlobalBounds().height / 2);
    menuRays.setPosition(window.getSize().x / 2, window.getSize().y / 3 + 60);
    menuRays.setScale(.5f, .5f);

    sf::Sprite logoT(logo), playS(playButton), aboutS(aboutButton), rulesS(rulesButton);

    playS.setScale(scaleButton, scaleButton);
    aboutS.setScale(scaleButton, scaleButton);
    rulesS.setScale(scaleButton, scaleButton);
    logoT.setOrigin(logoT.getGlobalBounds().width / 2 , logoT.getGlobalBounds().height / 2 );

    float xCenterGame = window.getSize().x / 2;
    float buttonY = playS.getGlobalBounds().height;
    float spacingButton = 20.0f;

    logoT.setPosition(xCenterGame, 370);
    playS.setPosition(xCenterGame - playS.getGlobalBounds().width / 2.0f, 570 + buttonY + spacingButton);
    rulesS.setPosition(xCenterGame - rulesS.getGlobalBounds().width / 2.0f, playS.getPosition().y + buttonY + spacingButton);
    aboutS.setPosition(xCenterGame - aboutS.getGlobalBounds().width / 2.0f, rulesS.getPosition().y + buttonY + spacingButton);

    sf::Sprite ruleP1(rulePage1), ruleP2(rulePage2), ruleP3(rulePage3), ruleP4(rulePage4);
    ruleP1.setPosition(0, 0);
    ruleP2.setPosition(0, 0);
    ruleP3.setPosition(0, 0);
    ruleP4.setPosition(0, 0);

    sf::Sprite nextS(nextButton), prevS(prevButton), homeS(homeButton);
    nextS.setPosition(1840, 1030);
    nextS.setScale(.43f, .43f);
    prevS.setPosition(30, 1030);
    prevS.setScale(.43f, .43f);
    homeS.setPosition(1850, 48);
    homeS.setScale(0.35f, 0.35f);

    MenuState menuState = MenuState::Main;
    int currentPg = 1;

    float scaleLogo = 1.3f;
    float scaleDirection = 1.0f;
    float scaleSpeed = 0.3f;

    sf::Clock clockLogo;

    sf::Music menusfx;
    menusfx.openFromFile("public/mainmenu.wav");
    menusfx.setLoop(true);
    menusfx.setVolume(50);

    sf::SoundBuffer clickBuff;
    clickBuff.loadFromFile("public/button click.wav");
    sf::Sound clicksfx(clickBuff);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            
            if (event.type == sf::Event::MouseMoved) {
                if (menuState == MenuState::Main) {
                    if (playS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        playS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        playS.setColor(sf::Color::White);

                    if (aboutS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        aboutS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        aboutS.setColor(sf::Color::White);

                    if (rulesS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        rulesS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        rulesS.setColor(sf::Color::White);
                }

                if (menuState == MenuState::Rules) {
                    if (nextS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        nextS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        nextS.setColor(sf::Color::White);

                    if (prevS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        prevS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        prevS.setColor(sf::Color::White);

                    if (homeS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        homeS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        homeS.setColor(sf::Color::White);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    if (menuState == MenuState::Main) {
                        if (playS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            clicksfx.play();
                            menuState = MenuState::Play;

                        if (rulesS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            menuState = MenuState::Rules;
                            currentPg = 1;
                            clicksfx.play();
                        }

                        if (aboutS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            menuState = MenuState::About;
                            clicksfx.play();
                    }

                    if (menuState == MenuState::Rules) {
                        sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                        if (homeS.getGlobalBounds().contains(mousePosition))
                            menuState = MenuState::Home;
                            clicksfx.play();

                        if (currentPg < 4) {
                            if (nextS.getGlobalBounds().contains(mousePosition)) {
                                currentPg++;
                                clicksfx.play();
                            }
                        }

                        if (currentPg > 1) {
                            if (prevS.getGlobalBounds().contains(mousePosition)) {
                                currentPg--;
                                clicksfx.play();
                            }
                        }
                    }
                }
            }
        }

         // Update animation at a constant rate
        sf::Time deltaTime = clockLogo.restart();

        scaleLogo += scaleSpeed * scaleDirection * deltaTime.asSeconds();
        if (scaleLogo > 1.5f || scaleLogo < 1.3f)
        {
            scaleDirection *= -1.0f; 
        }

        menuRays.rotate(.08);
        window.clear();
        window.draw(menuBackground1);
        window.draw(menuRays);
        window.draw(menuBackground);
        logoT.setScale(scaleLogo, scaleLogo);
        window.draw(logoT);
        sf::sleep(sf::milliseconds(1.4));

        if(menusfx.getStatus() != sf::Music::Playing)
        {
            menusfx.play();
        }
        

        switch (menuState) {
            case MenuState::Main:
                window.draw(playS);
                window.draw(aboutS);
                window.draw(rulesS);
                
                break;

            case MenuState::About:
                // Draw the about screen
                break;

            case MenuState::Rules:
                switch (currentPg) {
                    case 1:
                        window.draw(ruleP1);
                        window.draw(nextS);
                        break;

                    case 2:
                        window.draw(ruleP2);
                        window.draw(nextS);
                        window.draw(prevS);
                        break;

                    case 3:
                        window.draw(ruleP3);
                        window.draw(nextS);
                        window.draw(prevS);
                        break;

                    case 4:
                        window.draw(ruleP4);
                        window.draw(prevS);
                        break;
                }
                window.draw(homeS);
                break;

            case MenuState::Exit:
                window.close();
                break;

            case MenuState::Home:
                menuState = MenuState::Main;
                break;
        }

        window.display();
    }

    menusfx.stop();
    return 0;
}
