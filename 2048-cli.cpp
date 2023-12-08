#include "../core2048.hpp"
#include "../core2048.cpp"
#include <iostream>
#include <iomanip>

int max_digits(std::vector<std::vector<int>> board,int style){
    std::size_t max = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            max = std::max(max, styleoutput(style,board[i][j]).size());
        }
    }
    return max;
}
void printboard(std::vector<std::vector<int>> board,int style){
    std::cout << "Use w(up),a(left),s(down),d(right) to move. Press Q to quit." << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << "+";
            for(int k = 0; k < max_digits(board,style); k++){
                std::cout << "-";
            }
        }
        std::cout << "+"<<std::endl;
        for(int j = 0; j < 4; j++){
            std::cout << "|";
            std::cout  <<std::setw(max_digits(board,style))<<styleoutput(style,board[i][j]);
            
        }
        std::cout << "|" << std::endl;
    }
    for(int j = 0; j < 4; j++){
            std::cout << "+";
            for(int k = 0; k < max_digits(board,style); k++){
                std::cout << "-";
            }
        }
        std::cout << "+"<<std::endl;
}

void game(){
    Game2048 game;
    Player player;
    Rank rank;
    std::cout << "Welcome to 2048!" << std::endl;
    while(true){
        std::cout << "Please choose the game style: " << std::endl;
        std::cout << "Press 0 for traditional style, press 1 for chemistry style, press 2 for three body style." << std::endl;
        int style;
        std::cin >> style;
        if(style == 0){
            game.setgamestyle(0);
            break;
        }
        else if(style == 1){
            game.setgamestyle(1);
            break;
        }
        else if(style == 2){
            game.setgamestyle(2);
            break;
        }
        else{
            std::cout<<"Invalid input!"<<std::endl;
        }
    }
    game.load();
    game.changecontinue(false);
    if(game.getIsload()){
        while (true){
            std::cout << "Would you like to continue the game or start a new game ?" << std::endl;
            std::cout << "Press Y to continue, press N to start a new game." << std::endl;
            char choice;
            std::cin >> choice;
            if(choice == 'N'){
                std::cout << "Please enter your name: ";
                std::string name;
                std::cin >> name;
                player.setName(name);
                game.newgame();
                printboard(game.getBoard(),game.getgamestyle());
                break;
            }
            else if(choice == 'Y'){
                player.setName(game.getCurrent_name());
                printboard(game.getBoard(),game.getgamestyle());
                break;
            }
            else{
                std::cout<<"Invalid input!"<<std::endl;
            }
        }
    }
    else{
        std::cout << "Please enter your name: ";
        std::string name;
        std::cin >> name;
        player.setName(name);
        game.newgame();
        printboard(game.getBoard(),game.getgamestyle());
    }
    
    while(true){
        char diraction;
        std::cout << "Score: " << game.getScore() <<" Current Player: "<< player.getName() << std::endl;
        std::cout<<"Next move: ";
        std::cin >> diraction;

        if(!game.gaming(diraction)){
            if(!game.iswin()||game.isover()){
                std::cout << "Game over! Current Scores: " <<game.getScore()<< std::endl;
                std::cout <<"Current Player: "<< player.getName() << std::endl;
                if(rank.getRecord() < game.getScore()){
                    std::cout << "New record!" << std::endl;
                }
                player.setScore(game.getScore());
                rank.addPlayer(player);
                rank.sort();
                rank.print();
                break;
            }
        }
        else if(diraction=='Q'){
            std::cout<<"Game has been saved."<<std::endl;
            game.record(player.getName());
            break;
        }
        if(game.iswin()&&!game.getwincontinue()){
            std::cout << "You win! Current Scores: " <<game.getScore()<< std::endl;
            std::cout << "Would you like to continue the game, start a new game or quit the game ?" << std::endl;
            std::cout << "Press Y to continue, press N to start a new game,press any else to quit." << std::endl;
            char choice;
            std::cin >> choice;
            if(choice == 'N'){
                std::cout << "Game over! Current Scores: " <<game.getScore()<< std::endl;
                std::cout <<"Current Player: "<< player.getName() << std::endl;
                if(rank.getRecord() < game.getScore()){
                    std::cout << "New record!" << std::endl;
                }
                player.setScore(game.getScore());
                rank.addPlayer(player);
                rank.sort();
                rank.print();
                game.newgame();
                printboard(game.getBoard(),game.getgamestyle());
                continue;
            }
            else if(choice == 'Y'){
                game.changecontinue(true);
                continue;
            }
            else{
                std::cout << "Game over! Current Scores: " <<game.getScore()<< std::endl;
                std::cout <<"Current Player: "<< player.getName() << std::endl;
                if(rank.getRecord() < game.getScore()){
                    std::cout << "New record!" << std::endl;
                }
                player.setScore(game.getScore());
                rank.addPlayer(player);
                rank.sort();
                rank.print();
                break;
            }
        }
        else if(game.isover()){
            std::cout << "Game over! Current Scores: " <<game.getScore()<< std::endl;
            std::cout <<"Current Player: "<< player.getName() << std::endl;
            if(rank.getRecord() < game.getScore()){
                std::cout << "New record!" << std::endl;
            }
            player.setScore(game.getScore());
            rank.addPlayer(player);
            rank.sort();
            rank.print();
            break;
        }
        printboard(game.getBoard(),game.getgamestyle());
    }
    
}
int main(){
    game();
    while(true){
        char choice;
        std::cout << "Would you like to continue the game or quit the game ?" << std::endl;
        std::cout << "Press Y to continue, press any else to quit." << std::endl;
        std::cin >> choice;
        if(choice == 'Y'){
            game();
        }
        else{
            break;
        }
    }
    return 0;
}
