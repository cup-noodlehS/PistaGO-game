#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
void initializeDeck(std::string deck[104]){
    int i = 0;
    while(i < 14){
        deck[i] = "ccb";
        i++;
    };
    while(i < 28){
        deck[i] = "lb";
        i++;
    };
    while(i < 42){
        deck[i] = "empanada";
        i++;
    };
    while(i < 54){
        deck[i] = "2cupRice";
        i++;
    };
    while(i < 64){
        deck[i] = "halohalo";
        i++;
    };
    while(i < 70){
        deck[i] = "suka";
        i++;
    };
    while(i < 78){
        deck[i] = "3cupRice";
        i++;
    };
    while(i < 84){
        deck[i] = "1cupRice";
        i++;
    };
    while(i < 94){
        deck[i] = "chickenLumpia";
        i++;
    };
    while(i < 99){
        deck[i] = "tawgiLumpia";
        i++;
    };
    while(i < 104){
        deck[i] = "shanghaiLumpia";
        i++;
    };
}


//shuffling deck
void shuffle(std::string array[104]){
    int n = 104;
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        std::string temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


//randomly place langaws in the deck
void placeLangaw(std::string deck[104], int event[3]){
    for(int i=0; i < 3; i ++){
        int num;//number of langaw
        if(event[i]==1){
            //if rainy
            num = 5;
        }else if(event[i] == 0){
            //normal
            num = 3;
        }else{
            //sunny
            num = 2;
        }
        srand(time(NULL));
        for(int j = 0; j < num; j++){
            deck[(rand()%32) + (32*i)] = "langaw";
        }
    }
}


//distribute cards to 4 playersa
void distribute(std::string deck[104], std::string playerCards[4][8], int round){
    int deckindex = ((round + 1) * (32)) - 32;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            playerCards[i][j] = deck[deckindex];
            deckindex++;
        }
    }
}


//randomize event
void randevent(int event[3]) {
    event[0] = 0;
    event[1] = 1;
    event[2] = 2;
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        int index = rand() % 3;
        int temp = event[i];
        event[i] = event[index];
        event[index] = temp;
    }
}


//calculate score for cards that is scored individually
void calcScoreSingle(std::string placedCards[4][8], int points[4], int numOfCards[4]){
    for(int i = 0; i < 4; i++){
        int score = 0;
        //scoring for lumpia x suka
        for(int j = 0; j < numOfCards[i]; j++){
            std::string card = placedCards[i][j];
            if(card == "tawgiLumpia"){
                bool suka = false;
                for(int k = j - 1; k >=0; k--){
                    if(placedCards[i][k] == "suka"){
                        placedCards[i][k] = "sukaXtawgi";
                        suka = true;
                    }
                }
                if(suka){
                    score += 1 * 3;
                }else{
                    score += 1;
                }


            }
            else if(card == "chickenLumpia"){
                bool suka = false;
                for(int k = j - 1; k >=0; k--){
                    if(placedCards[i][k] == "suka"){
                        placedCards[i][k] = "sukaXchicken";
                        suka = true;
                    }
                }
                if(suka){
                    score += 2 * 3;
                }else{
                    score += 2;
                }


            }
            else if(card == "shanghaiLumpia"){
                bool suka = false;
                for(int k = j - 1; k >=0; k--){
                    if(placedCards[i][k] == "suka"){
                        placedCards[i][k] = "sukaXshanghai";
                        suka = true;
                    }
                }
                if(suka){
                    score += 3 * 3;
                }else{
                    score += 3;
                }


            }
        }
        //scoring for empanada & lb & ccb
        int empanadaCount = 0;
        int empanadaScore[] = {0, 1, 3, 6, 10, 15};
        int lbCount = 0;
        int ccbCount = 0;
        for(int j = 0; j < numOfCards[i]; j++){
            std::string card = placedCards[i][j];
            if(card == "empanada"){
                empanadaCount++;
            }else if(card == "lb"){
                lbCount++;
            }else if(card == "ccb"){
                ccbCount++;
            }
        }
        if(empanadaCount > 5){
            empanadaCount = 5;
        }
        score += empanadaScore[empanadaCount];
        if(lbCount >= 3){
            score += 10;
        }
        score += ((int)(ccbCount / 2)) * 5;


        points[i] = score;
    }
}


