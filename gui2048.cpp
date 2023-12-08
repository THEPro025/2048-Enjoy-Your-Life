#include "gui2048.h"
#include "../core2048.cpp"
#include <QDebug>

Gui2048::Gui2048(QWidget *parent)
    : QMainWindow(parent)

{

    creatmenu();
    setWindowTitle("2048 Enjoy your Life");
    setFixedSize(400, 520);
    //Below is main game concept

    // Central widget for the main window
    game.loadchange(false);

    QPushButton *Game=new QPushButton(this);
    QFont font("HP Simplified Jpan", 35, QFont::Bold);
    Game->setText("Game");
    Game->setStyleSheet("background-color: orange; color: white;");
    Game->setFont(font);
    Game->setGeometry(130,440,140,70);

    connect(Game, &QPushButton::clicked, this, &Gui2048::Gamebutton);

    if(game.getIsload()){
        gamestart();
    }

}

Gui2048::~Gui2048()
{

}
void Gui2048::closeEvent(QCloseEvent *event){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Exit");
    msgBox.setText("Warning!!!");
    msgBox.setInformativeText("Do you want to exit the game? \n Attention! Make sure you have saved the game!");
    QPushButton *Exit=msgBox.addButton(tr("Exit"),QMessageBox::AcceptRole);
    QPushButton *SaveExit=msgBox.addButton(tr("Save and Exit"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);

    msgBox.exec();
    if(msgBox.clickedButton()==Exit){
        game.loadchange(false);
        event->accept();
    }
    else if(msgBox.clickedButton()==SaveExit){
        if(!game.getIsload()){
            game.record(player.getName());
        }

        game.loadchange(false);
        event->accept();
    }
    else
        event->ignore();
}
//creat a menubar and menus
void Gui2048::creatmenu(){
    QMenuBar *menuBar = new QMenuBar(this); // Create a menu bar

    // Create menus to be added to the menu bar
    QMenu *gameMenu = menuBar->addMenu("Game");

    QAction *newAction = new QAction("New Game", this);
    gameMenu->addAction(newAction);
    connect(newAction, &QAction::triggered, this, &Gui2048::showGameNew);

    QAction *saveAction = new QAction("Save Game", this);
    gameMenu->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &Gui2048::showGameSave);

    QAction *loadAction = new QAction("Load Game", this);
    gameMenu->addAction(loadAction);
    connect(loadAction, &QAction::triggered, this, &Gui2048::showGameLoad);

    QAction *styleAction = new QAction("Game Style", this);
    gameMenu->addAction(styleAction);
    connect(styleAction, &QAction::triggered, this, &Gui2048::showGameStyle);

    QAction *exitAction = new QAction("Exit Game", this);
    gameMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &Gui2048::showGameExit);


    QMenu *rankMenu = menuBar->addMenu("Rank");

    QAction *ranklistAction = new QAction("Rank List", this);
    rankMenu->addAction(ranklistAction);
    connect(ranklistAction, &QAction::triggered, this, &Gui2048::showRankList);

    QAction *rankyouAction = new QAction("Your Rank", this);
    rankMenu->addAction(rankyouAction);
    connect(rankyouAction, &QAction::triggered, this, &Gui2048::showRankMy);

    QMenu *aboutMenu = menuBar->addMenu("About");

    QAction *authorAction = new QAction("Author", this);
    aboutMenu->addAction(authorAction);
    connect(authorAction, &QAction::triggered, this, &Gui2048::showaboutauthor);

    QAction *versionAction = new QAction("Version", this);
    aboutMenu->addAction(versionAction);
    connect(versionAction, &QAction::triggered, this, &Gui2048::showaboutversion);

    QAction *ruleAction = new QAction("Game Rule", this);
    aboutMenu->addAction(ruleAction);
    connect(ruleAction, &QAction::triggered, this, &Gui2048::showaboutrule);

    // Set the menu bar for the main window
    setMenuBar(menuBar);
}
void  Gui2048:: keyPressEvent(QKeyEvent *event){
    if(!iscontinue)
        return;

    if (event->key() == Qt::Key_Up) {
        // up
        diractiononce= 'a';

    } else if (event->key() == Qt::Key_Down) {
        // down
        diractiononce= 'd';

    }
    else if (event->key() == Qt::Key_Left) {
        // left
        diractiononce= 'w';

    }
    else if (event->key() == Qt::Key_Right) {
        // down
        diractiononce= 's';

    }
    else
        return;


    // else
    gameon();
    QWidget::keyPressEvent(event);
    update();
}
void Gui2048::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.setFont(QFont("HP Simplified Jpan",20,700,false));


    p.drawText(QPoint(40,60),"2048! Score: "+QString::number(game.getScore()));
    p.drawText(QPoint(40,100),"Current Player: "+QString::fromStdString(player.getName()));

    for(int j=0;j<4;j++){
        for(int i=0;i<4;i++){
            p.setPen(Qt::transparent);
            if(game.getBoard()[i][j]==0){
                p.setBrush(Qt::gray);
                p.drawRect(i*70+60,j*70+140,65,65);

            }
            else if (game.getBoard()[i][j]==2){
                p.setBrush(QColor(255,250,222,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));

                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 2)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==4) {
                p.setBrush(QColor(255,197,136,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 4)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==8) {
                p.setBrush(QColor(251,179,129,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 8)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==16) {
                p.setBrush(QColor(250,160,99,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 16)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==32) {
                p.setBrush(QColor(251,103,55,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 32)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==64) {
                p.setBrush(QColor(213,92,14,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 64)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==128) {
                p.setBrush(QColor(252,161,159,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 128)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==256) {
                p.setBrush(QColor(248,126,124,147));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 256)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==512) {
                p.setBrush(QColor(255,50,80,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 512)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==1024) {
                p.setBrush(QColor(188,25,22,255));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 1024)),QTextOption(Qt::AlignCenter));
            }
            else if (game.getBoard()[i][j]==2048) {
                p.setBrush(QColor(245,69,67,15));
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, 2048)),QTextOption(Qt::AlignCenter));
            }
            else{
                p.setBrush(Qt::darkBlue);
                p.drawRect(i*70+60,j*70+140,65,65);
                p.setPen(Qt::black);
                p.setFont(QFont("HP Simplified Jpan",12,700,false));
                p.drawText(QRectF(i*70+60,j*70+140,65,65),QString::fromStdString(styleoutput( setGameType, game.getBoard()[i][j])),QTextOption(Qt::AlignCenter));
            }


        }
    }
}

