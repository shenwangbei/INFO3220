#include "game.h"
#include "utils.h"

#include <QJsonArray>
#include <stdexcept>
#include <cmath>
#include <QDebug>
#include <iostream>
#include <QTime>

Game::~Game() {
    // cleanup ya boi
    for (auto b : *m_balls) delete b;
    delete m_balls;
    delete m_table;
}

void Game::render(QPainter &painter) const {
    // table is rendered first, as its the lowest
    m_table->render(painter);
    // then render all the balls
    for (Ball* b : *m_balls) b->render(painter);
}



bool  PocketEatingBall(QVector2D pos,double ballrad)
{
   bool status;
   QVector<CompontPocket *> Buf_m_pockets = p_CompositePockets.getvetor();
   //  for (auto it =p_CompositePockets.getvetor().begin();it!= p_CompositePockets.getvetor().end();it++)
   for (auto it =Buf_m_pockets.begin();it!= Buf_m_pockets.end();it++)
         {
           CompontPocket * Buf_Compont = *it;
           pocket  a_pocket =  Buf_Compont->Output();
           double Log2 = a_pocket.radius*a_pocket.radius-((a_pocket.x-pos.x())*(a_pocket.x-pos.x())+(a_pocket.y-pos.y())*(a_pocket.y-pos.y()));
           double rad2 = ballrad*ballrad;
           double value = Log2-rad2;
           if(value<0) {status = 0;}
           else  { status = 1; break;}
        }
    return status;
}

void Game::ballsDelItem()
{   
    int i =0,a=0;
    if(j == 0) return;
    for(a = 0;a<j;++a)
    {
        for (std::vector<Ball *>::iterator it = m_balls->begin();it!=m_balls->end();)
            {
                 Ball * DelBall = *it;
                if(i== buf[a])
                {
                    DelBallbuf[a][0] = DelBall->getBalltype();
                    DelBallbuf[a][1] = DelBall->getBalltypeIndex();
                    it =  m_balls->erase(it);
                 // qDebug()<<"Del A Ball"<<m_balls->size()<<DelBallbuf[a][0]<<DelBallbuf[a][1];
                }
                else    ++it;
                ++i;
            }
    }
    NextBallsShow(j);
}


void Game::NextBallsShow(int Num)
{
    for(int a = 0;a<Num;++a)
    {
        for (QMap<ParentStr *,Ball *>::iterator it = childball.begin();it!=childball.end();++it)
        {
            if(it.key()->balltype==DelBallbuf[a][0]&&it.key()->ballindex==DelBallbuf[a][1])
            {
               // qDebug()<<"No instert"<<m_balls->size();
                m_balls->push_back(it.value());
              //  qDebug()<<"Instert "<<m_balls->size();
            }
        }
    }
}

void Game::animate(double dt) {
    // (test) collide the ball with each other ball exactly once
    // to achieve this, balls only check collisions with balls "after them"
       if(j == 0) {}   else {ballsDelItem();}
       int i = 0;   j=0;  buf[1] = {0};
       int whileBall =0;
       for (auto it = m_balls->begin(); it != m_balls->end(); ++it)
       {
         Ball* ballA = *it;

        if(ballA->getBallColor() == Qt::white&&ballA->getBalltype() == 0) //Traverse to get the first white ball
        {
            if(whileBall == 0)
            {
                White_pos.setX( ballA->getPosition().x());
                White_pos.setY( ballA->getPosition().y());  //get white ball position
                WhiteCue_vec.setX(ballA->getVelocity().x());
                WhiteCue_vec.setY(ballA->getVelocity().y());  //get the speed of white ball
                if(SpeedSetflag){ ballA->changeVelocity(SpeedSetValue);
                    /*    ballA->SetVecZero();*/
                    /*    ballA->SetVecValue(SpeedSetValue);*/
                    SpeedSetValue.setX(0);SpeedSetValue.setY(0);  //Speed Seting clear
                    SpeedSetflag = 0; BallArmFlag = 0;}
            }
            whileBall++;
        }
        /*correct ball velocity if colliding with table */
            resolveCollision(m_table, ballA);
        /* check collision with all later balls*/
        for (auto nestedIt = it + 1; nestedIt != m_balls->end(); ++nestedIt) {
            Ball* ballB = *nestedIt;
            resolveCollision(ballA, ballB);
        }

        /*move ball due to speed*/
        ballA->translate(ballA->getVelocity() * dt);
        /* apply friction */
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);
        if(stageFlag)  //stage1 judgment
        {
            /*The ball is contained in the pocket or the ball is destroyed*/
        if(PocketEatingBall(ballA->getPosition(),ballA->getRadius())||EnergyCalculation(ballA)) { buf[j] = i;     j++;};
        ++i;
        }
   }
    if(stageFlag) BallVecCalcculation();
}

