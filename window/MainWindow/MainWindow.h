#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <config.h>
#include <QMainWindow>
#include <window/LensDataEditor/LensDataEditor.h>
#include <window/Layout2D/Layout2D.h>
#include <spotwidget.h>
#include <system/system.h>

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action2D_Layout_triggered();
    void on_actionNew_triggered();
    void on_actionStandard_triggered();
private:
    Obj *system;
    LensDataEditor *SurfaceDataEditor;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
