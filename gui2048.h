#ifndef GUI2048_H
#define GUI2048_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include "../core2048.hpp"
//creat a namespace for further use.
QT_BEGIN_NAMESPACE
namespace Ui { class Gui2048; }
QT_END_NAMESPACE
class InputName: public QDialog{
    Q_OBJECT
public:
    InputName(QWidget* parent = nullptr);
    std::string getname(){
        return tempName;
    }
private slots:
    void acceptone() ;
private:
    bool isset=false;
    QString tempname;
    std::string tempName;
    QLineEdit* usernameLineEdit;
    QFormLayout* formLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QDialogButtonBox* buttonBox;

};
class Gui2048 : public QMainWindow
{
    Q_OBJECT

public:
    Gui2048(QWidget *parent = nullptr);
    ~Gui2048();
    void gameon();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void gamestart();
private slots:
    void showaboutauthor();
    void showaboutversion();
    void showaboutrule();
    void showGameSave();
    void showGameExit();
    void showGameLoad();
    void showGameNew();
    void showRankList();
    void showRankMy();
    void showWinWindow();
    void showOverWindow();
    void newNameGet();
    void Gamebutton();
    void showGameStyle();



private:
    Game2048 game;
    Player player;
    Rank rank;
    InputName temp001;
    Ui::Gui2048 *ui;
    void creatmenu();
    void maingame();
    std::string tempName;
    bool iscontinue=true;
    char diractiononce=false;
    //To do:change the print board if can!
    int setGameType=0;
};




#endif // GUI2048_H
