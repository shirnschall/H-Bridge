#include "themepicker.h"
#include "ui_themepicker.h"

ThemePicker::ThemePicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemePicker)
{
    ui->setupUi(this);
}

ThemePicker::~ThemePicker()
{
    delete ui;
}
