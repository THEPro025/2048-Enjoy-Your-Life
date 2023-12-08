

#include "core2048.hpp"

Game2048::Game2048() {
    board.resize(4, std::vector<int>(4, 0));
    score = 0;
    std::mt19937 gen(rd());
}
std::string styleoutput(int style,int boardone){
    std::string output;
    if(style==0)
        output=std::to_string(boardone);
    else if(style==1){
    switch(boardone){
        case 0:
            output="    ";
            break;
        case 2:
            output=" H  ";
            break;
        case 4:
            output=" He ";
            break;
        case 8:
            output=" Li ";
            break;
        case 16:
            output=" Be ";
            break;
        case 32:
            output=" B  ";
            break;
        case 64:
            output=" C  ";
            break;
        case 128:
            output=" N  ";
            break;
        case 256:
            output=" O  ";
            break;
        case 512:
            output=" F  ";
            break;
        case 1024:
            output=" Ne ";
            break;
        case 2048:
            output=" Na ";
            break;
        default:
            output=" Na*"+std::to_string(boardone/2048);
            break;
        }
    }
    else if(style==2){
        switch(boardone){
        case 0:
            output="        ";
            break;
        case 2:
            output="Pastoral age";
            break;
        case 4:
            output="Magic age";
            break;
        case 8:
            output="Golden age";
            break;
        case 16:
            output="Era of crisis";
            break;
        case 32:
            output="Era of deter-rence";
            break;
        case 64:
            output="Post of deter-rence  ";
            break;
        case 128:
            output="Radio era";
            break;
        case 256:
            output="Era of Shelter";
            break;
        case 512:
            output="Galactic Era";
            break;
        case 1024:
            output="Dark Domain Era";
            break;
        case 2048:
            output="Out of the time";
            break;
        default:
            output="Era of Return*"+std::to_string(boardone/2048);
            break;
        }
    }
    /*else if(style==3){
        if(boardone==0)
            output="    ";
        else if(boardone==2)
            output="  2 ";
        else if(boardone==4)
            output="  4 ";
        else if(boardone==8)
            output="  8 ";
        else if(boardone==16)
            output=" 16 ";
        else if(boardone==32)
            output=" 32 ";
        else if(boardone==64)
            output=" 64 ";
        else if(boardone==128)
            output="128 ";
        else if(boardone==256)
            output="256 ";
        else if(boardone==512)
            output="512 ";
        else if(boardone==1024)
            output="1024";
        else if(boardone==2048)
            output="2048";
    
    }*/
    return output;
}
bool Game2048::gaming(char diraction){
    movetimes=0;
    move(diraction);
    if(isover()){
        return false;
    }
    if(movetimes!=0){
        newblock();
        return true;
    }
    
    //tprintboard(4);
    return true;    
    }
int Game2048::random() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    if (dist(rd) <= 90) {
        return 2;
    }
    else {
        return 4;
    }
}
void Game2048::newblock(){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);
    while (true){
        int row = dist(gen);
        int col = dist(gen);
        if(board[row][col] == 0){
            board[row][col] = random();
            break;
        }
    }
}
void Game2048::newgame(){
        board.resize(4, std::vector<int>(4, 0));
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                board[i][j]=0;
        newblock();
        newblock();
        score=0;
    }
bool Game2048::isover(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == board[i][j + 1]||board[i][j]==0||board[i][j+1]==0){
                    return false;
                }
            }
        }
        for(int j = 0; j < 4; j++){
            for(int i = 0; i < 3; i++){
                if(board[i][j] == board[i + 1][j]||board[i][j]==0||board[i+1][j]==0){
                    return false;
                }
            }
        }
        return true;
    }
bool Game2048::iswin(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] >= 2048){
                    return true;
                }
            }
        }
        return false;
    }
