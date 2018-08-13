#pragma once

#include <QColor>
#include <QPainter>
#include <QVector2D>
#include <QPen>


/*Adapter Design Pattern*/

//target:ballarm The underlying interface, providing adapter interface, do not implement
class ballarm
{
public:
    virtual void render(QPainter& painter ,QVector2D m_startpos,QVector2D m_endpos) = 0;
};

//adaptee:Adapting elements, providing adapting elements, and implementing elements need to be specifically described
class ColorBallarm
{
public:
    void DrawBallArm(QPainter& painter ,QVector2D m_startpos,QVector2D m_endpos)
    {
        QPen pen;
        pen.setColor(Qt::white); //white line
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(m_startpos.toPointF(),m_endpos.toPointF());  //draw line
    }
};
//adaptor: inheriting the underlying adapter interface, containing the ColorBallarm class as a separate adapter element
class UseBallarm: public ballarm
{
public:
    UseBallarm():m_ColorBallarm(new ColorBallarm) {}
    ~UseBallarm();
    void render(QPainter &painter, QVector2D m_startpos, QVector2D m_endpos)
    {
        m_ColorBallarm->DrawBallArm(painter,m_startpos,m_endpos);
    }
private:
    ColorBallarm * m_ColorBallarm;
};
