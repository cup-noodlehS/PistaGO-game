#include <iostream>
#include <cstdlib>
#include <string>

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
    int second = 0;
    for(int i = 0; i < 4; i++){
        if(riceCount[i] == max){
            points[i] += 6;
        }else{
            if(riceCount[i] > second){
                second = riceCount[i];
            }
        }
    }
    if(second != 0){
        for(int i = 0; i < 4; i++){
            if(riceCount[i]==second){
                points[i] += 3;
            }
        }
    }

    //for halo-halo
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
            points[i] += 6;
        }else if(haloCountArr[i]==min){
            points[i] -= 6;
        }
    }
}