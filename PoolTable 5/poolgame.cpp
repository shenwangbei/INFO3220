#include "poolgame.h"
#include <cmath>
#include <QDebug>


PoolGame::~PoolGame()
{
    for(Ball * b: m_balls)
    {
        delete b;
    }
    delete m_table;
}


void PoolGame::MementoInit()
{
    m_SaveDataStatus = new SaveDataStatus;
    m_ResetDataStatus = new ResetDataStatus(m_SaveDataStatus);
}

std::vector<std::vector<mementoData>> m_Mem_vector;

void PoolGame::simulateTimeStep(float timeStep)
{
    ChangeInPoolGame totalChange;
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        totalChange = totalChange.merge(m_table->ballCollision(b));
    }
    //a collision between each possible pair of balls
    for(size_t i = 0; i < m_balls.size();++i)
    {
        for(size_t j = i+1;j < m_balls.size();++j)
        {
            if(m_balls[i]->collidesWith(m_balls[j]))
            {
                totalChange = totalChange.merge(collide(m_balls[i],m_balls[j]));
            }
        }
    }

    for(Ball * e:totalChange.m_ballsToRemove)
    {
        m_balls.erase(std::find(m_balls.begin(),m_balls.end(),e));
    }

    for(Ball * a:totalChange.m_ballsToAdd)
    {
        m_balls.push_back(a);
    }
    QVector2D white_pos;
    if(Key_R_Flag)
    {
        if(m_ResetDataStatus->VectorSize() == 0) {qDebug()<<"Vector is Null !";}
        else  {
            QVector2D white_vec;
            bool white_falg = 0 ;
            for(auto it =m_balls.begin();it!=m_balls.end();++it)
            {
                Ball * balla = *it;
                if(balla->colour() == "white")
                {
                    white_vec = balla->velocity();
                    white_falg = 1;
                    white_pos = balla->position();
                }
            }
            if(white_falg==1&&white_vec.length()<0.005)
            {
                  std::vector<Ball *> m_Buf_Balls =  m_ResetDataStatus->Undo();
                  m_balls = m_Buf_Balls;
                  m_ResetDataStatus->ballGetValue(m_Mem_vector.back(),m_balls);
                  m_Mem_vector.pop_back();
                /*  for(auto it =m_balls.begin();it!=m_balls.end();++it)
                  {
                      Ball * balla = *it;
                      if(balla->colour() == "white")
                      {
                          white_pos = balla->position();
                          qDebug()<<"Reset"<<white_pos.x()<<white_pos.y();
                      }
                  }*/
                  qDebug()<<"white-vec = 0";
            }else if (white_falg == 0|| white_vec.length()>0.005)
            {
                 m_balls = Init_balls;
                 CompositeBall * b;
                 b = new CompositeBall;
                 m_balls = m_ResetDataStatus->ballGetValue(b,Init_data,m_balls);
                 qDebug()<<"white-vec = 1";
                 if(b == NULL) delete b;
            }
        }
       Key_R_Flag = 0;
      return;
    }

    for(Ball * b: m_balls)
    {
        if(b->colour()==Qt::white) white_pos = b->position();
        if(b->MousePressFlag ==1 )
        {
            qDebug()<<"Save"<<white_pos.x()<<white_pos.y()<<m_Mem_vector.size();
            m_SaveDataStatus->SetData(m_balls);
            m_ResetDataStatus->Save();
          /*  std::vector<mementoData> M_Buf = m_SaveDataStatus->m_SaveStruct;
            m_Mem_vector.push_back(M_Buf);*/
            m_Mem_vector.push_back(m_SaveDataStatus->m_SaveStruct);
            b->MousePressFlag = 0;
            return;
        }

        b->move(timeStep);

        //apply friction
        b->changeVelocity(-m_table->friction()*timeStep*b->velocity());

        //if moving less than 5 pixels per second just stop
        if(b->velocity().length()<5)
            b->setVelocity(QVector2D(0,0));

        if(b->colour()==Qt::white)  DisNum =  b->BatNum;        
    }
}

void PoolGame::draw(QPainter &p)
{
    m_table->draw(p);
    for(Ball * b: m_balls)
    {
        b->draw(p);
    }
}

ChangeInPoolGame PoolGame::collide(Ball *b1, Ball *b2)
{
    //using the code provided for the collision mechanics

     //calculate their mass ratio
     float mR = b2->mass() / b1->mass();

     //calculate the axis of collision
     QVector2D collisionVector = b2->position() - b1->position();
     collisionVector.normalize();

    //the proportion of each balls velocity along the axis of collision
     double vA = QVector2D::dotProduct(collisionVector, b1->velocity());
     double vB = QVector2D::dotProduct(collisionVector, b2->velocity());
     //the balls are moving away from each other so do nothing
     if (vA <= 0 && vB >= 0) {
      return ChangeInPoolGame();
     }

     //The velocity of each ball after a collision can be found by solving the quadratic equation
     //given by equating momentum and energy before and after the collision and finding the velocities
     //that satisfy this
     //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
     //first we find the discriminant
     double a = -(mR + 1);
     double b = 2 * (mR * vB + vA);
     double c = -((mR - 1) * vB * vB + 2 * vA * vB);
     double discriminant = sqrt(b * b - 4 * a * c);
     double root = (-b + discriminant)/(2 * a);
     //only one of the roots is the solution, the other pertains to the current velocities
     if (root - vB < 0.01) {
       root = (-b - discriminant)/(2 * a);
     }


     //The resulting changes in velocity for ball A and B
     ChangeInPoolGame changeFromB1 = b1->changeVelocity(mR * (vB - root) * collisionVector);
     ChangeInPoolGame changeFromB2 = b2->changeVelocity((root - vB) * collisionVector);
     return changeFromB1.merge(changeFromB2);
}
