
#include "gamebuilder.h"
#include "game.h"
#include <iostream>
#include <QJsonArray>
#include <QDebug>
StageOneBuilder::~StageOneBuilder() {
    // delete state if building not collected...
    if (m_buildingTable != nullptr) delete m_buildingTable;
    if (m_buildingBalls != nullptr) {
        for (Ball* b : *m_buildingBalls) delete b;
        delete m_buildingBalls;
    }
}

void StageOneBuilder::addBall(QJsonObject &ballData) {
    // if we haven't already started building
    if (m_buildingBalls == nullptr) {
        m_buildingBalls = new std::vector<Ball*>();
    }


    if(p_balltype == 0)  //First level ball into ball collection
    {
         m_buildingBalls->push_back(m_factory->makeBall(ballData));
    }else {  //Set the properties of all balls after the second level
             m_Partent = new ParentStr;
             m_Partent->balltype = p_balltype -1;
             m_Partent->ballindex =m_BallPos_int[p_balltype-1];
             Ball * pBall = m_factory->makeBall(ballData);
             childball.insert(m_Partent,pBall);  //Put the ball after the second level into the ball collection
          }
   // qDebug()<<p_balltype<<m_BallPos_int[p_balltype];
}

void StageOneBuilder::addTable(QJsonObject &tableData) {
    // ensure that we haven't already created another table
    if (m_buildingTable != nullptr) throw std::invalid_argument("table created twice");
    m_buildingTable = m_factory->makeTable(tableData);
}

Game* StageOneBuilder::getResult() {
    // no-one called addBall
    if (m_buildingBalls == nullptr) {
        // soft fail
        std::cerr << "warning! pool game without balls created...\n";
        m_buildingBalls = new std::vector<Ball*>();
    }
    // likewise for table
    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }

    Game* retGame = new Game(m_buildingBalls, m_buildingTable);
    // need to reset for when we build next
    m_buildingBalls = nullptr;
    m_buildingTable = nullptr;
    return retGame;
}

void GameDirector::CreatBall(QJsonArray ballData)  //crete ball
{
       for (const auto& item : ballData)
           {
            //   PosIndex ++;
               m_BallPos_int[p_balltype] = PosIndex;  //At the same level, the last recorded maximum value
               QJsonObject t = item.toObject();
               QJsonArray  t_Arry =t.value("balls").toArray();
               if(!t_Arry.count())   { m_builder->addBall(t);}
              else
               {
                   m_BallPos_int[p_balltype] = PosIndex;
                   m_builder->addBall(t);
                   p_balltype ++;
                   PosIndex =m_BallPos_int[p_balltype];
                   CreatBall(t_Arry);  //Recursively find each level of ball
               }
                PosIndex ++;
                BallNum ++;
                m_BallPos_int[p_balltype] = PosIndex;
           }

       if(p_balltype>0)    p_balltype --;    else ;  //Every time you quit, the grade is reduced by one and goes back to the previous level
        PosIndex = m_BallPos_int[p_balltype];  //Get the position of the last ball on the last level
}

Game* GameDirector::createGame() {
    // construct our table
    QJsonObject tableData = m_conf->value("table").toObject();
    m_builder->addTable(tableData);

    // for each of our balls, construct them
    QJsonArray ballData = m_conf->value("balls").toArray();
    if(!stageFlag)
    {
        for (const auto& item : ballData)
        {
            QJsonObject t = item.toObject();
            m_builder->addBall(t);
        }
    }else  CreatBall(ballData);
    return m_builder->getResult();
}
