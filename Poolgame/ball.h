#pragma once

#include <QPoint>
#include <QPainter>
#include <QVector2D>
#include <QMap>
#include <QVector>



class Ball {
protected:
    QBrush m_brush;
    QVector2D m_pos;
    QVector2D m_velocity;
    double m_mass;
    int m_radius;
    double m_strength;
    int m_BallType;   //  the level of composite ball
    int m_TypeIndex;  //  the index of composite ball
public:
    virtual ~Ball() {}
    Ball(QColor colour, QVector2D position,
         QVector2D velocity, double mass, int radius,double strength,int Balltype,int TypeIndex ) :
        m_brush(colour), m_pos(position), m_velocity(velocity),
        m_mass(mass), m_radius(radius),m_strength(strength),m_BallType(Balltype),m_TypeIndex(TypeIndex) {}

    /**
     * @brief render - draw the ball to the screen
     * @param painter - QPainter that is owned by the dialog
     */
    virtual void render(QPainter &painter) = 0;
    /**
     * @brief translate - Move the ball's position by provided vector
     * @param vec - vector
     */
    virtual void translate(QVector2D vec) = 0;

    QVector2D getVelocity() const { return m_velocity; }
    /**
     * @brief changeVelocity - modify speed by a constant amount
     * @param delta - change in velocity (x,y)
     */
    void changeVelocity(const QVector2D& delta) { m_velocity += delta; }
    /**
     * @brief multiplyVelocity - apply vector multiplicatively
     * @param vel - vector
     */
    void multiplyVelocity(const QVector2D& vel) { m_velocity *= vel; }



    double getMass() const { return m_mass; }
    double getRadius() const { return m_radius; }
    QVector2D getPosition() const { return m_pos; }
    double getstrength() const {return m_strength;}
    int getBalltype() const {return m_BallType;}
    int getBalltypeIndex() const {return m_TypeIndex;}    
    QBrush  getBallColor() const {return m_brush;}

    /**
     * @brief SetVecZero- set velocity to zero,otherwise use velocity from last time
    */
    void SetVecZero()   { m_velocity.setX(0); m_velocity.setY(0);}
    /**
     * @brief SetVecValue- set velocity from parameter
     * @param vec - vector
    */
    void SetVecValue( const QVector2D vec)  {m_velocity.setX(vec.x()); m_velocity.setY(vec.y());}
};

struct  ParentStr
{
   int  balltype ;
   int  ballindex;
};

extern int p_balltype;   //level of ball
extern ParentStr *m_Partent;  // composite ball type
extern QMap<ParentStr *,Ball *>  childball;  // after second level the set of ball
extern int PosIndex;     //Location index
extern int m_BallPos_int[5];
extern int BallNum;   //count of ball
extern bool BallArmFlag, CreatBallArmFlag;  //The cue flag, the flag to create the cue
extern QVector2D White_pos;   //the first position of white ball
extern QVector2D WhiteCue_vec;  //the speed of white ball
extern double  WhiteCue_ang;   //the angle of white ball
extern QVector2D SpeedSetValue;  //Speed setting when hitting the ball
extern bool SpeedSetflag;   //Speed setting flag
extern bool stageFlag;    //stage flag

class StageOneBall : public Ball {
public:
    StageOneBall(QColor colour, QVector2D position,
                 QVector2D velocity, double mass, int radius,double strength,int Balltype,int TypeIndex) :
        Ball(colour, position, velocity, mass, radius,strength,Balltype,TypeIndex) {}
    //
    /**
     * @brief render - draw the ball to the screen
     * @param painter - QPainter that is owned by the dialog
     */
    void render(QPainter &painter) override;
    /**
     * @brief translate - Move the ball's position by provided vector
     * @param vec - vector
     */
    void translate(QVector2D vec) override;
};
