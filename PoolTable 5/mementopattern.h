#ifndef MEMENTOPATTERN_H
#define MEMENTOPATTERN_H

#include <vector>
#include "ball.h"
#include <QMap>
#include <QDebug>
#include "stage2ball.h"
#include "stage2factory.h"
/**Memento Pattern: Without violating encapsulation,
 * capture and externalize an object's internal state so
 * that the object can be restored to this state later.
 */

/*Flag - user:define mementoData  struct*/
struct mementoData
{
    QColor color;
    QVector2D pos;
    QVector2D vec;
    float mass;
    float radius;

};

// Memento part:Responsible for storing the internal state of the Originator object
class DataStatus
{
public:
    DataStatus(std::vector<Ball *> data ):m_SaveBalls(data){}

    void SetBallsStatus(std::vector<Ball *> data)
    {
       m_SaveBalls = data;
    }
/*Flag - user: Get Save Data*/
    std::vector<mementoData> SetstructValue(std::vector<Ball *> data)
    {
        std::vector<mementoData> m_struct;
        for(auto it = data.begin();it!=data.end();++it)
        {
            Ball * a = *it;
            mementoData m_mem;
            memset(&m_mem,0,sizeof(mementoData));
            m_mem.color = a->colour();
            m_mem.mass = a->mass();
            m_mem.pos = a->position();
            if(m_mem.color == Qt::white) m_mem.vec = QVector2D(0,0);
            else   m_mem.vec = a->velocity();
            m_mem.radius = a->radius();
        //    m_mem.strength =a->Strength();
            m_struct.push_back(m_mem);
            if(a == NULL) delete a;
        }


        return m_struct;
    }

    std::vector<Ball *> GetBallsStatus()
    {
        return m_SaveBalls;
    }

    std::vector<mementoData> m_SaveStruct;

private:
    std::vector<Ball *> m_SaveBalls;

};

//Originator:recorded the state of ball,Originator creates and stores states in Memento objects
class SaveDataStatus
{
public:

    void SetData(std::vector<Ball *> data)
    {
        m_SaveBalls = data;
    }

   std::vector<Ball *>  SetMemento(DataStatus *data)
    {
        m_SaveBalls = data->GetBallsStatus();
        return m_SaveBalls;
    }

    DataStatus *CreatDataBalls()
    {
        DataStatus * buf;
        buf = new DataStatus(m_SaveBalls);
        m_SaveStruct = buf->SetstructValue(m_SaveBalls);
        if(buf == NULL) delete buf;
        return new DataStatus(m_SaveBalls);

    }

    std::vector<mementoData> get_m_SaveStruct()
    {
        return m_SaveStruct;
    }

    std::vector<mementoData> m_SaveStruct;
private:
    std::vector<Ball *> m_SaveBalls;

};

/**Caretaker part: Responsible for saving the memento,
 * can not operate or check the contents of the memento.
 * responsible to restore object state from Memento
 */
class ResetDataStatus
{
public:
    ResetDataStatus(SaveDataStatus * Dta):m_SaveDataStatus(Dta) {}

    /*Flag - user: Save Data*/
    void Save()
    {
        m_DataVector.push_back(m_SaveDataStatus->CreatDataBalls());
    }

    /*Flag - user:Pop Data*/
    std::vector<Ball *>  Undo()
    {
        DataStatus * buf = m_DataVector.back();
        std::vector<Ball *> balls_Get = m_SaveDataStatus->SetMemento(buf);
        m_structData = m_SaveDataStatus->m_SaveStruct;
        m_DataVector.pop_back();
        return balls_Get;
    }

    std::vector<mementoData> UndoStruct()
    {
        return m_structData;
    }

    int VectorSize() {return m_DataVector.size();}

    /*Flag - user: Return Get Ball Vector*/
    std::vector<Ball *> ballGetValue(std::vector<mementoData> m_struct,std::vector<Ball *> m_point)
    {
            int i =0;
            for(auto it = m_struct.begin();it!=m_struct.end();++it)
            {
                int j =0;
                for(auto ita = m_point.begin();ita!= m_point.end();++ita)
                {
                    Ball * a = * ita;
                    if(i == j)
                    {
                        a->setColour(it->color);
                        a->setMass(it->mass);
                        a->setPosition(it->pos);
                        a->setRadius(it->radius);
                        a->setVelocity(it->vec);

                    }
                    j++;
                }
                i++;
            }
            return m_point;
    }


    /*Flag - user: Reset Init Status Get Ball Vector*/
    std::vector<Ball *> ballGetValue(CompositeBall * b,std::vector<mementoData> m_struct,std::vector<Ball *> m_point)
    {

        CompositeBall * EightBall; EightBall =new CompositeBall;
        CompositeBall * SevenBall; SevenBall =new CompositeBall;
            int _i=0;
            for(auto it = m_struct.begin();it!=m_struct.end();++it)
            {
                int _j =0;
                for(auto ita = m_point.begin();ita!= m_point.end();++ita)
                {
                    if(_i == _j)
                    {
                        Ball * a = * ita;
                        a->setColour(it->color);
                        a->setMass(it->mass);
                        a->setPosition(it->pos);
                        a->setRadius(it->radius);
                        a->setVelocity(it->vec);
                    //    a->setStrength(it->strength);
                    }
                    _j++;
                }
                if((_i+1) >= m_point.size())
                 {
                      Dialog* c;
                     if((_i+1)==m_point.size())
                     {
                         b->setColour(it->color);
                         b->setMass(it->mass);
                         b->setPosition(it->pos);
                         b->setRadius(it->radius);
                         b->setVelocity(it->vec);
                      //   b->setStrength(10000);
                     }else if(_i>=4&&_i<=6)
                     {
                         Ball * a  = Stage2Factory(c).makeBall(it->color,it->pos,it->vec,it->mass,it->radius,100000);
                         b->addBall(a);
                    }else if (_i == 7)
                     {
                         SevenBall->setColour(it->color);
                         SevenBall->setMass(it->mass);
                         SevenBall->setPosition(it->pos);
                         SevenBall->setRadius(it->radius);
                         SevenBall->setVelocity(it->vec);
                         SevenBall->setStrength(10000);
                     }
                     else if( _i==8)
                     {
                         EightBall->setColour(it->color);
                         EightBall->setMass(it->mass);
                         EightBall->setPosition(it->pos);
                         EightBall->setRadius(it->radius);
                         EightBall->setVelocity(it->vec);
                         EightBall->setStrength(10000);
                     }else
                     {
                         Ball * b_9  = Stage2Factory(c).makeBall(it->color,it->pos,it->vec,it->mass,it->radius,100000);
                         EightBall->addBall(b_9);
                         SevenBall->addBall(EightBall);
                         b->addBall(SevenBall);
                     }
                     if(c == NULL) delete c;
                 }
                _i++;
            }
            int c = 0;
            for(auto it = m_point.begin();it!= m_point.end();++it)
            {
                    int a = m_point.size();
                    if(c+1 == a)
                    {
                        Ball * a = b;
                        m_point.erase(it);
                        m_point.push_back(a);
                    }
                    c++;
            }
            return m_point;
    }

    std::vector<mementoData> m_structData;
private:
     SaveDataStatus *m_SaveDataStatus;
     std::vector<DataStatus *> m_DataVector;
};
#endif // MEMENTOPATTERN_H
