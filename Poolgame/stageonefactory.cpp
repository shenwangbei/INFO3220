#include "stageonefactory.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Ball* StageOneFactory::makeBall(const QJsonObject& ballData) {
    // construct a ball from its values

    QString col = ballData.value("colour").toString();

    // extract pos into two doubles
    QJsonObject tPos = ballData.value("position").toObject();
    double xpos = tPos.value("x").toDouble();
    double ypos = tPos.value("y").toDouble();

    // extract velocity into two doubles
    QJsonObject tVel = ballData.value("velocity").toObject();
    double xvel = tVel.value("x").toDouble();
    double yvel = tVel.value("y").toDouble();

    double mass = ballData.value("mass").toDouble();
    double radius = ballData.value("radius").toDouble();

    double strength = ballData.value("strength").toDouble();

    int Balltype = p_balltype;
    int TypeIndex = m_BallPos_int[p_balltype];

    return new StageOneBall(QColor(col), QVector2D(xpos, ypos), QVector2D(xvel, yvel), mass, radius,strength,Balltype,TypeIndex);

}



Table* StageOneFactory::makeTable(const QJsonObject& tableData) {
    // create a stage one table based on the fed in json data
    QString colour = tableData.value("colour").toString();

    // extract width and height from json vals
    QJsonObject tSize = tableData.value("size").toObject();
    double width = tSize.value("x").toDouble();
    double height = tSize.value("y").toDouble();

    double friction = tableData.value("friction").toDouble();

    QJsonArray PocketData = tableData.value("pockets").toArray();

        for (const auto& item : PocketData) {
                QJsonObject t = item.toObject();     
                QJsonObject tPosition = t.value("position").toObject();
                buf_pocket.x =  tPosition.value("x").toDouble();
                buf_pocket.y =  tPosition.value("y").toDouble();
                if(t.value("radius").toDouble()>0)  buf_pocket.radius = t.value("radius").toDouble();
                else buf_pocket.radius = 15;
                p_LeafPocket = new LeafPocket;
                p_LeafPocket->PocketSetValue(buf_pocket.x,buf_pocket.y,buf_pocket.radius);
                p_CompositePockets.Addpocket(p_LeafPocket);
           }

    return new StageOneTable(width, height, QColor(colour), friction);
}