void Game2048::move(char diraction){
    if(diraction=='w'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] == 0){
                    for(int k = i + 1; k < 4; k++){
                        if(board[k][j] != 0){
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //test only
        //tprintboard(1);
        for(int  j = 0; j < 4; j++){
            for(int i = 0; i < 3; i++){
                if(board[i][j] == board[i+1][j]){
                    board[i][j] *= 2;
                    board[i+1][j] = 0;
                    score+=board[i][j];
                    if(board[i][j]!=0)                        
                        movetimes++;
                }
            }
        }
        //tprintboard(2);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] == 0){
                    for(int k = i + 1; k < 4; k++){
                        if(board[k][j] != 0){
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(3);
    }    
    else if(diraction=='s'){
        for(int i = 3; i >= 0; i--){
            for(int j = 3; j >= 0; j--){
                if(board[i][j] == 0){
                    for(int k = i - 1; k >= 0; k--){
                        if(board[k][j] != 0){
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(1);
        for(int j = 3; j >= 0; j--){
            for(int i = 3; i > 0; i--){
                if(board[i][j] == board[i-1][j]){
                    board[i][j] *= 2;
                    board[i-1][j] = 0;
                    score+=board[i][j];
                    if(board[i][j]!=0)                        
                        movetimes++;
                }
            }
        }
        //tprintboard(2);
        for(int i = 3; i >= 0; i--){
            for(int j = 3; j >= 0; j--){
                if(board[i][j] == 0){
                    for(int k = i - 1; k >= 0; k--){
                        if(board[k][j] != 0){
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(3);
    }
    else if (diraction=='a'){
        for(int j = 0; j < 4; j++){
            for(int i = 0; i < 4; i++){
                if(board[i][j] == 0){
                    for(int k = j + 1; k < 4; k++){
                        if(board[i][k] != 0){
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(1);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == board[i][j+1]){
                    board[i][j] *= 2;
                    board[i][j+1] = 0;
                    score+=board[i][j];
                    if(board[i][j]!=0)                        
                        movetimes++;
                }
            }
        }
        //tprintboard(2);
        for(int j = 0; j < 4; j++){
            for(int i = 0; i < 4; i++){
                if(board[i][j] == 0){
                    for(int k = j + 1; k < 4; k++){
                        if(board[i][k] != 0){
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(3);
    }
    else if (diraction=='d'){
        for(int j = 3; j >= 0; j--){
            for(int i = 3; i >= 0; i--){
                if(board[i][j] == 0){
                    for(int k = j - 1; k >= 0; k--){
                        if(board[i][k] != 0){
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(1);
        for(int i = 3; i >= 0; i--){
            for(int j = 3; j > 0; j--){
                if(board[i][j] == board[i][j-1]){
                    board[i][j] *= 2;
                    board[i][j-1] = 0;
                    score+=board[i][j];
                    if(board[i][j]!=0)                        
                        movetimes++;
                }
            }
        }
        //tprintboard(2);
        for(int j = 3; j >= 0; j--){
            for(int i = 3; i >= 0; i--){
                if(board[i][j] == 0){
                    for(int k = j - 1; k >= 0; k--){
                        if(board[i][k] != 0){
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            movetimes++;
                            break;
                        }
                    }
                }
            }
        }
        //tprintboard(3);
    }
}
void Game2048::record(std::string name){
    std::ofstream out("../temp.dat", std::ios::trunc);
    out <<"true" <<std::endl;
    out<<score <<" "<< name << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            out << board[i][j] << " ";
        }
        out << std::endl;
    }
    out.close();
}

void Game2048::load(){
    std::ifstream in("../temp.dat");
    if (!in) {
        std::cout << "No saved game found." << std::endl;
        isload = false;
        return;
    }
    std::string playerName,t;
    
    in >>t;
    if(t!="true"){
        std::cout << "No saved game found." << std::endl;
        isload = false;
        return;
    }
    in>> score>>playerName;
    Current_name=playerName;
    std::cout<<"Welcome back, "<<playerName<<"!"<<std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in >> board[i][j];
        }
    }
    in.close();
    std::cout << "Saved game loaded." << std::endl;
    isload = true;
    std::ofstream out("../temp.dat", std::ios::trunc);
    out<<"false"<<std::endl;
    out.close();
}

    
//test the program
/*void Game2048::tprintboard(int test){
    std::cout << "Test Only?? " << test<<std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << "|";
            std::cout  <<board[i][j];
            
        }
        std::cout << "|" << std::endl;
    }
    std::cout<<movetimes<<std::endl;
}*/
Player::Player(){
    name = "Player";
    score = 0;
}
void Player::setScore(int score){
    this->score = score;
}
void Player::setName(std::string name){
    this->name = name;
}
Rank::Rank(){
    load();
}
Rank::~Rank(){
    sort();
    save();
}
void Rank::addPlayer(Player player){
    for(int i = 0; i < players.size(); i++){
        if(players[i].getName() == player.getName()){
            players[i].setScore(player.getScore());
            return;
        }
    }
    players.push_back(player);
}
void Rank::sort(){
    for(int i = 0; i < players.size(); i++){
        for(int j = 0; j < players.size() - i - 1; j++){
            if(players[j].getScore() < players[j + 1].getScore()){
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
void Rank::print(){
    std::cout << "Ranking List:" << std::endl;
    for(int i = 0; i < players.size(); i++){
        std::cout << i + 1 << ". " << players[i].getName() << " " << players[i].getScore() << std::endl;
    }
}
void Rank::save(){
    std::ofstream out("../playerdata.dat",std::ios::trunc);
    for(int i = 0; i < players.size(); i++){
        if(i == players.size() - 1){
            out << players[i].getName() << " " << players[i].getScore();
            break;
        }
        out << players[i].getName() << " " << players[i].getScore() << std::endl;
    }
    out.close();
}
void Rank::load(){
    std::ifstream in("../playerdata.dat");
    if(!in){
        std::cout << "No player data found." << std::endl;
        return;
    }
    while(!in.eof()){
        std::string name;
        int score;
        in >> name >> score;
        Player player;
        player.setName(name);
        player.setScore(score);
        players.push_back(player);
    }
    if(players.size() > 0){
        std::cout << "Player data loaded." << std::endl;
        print();
    }
    else{
        std::cout << "No player data found." << std::endl;
    }
    in.close();
}
int Rank::getRecord(){
    if(players.size() > 0){
        return players[0].getScore();
    }
    else{
        return 0;
    }
}
