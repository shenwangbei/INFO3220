#pragma once
#include <QDialog>
#include "ball.h"
#include "game.h"
#include "ballarm.h"
#include <QMouseEvent>
#include <QLabel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Game* game, QWidget *parent = 0);
    ~Dialog();

protected:
    /**
     * @brief paintEvent - called whenever window repainting is requested
     */
    void paintEvent(QPaintEvent *);
    /**
     * @brief mousePressEvent - If you left-click and the white ball stops moving, set the mouse position to the end of the bat
     */
    void mousePressEvent(QMouseEvent * );
    /**
     * @brief mouseMoveEvent - If the mouse is dragged and the white ball stops moving, set the mouse position to the end of the cue and display label)
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief mouseReleaseEvent - mouse relase, set strength of cue
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    /**
     * @brief nextAnim - move the objects and perform collision events
     */
    void nextAnim();
    /**
     * @brief tryRender - draw the objects to screen
     */
    void tryRender();

    /*Display Frist White Cue Info*/
    void DisplayCueInfo();

    /**
     * @brief SpeedSeting - The setting of the batting speed is 10:1 in proportion to the coordinate position. If the mouse is not dragged, the speed is 0.
     */
    void SpeedSeting();

private:
    /**
     * @brief aTimer - timer for calling nextAnim in intervals
     */
    QTimer* aTimer = nullptr;
    /**
     * @brief dTimer - timer for calling tryRender in intervals
     */
    QTimer* dTimer = nullptr;
    /**
     * @brief ui our drawable ui
     */
    Ui::Dialog *ui;
    /**
     * @brief m_game - our game object to be played
     */
    Game* m_game = nullptr;

    /**
     * @brief m_ballarm - pointer of cue
     */
    ballarm * m_ballarm ;
    /**
     * @brief startpos - cue the start position, endpos - cue the end position
     */
    QVector2D startpos,endpos;
    /**
     * @brief m_lable - the lable of word
     */
    QLabel  * m_lable;
};

