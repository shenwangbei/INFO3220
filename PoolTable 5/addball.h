#ifndef ADDBALL_H
#define ADDBALL_H

#include <QTextLine>
#include <QLabel>
#include "stage2factory.h"
#include <QVector2D>
#include <QColor>
#include "dialog.h"
#include <QLineEdit>


class AddBall
{
public:
    /*set the default parameter of ball and add the ball to table*/
    AddBall(Dialog * partent);

    /*create a user interface*/
    void UiInit();

    /*add ball that player set, include color, pos, speed, mas,strength and radius*/
    Ball * Addm_ball(QColor color,QVector2D pos,QVector2D vec,int mass,int strength,int radius);

    /*set postions of each parameter in the User interface*/
    QLineEdit * color,*pos_x,*pos_y,*vec_x,*vec_y,*mass,*strength,*radius;

    /*set the input type*/
    QLabel *color_lable,*pos_x_lable,*pos_y_lable,*vec_x_lable,*vec_y_lable,*mass_lable,*strength_lable,*radius_lable;

    /*add ball that player set, include color, pos, speed, mas,strength and radius*/
    Ball * Addm_ball();

    Stage2Factory * factory;
};

#endif // ADDBALL_H