//calc score for cards that is scored not individually?? ambot
void calcScoreAll(std::string placedCards[4][8], int points[4], int numOfCards[4]){
    int haloCountArr[] = {0, 0, 0, 0};
    int riceCount[] = {0, 0, 0, 0};
    for(int i = 0; i < 4; i++){
        int count = 0;
        int haloCount = 0;
        for(int j = 0; j < numOfCards[i];j++){
            std::string card = placedCards[i][j];
            if(card == "1cupRice"){
                count++;
            }else if(card == "2cupRice"){
                count += 2;
            }else if(card == "3cupRice"){
                count += 3;
            }else if(card == "halohalo"){
                haloCount++;
            }
        }
        riceCount[i] = count;
        haloCountArr[i] = haloCount;
    }
    //for rice
    int max = riceCount[0];
    for(int i = 1; i < 4; i++){
        if(riceCount[i] > max){
            max = riceCount[i];
        }
    }
    int samecounter = 0;
    int second = 0;
    for(int i = 0; i < 4; i++){
        if(riceCount[i] == max){
		samecounter++;
        }else{
            if(riceCount[i] > second){
                second = riceCount[i];
            }
        }
    }


 	for(int i = 0; i < 4; i++){
        if(riceCount[i] == max){
            points[i] += 6/samecounter;
		}
}


    if(second != 0 && samecounter ==1){
        for(int i = 0; i < 4; i++){
            if(riceCount[i]==second){
                points[i] += 3;
            }
        }
    }


    //for halo-halo
    int samecountermax, samecountermin;
    max = haloCountArr[0];
    int min = haloCountArr[0];
    for(int i = 1; i < 4; i++){
        if(haloCountArr[i] > max){
            max = haloCountArr[i];
        }else if(haloCountArr[i] < min && haloCountArr[i] > 0){
            min = haloCountArr[i];
        }
    }
    for(int i = 0; i < 4; i++){
        if(haloCountArr[i]==max){
		    samecountermax++;
        }else if(haloCountArr[i]==min){
		    samecountermin++;
        }
    }
	if(samecountermax != 4){
         for(int i = 0; i < 4; i++){
                     if(haloCountArr[i]==max){
	                  points[i] += 6/samecountermax++;
                    }else if(haloCountArr[i]==min){
		                points[i] -= 6/samecountermin;
                    }
	          }
            }
}

class Textbox{
    public:
        Textbox() { }

        Textbox(int size, sf::Color color, bool sel){
            textbox.setCharacterSize(size);
            textbox.setColor(color);
            isSelected = sel;
            if(sel){
                textbox.setString("_");
            }
            else{
                textbox.setString("");
            }
        }

        void setFont(sf::Font &font){
            textbox.setFont(font);
        }

        void setPosition(sf::Vector2f pos){
            textbox.setPosition(pos);
        }

        void setOrigin(sf::Vector2f pos){
            textbox.setOrigin(pos);
        }

        void setLimit(bool ToF){
            haslimit = ToF;
        }
        
        void setLimit(bool ToF, int lim){
            haslimit = ToF;
            limit = lim - 1;
        }

        void setSelected(bool sel){
            isSelected = sel;
            if(!sel){
                std::string t = text.str();
                std::string newT = "";
                for(int i = 0; i < t.length(); i++){
                    newT += t[i];
                }
                textbox.setString(newT);

            }
        }

        std::string getText(){
            return text.str();
        }
        int getLength(){
            return text.str().length();
        }

        void drawTo(sf::RenderWindow &window){
            window.draw(textbox);
        }

        void typedOn(sf::Event input){
            if(isSelected){
                int charTyped = input.text.unicode;
                if (charTyped < 128){
                    if(haslimit){
                        if(text.str().length() <= limit){
                            inputLogic(charTyped);
                        }
                        else if(text.str().length() > limit && charTyped == DELETE_KEY){
                            deleteLastChar();
                        }
                    }
                    else{
                        inputLogic(charTyped);
                    }
                }
            }
        }

        sf::FloatRect getBounds(){
            return textbox.getGlobalBounds();
        }

         void handleEvent(sf::Event event, sf::RenderWindow& window,sf::RectangleShape border) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (border.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    setSelected(true);
                    std::string t = text.str();
                    std::string newT = "";
                    for(int i = 0; i < t.length(); i++){
                        newT += t[i];
                    }
                    newT += "_";
                    textbox.setString(newT);
                
                } else {
                    setSelected(false);
                }
            }
        }


    private:
        sf::Text textbox;
        std::ostringstream text;
        bool isSelected = false;
        bool haslimit = false;
        int limit;

        void inputLogic(int chartyped){
            if(chartyped != DELETE_KEY && chartyped != ENTER_KEY && chartyped != ESCAPE_KEY){
                text << static_cast<char>(chartyped);
            }
            else if(chartyped == DELETE_KEY){
                if (text.str().length() > 0){
                    deleteLastChar();
                }
            }
            textbox.setString(text.str() + "_");
        }

        void deleteLastChar(){
            std::string t = text.str();
            std::string newT = "";
            for(int i = 0; i < t.length() - 1; i++){
                newT += t[i];
            }
            text.str("");
            text << newT;
            textbox.setString(text.str());
        }
};

