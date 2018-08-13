#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include "utils.h"
#include <QDebug>
#include <stdio.h>
#include<cmath>
Dialog::Dialog(Game *game, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_game(game)
{
     ui->setupUi(this);
     m_ballarm = new UseBallarm();
     m_lable = new QLabel(this);
    // for animating (i.e. movement, collision) every animFrameMS
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(nextAnim()));
    aTimer->start(animFrameMS);

    // for drawing every drawFrameMS milliseconds
    dTimer = new QTimer(this);
    connect(dTimer, SIGNAL(timeout()), this, SLOT(tryRender()));
    dTimer->start(drawFrameMS);

    // set the window size to be at least the table size
    this->resize(game->getMinimumWidth(), game->getMinimumHeight());
}



Dialog::~Dialog()
{
    delete aTimer;
    delete dTimer;
    delete m_game;
    delete ui;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_game->animate(1.0/(double)animFrameMS);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_game->render(painter);
    p_CompositePockets.render(painter);
    if(CreatBallArmFlag)
    {
        if(!BallArmFlag) ;
        else   m_ballarm->render(painter,White_pos,endpos);
    }
}

bool Mousemoveflag = 0;
void Dialog::mousePressEvent(QMouseEvent * e)
{
    BallArmFlag =1;
    if(e->button()==Qt::LeftButton&&CreatBallArmFlag)
    {
        endpos.setX(White_pos.x());
        endpos.setY(White_pos.y());
    }
        Mousemoveflag = 0;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{ 
       Mousemoveflag =1;
       BallArmFlag =1;
        if(event->button() != Qt::RightButton||CreatBallArmFlag)
        {
            endpos.setX(event->x());
            endpos.setY(event->y());
        }
        if(stageFlag)
        {
            m_lable->show();
            DisplayCueInfo();
        }

}

void Dialog::DisplayCueInfo()
{
    m_lable->setGeometry(endpos.x(),endpos.y(),150,15);
    double vec = WhiteCue_vec.x()*WhiteCue_vec.x()+WhiteCue_vec.y()*WhiteCue_vec.y();
    char Info[24];
    sprintf(Info,"%0.2f/%0.2f",sqrt(vec),WhiteCue_ang);
    m_lable->setText(QString(Info));
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton&&stageFlag)
    {
        m_lable->hide();
        if(CreatBallArmFlag&&BallArmFlag) SpeedSeting();
        SpeedSetflag = 1;
        CreatBallArmFlag =0 ;
    }
}

void Dialog::SpeedSeting()
{
    if(BallArmFlag&&Mousemoveflag)
    {
        SpeedSetValue.setX((endpos.x()-White_pos.x())/10);
        SpeedSetValue.setY((endpos.y()-White_pos.y())/10);
    }
}

