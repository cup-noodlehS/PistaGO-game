#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "gameMechanics.h"
#include <cmath>
#include <fstream>

enum class MenuState { Main, Play, About, Rules, Rankings, Exit, Home };

int main()
{
    
    //setup
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pista GO", sf::Style::Fullscreen);
    sf::Vector2u windowSize = window.getSize();
    sf::Font font;
    if (!font.loadFromFile("public/fredokaBold.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
        return 1;
    }
    sf::Clock clock;
    sf::Time elapsedTime;
    // 

    //Main Menu
    sf::Texture menuBG, menuBG1, menuRS, playButton, rulesButton, 
    aboutButton, logo, nextButton, prevButton, homeButton, rankButton, 
        rankRS;
    sf::Texture rulePage1, rulePage2, rulePage3, rulePage4, aboutPage1, aboutPage;


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
        !homeButton.loadFromFile("public/BUTTON HOME.png") ||
        !rankButton.loadFromFile("public/BUTTON RANKING.png") ||
        !rankRS.loadFromFile("public/PLAYER RAYS.png") ||
        !aboutPage1.loadFromFile("public/ABOUT1.png") ||
        !aboutPage.loadFromFile("public/ABOUT2.png"))  {
        return EXIT_FAILURE;
    }

    float scaleButton = 0.43f;

    sf::Sprite menuBackground(menuBG), menuBackground1(menuBG1), menuRays(menuRS), rankRays(rankRS);
    menuBackground.setPosition(0, 0);
    menuRays.setOrigin(menuRays.getGlobalBounds().width / 2, menuRays.getGlobalBounds().height / 2);
    rankRays.setOrigin(rankRays.getGlobalBounds().width / 2, rankRays.getGlobalBounds().height / 2);    
    menuRays.setPosition(window.getSize().x / 2, window.getSize().y / 3 + 60);
    rankRays.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 60);
    rankRays.setScale(.5f,.5f);
    menuRays.setScale(.5f, .5f);

    sf::Sprite logoT(logo), playS(playButton), aboutS(aboutButton), rulesS(rulesButton), rankS(rankButton);

    playS.setScale(scaleButton, scaleButton);
    aboutS.setScale(scaleButton, scaleButton);
    rulesS.setScale(scaleButton, scaleButton);
    rankS.setScale(0.58f, 0.58f);
    logoT.setOrigin(logoT.getGlobalBounds().width / 2 , logoT.getGlobalBounds().height / 2 );

    float xCenterGame = window.getSize().x / 2;
    float buttonY = playS.getGlobalBounds().height;
    float spacingButton = 20.0f;

    logoT.setPosition(xCenterGame, 370);
    playS.setPosition(xCenterGame - playS.getGlobalBounds().width / 2.0f, 520 + buttonY + spacingButton);
    rulesS.setPosition(xCenterGame - rulesS.getGlobalBounds().width / 2.0f, playS.getPosition().y + buttonY + spacingButton);
    rankS.setPosition(xCenterGame - rankS.getGlobalBounds().width / 2.0f , rulesS.getPosition().y + buttonY + spacingButton);
    aboutS.setPosition(xCenterGame - aboutS.getGlobalBounds().width / 2.0f, rankS.getPosition().y + buttonY + spacingButton);


    //about
    sf::Texture backTexture1;
    backTexture1.loadFromFile("public/developer1.png");

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

    sf::Texture frontTexture4;
    frontTexture4.loadFromFile("public/creator7.png");

    sf::Texture frontTexture5;
    frontTexture5.loadFromFile("public/creator8.png");

    sf::Texture frontTexture6;
    frontTexture6.loadFromFile("public/creator9.png");

        // Create sprite objects for the cards
    sf::Sprite cardSprite1(backTexture1);
    sf::Sprite cardSprite2(backTexture2);
    sf::Sprite cardSprite3(backTexture3);
    sf::Sprite cardSprite4(backTexture3);
    sf::Sprite cardSprite5(backTexture3);
    sf::Sprite cardSprite6(backTexture3);

    // Set initial positions for the cards
    cardSprite1.setPosition(180.0f, 250.0f);
    cardSprite1.setScale(0.4f, 0.4f);
    cardSprite2.setPosition(730.0f, 250.0f);
    cardSprite2.setScale(0.4f, 0.4f);
    cardSprite3.setPosition(1280.0f, 250.0f);
    cardSprite3.setScale(0.4f, 0.4f);
    cardSprite4.setPosition(180.0f, 250.0f);
    cardSprite4.setScale(0.4f, 0.4f);
    cardSprite5.setPosition(730.0f, 250.0f);
    cardSprite5.setScale(0.4f, 0.4f);
    cardSprite6.setPosition(1280.0f, 250.0f);
    cardSprite6.setScale(0.4f, 0.4f);

    // Define variables
    bool isFlipping1 = false;
    bool isFlipping2 = false;
    bool isFlipping3 = false;
    bool isBack1 = true;
    bool isBack2 = true;
    bool isBack3 = true;
    std::string topname[5];
    std::string topscore[5];
    int getlinecount = 0;
    sf::Sprite ruleP1(rulePage1), ruleP2(rulePage2), ruleP3(rulePage3), ruleP4(rulePage4), 
        aboutP1(aboutPage1), aboutP2(aboutPage), aboutP3(aboutPage);


    sf::Sprite nextS(nextButton), prevS(prevButton), homeS(homeButton);
    nextS.setPosition(1840, 1030);
    nextS.setScale(.43f, .43f);
    prevS.setPosition(30, 1030);
    prevS.setScale(.43f, .43f);
    homeS.setPosition(1850, 48);
    homeS.setScale(0.35f, 0.35f);

    MenuState menuState = MenuState::Main;
    int currentPg = 1;
    int currentPge = 1;

    float scaleLogo = 0.8f;
    float scaleDirection = 1.0f;
    float scaleSpeed = 0.15f;

    sf::Clock clockLogo;

    sf::Music menusfx;
    menusfx.openFromFile("public/mainmenu.wav");
    menusfx.setLoop(true);
    menusfx.setVolume(50);

    sf::SoundBuffer clickBuff, pickBuff, flyBuff;
    clickBuff.loadFromFile("public/button click.wav");
    pickBuff.loadFromFile("public/sfx/pick card.wav");
    flyBuff.loadFromFile("public/sfx/fly sfx.wav");
    sf::Sound clicksfx(clickBuff), picksfx(pickBuff), flysfx(flyBuff);
    //

    // picksfx.play();
    // flysfx.play();

    //initializing images
    sf::Texture texture;
    if (!texture.loadFromFile("public/back.png"))
    {
        std::cout << "Failed to load image" << std::endl;
        return 1;
    }
    sf::Vector2u spriteSize = texture.getSize();
    //

    //Position of the hand cards

    float bottomRow = (windowSize.y / 5.0f) * 4.0f;
    float topRow = (windowSize.y / 5.0f) * 2.0f;

    float firstCol = (windowSize.x / 10.0f) * 0.95f;
    float secondCol = (windowSize.x / 10.0f) * 2.1f;
    float thirdCol = (windowSize.x / 10.0f) * 3.25f;
    float fourthCol = (windowSize.x / 10.0f) * 4.4f;
    float fifthCol = (windowSize.x / 10.0f) * 5.55f;
    float sixthCol = (windowSize.x / 10.0f) * 6.7f;
    float seventhCol = (windowSize.x / 10.0f) * 7.85f;
    float eighthCol = (windowSize.x / 10.0f) * 9.0f;
    // positions for cards in hand
    sf::Vector2f positionOne(firstCol, bottomRow);
    sf::Vector2f positionTwo(secondCol, bottomRow);
    sf::Vector2f positionThree(thirdCol, bottomRow);
    sf::Vector2f positionFour(fourthCol, bottomRow);
    sf::Vector2f positionFive(fifthCol, bottomRow);
    sf::Vector2f positionSix(sixthCol, bottomRow);
    sf::Vector2f positionSeven(seventhCol, bottomRow);
    sf::Vector2f positionEight(eighthCol, bottomRow);

    //positions of placed cards
    sf::Vector2f positionOneTop(firstCol, topRow);
    sf::Vector2f positionTwoTop(secondCol, topRow);
    sf::Vector2f positionThreeTop(thirdCol, topRow);
    sf::Vector2f positionFourTop(fourthCol, topRow);
    sf::Vector2f positionFiveTop(fifthCol, topRow);
    sf::Vector2f positionSixTop(sixthCol, topRow);
    sf::Vector2f positionSevenTop(seventhCol, topRow);
    sf::Vector2f positionEightTop(eighthCol, topRow);
    
    //position of opponents cards
    float op = (windowSize.y / 5.0f) * 1.95f;

    sf::Vector2f positionOneOp(firstCol, op);
    sf::Vector2f positionTwoOp(secondCol, op);
    sf::Vector2f positionThreeOp(thirdCol, op);
    sf::Vector2f positionFourOp(fourthCol, op);
    sf::Vector2f positionFiveOp(fifthCol, op);
    sf::Vector2f positionSixOp(sixthCol, op);
    sf::Vector2f positionSevenOp(seventhCol, op);
    sf::Vector2f positionEightOp(eighthCol, op);

    //position of show plced cards for all
    float firstRow = (windowSize.y / 5.0f) * 1.1f;
    float secondRow = (windowSize.y / 5.0f) * 2.2f;
    float thirdRow = (windowSize.y / 5.0f) * 3.3f;
    float fourthRow = (windowSize.y / 5.0f) * 4.4f;

    float firstColShow = (windowSize.x / 10.0f) * 1.4f;
    float secondColShow = (windowSize.x / 10.0f) * 2.3f;
    float thirdColShow = (windowSize.x / 10.0f) * 3.2f;
    float fourthColShow = (windowSize.x / 10.0f) * 4.1f;
    float fifthColShow = (windowSize.x / 10.0f) * 5.0f;
    float sixthColShow = (windowSize.x / 10.0f) * 5.9f;
    float seventhColShow = (windowSize.x / 10.0f) * 6.8f;
    float eighthColShow = (windowSize.x / 10.0f) * 7.7f;

    sf::Vector2f positionOneOne(firstColShow, firstRow);
    sf::Vector2f positionOneTwo(secondColShow, firstRow);
    sf::Vector2f positionOneThree(thirdColShow, firstRow);
    sf::Vector2f positionOneFour(fourthColShow, firstRow);
    sf::Vector2f positionOneFive(fifthColShow, firstRow);
    sf::Vector2f positionOneSix(sixthColShow, firstRow);
    sf::Vector2f positionOneSeven(seventhColShow, firstRow);
    sf::Vector2f positionOneEight(eighthColShow, firstRow);

    sf::Vector2f positionTwoOne(firstColShow, secondRow);
    sf::Vector2f positionTwoTwo(secondColShow, secondRow);
    sf::Vector2f positionTwoThree(thirdColShow, secondRow);
    sf::Vector2f positionTwoFour(fourthColShow, secondRow);
    sf::Vector2f positionTwoFive(fifthColShow, secondRow);
    sf::Vector2f positionTwoSix(sixthColShow, secondRow);
    sf::Vector2f positionTwoSeven(seventhColShow, secondRow);
    sf::Vector2f positionTwoEight(eighthColShow, secondRow);

    sf::Vector2f positionThreeOne(firstColShow, thirdRow);
    sf::Vector2f positionThreeTwo(secondColShow, thirdRow);
    sf::Vector2f positionThreeThree(thirdColShow, thirdRow);
    sf::Vector2f positionThreeFour(fourthColShow, thirdRow);
    sf::Vector2f positionThreeFive(fifthColShow, thirdRow);
    sf::Vector2f positionThreeSix(sixthColShow, thirdRow);
    sf::Vector2f positionThreeSeven(seventhColShow, thirdRow);
    sf::Vector2f positionThreeEight(eighthColShow, thirdRow);
  
    sf::Vector2f positionFourOne(firstColShow, fourthRow);
    sf::Vector2f positionFourTwo(secondColShow, fourthRow);
    sf::Vector2f positionFourThree(thirdColShow, fourthRow);
    sf::Vector2f positionFourFour(fourthColShow, fourthRow);
    sf::Vector2f positionFourFive(fifthColShow, fourthRow);
    sf::Vector2f positionFourSix(sixthColShow, fourthRow);
    sf::Vector2f positionFourSeven(seventhColShow, fourthRow);
    sf::Vector2f positionFourEight(eighthColShow, fourthRow);



    // Assigning the positions to the cards
    sf::Vector2f cardScale(0.95f, 0.95f);
    
    //cards in hand
    sf::Sprite sprite1(texture);
    sprite1.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite1.setPosition(positionOne);
    sprite1.setScale(cardScale);

    sf::Sprite sprite2(texture);
    sprite2.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite2.setPosition(positionTwo);
    sprite2.setScale(cardScale);


    sf::Sprite sprite3(texture);
    sprite3.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite3.setPosition(positionThree);
    sprite3.setScale(cardScale);

    sf::Sprite sprite4(texture);
    sprite4.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite4.setPosition(positionFour);
    sprite4.setScale(cardScale);

    sf::Sprite sprite5(texture);
    sprite5.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite5.setPosition(positionFive);
    sprite5.setScale(cardScale);

    sf::Sprite sprite6(texture);
    sprite6.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite6.setPosition(positionSix);
    sprite6.setScale(cardScale);

    sf::Sprite sprite7(texture);
    sprite7.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite7.setPosition(positionSeven);
    sprite7.setScale(cardScale);

    sf::Sprite sprite8(texture);
    sprite8.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    sprite8.setPosition(positionEight);
    sprite8.setScale(cardScale);
    //

    //cards placed
    sf::Sprite coke1(texture);
    coke1.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke1.setPosition(positionOneTop);
    coke1.setScale(cardScale);

    sf::Sprite coke2(texture);
    coke2.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke2.setPosition(positionTwoTop);
    coke2.setScale(cardScale);

    sf::Sprite coke3(texture);
    coke3.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke3.setPosition(positionThreeTop);
    coke3.setScale(cardScale);

    sf::Sprite coke4(texture);
    coke4.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke4.setPosition(positionFourTop);
    coke4.setScale(cardScale);

    sf::Sprite coke5(texture);
    coke5.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke5.setPosition(positionFiveTop);
    coke5.setScale(cardScale);

    sf::Sprite coke6(texture);
    coke6.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke6.setPosition(positionSixTop);
    coke6.setScale(cardScale);

    sf::Sprite coke7(texture);
    coke7.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke7.setPosition(positionSevenTop);
    coke7.setScale(cardScale);

    sf::Sprite coke8(texture);
    coke8.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    coke8.setPosition(positionEightTop);
    coke8.setScale(cardScale);
    //

    //opponents cards
    sf::Sprite opSprite1(texture);
    opSprite1.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite1.setPosition(positionOneOp);
    opSprite1.setScale(cardScale);

    sf::Sprite opSprite2(texture);
    opSprite2.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite2.setPosition(positionTwoOp);
    opSprite2.setScale(cardScale);

    sf::Sprite opSprite3(texture);
    opSprite3.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite3.setPosition(positionThreeOp);
    opSprite3.setScale(cardScale);

    sf::Sprite opSprite4(texture);
    opSprite4.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite4.setPosition(positionFourOp);
    opSprite4.setScale(cardScale);

    sf::Sprite opSprite5(texture);
    opSprite5.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite5.setPosition(positionFiveOp);
    opSprite5.setScale(cardScale);

    sf::Sprite opSprite6(texture);
    opSprite6.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite6.setPosition(positionSixOp);
    opSprite6.setScale(cardScale);

    sf::Sprite opSprite7(texture);
    opSprite7.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite7.setPosition(positionSevenOp);
    opSprite7.setScale(cardScale);

    sf::Sprite opSprite8(texture);
    opSprite8.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    opSprite8.setPosition(positionEightOp);
    opSprite8.setScale(cardScale);


    //

    //show player cards
    // sf::Vector2f showCardScale(0.7f, 0.7f);

    // sf::Sprite royal11(texture);
    // royal11.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal11.setPosition(positionOneOne);
    // royal11.setScale(showCardScale);

    // sf::Sprite royal12(texture);
    // royal12.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal12.setPosition(positionOneTwo);
    // royal12.setScale(showCardScale);

    // sf::Sprite royal13(texture);
    // royal13.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal13.setPosition(positionOneThree);
    // royal13.setScale(showCardScale);    

    // sf::Sprite royal14(texture);
    // royal14.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal14.setPosition(positionOneFour);
    // royal14.setScale(showCardScale);

    // sf::Sprite royal15(texture);
    // royal15.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal15.setPosition(positionOneFive);
    // royal15.setScale(showCardScale);

    // sf::Sprite royal16(texture);
    // royal16.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal16.setPosition(positionOneSix);
    // royal16.setScale(showCardScale);

    // sf::Sprite royal17(texture);
    // royal17.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal17.setPosition(positionOneSeven);
    // royal17.setScale(showCardScale);

    // sf::Sprite royal18(texture);
    // royal18.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal18.setPosition(positionOneEight);
    // royal18.setScale(showCardScale);

    // sf::Sprite royal21(texture);
    // royal21.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal21.setPosition(positionTwoOne);
    // royal21.setScale(showCardScale);

    // sf::Sprite royal22(texture);
    // royal22.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal22.setPosition(positionTwoTwo);
    // royal22.setScale(showCardScale);

    // sf::Sprite royal23(texture);
    // royal23.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal23.setPosition(positionTwoThree);
    // royal23.setScale(showCardScale);

    // sf::Sprite royal24(texture);
    // royal24.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal24.setPosition(positionTwoFour);
    // royal24.setScale(showCardScale);

    // sf::Sprite royal25(texture);
    // royal25.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal25.setPosition(positionTwoFive);
    // royal25.setScale(showCardScale);

    // sf::Sprite royal26(texture);
    // royal26.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal26.setPosition(positionTwoSix);
    // royal26.setScale(showCardScale);

    // sf::Sprite royal27(texture);
    // royal27.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal27.setPosition(positionTwoSeven);
    // royal27.setScale(showCardScale);

    // sf::Sprite royal28(texture);
    // royal28.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal28.setPosition(positionTwoEight);
    // royal28.setScale(showCardScale);

    // sf::Sprite royal31(texture);
    // royal31.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal31.setPosition(positionThreeOne);
    // royal31.setScale(showCardScale);

    // sf::Sprite royal32(texture);
    // royal32.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal32.setPosition(positionThreeTwo);
    // royal32.setScale(showCardScale);

    // sf::Sprite royal33(texture);
    // royal33.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal33.setPosition(positionThreeThree);
    // royal33.setScale(showCardScale);

    // sf::Sprite royal34(texture);
    // royal34.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal34.setPosition(positionThreeFour);
    // royal34.setScale(showCardScale);

    // sf::Sprite royal35(texture);
    // royal35.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal35.setPosition(positionThreeFive);
    // royal35.setScale(showCardScale);

    // sf::Sprite royal36(texture);
    // royal36.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal36.setPosition(positionThreeSix);
    // royal36.setScale(showCardScale);

    // sf::Sprite royal37(texture);
    // royal37.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal37.setPosition(positionThreeSeven);
    // royal37.setScale(showCardScale);

    // sf::Sprite royal38(texture);
    // royal38.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal38.setPosition(positionThreeEight);
    // royal38.setScale(showCardScale);

    // sf::Sprite royal41(texture);
    // royal41.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal41.setPosition(positionFourOne);
    // royal41.setScale(showCardScale);

    // sf::Sprite royal42(texture);
    // royal42.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal42.setPosition(positionFourTwo);
    // royal42.setScale(showCardScale);

    // sf::Sprite royal43(texture);
    // royal43.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal43.setPosition(positionFourThree);
    // royal43.setScale(showCardScale);

    // sf::Sprite royal44(texture);
    // royal44.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal44.setPosition(positionFourFour);
    // royal44.setScale(showCardScale);

    // sf::Sprite royal45(texture);
    // royal45.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal45.setPosition(positionFourFive);
    // royal45.setScale(showCardScale);

    // sf::Sprite royal46(texture);
    // royal46.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal46.setPosition(positionFourSix);
    // royal46.setScale(showCardScale);

    // sf::Sprite royal47(texture);
    // royal47.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal47.setPosition(positionFourSeven);
    // royal47.setScale(showCardScale);

    // sf::Sprite royal48(texture);
    // royal48.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    // royal48.setPosition(positionFourEight);
    // royal48.setScale(showCardScale);
    //

    sf::Texture iconTexture;
    iconTexture.loadFromFile("public/icons/p1.png");

    sf::Sprite icon1(iconTexture);
    icon1.setOrigin(iconTexture.getSize().x / 2.0f, iconTexture.getSize().y / 2.0f);
    icon1.setPosition(windowSize.x / 2.0f - (iconTexture.getSize().x + 50), windowSize.y / 2.0f);

    sf::Sprite icon2(iconTexture);
    icon2.setOrigin(iconTexture.getSize().x / 2.0f, iconTexture.getSize().y / 2.0f);
    icon2.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    sf::Sprite icon3(iconTexture);
    icon3.setOrigin(iconTexture.getSize().x / 2.0f, iconTexture.getSize().y / 2.0f);
    icon3.setPosition(windowSize.x / 2.0f + (iconTexture.getSize().x + 50), windowSize.y / 2.0f);
    //

    //langaw bg
    sf::Texture bgLangawTex;
    bgLangawTex.loadFromFile("public/bgLangaw.png");

    sf::Sprite bgLangaw(bgLangawTex);
    //

    //plyer turn text
    sf::Text headerText("", font, 60);
    headerText.setFillColor(sf::Color::Black);
    //
    sf::Font nameFont;
    nameFont.loadFromFile("public/Fredoka-VariableFont_wdth,wght.ttf");
    sf::Text test("thisis20charactersss",font,50);
    sf::FloatRect textboxesbounds = test.getLocalBounds();
    //Textbox1
    Textbox textbox1( 55, sf::Color::Black, false);
    textbox1.setFont(nameFont);
    sf::FloatRect textbox1bounds = textbox1.getBounds();
    textbox1.setOrigin(sf::Vector2f(22.5, 58));
    textbox1.setPosition(sf::Vector2f((textboxesbounds.left + textboxesbounds.width + 245.0f)/1.4f, windowSize.y / 3.5 - 37.5f));
    textbox1.setLimit(true, 20);
    //invisible bound
    sf::RectangleShape rectangletext1(sf::Vector2f(920,100));
    rectangletext1.setFillColor(sf::Color::Transparent);
    rectangletext1.setOrigin(22.5, 58);
    rectangletext1.setPosition(532.143, 260.071);
    //Textbox2
    Textbox textbox2( 55, sf::Color::Black, false);
    textbox2.setFont(nameFont);
    sf::FloatRect textbox2bounds = textbox2.getBounds();
    textbox2.setOrigin(sf::Vector2f(22.5, 58));
    textbox2.setPosition(sf::Vector2f(532.143, 475.071));
    textbox2.setLimit(true, 20);
    //invisible bound
    sf::RectangleShape rectangletext2(sf::Vector2f(920,100));
    rectangletext2.setFillColor(sf::Color::Transparent);
    rectangletext2.setOrigin(22.5, 58);
    rectangletext2.setPosition(532.143, 460.071);
    //Textbox2
    Textbox textbox3( 55, sf::Color::Black, false);
    textbox3.setFont(nameFont);
    sf::FloatRect textbox3bounds = textbox3.getBounds();
    textbox3.setOrigin(sf::Vector2f(22.5, 58));
    textbox3.setPosition(sf::Vector2f(532.143, 680.071));
    textbox3.setLimit(true, 20);
    //invisible bound
    sf::RectangleShape rectangletext3(sf::Vector2f(920,100));
    rectangletext3.setFillColor(sf::Color::Transparent);
    rectangletext3.setOrigin(22.5, 58);
    rectangletext3.setPosition(532.143, 671.071);
    //Textbox2
    Textbox textbox4( 55, sf::Color::Black, false);
    textbox4.setFont(nameFont);
    sf::FloatRect textbox4bounds = textbox4.getBounds();
    textbox4.setOrigin(sf::Vector2f(22.5, 58));
    textbox4.setPosition(sf::Vector2f(532.143, 880.071));
    textbox4.setLimit(true, 20);
    //invisible bound
    sf::RectangleShape rectangletext4(sf::Vector2f(920,100));
    rectangletext4.setFillColor(sf::Color::Transparent);
    rectangletext4.setOrigin(22.5, 58);
    rectangletext4.setPosition(532.143, 871.071);
    

    //graphics
    sf::Texture Playerinfo,Playerbg,playerrays,Startbut;
    Playerinfo.loadFromFile("public/2.png");
    Playerbg.loadFromFile("public/1.png");
    playerrays.loadFromFile("public/PLAYER RAYS.png");
    Startbut.loadFromFile("public/BUTTON START.png");
    sf::Sprite playerinfobg(Playerinfo),Playerbgsprite(Playerbg), PlayerraysSprite(playerrays),StartbutSprite(Startbut);
    playerinfobg.setPosition(0,0);
    PlayerraysSprite.setOrigin(PlayerraysSprite.getGlobalBounds().width / 2, PlayerraysSprite.getGlobalBounds().height/2);
    PlayerraysSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 60);
    PlayerraysSprite.setScale(.5f,.5f);
    sf::FloatRect originbutton = StartbutSprite.getLocalBounds();
    StartbutSprite.setOrigin(originbutton.left + originbutton.width/2,originbutton.top + originbutton.height/2);
    StartbutSprite.setPosition(window.getSize().x/2,window.getSize().y/2 + 450);
    StartbutSprite.setScale(0.53f,0.53f);

    //ShowcardAnimationjourdan
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("public/background.PNG"))
    {
        // Handle error if the image cannot be loaded
        return 1;
    }

    sf::Texture frontTextureshow1;
    sf::Texture frontTextureshow2;
    sf::Texture frontTextureshow3;
    sf::Texture frontTextureshow4;
    // Create a sprite for the background image
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the screen without stretching
    float scaleRatioX = static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width;
    float scaleRatioY = static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scaleRatioX, scaleRatioY);

    sf::Texture backTexture;
    backTexture.loadFromFile("public/switchCards/backCard.png");

    sf::Sprite cardSpriteshow1(backTexture);
    sf::Sprite cardSpriteshow2(backTexture);
    sf::Sprite cardSpriteshow3(backTexture);
    sf::Sprite cardSpriteshow4(backTexture);

    // Set initial positions
    float cardWidth = 337.0f;
    float cardHeight = 472.0f;
    float spacing = 0.5f * 1920.0f / 96.0f; // 0.5 inch margin (assuming 96 pixels per inch)
    float startX = (1920.0f - 4.0f * cardWidth - 3.0f * spacing) / 2.0f;
    float startY = 1080.0f - cardHeight - spacing;

    cardSpriteshow1.setPosition(startX + 30.0f, startY + 100.0f);
    cardSpriteshow2.setPosition(startX + cardWidth + spacing + 120.0f, startY + 100.0f);
    cardSpriteshow3.setPosition(startX + 2.0f * (cardWidth + spacing) + 210.0f, startY + 100.0f);
    cardSpriteshow4.setPosition(startX + 3.0f * (cardWidth + spacing) + 300.0f, startY + 100.0f);

    // Define variables
    float currentAngle = 0.0f;
    float flipSpeed = 2.0f;
    float flipAngle = 180.0f;
    bool isFlipping = false;
    bool isBack = true;

    // Store original sizes
    sf::Vector2f backTextureSize(backTexture.getSize().x, backTexture.getSize().y);
    sf::Vector2f frontTextureSize1(frontTextureshow1.getSize().x, frontTextureshow1.getSize().y);
    sf::Vector2f frontTextureSize2(frontTextureshow2.getSize().x, frontTextureshow2.getSize().y);
    sf::Vector2f frontTextureSize3(frontTextureshow3.getSize().x, frontTextureshow3.getSize().y);
    sf::Vector2f frontTextureSize4(frontTextureshow4.getSize().x, frontTextureshow4.getSize().y);
    // Timer variables
    sf::Clock timer;
    float animationDelay = 0.0f; // Delay in seconds before the animation starts

    // Animation counter
    int animationCounter1 = 0;
    int maxAnimationCount1 = 2;
    
    sf::Texture homeBtn;
    homeBtn.loadFromFile("public/homeBtn.png");
    sf::Sprite homeSprite(homeBtn);
    homeSprite.setOrigin(homeSprite.getGlobalBounds().width / 2.0f, homeSprite.getGlobalBounds().height / 2.0f);
    homeSprite.setPosition(windowSize.x / 2.0f, 1045);
    homeSprite.setScale(0.6f , 0.6f);

    sf::Texture rankingBox;
    rankingBox.loadFromFile("public/rankings.png");
    sf::Sprite rankingSprite(rankingBox);

    sf::Text top1("asdfklj - 59", font, 45);
    sf::Text top2("asdfklj - 59", font, 45);
    sf::Text top3("asdfklj - 59", font, 45);
    sf::Text top4("asdfklj - 59", font, 45);
    sf::Text top5("asdfklj - 59", font, 45);
    sf::FloatRect textBounds;


    //initalizing
    int points[4];//players points each round
    int totalPoints[4];
    std::string deck[104];//deck of cards
    std::string playerCards[4][8];//cards for each player
    std::string placedCards[4][8];//cards used by the players
    int eventDay[3];

    
    //variables
    int cardNum = 8;
    std::string day[3] = {"Fair Day", "Rainy Day", "Sunny Day"};
    int index[4];
    int numOfCards[4];
    int chosenIndex;
    int chosenPlayer = -1;
    int langawIndex = -1;
    std::string eventBg[] = {"fair.png", "rainy.png", "sunny.png"};
    float frame = 0;
    int playerChoices[3];
    std::string playerNames[4];
    std::string showPicCards[4];
    int roundPoints[3][4];
    sf::Time deltaTime;
    
    //bools
    bool gameProperBool = false;//if game proper
    bool iChange = true;//determines if the round changes
    bool chosenIndexBool = false;//if an index is chosen
    bool useLangaw = false;//if a langaw card is used
    bool switchFrame = false;//switch cards scene
    bool playerHandBool = true;//shows players hand
    bool isFullscreen = true;
    bool roundScoreBool = false;
    bool fading = false;//basta hehe
    bool mainmenu = true;
    bool show = true;//for testing rani
    bool nameInput = false;
    bool scoreOpen = false;

    //start game
    int i = 0;//round
    int t = 0;//turns
    int j = 0;//player

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(gameProperBool){
                if(event.type == sf::Event::MouseButtonPressed){
                    if(!iChange && !switchFrame){
                        if(event.mouseButton.button == sf::Mouse::Left){
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                            if(useLangaw){
                                if(chosenPlayer == -1){
                                    if(icon1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                        chosenPlayer = playerChoices[0];
                                        std::cout<<chosenPlayer + 1;
                                    }else if(icon2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                        chosenPlayer = playerChoices[1];
                                        std::cout<<chosenPlayer + 1;
                                    } else if(icon3.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                        chosenPlayer = playerChoices[2];
                                        std::cout<<chosenPlayer + 1;
                                    }
                                    std::cout<<">>"<<numOfCards[chosenPlayer]<<"<< ";

                                }else{
                                    if(opSprite1.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 0){
                                        langawIndex = 0;
                                        std::cout<<0;
                                    }else if(opSprite2.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 1){
                                        langawIndex = 1;
                                        std::cout<<1;
                                    }else if(opSprite3.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 2){
                                        langawIndex = 2;
                                        std::cout<<2;
                                    }else if(opSprite4.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 3){
                                        langawIndex = 3;
                                        std::cout<<3;
                                    }else if(opSprite5.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 4){
                                        langawIndex = 4;
                                        std::cout<<4;
                                    }else if(opSprite6.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 5){
                                        langawIndex = 5;
                                        std::cout<<5;
                                    }else if(opSprite7.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 6){
                                        langawIndex = 6;
                                        std::cout<<6;
                                    }else if(opSprite8.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && numOfCards[chosenPlayer] > 7){
                                        langawIndex = 7;
                                        std::cout<<7;
                                    }
                                }

                            }else if(i == 3){
                                if(homeSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    std::vector<ScoreEntry> scores;
                                    std::cout<<"1"<<std::endl;
                                    for(int k = 0; k < 4; k++){
                                        ScoreEntry entry;
                                        std::cout<<"2"<<std::endl;
                                        entry.name = playerNames[k];
                                        std::cout<<"3"<<std::endl;
                                        entry.score = totalPoints[k];
                                        std::cout<<"4"<<std::endl;
                                        scores.push_back(entry);
                                        std::cout<<"5"<<std::endl;
                                    }
                                    std::sort(scores.begin(), scores.end(), compareScoreEntries);
                                    std::cout<<"sorted"<<std::endl;
                                    compareAndReplaceScores("top_scores_record.txt", scores);
                                    std::cout<<"replaced"<<std::endl;
                                    gameProperBool = false;
                                    roundScoreBool = false;
                                    mainmenu = true;
                                    std::cout<<"back to main menu"<<std::endl;
                                }
                            }
                            else{
                                //placing card
                                bool change = false;
                                if(sprite1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 0;
                                    change = true;
                                }else if(sprite2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 1;
                                    change = true;
                                }else if(sprite3.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 2;
                                    change = true;
                                }else if(sprite4.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 3;
                                    change = true;
                                }else if(sprite5.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 4;
                                    change = true;
                                }else if(sprite6.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 5;
                                    change = true;
                                }else if(sprite7.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 6;
                                    change = true;
                                }else if(sprite8.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    chosenIndex = 7;
                                    change = true;
                                }

                                if(change){
                                    if(playerCards[index[j]][chosenIndex] == "langaw"){
                                        if(t != 0){
                                            int x = 0;
                                            for(int k = 0; k < 4; k++){
                                                if(k != j){
                                                    playerChoices[x] = k;
                                                    x++;
                                                }
                                            }
                                            useLangaw = true;
                                        }else{
                                            //display cannot use that
                                            continue;
                                        }
                                    }else{
                                        chosenIndexBool = true;
                                    }
                                }
                                

                                std::cout<<chosenIndex;
                            }
                        }
                    }else{
                        if(event.mouseButton.button == sf::Mouse::Left){
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                            if(i == 3){
                                if(homeSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                    std::vector<ScoreEntry> scores;
                                    for(int k = 0; k < 4; k++){
                                        ScoreEntry entry;
                                        entry.name = playerNames[k];
                                        entry.score = totalPoints[k];
                                        scores.push_back(entry);
                                        std::cout<<entry.name<<"-"<<entry.score<<std::endl;
                                    }
                                    std::sort(scores.begin(), scores.end(), compareScoreEntries);
                                    std::cout<<"sorted"<<std::endl;
                                    compareAndReplaceScores("top_scores_record.txt", scores);
                                    gameProperBool = false;
                                    roundScoreBool = false;
                                    MenuState menuState = MenuState::Main;
                                    scaleLogo = 0.8f;
                                    deltaTime = clockLogo.restart();
                                    mainmenu = true;
                                    
                                }
                            }
                        }
                    }
                }
            }
            else if (nameInput){

                if(event.type == sf::Event::TextEntered){
                    textbox1.typedOn(event);
                    textbox2.typedOn(event);
                    textbox3.typedOn(event);
                    textbox4.typedOn(event);
                }
                else if(event.type == sf::Event::MouseMoved){
                    if(StartbutSprite.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y))
                            StartbutSprite.setColor(sf::Color(255,255,255,128));
                        else
                            StartbutSprite.setColor(sf::Color::White);       
                }
                else if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(StartbutSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            clicksfx.play();
                            playerNames[0] = textbox1.getText();
                            playerNames[1] = textbox2.getText();
                            playerNames[2] = textbox3.getText();
                            playerNames[3] = textbox4.getText();



                            //reset variables
                            i = 0;
                            t = 0;
                            j = 0;
                            initializeDeck(deck);//deck initalize
                            shuffle(deck); //shuffle deck
                            randevent(eventDay);//randomize event each round (normal, rainy day, sunnyday)
                            placeLangaw(deck, eventDay);//distributing langaws in each deck
                            //

                            for(int k = 0; k < 4; k++){
                                totalPoints[k] = 0;
                                showPicCards[k] = "";
                            }

                            for(int k = 0; k < 3; k++){
                                for(int q = 0; q < 4; q++){
                                    roundPoints[k][q] = 0;
                                }
                            }
                            
                            nameInput = false;
                            gameProperBool = true;
                            menusfx.stop();
                        }

                    }
                }
            }
            else if(mainmenu){
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
                        
                        if (rankS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        rankS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        rankS.setColor(sf::Color::White);

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

                    if (menuState == MenuState::About) {
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

                    if (menuState == MenuState::Rankings) {
                    if (homeS.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        homeS.setColor(sf::Color(255, 255, 255, 128));
                    else
                        homeS.setColor(sf::Color::White);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        
                        if (menuState == MenuState::Main) {
                            if (playS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                clicksfx.play();
                                mainmenu = false;
                                nameInput = true;
                            }
                            if (rulesS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                menuState = MenuState::Rules;
                                currentPg = 1;
                                clicksfx.play();
                            }

                            if (rankS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                menuState = MenuState::Rankings;
                                std::ifstream file("top_scores_record.txt");
                                if(file.is_open()){
                                    std::string line;
                                    std::cout<<"1"<<std::endl;
                                    while (std::getline(file,line) && getlinecount<= 4){
                                        size_t colonPos = line.find(':');
                                        std::cout<<"2"<<std::endl;
                                        topname[getlinecount] = line.substr(0,colonPos);
                                        std::cout<<"3"<<std::endl;
                                        topscore[getlinecount] = line.substr(colonPos + 2);
                                        std::cout<<"4"<<std::endl;
                                        std::cout<<topname[getlinecount]<<"-"<<topscore[getlinecount]<<std::endl;
                                        getlinecount++;
                                        std::cout<<"15"<<std::endl;
                                    }
                                    file.close();
                                    std::cout<<"file is closed"<<std::endl;
                                }else{
                                        std::cout<<"unable to open";
                                }
                                for(int k = 0; k<5; k++){
                                    std::cout<<topname[k]<<"-"<<topscore[k]<<std::endl;
                                }
                                clicksfx.play();
                                getlinecount = 0;
                                                           
                        }

                            if (aboutS.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                menuState = MenuState::About;
                                clicksfx.play();
                                currentPge = 1;
                            }
                        }

                        if (menuState == MenuState::Rules) {
                            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                            if (homeS.getGlobalBounds().contains(mousePosition)){
                                menuState = MenuState::Home;
                                clicksfx.play();
                            }
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

                        if (menuState == MenuState::Rankings) {
                            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                            if (homeS.getGlobalBounds().contains(mousePosition)){
                                menuState = MenuState::Home;
                                clicksfx.play();
                            }
                        }

                        if (menuState == MenuState::About) {
                            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                            if (homeS.getGlobalBounds().contains(mousePosition)){
                                menuState = MenuState::Home;
                                clicksfx.play();
                            }
                            if (currentPge < 3) {
                                if (nextS.getGlobalBounds().contains(mousePosition)) {
                                    currentPge++;
                                    clicksfx.play();
                                }
                            }

                            if (currentPge > 1) {
                                if (prevS.getGlobalBounds().contains(mousePosition)) {
                                    currentPge--;
                                    clicksfx.play();
                                }
                            }

                            if (currentPge!=1)
                            {
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
                }
            }
        }
        window.clear(sf::Color::White);
        
        
        if(menusfx.getStatus() != sf::Music::Playing)
                    {
                        menusfx.play();
                    }
            

        if(mainmenu){

            window.clear(sf::Color::Red);
            deltaTime = clockLogo.restart();
            scaleLogo += scaleSpeed * scaleDirection * deltaTime.asSeconds();
                    if (scaleLogo > 1.3f || scaleLogo < 0.8f)
                    {
                        scaleDirection *= -1.0f; 
                    }

            switch (menuState) {
                case MenuState::Main:{
                    
                    menuRays.rotate(.08);
                    logoT.setScale(scaleLogo, scaleLogo);
                    window.draw(menuBackground1);
                    window.draw(menuRays);
                    window.draw(menuBackground);
                    sf::sleep(sf::milliseconds(1.4));
                    window.draw(logoT);
                    window.draw(playS);
                    window.draw(aboutS);
                    window.draw(rankS);
                    window.draw(rulesS);
                    
                    break;}

                case MenuState::About:
                switch (currentPge) {
                        

                        case 1:
                            cardSprite1.setTexture(backTexture1);
                            cardSprite2.setTexture(backTexture2);
                            cardSprite3.setTexture(backTexture2);
                            cardSprite4.setTexture(backTexture2);
                            cardSprite5.setTexture(backTexture2);
                            cardSprite6.setTexture(backTexture2);
                            window.draw(aboutP1);
                            window.draw(nextS);
                            break;

                        case 2:{
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
                            

                            window.draw(aboutP2);
                            window.draw(nextS);
                            window.draw(prevS);
                            window.draw(cardSprite1);
                            window.draw(cardSprite2);
                            window.draw(cardSprite3);
                            break;}

                        case 3:{
                            
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                            
                            // Card 1
                            if (cardSprite4.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                            {
                                cardSprite4.setScale(0.43f, 0.43f);
                                if (isFlipping1)
                                {
                                    if (isBack1)
                                        cardSprite4.setTexture(frontTexture4);
                                    else
                                        cardSprite4.setTexture(backTexture3);
                                    isFlipping1 = false;
                                }
                            }
                            else
                            {
                                cardSprite4.setScale(0.4f, 0.4f);
                            }

                            // Card 2
                            if (cardSprite5.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                            {
                                cardSprite5.setScale(0.43f, 0.43f);
                                if (isFlipping2)
                                {
                                    if (isBack2)
                                        cardSprite5.setTexture(frontTexture5);
                                    else
                                        cardSprite5.setTexture(backTexture2);
                                    isFlipping2 = false;
                                }
                            }
                            else
                            {
                                cardSprite5.setScale(0.4f, 0.4f);
                            }

                            // Card 3
                            if (cardSprite6.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                            {
                                cardSprite6.setScale(0.43f, 0.43f);
                                if (isFlipping3)
                                {
                                    if (isBack3)
                                        cardSprite6.setTexture(frontTexture6);
                                    else
                                        cardSprite6.setTexture(backTexture3);
                                    isFlipping3 = false;
                                }
                            }
                            else
                            {
                                cardSprite6.setScale(0.4f, 0.4f);
                            }
                            
                            window.draw(aboutP3);
                            window.draw(prevS);
                            window.draw(cardSprite4);
                            window.draw(cardSprite5);
                            window.draw(cardSprite6);
                            break;
                        }

                    }
                    window.draw(homeS);
                    break;                    break;

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
                
                case MenuState::Rankings:
                    rankRays.rotate(0.03f);
                    window.clear(sf::Color(253,227,169));
                    window.draw(rankRays);
                    window.draw(homeS);
                    window.draw(rankingSprite);
                    
                    top1.setString(topname[0] + " - " + topscore[0]);
                    textBounds = top1.getLocalBounds();
                    top1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    top1.setPosition(windowSize.x / 2.0f, 275);
                    top1.setFillColor(sf::Color::Black);
                    window.draw(top1);

                    top2.setString(topname[1] + " - " + topscore[1]);
                    textBounds = top2.getLocalBounds();
                    top2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    top2.setPosition(windowSize.x / 2.0f, 430);
                    top2.setFillColor(sf::Color::Black);
                    window.draw(top2);

                    top3.setString(topname[2] + " - " + topscore[2]);
                    textBounds = top3.getLocalBounds();
                    top3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    top3.setPosition(windowSize.x / 2.0f, 585);
                    top3.setFillColor(sf::Color::Black);
                    window.draw(top3);

                    
                    top4.setString(topname[3] + " - " + topscore[3]);
                    textBounds = top4.getLocalBounds();
                    top4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    top4.setPosition(windowSize.x / 2.0f, 740);
                    top4.setFillColor(sf::Color::Black);
                    window.draw(top4);

                    top5.setString(topname[4] + " - " + topscore[4]);
                    textBounds = top5.getLocalBounds();
                    top5.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    top5.setPosition(windowSize.x / 2.0f, 895);
                    top5.setFillColor(sf::Color::Black);
                    window.draw(top5);
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

        if(nameInput){
            //textbox1 position and borderz
            
            PlayerraysSprite.rotate(.03);
            window.draw(Playerbgsprite);
            window.draw(PlayerraysSprite);
            window.draw(playerinfobg);
            window.draw(rectangletext1);
            window.draw(rectangletext2);
            window.draw(rectangletext3);
            window.draw(rectangletext4);
            textbox1.drawTo(window);
            textbox1.handleEvent(event, window, rectangletext1);
            textbox2.drawTo(window);
            textbox2.handleEvent(event, window, rectangletext2);
            textbox3.drawTo(window);
            textbox3.handleEvent(event, window, rectangletext3);
            textbox4.drawTo(window);
            textbox4.handleEvent(event, window, rectangletext4);
            if(textbox1.getLength() >= 2 && textbox2.getLength() >= 2 && textbox3.getLength() >= 2 && textbox4.getLength() >= 2)
                window.draw(StartbutSprite);
            window.display();
            continue;
        }


        //game proper
        if(gameProperBool){
            //last turn
            if(t==7){
                for(int k = 0; k < 4; k++){
                    if(playerCards[index[j]][0] != "langaw"){
                        placedCards[j][numOfCards[j]] = playerCards[index[j]][0];
                        numOfCards[j]++;
                    }
                }
                calcScoreSingle(placedCards, points, numOfCards);
                calcScoreAll(placedCards, points, numOfCards);
                for(int k = 0; k < 4; k++){
                    totalPoints[k] += points[k];
                    roundPoints[i][k] = points[k];
                }

                t = 0;
                j = 0;
                i++;
                roundScoreBool = true;
                iChange = true;
                clock.restart();
            }

            if(scoreOpen){
                sf::Texture bgScore;
                bgScore.loadFromFile("public/scores/bg.png");
                sf::Sprite scoreSprite(bgScore);
                window.draw(scoreSprite);
                sf::Texture frame;
                frame.loadFromFile("public/scores/scoreBoard.png");
                sf::Sprite frameSprite(frame);
                window.draw(frameSprite);
                
                //total score
                sf::Text total1(std::to_string(totalPoints[0]), font, 30);
                sf::FloatRect textBounds = total1.getLocalBounds();
                total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 370);
                total1.setFillColor(sf::Color::Black); 
                window.draw(total1);

                sf::Text total2(std::to_string(totalPoints[1]), font, 30);
                textBounds = total2.getLocalBounds();
                total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 370);
                total2.setFillColor(sf::Color::Black); 
                window.draw(total2);

                sf::Text total3(std::to_string(totalPoints[2]), font, 30);
                textBounds = total3.getLocalBounds();
                total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 370);
                total3.setFillColor(sf::Color::Black); 
                window.draw(total3);

                sf::Text total4(std::to_string(totalPoints[3]), font, 30);
                textBounds = total4.getLocalBounds();
                total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 370);
                total4.setFillColor(sf::Color::Black); 
                window.draw(total4);
                
                
                //
                if(i >= 1){
                    sf::Text total1(std::to_string(roundPoints[0][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) - 10);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[0][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) - 10);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[0][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) - 10);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[0][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) - 10);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                    }
                if(i >= 2){
                    sf::Text total1(std::to_string(roundPoints[1][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 115);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[1][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 115);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[1][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 115);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[1][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 115);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                    
                }
                if(i==3){
                    sf::Text total1(std::to_string(roundPoints[2][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 230);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[2][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 230);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[2][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 230);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[2][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 230);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                }

                window.display();
                continue;
            } 

            //show score after round
            if(roundScoreBool){
                elapsedTime = clock.getElapsedTime();
                if(i != 3){
                    if(elapsedTime.asSeconds() > 5.0f){
                        roundScoreBool = false;
                        clock.restart();
                    }
                }
                   
                sf::Texture bgScore;
                bgScore.loadFromFile("public/scores/bg.png");
                sf::Sprite scoreSprite(bgScore);
                window.draw(scoreSprite);
                sf::Texture frame;
                frame.loadFromFile("public/scores/scoreBoard.png");
                sf::Sprite frameSprite(frame);
                window.draw(frameSprite);
                
                //total score
                sf::Text total1(std::to_string(totalPoints[0]), font, 30);
                sf::FloatRect textBounds = total1.getLocalBounds();
                total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 370);
                total1.setFillColor(sf::Color::Black); 
                window.draw(total1);

                sf::Text total2(std::to_string(totalPoints[1]), font, 30);
                textBounds = total2.getLocalBounds();
                total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 370);
                total2.setFillColor(sf::Color::Black); 
                window.draw(total2);

                sf::Text total3(std::to_string(totalPoints[2]), font, 30);
                textBounds = total3.getLocalBounds();
                total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 370);
                total3.setFillColor(sf::Color::Black); 
                window.draw(total3);

                sf::Text total4(std::to_string(totalPoints[3]), font, 30);
                textBounds = total4.getLocalBounds();
                total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 370);
                total4.setFillColor(sf::Color::Black); 
                window.draw(total4);
                
                
                //
                if(i >= 1){
                    sf::Text total1(std::to_string(roundPoints[0][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) - 10);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[0][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) - 10);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[0][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) - 10);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[0][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) - 10);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                    }
                if(i >= 2){
                    sf::Text total1(std::to_string(roundPoints[1][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 115);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[1][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 115);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[1][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 115);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[1][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 115);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                    
                }
                if(i==3){
                    sf::Text total1(std::to_string(roundPoints[2][0]), font, 30);
                    textBounds = total1.getLocalBounds();
                    total1.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total1.setPosition((windowSize.x / 2)-525, (windowSize.y / 2) + 230);
                    total1.setFillColor(sf::Color::Black); 
                    window.draw(total1);

                    sf::Text total2(std::to_string(roundPoints[2][1]), font, 30);
                    textBounds = total2.getLocalBounds();
                    total2.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total2.setPosition((windowSize.x / 2)-180, (windowSize.y / 2) + 230);
                    total2.setFillColor(sf::Color::Black); 
                    window.draw(total2);

                    sf::Text total3(std::to_string(roundPoints[2][2]), font, 30);
                    textBounds = total3.getLocalBounds();
                    total3.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total3.setPosition((windowSize.x / 2)+185, (windowSize.y / 2) + 230);
                    total3.setFillColor(sf::Color::Black); 
                    window.draw(total3);

                    sf::Text total4(std::to_string(roundPoints[2][3]), font, 30);
                    textBounds = total4.getLocalBounds();
                    total4.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    total4.setPosition((windowSize.x / 2)+530, (windowSize.y / 2) + 230);
                    total4.setFillColor(sf::Color::Black); 
                    window.draw(total4);
                    window.draw(homeSprite);
                }

                window.display();
                continue;
            }            

            //if round changed
            if(iChange){
                if(eventDay[i] == 2){
                    if(frame <= 75){
                        sf::Texture eventTexture;
                        eventTexture.loadFromFile("public/sunny/SUNNY" + std::to_string((int)frame) + ".png");
                        sf::Sprite eventSprite(eventTexture);
                        
                        window.draw(eventSprite);
                        window.display();
                        frame += 0.75;
                        continue;
                    }else{
                        for(int k = 0; k < 4; k++){
                            points[k] = 0;
                        }
                        iChange = false;
                        switchFrame = false;
                        fading = true;
                        clock.restart();
                        distribute(deck, playerCards, i);//distribute the cards
                        for(int k = 0; k < 4; k++){
                            index[k] = k;
                            numOfCards[k] = 0;
                        }
                    }

                }else if(eventDay[i] == 1){
                    if(frame <= 69){
                        sf::Texture eventTexture;
                        eventTexture.loadFromFile("public/rainy/RAINY" + std::to_string((int)frame) + ".png");
                        sf::Sprite eventSprite(eventTexture);
                        
                        window.draw(eventSprite);
                        window.display();
                        frame += 0.75;
                        continue;
                    }else{
                        for(int k = 0; k < 4; k++){
                            points[k] = 0;
                        }
                        iChange = false;
                        switchFrame = false;
                        fading = true;
                        clock.restart();
                        distribute(deck, playerCards, i);//distribute the cards
                        for(int k = 0; k < 4; k++){
                            index[k] = k;
                            numOfCards[k] = 0;
                        }
                    }
                }else{
                    if(frame <= 65){
                        sf::Texture eventTexture;
                        eventTexture.loadFromFile("public/cloudy/CLOUDY" + std::to_string((int)frame) + ".png");
                        sf::Sprite eventSprite(eventTexture);
                        
                        window.draw(eventSprite);
                        window.display();
                        frame += 0.75;
                        continue;
                    }else{
                        for(int k = 0; k < 4; k++){
                            points[k] = 0;
                        }
                        iChange = false;
                        switchFrame = false;
                        fading = true;
                        clock.restart();
                        distribute(deck, playerCards, i);//distribute the cards
                        for(int k = 0; k < 4; k++){
                            index[k] = k;
                            numOfCards[k] = 0;
                        }
                    }
                }
                

            }

            if(switchFrame && !useLangaw){
                //jourdan
                elapsedTime = clock.getElapsedTime();
                if(elapsedTime.asSeconds() < 5.0f){
                    if(showPicCards[0] != ""){
                        frontTextureshow1.loadFromFile("public/switchCards/"+showPicCards[0]+".png");
                    }else{
                        frontTextureshow1.loadFromFile("public/switchCards/langaw.png");
                    }
                    if(showPicCards[1] != ""){
                        frontTextureshow2.loadFromFile("public/switchCards/"+showPicCards[1]+".png");
                    }else{
                        frontTextureshow2.loadFromFile("public/switchCards/langaw.png");
                    }
                    if(showPicCards[2] != ""){
                     frontTextureshow3.loadFromFile("public/switchCards/"+showPicCards[2]+".png");
                    }else{
                        frontTextureshow3.loadFromFile("public/switchCards/langaw.png");
                    }
                    if(showPicCards[3] != ""){
                     frontTextureshow4.loadFromFile("public/switchCards/"+showPicCards[3]+".png");
                    }else{
                        frontTextureshow4.loadFromFile("public/switchCards/langaw.png");
                    }

                    //animation
                    if (!isFlipping && timer.getElapsedTime().asSeconds() >= animationDelay)
                    {
                        isFlipping = true;
                        currentAngle = 0.0f;
                        if (isBack)
                        {
                            cardSpriteshow1.setTexture(backTexture);
                            cardSpriteshow2.setTexture(backTexture);
                            cardSpriteshow3.setTexture(backTexture);
                            cardSpriteshow4.setTexture(backTexture);
                            
                        }
                        else {
                            cardSpriteshow1.setTexture(frontTextureshow1);
                            cardSpriteshow2.setTexture(frontTextureshow2);
                            cardSpriteshow3.setTexture(frontTextureshow3);
                            cardSpriteshow4.setTexture(frontTextureshow4);
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
                                cardSpriteshow1.setTexture(frontTextureshow1);
                                cardSpriteshow2.setTexture(frontTextureshow2);
                                cardSpriteshow3.setTexture(frontTextureshow3);
                                cardSpriteshow4.setTexture(frontTextureshow4);
                            }
                            else {
                                cardSpriteshow1.setTexture(backTexture);
                                cardSpriteshow2.setTexture(backTexture);
                                cardSpriteshow3.setTexture(backTexture);
                                cardSpriteshow4.setTexture(backTexture);
                            }

                            // Increment the animation counter
                            animationCounter1++;
                            animationDelay = 2.0f;

                            // Check if the maximum animation count has been reached
                            if (animationCounter1 >= maxAnimationCount1)
                            {
                                isFlipping = true;
                                
                            }
                        }
                    }
                    //render
                    headerText.setString("Turn " + std::to_string(t) + " Result");
                    textBounds = headerText.getLocalBounds();
                    headerText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    headerText.setPosition(windowSize.x / 2.0f, 65);
                    window.clear();
                    window.draw(backgroundSprite);
                    window.draw(headerText);

                    if (isBack)
                    {
                        cardSpriteshow1.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow2.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow3.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow4.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow1.setOrigin(backTextureSize.x * cardSpriteshow1.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow1.getScale().y / 2.0f);
                        cardSpriteshow2.setOrigin(backTextureSize.x * cardSpriteshow2.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow2.getScale().y / 2.0f);
                        cardSpriteshow3.setOrigin(backTextureSize.x * cardSpriteshow3.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow3.getScale().y / 2.0f);
                        cardSpriteshow4.setOrigin(backTextureSize.x * cardSpriteshow4.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow4.getScale().y / 2.0f);
                    }
                    else
                    {
                        cardSpriteshow1.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow2.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow3.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow4.setScale(std::cos((flipAngle - currentAngle) * 3.14159f / 360.0f), 1.0f);
                        cardSpriteshow1.setOrigin(backTextureSize.x * cardSpriteshow1.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow1.getScale().y / 2.0f);
                        cardSpriteshow2.setOrigin(backTextureSize.x * cardSpriteshow2.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow2.getScale().y / 2.0f);
                        cardSpriteshow3.setOrigin(backTextureSize.x * cardSpriteshow3.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow3.getScale().y / 2.0f);
                        cardSpriteshow4.setOrigin(backTextureSize.x * cardSpriteshow4.getScale().x / 2.0f,
                            backTextureSize.y * cardSpriteshow4.getScale().y / 2.0f);
                    }
                    window.draw(cardSpriteshow1);
                    window.draw(cardSpriteshow2);
                    window.draw(cardSpriteshow3);
                    window.draw(cardSpriteshow4);
                    window.display();
                    continue;
                }else{
                    if(frame <= 60){
                        sf::Texture switchTexture;
                        switchTexture.loadFromFile("public/switch/SWITCH" + std::to_string((int)frame) + ".png");
                        sf::Sprite switchSprite(switchTexture);
                        
                        window.draw(switchSprite);
                        window.display();
                        if(frame > 55){
                            frame+=0.75;
                        }else{
                            frame+=0.75;
                        }
                        
                        continue;
                    }else{
                        if(elapsedTime.asSeconds() > 9.0f){
                            frame = 0;
                            switchFrame = false;
                            clock.restart();

                            //switching index
                            for(int k=0; k < 4; k++){
                                index[k] = (index[k] + 1) % 4;
                                showPicCards[k] = "";
                            }
                        }
                        sf::Texture switchTexture;
                        switchTexture.loadFromFile("public/switch/SWITCH60.png");
                        sf::Sprite switchSprite(switchTexture);
                        
                        window.draw(switchSprite);
                        window.display();

                        continue;
                    }
                    
                } 
            }

            if(chosenIndexBool){
                picksfx.play();
                placedCards[j][numOfCards[j]] = playerCards[index[j]][chosenIndex];
                showPicCards[j] = placedCards[j][numOfCards[j]];
                std::cout<<playerCards[index[j]][chosenIndex];
                numOfCards[j]++;

                //deleting the picked card
                for(int k = chosenIndex; k < 8 - t;k++){
                    playerCards[index[j]][k] = playerCards[index[j]][k+1];
                }
                j++;

                if(j == 4){
                    j = 0;
                    clock.restart();
                    isFlipping=false;
                    animationCounter1 = 0;
                    switchFrame = true;
                    t++;
                }

                chosenIndexBool = false;
            }
            if(useLangaw){
                if(chosenPlayer != -1 && numOfCards[chosenPlayer] > 0){
                    if(langawIndex != -1){
                        flysfx.play();
                        std::cout<<placedCards[chosenPlayer][langawIndex];
                        placedCards[chosenPlayer][langawIndex] = "";
                        for(int k = langawIndex; k < numOfCards[chosenPlayer]; k++){
                            placedCards[chosenPlayer][k] = placedCards[chosenPlayer][k+1];
                        }
                        numOfCards[chosenPlayer] = numOfCards[chosenPlayer] - 1;
                        j++;
                        if(j == 4){
                            j = 0;
                            clock.restart();
                            switchFrame = true;
                            t++;
                        }
                        useLangaw = false;
                        chosenPlayer = -1;
                        langawIndex = -1;
                        continue;
                    }
                    window.draw(bgLangaw);
                    headerText.setString("Place Your Langaw");
                    window.draw(headerText);

                    int opCardNum = numOfCards[chosenPlayer];
                    // std::cout<<numOfCards[chosenPlayer]<<"-"<< opCardNum;
                    if(opCardNum > 0){

                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][0]+".png")){
                            opSprite1.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite1);
                    }if(opCardNum > 1){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][1]+".png")){
                            opSprite2.setTexture(texture);
                        }else{
                            return -1;
                        }

                        window.draw(opSprite2);
                    }if(opCardNum > 2){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][2]+".png")){
                            opSprite3.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite3);
                    }if(opCardNum > 3){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][3]+".png")){
                            opSprite4.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite4);
                    }if(opCardNum > 4){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][4]+".png")){
                            opSprite5.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite5);
                    }if(opCardNum > 5){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][5]+".png")){
                            opSprite6.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite6);
                    }if(opCardNum > 6){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][6]+".png")){
                            opSprite7.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite7);
                    }if(opCardNum > 7){
                        if(texture.loadFromFile("public/"+placedCards[chosenPlayer][7]+".png")){
                            opSprite8.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(opSprite8);
                    }

                    cardNum = numOfCards[j];
                    if(cardNum > 0){
                        if(texture.loadFromFile("public/"+placedCards[j][0]+".png")){
                            sprite1.setTexture(texture);
                        }else{
                            return -1;
                        }
                        window.draw(sprite1);
                    }
                    if (cardNum >1){
                        if(texture.loadFromFile("public/"+placedCards[j][1]+".png")){
                            sprite2.setTexture(texture);
                        }
                        window.draw(sprite2);
                    }
                    if(cardNum > 2){
                        if(texture.loadFromFile("public/"+placedCards[j][2]+".png")){
                            sprite3.setTexture(texture);
                        }
                        window.draw(sprite3);
                    }
                    if(cardNum > 3){
                        if(texture.loadFromFile("public/"+placedCards[j][3]+".png")){
                            sprite4.setTexture(texture);
                        }
                        window.draw(sprite4);
                    }
                    if(cardNum > 4){
                        if(texture.loadFromFile("public/"+placedCards[j][4]+".png")){
                            sprite5.setTexture(texture);
                        }
                        window.draw(sprite5);
                    }
                    if(cardNum > 5){
                        if(texture.loadFromFile("public/"+placedCards[j][5]+".png")){
                            sprite6.setTexture(texture);
                        }
                        window.draw(sprite6);
                    }
                    if(cardNum > 6){
                        if(texture.loadFromFile("public/"+placedCards[j][6]+".png")){
                            sprite7.setTexture(texture);
                        }
                        window.draw(sprite7);
                    }
                    if(cardNum > 7){
                        if(texture.loadFromFile("public/"+placedCards[j][7]+".png")){
                            sprite7.setTexture(texture);
                        }
                        window.draw(sprite8);
                    }

                    window.display();
                    continue;
                }

                sf::Text text("Choose a Player", font, 70);
                sf::FloatRect textBounds = text.getLocalBounds();
                text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                text.setPosition(windowSize.x / 2, 100);
                text.setFillColor(sf::Color::Black); 
                window.clear(sf::Color(251, 60, 55));
                window.draw(text);

                sf::Text text1(playerNames[playerChoices[0]], nameFont, 30);
                sf::Text text2(playerNames[playerChoices[1]], nameFont, 30);
                sf::Text text3(playerNames[playerChoices[2]], nameFont, 30);

                text1.setOrigin(text1.getGlobalBounds().left + text1.getGlobalBounds().width / 2.0f, text1.getGlobalBounds().top + text1.getGlobalBounds().height / 2.0f);
                text2.setOrigin(text2.getGlobalBounds().left + text2.getGlobalBounds().width / 2.0f, text2.getGlobalBounds().top + text2.getGlobalBounds().height / 2.0f);
                text3.setOrigin(text3.getGlobalBounds().left + text3.getGlobalBounds().width / 2.0f, text3.getGlobalBounds().top + text3.getGlobalBounds().height / 2.0f);

                text1.setFillColor(sf::Color::Black); 
                text2.setFillColor(sf::Color::Black); 
                text3.setFillColor(sf::Color::Black); 

                text1.setPosition((windowSize.x / 2) - 300, (windowSize.y / 2) + 170);
                text2.setPosition(windowSize.x / 2, (windowSize.y / 2) + 170);
                text3.setPosition((windowSize.x / 2) + 300, (windowSize.y / 2) + 170);

                window.draw(text1);
                window.draw(text2);
                window.draw(text3);

                if(iconTexture.loadFromFile("public/icons/p" + std::to_string(playerChoices[0] + 1) + ".png")){
                    icon1.setTexture(iconTexture);
                }
                window.draw(icon1);
                if(iconTexture.loadFromFile("public/icons/p" + std::to_string(playerChoices[1] + 1) + ".png")){
                    icon2.setTexture(iconTexture);
                }
                window.draw(icon2);

                if(iconTexture.loadFromFile("public/icons/p" + std::to_string(playerChoices[2] + 1) + ".png")){
                    icon3.setTexture(iconTexture);
                }
                window.draw(icon3);
                window.display();
                continue;
            }

            //showing players hand
            if(playerHandBool){
                sf::Texture bg;
                bg.loadFromFile("public/bg/"+ eventBg[eventDay[i]]);

                sf::Sprite bgSprite(bg);

                window.draw(bgSprite);

                sf::Texture turnTex;
                turnTex.loadFromFile("public/turn/P"+ std::to_string(j+1) +" TURN.png");
                sf::Sprite turnSprite(turnTex);
                turnSprite.setOrigin(turnTex.getSize().x / 2.0f, turnTex.getSize().y / 2.0f);
                turnSprite.setPosition(windowSize.x / 2.0f, 65);
                window.draw(turnSprite);

                std::string turn = playerNames[j]+ "'s Turn";
                headerText.setString(turn);
                textBounds = headerText.getLocalBounds();
                headerText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

                headerText.setPosition(windowSize.x / 2.0f, 65);
                window.draw(headerText);

                int placedCardsNum = numOfCards[j];
                // displaying placed cards
                if(placedCardsNum > 0){
                    if(texture.loadFromFile("public/"+placedCards[j][0]+".png")){
                        coke1.setTexture(texture);
                    }
                    window.draw(coke1);
                }
                if(placedCardsNum > 1){
                    if(texture.loadFromFile("public/"+placedCards[j][1]+".png")){
                        coke2.setTexture(texture);
                    }
                    window.draw(coke2);
                }
                if(placedCardsNum > 2){
                    if(texture.loadFromFile("public/"+placedCards[j][2]+".png")){
                        coke3.setTexture(texture);
                    }
                    window.draw(coke3);
                }
                if(placedCardsNum > 3){
                    if(texture.loadFromFile("public/"+placedCards[j][3]+".png")){
                        coke4.setTexture(texture);
                    }
                    window.draw(coke4);
                }
                if(placedCardsNum > 4){
                    if(texture.loadFromFile("public/"+placedCards[j][4]+".png")){
                        coke5.setTexture(texture);
                    }
                    window.draw(coke5);
                }
                if(placedCardsNum > 5){
                    if(texture.loadFromFile("public/"+placedCards[j][5]+".png")){
                        coke6.setTexture(texture);
                    }
                    window.draw(coke6);
                }
                if(placedCardsNum > 6){
                    if(texture.loadFromFile("public/"+placedCards[j][6]+".png")){
                        coke7.setTexture(texture);
                    }
                    window.draw(coke7);
                }
                if(placedCardsNum > 7){
                    if(texture.loadFromFile("public/"+placedCards[j][7]+".png")){
                        coke8.setTexture(texture);
                    }
                    window.draw(coke8);
                }



                //showing cards on hand
                cardNum = 8-t;
                if (cardNum >1){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][0]+".png")){
                        sprite1.setTexture(texture);
                    }
    
                    window.draw(sprite1);

                    if(texture.loadFromFile("public/"+playerCards[index[j]][1]+".png")){
                        sprite2.setTexture(texture);
                    }
                    window.draw(sprite2);
                }
                if(cardNum > 2){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][2]+".png")){
                        sprite3.setTexture(texture);
                    }
                    window.draw(sprite3);
                }
                if(cardNum > 3){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][3]+".png")){
                        sprite4.setTexture(texture);
                    }
                    window.draw(sprite4);
                }
                if(cardNum > 4){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][4]+".png")){
                        sprite5.setTexture(texture);
                    }
                    window.draw(sprite5);
                }
                if(cardNum > 5){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][5]+".png")){
                        sprite6.setTexture(texture);
                    }
                    window.draw(sprite6);
                }
                if(cardNum > 6){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][6]+".png")){
                        sprite7.setTexture(texture);
                    }
                    window.draw(sprite7);
                }
                if(cardNum > 7){
                    if(texture.loadFromFile("public/"+playerCards[index[j]][7]+".png")){
                        sprite7.setTexture(texture);
                    }
                    window.draw(sprite8);
                }

                if(fading){
                    if(eventDay[i] == 2){
                        if(frame <= 90){
                            sf::Texture eventTexture;
                            eventTexture.loadFromFile("public/sunny/SUNNY" + std::to_string((int)frame) + ".png");
                            sf::Sprite eventSprite(eventTexture);
                            window.draw(eventSprite);
                            frame += 0.75;
                        }else{
                            fading = false;
                            frame = 0;
                        }
                    }else if(eventDay[i] == 1){
                        if(frame <= 90){
                            sf::Texture eventTexture;
                            eventTexture.loadFromFile("public/rainy/RAINY" + std::to_string((int)frame) + ".png");
                            sf::Sprite eventSprite(eventTexture);
                            window.draw(eventSprite);
                            frame += 0.75;
                        }else{
                            fading = false;
                            frame = 0;
                        }
                    }else {
                        if(frame <= 90){
                            sf::Texture eventTexture;
                            eventTexture.loadFromFile("public/cloudy/CLOUDY" + std::to_string((int)frame) + ".png");
                            sf::Sprite eventSprite(eventTexture);
                            window.draw(eventSprite);
                            frame += 0.75;
                        }else{
                            fading = false;
                            frame = 0;
                        }
                    }
                }


                window.display();

                continue;
            }
        }
    }
    
    return 0;
}
