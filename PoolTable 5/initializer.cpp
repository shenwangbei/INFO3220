#include "initializer.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "stage1factory.h"
#include "stage2factory.h"
#include "gamebuilder.h"

class Dialog;

QJsonObject jsonFromFile(const std::string &configFilePath)
{
    std::ifstream configFile(configFilePath);
    if(!configFile.good())
    {
        std::cout << "could not open \"" << configFilePath <<"\"" <<std::endl;
        return QJsonObject();
    }

    std::stringstream ss;
    //associate the read buffer to the stringstream, so now string stream will use that buffer
    ss << configFile.rdbuf();
    std::string s = ss.str();
    QJsonDocument jsonDocConfig = QJsonDocument::fromJson(QByteArray::fromStdString(ss.str()));
    if(jsonDocConfig.isNull())
    {
        std::cout << configFilePath <<" is not valid Json" <<std::endl;
        return QJsonObject();
    }
    return jsonDocConfig.object();
}

PoolGame *Initializer::createPoolgame(const std::string &configFilePath, Dialog *parent)
{

    QJsonObject config = jsonFromFile(configFilePath);
    if(config.isEmpty())
        return nullptr;

    AbstractFactory *factory;
    if(config["stage2"].toBool())
    {
        factory = new Stage2Factory(parent);
    }
    else
    {
        factory = new Stage1Factory();
    }

    GameBuilder builder(factory);

    if(config.contains("table"))
    {
        builder.buildTable(config["table"].toObject());
    }
    else
    {
        std::cout << "no \"table\" key found" <<std::endl;
        return nullptr;
    }

    if(config.contains("balls"))
    {
        QJsonArray balls = config["balls"].toArray();
        for(int i = 0; i < balls.size();++i)
        {
            builder.addBall(balls[i].toObject());
        }
    }
    else
    {
        if(config["stage2"].toBool())
        {

        }
        std::cout << "no \"ball\" key found" <<std::endl;
        return nullptr;
    }

    Init_balls = builder.getInitballs();

    stage3flag = config["stage3"].toBool();
    if(config.contains("Music"))
    {
        QJsonArray musics = config["Music"] .toArray();
        for(int i=0;i<musics.size();++i)
        {
            QJsonObject m_musicdata = musics[i].toObject();
            m_path = m_musicdata.value("path").toString();
            m_volum= m_musicdata.value("volume").toInt();
            m_mode = m_musicdata.value("mode").toInt();
        }
    }

    return builder.getGame();
}

std::vector<Ball *> Initializer::get_Initballs()
{
    return Init_balls;
}
