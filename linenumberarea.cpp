#include "linenumberarea.h"
#include "ui_linenumberarea.h"

LineNumberArea::LineNumberArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineNumberArea)
{
    ui->setupUi(this);
}

LineNumberArea::~LineNumberArea()
{
    delete ui;
}
