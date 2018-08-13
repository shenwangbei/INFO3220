#include <QApplication>

#include "dialog.h"
#include "initializer.h"
#include "poolgame.h"

#include <QDebug>

std::vector<mementoData> m_struct;
std::vector<mementoData> structValue(std::vector<Ball *> data)
{
    for(auto it = data.begin();it!=data.end();++it)
    {
        Ball * a = *it;
        mementoData m_mem;
        m_mem.color = a->colour();
        m_mem.mass = a->mass();
        m_mem.pos = a->position();
        if(m_mem.color == Qt::white) m_mem.vec = QVector2D(0,0);
        else   m_mem.vec = a->velocity();
        m_mem.radius = a->radius();
        m_struct.push_back(m_mem);
        std::vector<Ball *> m_count = a->get_m_containedBalls();
        if(m_count.size()>0) structValue(m_count);
    }
    return m_struct;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    Initializer * m_init;
    m_init = new Initializer();
    PoolGame* game = m_init->createPoolgame("/Users/shen/Desktop/config.json",&w);

    //if the returned game is a nullptr the json file couldn't be found or was invalid
    if(!game) return a.exec();
    w.stage3flag = m_init->stage3flag;
    w.m_volum = m_init->m_volum;
    w.m_path = m_init->m_path;
    game->Init_balls = m_init->get_Initballs();
    game->Init_data  = structValue(game->Init_balls);
    w.m_mode = m_init->m_mode;
    w.show();
    w.start(game);

    return a.exec();

}
