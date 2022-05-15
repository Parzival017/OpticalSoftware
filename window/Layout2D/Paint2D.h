#ifndef PAINT2D_H
#define PAINT2D_H

#include <QGraphicsView>

#include <QScrollBar>
#include <QGraphicsGridLayout>
#include <QtMath>
#include <QApplication>
#include <QWheelEvent>
#include <cmath>
#include <system/system.h>


class Paint2D :public QGraphicsView
{
    Q_OBJECT

public:
    Paint2D(QWidget *parent = 0);
    ~Paint2D();
    QGraphicsScene* getscene();
    //return scene;
    void draw_system(Obj *sys);

private:
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void drawSurface(Standard sur, const double x);
    QPointF drawSurface_withReturn(Standard sur, const double x);
    void drawEdge(QPointF upperPoint1,QPointF upperPoint2);
    void Demo();

    QGraphicsScene *scene;
    //The visual rect in scene
    bool isMousePressed;
    //if mouse pressed, using in zoom change
    QPointF  m_lastPointF;
    //record mouse coordinate
    //record root node
    int cnt;
    //count number in functions of getting middle order
};

#endif // PAINT2D_H
