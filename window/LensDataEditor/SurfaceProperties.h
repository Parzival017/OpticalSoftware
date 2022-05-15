#ifndef SURFACEPROPERTIES_H
#define SURFACEPROPERTIES_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class SurfaceProperties;
}

class SurfaceProperties : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceProperties(QWidget *parent = nullptr);
    QString getType();
    ~SurfaceProperties();

private:
    Ui::SurfaceProperties *ui;
};

#endif // SURFACEPROPERTIES_H
