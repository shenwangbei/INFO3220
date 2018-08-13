#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>
#include "poolgame.h"
#include "backgroundmusic.h"
#include <QSlider>
#include "displaylable.h"
#include <QPushButton>
#include <QKeyEvent>

/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    /**
     * @brief starts the simulation
     */
    void start(PoolGame * game);

    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent just emits the mousePressed signal
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits the mouseMoved signal
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits a mouseReleased signal
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);


    int m_volum;      //Flag - user: define volum
    QString m_path;   //Flag - user: define BGM path
    int m_mode;       //Flag - user: define PlayList Playmode
    bool stage3flag;  //Flag - user: define stage3 Flag

    Musics * m_musics;

    DisplayLable * lable;
    void DisBatNum();  //Flag - user: Dislay Bating Num
    void keyPressEvent(QKeyEvent * ); //Flag - user: Keybord Event

    void stage3Init();  //Flag - user:stage3 Init

    std::vector<Ball *> Init_balls;

signals:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);

public slots:
    void runSimulationStep();
    void SetBGMVolum(int volum); //Flag - user: BGM volum seting slot
    void ButtonAddball();  //Flag - user:Button Slot

    bool FoucsClicked();
private:
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
    QSlider * m_VolumSlider;  //Flag - user:Slider Point
    QPushButton * m_Button;   //Flag - user:Button Point
    QPushButton * m_Focus;   //Flag-user:set focus of mouse
};

#endif // DIALOG_H
