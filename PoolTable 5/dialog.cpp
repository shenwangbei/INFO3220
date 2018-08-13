#include "dialog.h"
#include "addball.h"
#include <QPainter>
#include <QSize>

constexpr float fps = 60;
constexpr float timeStep = 0.01;
 AddBall * m_addball;

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer())
{


}

void Dialog::stage3Init()
{
    /*set the postion of the volum slider*/
    m_musics = new Musics(m_volum,m_path,m_mode);
    m_VolumSlider = new QSlider(this);
    m_VolumSlider->setOrientation(Qt::Horizontal);
    m_VolumSlider->setGeometry(m_game->size().width()+20,20,150,15);
    m_VolumSlider->setValue(m_volum);
    m_VolumSlider->show();

    connect(m_VolumSlider,SIGNAL(valueChanged(int)),this,SLOT(SetBGMVolum(int)));
 //   qDebug()<<m_volum<<m_path<<stage3flag<<m_mode;

    lable = new M_Lable();
    lable->m_lable = new QLabel(this);
    lable->LableShow(lable->m_lable);
    /*set position of the add ball buttion*/
    m_Button = new QPushButton(this);
    m_Button->setGeometry(640,240,60,20);
    m_Button->setText("AddBall");
    m_Button->show();

    connect(m_Button,SIGNAL(clicked()),this,SLOT(ButtonAddball()));


    m_addball = new AddBall(this);
    m_addball->UiInit();

    m_Focus = new QPushButton(this);
    /*set the focus position */
    m_Focus->setGeometry(740,240,40,20);
    m_Focus->setText("Focus");
    m_Focus->show();

    connect(m_Focus,SIGNAL(clicked()),this,SLOT(FoucsClicked()));

}
bool Focusflag = 0;
/*set the flag of focous to check whether it can type input*/
bool Dialog::FoucsClicked()
{
   if(Focusflag) Focusflag=0;
   else Focusflag=1;
  if(Focusflag==0)
    {
            m_addball->color->setFocusPolicy(Qt::NoFocus);
            m_addball->mass->setFocusPolicy(Qt::NoFocus);
            m_addball->pos_x->setFocusPolicy(Qt::NoFocus);
            m_addball->pos_y->setFocusPolicy(Qt::NoFocus);
            m_addball->vec_x->setFocusPolicy(Qt::NoFocus);
            m_addball->vec_y->setFocusPolicy(Qt::NoFocus);
            m_addball->radius->setFocusPolicy(Qt::NoFocus);
            m_addball-> strength->setFocusPolicy(Qt::NoFocus);
            m_Focus->setFocus();
    }else
    {
        m_addball->color->setFocusPolicy(Qt::ClickFocus);
        m_addball->mass->setFocusPolicy(Qt::ClickFocus);
        m_addball->pos_x->setFocusPolicy(Qt::ClickFocus);
        m_addball->pos_y->setFocusPolicy(Qt::ClickFocus);
        m_addball->vec_x->setFocusPolicy(Qt::ClickFocus);
        m_addball->vec_y->setFocusPolicy(Qt::ClickFocus);
        m_addball->radius->setFocusPolicy(Qt::ClickFocus);
        m_addball-> strength->setFocusPolicy(Qt::ClickFocus);
    }
}
/*set the layout of user interface*/
void Dialog::start(PoolGame *game)
{
    m_game = game;
    this->setMinimumSize(m_game->size());
    if(stage3flag) this->resize(m_game->size().width()+200,m_game->size().height());
    else this->resize(m_game->size().width(),m_game->size().height());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);

    m_game->MementoInit();

    if(stage3flag) stage3Init();
    else ;
}

void Dialog::DisBatNum()
{
//    char a[1] = {0};
//    sprintf(a,"%d",m_game->DisNum);
    lable->LableSetText(lable->m_lable,QString("%1").arg(m_game->DisNum));
}

//set the flag of pressing R
void Dialog::keyPressEvent(QKeyEvent * e)
{
    if(e->key() == Qt::Key_R)
    {
        m_game->Key_R_Flag = 1;
    }
}
int a  = 1;int _a = 0;
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(m_game){
        m_game->draw(p);
    }

    if(stage3flag)
    {
        if(_a == 0) ;
        else
        {
            if(a != m_game->DisNum)
            {
                a = m_game->DisNum;
                DisBatNum();
            }
        }
    }else;
    _a++;
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}


Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::SetBGMVolum(int volum)
{
    m_musics->m_player.setVolume(volum);
    //    qDebug()<<volum;
}

void Dialog::ButtonAddball()
{
    m_game->M_BallPush(m_addball->Addm_ball());
}

void Dialog::runSimulationStep()
{
    if(m_game){
        m_game->simulateTimeStep(timeStep);
    }
}
