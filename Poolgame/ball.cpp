#include "ball.h"
#include <iostream>

int p_balltype = 0;
ParentStr *m_Partent;
QMap<ParentStr *,Ball*>  childball;
int PosIndex=0;
int m_BallPos_int[5] = {0};
int BallNum =0;
bool BallArmFlag=0,CreatBallArmFlag = 0;
QVector2D White_pos;
QVector2D WhiteCue_vec;
double WhiteCue_ang;
QVector2D SpeedSetValue;
bool SpeedSetflag;
bool stageFlag;

void StageOneBall::translate(QVector2D vec) {
    m_pos += vec;
}

void StageOneBall::render(QPainter &painter) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);
}
