#include "searchbox.h"
#include "ui_searchbox.h"
#include "mainwindow.h"

SearchBox::SearchBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchBox)
{
    ui->setupUi(this);
}

SearchBox::~SearchBox()
{
    delete ui;
}

void SearchBox::on_toolButton_clicked()
{
    setVisible(false);
}
