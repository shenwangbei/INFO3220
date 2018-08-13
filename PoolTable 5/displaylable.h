#ifndef DISPLAYLABLE_H
#define DISPLAYLABLE_H

#include <QLabel>
#include <QFont>
/*Adapter Design Pattern*/

//target:displayable is the underlying interface, providing adapter interface, do need to not implement
class DisplayLable
{
public:
   // DisplayLable();
    virtual void LableShow(QLabel * m_lable)=0;
    virtual void LableSetText(QLabel * m_lable,QString Text) = 0;
    QLabel * m_lable;
};

//adaptee:Adapting elements, providing adapting elements, and implementing elements need to be specifically described
class LableStyle
{
public:
    void Style(QLabel * m_lable)
    {   //set the different parameter to the score windows
        QFont m_font("Helvetica [Cronyx]", 14);
        m_lable->setGeometry(660,50,80,40);
        m_lable->setFrameShape(QFrame::Box);
        m_lable->setAlignment(Qt::AlignCenter);
        m_lable->setStyleSheet("color:red;border:2px solid blue;background-color:black;");
        m_lable->setFont(m_font);
        m_lable->setText("0");
        m_lable->show();
    }

    void SetText(QLabel * m_lable,QString text)
    {
        m_lable->setText(text);
    }
};
//adaptor: wrap the object of adaptee,and then change adaptee interfaceto target interface
class M_Lable :public DisplayLable
{
public:
    M_Lable():m_LableStyle(new LableStyle)
    {

    }

    void LableShow(QLabel * m_lable)
    {
        Q_CHECK_PTR(m_lable);
        m_LableStyle->Style(m_lable);
    }

    void LableSetText(QLabel * m_lable,QString Text)
    {
        m_LableStyle->SetText(m_lable,Text);
    }
  private:
    LableStyle * m_LableStyle;
};

#endif // DISPLAYLABLE_H
