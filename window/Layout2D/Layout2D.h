#ifndef LAYOUT2D_H
#define LAYOUT2D_H

#include <QDialog>
#include <QMainWindow>

#include "Paint2D.h"
#include <system/system.h>

namespace Ui {
class Layout2D;
}

class Layout2D : public QMainWindow
{
    Q_OBJECT

  public:
    Layout2D(QWidget *parent = nullptr);
    ~Layout2D();
    void draw_system(Obj *sys);

  private:
    Ui::Layout2D *ui;
    Paint2D *paint;
};

#endif // LAYOUT2D_H
