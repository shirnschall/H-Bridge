#include "serialmonitor.h"
#include "ui_serialmonitor.h"
#include <fstream>

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
