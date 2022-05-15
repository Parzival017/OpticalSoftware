#include "SurfaceProperties.h"
#include "ui_SurfaceProperties.h"

SurfaceProperties::SurfaceProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceProperties)
{
    ui->setupUi(this);
}

QString SurfaceProperties::getType()
{
    return ui->comboBox_1->currentText();
}

SurfaceProperties::~SurfaceProperties()
{
    delete ui;
}