void Game::resolveCollision(const Table* table, Ball* ball) {
    QVector2D bPos = ball->getPosition();

    // resulting multiplicity of direction. If a component is set to -1, it
    // will flip the velocity's corresponding component
    QVector2D vChange(1,1);

    // ball is beyond left side of table's bounds
    if (bPos.x() - ball->getRadius() <= table->getX()) {
        // flip velocity if wrong dir
        if (ball->getVelocity().x() <= 0) vChange.setX(-1);
    // ball is beyond right side of table's bounds
    } else if (bPos.x() + ball->getRadius() >= table->getX() + table->getWidth()) {
        // flip velocity if wrong dir
        if (ball->getVelocity().x() >= 0) vChange.setX(-1);
    }
    // ball is above top of the table's bounds
    if (bPos.y() - ball->getRadius() <= table->getY()) {
        // flip iff we're travelling in the wrong dir
        if (ball->getVelocity().y() <= 0) vChange.setY(-1);
    // ball is beyond bottom of table's bounds
    } else if (bPos.y() + ball->getRadius() >= table->getY() + table->getHeight()) {
        // if we're moving down (we want to let the ball bounce up if its heading back)
        if (ball->getVelocity().y() >= 0) vChange.setY(-1);
    }

    ball->multiplyVelocity(vChange);
}
QVector2D changeVec;
void Game::resolveCollision(Ball* ballA, Ball* ballB) {
    // SOURCE : ASSIGNMENT SPEC

    // if not colliding (distance is larger than radii)
    QVector2D collisionVector = ballB->getPosition() - ballA->getPosition();
    if (collisionVector.length() > ballA->getRadius() + ballB->getRadius()) return;
    collisionVector.normalize();

    float mr = ballB->getMass() / ballA->getMass();
    double pa = QVector2D::dotProduct(collisionVector, ballA->getVelocity());
    double pb = QVector2D::dotProduct(collisionVector, ballB->getVelocity());

    if (pa <= 0 && pb >= 0) return;

    double a = -(mr + 1);
    double b = 2*(mr * pb + pa);
    double c = -((mr - 1)*pb*pb + 2*pa*pb);
    double disc = sqrt(b*b - 4*a*c);
    double root = (-b + disc)/(2*a);
    if (root - pb < 0.01) {
        root = (-b - disc)/(2*a);
    }
    QVector2D bufball = ballA->getVelocity();
    ballA->changeVelocity(mr * (pb - root) * collisionVector);
    ballB->changeVelocity((root-pb) * collisionVector);

    changeVec = mr * (pb - root) * collisionVector;
    QVector2D buf =mr * (pb - root) * collisionVector + bufball;

    double ang = buf.y()/buf.x();
    WhiteCue_ang = atan(ang)*180/3.14;
}

bool Game::EnergyCalculation(Ball* ballA)  //Collision energy calculation
{
    bool status;
    float ballMass  = ballA->getMass();
    float ballStrength = ballA->getstrength();
    float ballRadius  = ballA->getRadius();
    QVector2D preCollisionVelocity  = ballA->getVelocity()+=changeVec;
    QVector2D deltaV = changeVec;
    float energyOfCollision = ballMass*deltaV.lengthSquared();  //Energy formula
//    qDebug()<<energyOfCollision << deltaV.lengthSquared()<<changeVec.x()<<changeVec.y();
    int balltype = ballA->getBalltype();
    int ballIndex = ballA->getBalltypeIndex();
    int numComponentBalls = 0;
    /*Get the number of sub-balls in the current ball*/
    for(QMap<ParentStr *,Ball *>::iterator it = childball.begin();it!=childball.end();++it)
    {
        Ball * componentBall = *it;
        if(componentBall->getBalltypeIndex() == balltype && componentBall->getBalltypeIndex() == ballIndex)
        {
            numComponentBalls++;
        }
    }
    /* if strength smaller than energy of collision*/
    if(ballStrength<energyOfCollision)
    {
        float energyPerBall = energyOfCollision/numComponentBalls;//the energy of sub ball
        deltaV.normalize();
        QVector2D pointOfCollision((-deltaV)*ballRadius);
        //for each component ball
        for(QMap<ParentStr *,Ball *>::iterator it = childball.begin();it!=childball.end();++it)
        {
            Ball * componentBall = *it;
            if(componentBall->getBalltypeIndex() == balltype && componentBall->getBalltypeIndex() == ballIndex)
            {
                QVector2D buf = componentBall->getPosition()-pointOfCollision;
                buf.normalize();
                QVector2D componentBallVelocity = preCollisionVelocity + sqrt(energyPerBall/componentBall->getMass())*buf; //子球速度的计算
                componentBall->changeVelocity(componentBallVelocity);  //set the speed of subball
            }
        }
        status = 1;
    }else status =0;
    return status;
}

void Game::BallVecCalcculation()
{  
    for (auto it = m_balls->begin(); it != m_balls->end(); ++it) {
        Ball* ballA = *it;

        if(ballA->getBallColor() == Qt::white&&ballA->getBalltype() == 0)
        {
          if(ballA->getVelocity().x()<0.001&&ballA->getVelocity().y()<0.001)
          {
             // qDebug()<<"White Stop!";
              CreatBallArmFlag =1;
          }else
          {
             // qDebug()<<"White Moving";
          }
        }
   }

}

