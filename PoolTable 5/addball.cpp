#include "addball.h"
#include "stage2ball.h"


AddBall::AddBall(Dialog *partent)
{
    factory = new Stage2Factory(partent);

    color = new QLineEdit(partent);
    mass = new QLineEdit(partent);
    pos_x = new QLineEdit(partent);
    pos_y = new QLineEdit(partent);
    vec_x = new QLineEdit(partent);
    vec_y = new QLineEdit(partent);
    radius = new QLineEdit(partent);
    strength = new QLineEdit(partent);

    color_lable = new QLabel(partent);
    pos_x_lable = new QLabel(partent);
    pos_y_lable = new QLabel(partent);
    vec_x_lable = new QLabel(partent);
    vec_y_lable = new QLabel(partent);
    mass_lable = new QLabel(partent);
    strength_lable = new QLabel(partent);
    radius_lable = new QLabel(partent);
}

void AddBall::UiInit()
{
    int pos_left = 655,pos_top= 120;
    int pos_left_Text = 610,pos_top_Text = 120;
    color->setGeometry(pos_left,pos_top,40,20);         color->show();
    mass->setGeometry(pos_left+90,pos_top,40,20);       mass->show();
    pos_x->setGeometry(pos_left,pos_top+=30,40,20);     pos_x->show();
    pos_y->setGeometry(pos_left+90,pos_top,40,20);      pos_y->show();
    vec_x->setGeometry(pos_left,pos_top+=30,40,20);     vec_x->show();
    vec_y->setGeometry(pos_left+90,pos_top,40,20);      vec_y->show();
    radius->setGeometry(pos_left,pos_top+=30,40,20);    radius->show();
    strength->setGeometry(pos_left+90,pos_top,40,20);   strength->show();

    color_lable->setGeometry(pos_left_Text,pos_top_Text,40,20);      color_lable->setText("color");    color_lable->show();
    mass_lable->setGeometry(pos_left_Text+90,pos_top_Text,40,20);     mass_lable->setText("mass");     mass_lable->show();
    pos_x_lable->setGeometry(pos_left_Text,pos_top_Text+=30,40,20);   pos_x_lable->setText("pos_x");   pos_x_lable->show();
    pos_y_lable->setGeometry(pos_left_Text+90,pos_top_Text,40,20);     pos_y_lable->setText("pos_y");  pos_y_lable->show();
    vec_x_lable->setGeometry(pos_left_Text,pos_top_Text+=30,40,20);   vec_x_lable->setText("vex_x");   vec_x_lable->show();
    vec_y_lable->setGeometry(pos_left_Text+90,pos_top_Text,40,20);    vec_y_lable->setText("vec_y");   vec_y_lable->show();
    radius_lable->setGeometry(pos_left_Text,pos_top_Text+=30,40,20);   radius_lable->setText("radius"); radius_lable->show();
    strength_lable->setGeometry(pos_left_Text+90,pos_top_Text,40,20);  strength_lable->setText("strength"); strength_lable->show();
}

Ball * AddBall::Addm_ball(QColor color, QVector2D pos, QVector2D vec, int mass, int strength, int radius)
{
    Ball * a ;
    a->setColour(color);
    a->setPosition(pos);
    a->setVelocity(vec);
    a->setMass(mass);
    a->setRadius(radius);
    return  a;
}

Ball * AddBall::Addm_ball()
{
    QColor _color;
    /**Flag - user: input colortext : red,white,black,
     *default color is red
    */
    QString Color = color->text();
    if(Color == "red") _color = QColor("red");
    else if(Color == "white") _color = QColor("white");
    else if(Color == "black") _color = QColor("black");
    else _color= QColor("red");

    QVector2D pos(pos_x->text().toDouble(),pos_y->text().toDouble());
    if(pos.length()<0.005) {pos.setX(100);pos.setY(100);}

    QVector2D vec(vec_x->text().toDouble(),vec_x->text().toDouble());
    if(vec.length()<0.005) {vec.setX(0);vec.setY(0);}

    float massA = mass->text().toFloat() ;
    if(massA < 0.05) massA = 1;

    float RadiusA = radius->text().toFloat();
    if(RadiusA < 0.05) RadiusA = 10;

    double Strengh = strength->text().toFloat();
    if(Strengh <0.05) Strengh = 10000;

    Ball * ball = factory->makeBall(_color,pos,vec,massA,RadiusA,Strengh);

    //qDebug()<<ball->position().x()<<ball->position().y();
    return  ball ;
}