void Gui2048::gamestart(){
    iscontinue=true;
    game.changecontinue(false);
    setFocusPolicy(Qt::StrongFocus);
    update();
}
void Gui2048::gameon(){

    if(!game.gaming(diractiononce)){
        if(game.iswin()){
            showWinWindow();
        }
        else{
            showOverWindow();
        }
    }
    if(game.isover())
        showOverWindow();
    else if(game.iswin()&&!game.getwincontinue())
        showWinWindow();
        //the board is wait to show


}
void Gui2048::Gamebutton(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Game Concept");
    msgBox.setText(" There are some game functions you can choose!");
    msgBox.setInformativeText(" You can start a new game, \n Load previous game, \n Save the game, \n Or know how to play!\n");
    QPushButton *NewGame=msgBox.addButton(tr("New Game"),QMessageBox::AcceptRole);
    QPushButton *LoadGame=msgBox.addButton(tr("Load Game"),QMessageBox::AcceptRole);
    QPushButton *SaveGame=msgBox.addButton(tr("Save Game"),QMessageBox::AcceptRole);
    QPushButton *RuleGame=msgBox.addButton(tr("Help"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);

    msgBox.exec();
    if(msgBox.clickedButton()==NewGame){
        showGameNew();
    }
    else if(msgBox.clickedButton()==LoadGame){
        showGameLoad();
    }
    else if(msgBox.clickedButton()==SaveGame){
        showGameSave();
    }
    else if(msgBox.clickedButton()==RuleGame){
        showaboutrule();
    }

}

void Gui2048::showaboutauthor() {
    // Implement showing the About dialog here
    QMessageBox::about(this, "Author", "The Gunius Writer!!!    \n Written by Kejun LIU!   \n作者大大真是英俊帅气啊！！！ ");
}
void Gui2048::showaboutversion() {
    // Implement showing the About dialog here
    QMessageBox::about(this, "Version", "Current Version:    \n  Beta 1.0.1  \n Update diaglog: Equiped with basic 2048 game function with the game rule. \n Friendly GUI for the gamer has been showed. \n New style can be used to be more fun!\nThe game can be saved.\n上面三个是加分项（doge）\n语言问题很难在格式上解决，因此为全英界面，请见谅！");
}
void Gui2048::showaboutrule() {
    // Implement showing the About dialog here
    QMessageBox::about(this, "Game Rule", "Grid: The game is played on a 4x4 grid, making a total of 16 cells.\n\nInitial Tiles: At the start of the game, two tiles with the number 2 are placed randomly on the grid. These tiles can appear in any empty cell.\n\nTile Movement: The player can use the arrow keys (up, down, left, and right) to slide all the tiles on the grid. All tiles move as far as possible in the chosen direction, either merging with other tiles or stopping at the edge of the grid.\n\nTile Merging: When two tiles with the same number collide while moving, they merge into a single tile with double the value. For example, two tiles with the number 2 combine to form a tile with the number 4.\n\nScoring: Each time two tiles merge, the player earns points equal to the value of the resulting tile. For example, merging two tiles with the number 4 gives the player 4 points. The score increases with each successful merge.\n\nNew Tiles: After each move, a new tile with the number 2 or 4 is randomly generated and placed in an empty cell. The chance of getting a tile with the number 2 is higher compared to getting a tile with the number 4.\n\nWinning: The player wins the game when they successfully create a tile with the number 2048. However, the game doesn't end there, and players can continue to play and achieve higher scores.\n\nLosing: The player loses the game when there are no more empty cells on the grid and no possible moves left. If the player reaches this point, it signifies that the grid is completely filled with tiles, and there are no more opportunities for merging.\n\nStrategy: The game requires strategic thinking and planning to maximize tile merges and prevent the grid from filling up too quickly. It is essential to create larger tiles by merging smaller ones and to keep the highest-valued tiles in the corners or along one edge to free up space for further moves.\n\nHigh Score: The game keeps track of the player's score, and the objective is not only to reach 2048 but also to achieve the highest possible score by making optimal moves and combining tiles efficiently.\n\n Powered by ChatGPT. Good Luck! ");
}
void Gui2048::showGameSave(){
    if(!game.getIsload()){
        QMessageBox::information(this, "Attention", "The game has not been loaded before!   ");
        return;
    }
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Save");
    msgBox.setText("Ready to Save!");
    msgBox.setInformativeText("Do you want to save the game? \n");
    QPushButton *Save=msgBox.addButton(tr("Save"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);

    msgBox.exec();
    if(msgBox.clickedButton()==Save){
        game.record(player.getName());
        game.loadchange(false);
    }
}
void Gui2048::showGameExit(){
    this->close();

}
void Gui2048::showGameStyle(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Style");
    msgBox.setText("Choose your style!");
    msgBox.setInformativeText("The default style is normal. \n");
    QPushButton *Normal=msgBox.addButton(tr("Normal"),QMessageBox::AcceptRole);
    QPushButton *Ch=msgBox.addButton(tr("Chemistry"),QMessageBox::AcceptRole);
    QPushButton *TH=msgBox.addButton(tr("Three Body"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);
    msgBox.exec();
    if(msgBox.clickedButton()==Normal){
        setGameType=0;
    }
    else if(msgBox.clickedButton()==Ch){
        setGameType=1;
    }
    else if(msgBox.clickedButton()==TH){
        setGameType=2;
    }

}
void Gui2048::showGameLoad(){
    if(game.getIsload()){
        QMessageBox::information(this, "Attention", "The game has been loaded before!   ");
        return;
    }
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Load");
    msgBox.setText("Previous data has been ready to be loaded.");
    msgBox.setInformativeText("Do you want to load the game?");
    QPushButton *Load=msgBox.addButton(tr("Load"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);
    msgBox.exec();
    if(msgBox.clickedButton()==Load){
        game.load();
        player.setName(game.getCurrent_name());
        showGameStyle();
        gamestart();
    }

}
void Gui2048::showGameNew(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("New Game");
    msgBox.setText("Warning!!!");
    msgBox.setInformativeText("Do you want to start a new the game? \n Attention! Previous game record may be delated!!");
    QPushButton *Newgame=msgBox.addButton(tr("New Game"),QMessageBox::AcceptRole);
    QPushButton *Cancel=msgBox.addButton(tr("Cancel"),QMessageBox::RejectRole);
    msgBox.exec();
    if(msgBox.clickedButton()==Newgame){
        newNameGet();
        temp001.getname();
        showGameStyle();

        //write a board to record name
    }

}
void Gui2048::newNameGet(){
    temp001.show();
    temp001.exec();
    player.setName(temp001.getname());
    while(player.getName()==""){
        QMessageBox::warning(this, "Attention", "You have to input your name to star your game!   ");
        newNameGet();
    }


    game.loadchange(true);
    game.newgame();
    gamestart();
}

void Gui2048::showRankList(){
    std::string text="Ranking List:\n";
    for(int i=0;i<rank.getplayers().size();i++){
        text=text+rank.getplayers()[i].getName()+" "+std::to_string(rank.getplayers()[i].getScore())+"\n";
    }
    QString text2=QString::fromStdString(text);
    QMessageBox::information(this,"Rank List",text2);
}
void Gui2048::showRankMy(){
    if(!game.getIsload()){
        QMessageBox::information(this,"Your Rank","You have not loaded the game!");
        return;
    }
    std::string text=player.getName()+", Your Record:";
    bool ishave=false;
    for(int i=0;i<rank.getplayers().size();i++){
        if(player.getName()==rank.getplayers()[i].getName()){
            text=text+rank.getplayers()[i].getName()+" "+std::to_string(rank.getplayers()[i].getScore())+"\n";
            ishave=true;
        }
    }
    if(!ishave)
        text=text+" None Record\n";
    text=text+"Current gamescore:"+std::to_string(game.getScore());
    QString text2=QString::fromStdString(text);
    QMessageBox::information(this,"Your Rank",text2);
}
void Gui2048::showWinWindow(){
    //To do:justify what if it is a record
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("You Win!!!");
    msgBox.setText("You have won the game!");
    msgBox.setInformativeText("Continue the game or end a new game?");
    QPushButton *Endgame=msgBox.addButton(tr("End the Game"),QMessageBox::AcceptRole);
    QPushButton *Continue=msgBox.addButton(tr("Continue the Game"),QMessageBox::RejectRole);
    msgBox.exec();
    if(msgBox.clickedButton()==Endgame){
        //the record will be saved
        showOverWindow();
    }
    else if(msgBox.clickedButton()==Continue){
        //the record will be saved
        game.changecontinue(true);
    }

}
void Gui2048::showOverWindow(){
    std::string text="Game over! Current Scores: "+std::to_string(game.getScore())+"\nCurrent Player: "+player.getName();
    if(rank.getRecord() < game.getScore()){
        text=text+"\nNew record!" ;
    }
    QString text0=QString::fromStdString(text);
    player.setScore(game.getScore());
    rank.addPlayer(player);
    rank.sort();
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Game Over!!!");
    msgBox.setText(text0);
    msgBox.setInformativeText("Continue the game, exit the game or start a new game?");
    QPushButton *Newgame=msgBox.addButton(tr("New Game"),QMessageBox::AcceptRole);
    QPushButton *Exit=msgBox.addButton(tr("Exit Game"),QMessageBox::AcceptRole);
    msgBox.exec();
    showRankList();
    iscontinue=false;
    if(msgBox.clickedButton()==Newgame){
        //the record will be saved
        showGameNew();
    }
    else if(msgBox.clickedButton()==Exit){
        game.loadchange(false);
        this->close();
    }
}
void InputName::acceptone ()   {
    QString tempname=usernameLineEdit->text();
    tempName=tempname.toStdString();
    QDialog::accept();
    this->close();
}
InputName::InputName(QWidget* parent) : QDialog(parent){
    setWindowTitle("New Name Input");
    setFixedSize(300, 100);

    formLayout = new QFormLayout(this);

    usernameLineEdit = new QLineEdit(this);

    formLayout->addRow("Press your name here:", usernameLineEdit);

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    connect(okButton, &QPushButton::clicked, this,& InputName::acceptone);
    connect(cancelButton, &QPushButton::clicked, this,& InputName::reject);


    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    formLayout->addRow(buttonBox);

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui2048 w;
    w.show();
    return a.exec();
}
