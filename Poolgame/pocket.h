#ifndef POCKET_H
#define POCKET_H
#include <QVector>
#include <QPainter>
#include <QVector2D>
struct pocket
{
    double x;
    double y;
    double radius;
};


/*Composite Pattern*/
/*composite pattern: component*/
class CompontPocket
{
public:
    CompontPocket() {}
    virtual void Addpocket(CompontPocket *) = 0;
    virtual void Removepocket(CompontPocket *) = 0;
    virtual pocket  Output() = 0;
    virtual int getVecCount() = 0;
    virtual QVector <CompontPocket *> getvetor() = 0;
    virtual void render(QPainter& painter) = 0;
  /*  virtual CompontPocket * getItem(QVector<CompontPocket *>::iterator it) =0;*/
    virtual void PocketSetValue(double x,double y ,int rad)=0;
protected:
    pocket  p_pocket;
};
/*composite pattern: leaf*/
class LeafPocket : public CompontPocket
{
public:
    LeafPocket():CompontPocket() {}
    void Addpocket(CompontPocket *) {return ;}
    void Removepocket(CompontPocket *) {return ;}
    pocket  Output() {  return p_pocket;}
    int getVecCount() {return 0;}
    QVector <CompontPocket *> getvetor() {  QVector<CompontPocket * > a;     return  a; }
  //  CompontPocket * getItem(QVector<CompontPocket *>::iterator it) { CompontPocket * a; a = NULL; return a; }
    void PocketSetValue(double x,double y ,int rad)
    {
        p_pocket.x = x;
        p_pocket.y = y;
        p_pocket.radius = rad;
    }
    /**
     * @brief render - to color the pocket
     * @param painter
     */
    void render(QPainter& painter)
    {
        QVector2D m_point;
        m_point.setX(p_pocket.x);
        m_point.setY(p_pocket.y);
        // use our colour
        painter.setBrush(Qt::black);
        // circle centered
        painter.drawEllipse(m_point.toPointF(), p_pocket.radius, p_pocket.radius);
    }
};
/*composite pattern: composite part*/
class CompositePockets: public CompontPocket
{    
public:    
//  CompositePockets():CompontPocket() {}
    void Addpocket(CompontPocket* m_Pocket)
    {
        m_Pockets.push_back(m_Pocket);
    }
    void Removepocket(CompontPocket * p_Pocket)
    {
        for(QVector<CompontPocket *>::iterator it=m_Pockets.begin();it!=m_Pockets.end();++it)
        {
            if(p_Pocket == *it)
            {
                m_Pockets.erase(it);
                break;
            }
        }
    }
    pocket  Output()
    {
      /*  for(QVector<CompontPocket *>::iterator it = m_Pockets.begin();it<m_Pockets.end();++it )
        {
            CompontPocket * poc = *it;
            poc->Output();
        }*/
        return p_pocket;
    }
    int getVecCount()
    {
        int Count = m_Pockets.size();
        return Count;
    }
    QVector<CompontPocket *> getvetor()
    {
        return m_Pockets;
    }
 /*   CompontPocket * getItem(QVector<CompontPocket *>::iterator it)
    {
        CompontPocket * Buf =*it;
        return Buf;
    }*/
    void PocketSetValue(double x,double y ,int rad)
    {
        p_pocket.x = x;
        p_pocket.y = y;
        p_pocket.radius = rad;
    }

    void render(QPainter& painter)
    {
        for(auto it = m_Pockets.begin();it!= m_Pockets.end();++it)
        {
            CompontPocket * pockets = *it;
            pockets->render(painter);
        }
    }

private:
    QVector <CompontPocket *> m_Pockets;  //colloction of pockets
};

extern CompositePockets  p_CompositePockets;




#endif // POCKET_H
