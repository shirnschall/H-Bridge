#include "serialmonitor.h"
#include "ui_serialmonitor.h"

serialMonitor::serialMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialMonitor)
{
    ui->setupUi(this);
}

serialMonitor::~serialMonitor()
{
    delete ui;
}
