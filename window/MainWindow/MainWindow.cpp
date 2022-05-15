#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SurfaceDataEditor = new LensDataEditor(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action2D_Layout_triggered()
{
    if(SurfaceDataEditor->isHidden())
    {
        QMessageBox::warning(this, "error", "没有数据");
        return ;
    }
    Layout2D *Layout = new Layout2D(this);
    Layout->draw_system(system);
    Layout->show();
}

void MainWindow::on_actionNew_triggered()
{
    SurfaceDataEditor = new LensDataEditor(this);
    system = new Obj();
//    qDebug() << system->check();
    SurfaceDataEditor->bind_system(system);
    SurfaceDataEditor->show();
}

void MainWindow::on_actionStandard_triggered()       //点列图
{
    if(SurfaceDataEditor->isHidden())
    {
        QMessageBox::warning(this, "error", "没有数据");
        return ;
    }
    SpotWidget *Spot = new SpotWidget(this);
    Spot->show();
}

