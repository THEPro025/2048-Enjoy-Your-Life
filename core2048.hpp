#ifndef CORE2048_HPP
#define CORE2048_HPP

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <fstream>


class Game2048 {
public:
    Game2048();
    int random();
    std::vector<std::vector<int>> getBoard() {
        return board;
    }
    void newblock();
    void move(char diraction);
    bool isover();
    bool iswin();
    void newgame();
    bool gaming(char diraction);
    int getScore() {
        return score;
    }
    void record(std::string name);
    void load();
    bool getIsload() {
        return isload;
    }
    void loadchange(bool tight){
        isload=tight;
    }
    std::string getCurrent_name() {
        return Current_name;
    }
    void setCurrent_name(std::string name) {
        Current_name = name;
    }
    bool getwincontinue(){
        return wincontinue;
    }
    void changecontinue(bool tight){
        wincontinue=tight;
    }
    int getgamestyle(){
        return gamestyle;
    }
    void setgamestyle(int style){
        gamestyle=style;
    }


    //void tprintboard(int test);
    
private:
    std::vector<std::vector<int>> board;
    int score;
    std::random_device rd;
    int movetimes;
    bool isload;
    std::string Current_name;
    bool wincontinue=false;
    //gamestyle 0: normal 1: chemistry 2: the death ends
    int gamestyle;
};
class Player {
public:
    Player();
    void setName(std::string name);
    std::string getName() {
        return name;
    }
    void setScore(int score);
    int getScore() {
        return score;
    }
private:
    std::string name;
    int score;
    
};
class Rank {
public:
    Rank();
    void addPlayer(Player player);
    void sort();
    void print();
    void save();
    void load();
    int getRecord();
    ~Rank();
    std::vector<Player> getplayers(){
        return players;
    }
private:
    std::vector<Player> players;
    int record;
};
#endif // CORE2048_HPP
