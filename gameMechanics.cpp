#include <iostream>
#include <cstdlib>
#include <string>

#include "gameMechanics.h"

int main(){
    int points[] = {0, 0, 0, 0};//players points
    std::string deck[104];//deck of cards
    std::string playerCards[4][8];//cards for each player
    std::string placedCards[4][8];//cards used by the players
    int event[3];

    initializeDeck(deck);//deck initalize
    shuffle(deck); //shuffle deck
    randevent(event);//randomize event each round (normal, rainy day, sunnyday)
    placeLangaw(deck, event);//distributing langaws in each deck

    std::cout<<"Pista Go!"<<std::endl<<std::endl;


    for(int i = 0; i < 3; i ++){
        std::string day[3] = {"Fair Day", "Rainy Day", "Sunny Day"};
        std::cout<<">>"<<day[event[i]]<<"<<"<<std::endl;
        if(event[i] == 1){
            std::cout<<"Beware of Langaws and Avoid Halo-halo!!!"<<std::endl;
        }else if(event[i] == 2){
            std::cout<<"Halo-halo boost!!!"<<std::endl;
        }
        
        distribute(deck, playerCards, i);//distribute 8 cards to each player

        //truns
        int index[] = {0, 1, 2, 3}; //index for switching cards
        int numOfCards[] = {0, 0, 0, 0}; //number of cards for each player

        for(int t = 0; t < 8; t++){
            //if last card then place it on the deck then break
            if(t==7){
                for(int j = 0; j < 4; j++){
                    if(playerCards[index[j]][0] != "langaw"){
                        placedCards[j][numOfCards[j]] = playerCards[index[j]][0];//place to the last
                        numOfCards[j]++;
                    }
                }

                //display picked cards
                for(int j = 0; j < 4; j++){
                    std::cout<<"Player "<<j+1<<": ";
                    for(int k = 0; k < numOfCards[j]; k++){
                        std::cout<<placedCards[j][k]<<" | ";
                    }
                    std::cout<<std::endl;
                }
                std::cout<<std::endl;
                break;
            }

            //displaying the cards
            for(int j = 0; j < 4; j++){
                std::cout<<"Player"<<j+1<<": ";
                for(int k = 0; k < 8 - t; k++){
                    std::cout<<"<"<<k<<">"<<playerCards[index[j]][k]<<"  ";
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;

            //placing then removing cards from deck
            for(int j = 0; j < 4; j++){
                int chosenIndex;
                std::cout<<"Player "<<j+1<<"'s turn: ";
                //bounds check
                std::cin>>chosenIndex;
                while(!((chosenIndex >= 0) && (chosenIndex <= 7 - t))){
                    std::cout<<"invalid input:<"<<std::endl<<"Player "<<j+1<<"'s turn: ";
                    std::cin>>chosenIndex;
                }
                if(t == 0){
                    while(playerCards[index[j]][chosenIndex] == "langaw"){
                        std::cout<<"invalid input:<"<<std::endl<<"Player "<<j+1<<"'s turn: ";
                        std::cin>>chosenIndex;
                    }
                }
              
                //placing card
                if(playerCards[index[j]][chosenIndex] != "langaw"){
                    placedCards[j][numOfCards[j]] = playerCards[index[j]][chosenIndex];
                    numOfCards[j]++;
                }else{
                    int player;
                    std::cout<<"Choose a player: ";
                    std::cin>>player;
                    while(!(player > 0 && player <=4 && player != j+1)){
                        std::cout<<"invalid input:<"<<std::endl<<"Choose a player: ";
                        std::cin>>player;
                    }
                    player--;
                    std::cout<<"Player "<<player+1<<"'s Cards: ";
                    for(int k =0; k < numOfCards[player]; k++){
                        std::cout<<"<"<<k<<">"<<placedCards[player][k]<<" | ";
                    }
                    int cardIndex;
                    std::cout<<std::endl<<"Choose card: ";
                    std::cin>>cardIndex;
                    while(!(cardIndex >= 0 && cardIndex < numOfCards[player])){
                        std::cout<<"invalid input"<<std::endl<<"Choose card:";
                        std::cin>>cardIndex;
                    }

                    for(int k = cardIndex; k < numOfCards[player]; k++){
                        placedCards[player][k] = placedCards[player][k+1];
                    }
                    placedCards[player][numOfCards[player]] = "";
                    numOfCards[player]--;
                }
                

                //removing
                for(int k = chosenIndex; k < 8 - t; k++){
                    playerCards[index[j]][k] = playerCards[index[j]][k+1];
                }
            }
            std::cout<<std::endl;

            //displaying picked cards
            std::cout<<">>>Picked Cards<<<"<<std::endl;
            if(t == 6){
                //switch
                for(int j=0; j < 4; j++){
                    index[j] = (index[j] + 1) % 4;
                }
                continue;
            }
            for(int j = 0; j < 4; j++){
                std::cout<<"Player "<<j+1<<": ";
                for(int k = 0; k < numOfCards[j]; k++){
                    std::cout<<placedCards[j][k]<< " | ";
                }
                std::cout<<std::endl;
            }    

            //switching cards
            for(int j=0; j < 4; j++){
                index[j] = (index[j] + 1) % 4;
            }
            std::cout<<std::endl<<">>>Switch!<<<"<< std::endl<<std::endl;
        }
        calcScoreSingle(placedCards, points, numOfCards);
        calcScoreAll(placedCards, points, numOfCards);
        std::cout<<">>>Scores<<<"<<std::endl;
        for(int j = 0; j < 4; j++){
            std::cout<<"Player "<<j+1<<": "<<points[j]<<std::endl;
        }
    }

    return 0;
}
