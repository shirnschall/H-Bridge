#include "searchbox.h"
#include "ui_searchbox.h"
#include "mainwindow.h"

#include <fstream>

SearchBox::SearchBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchBox)
{
    ui->setupUi(this);

    std::string style="";
        std::string tmp;
        std::ifstream in;
        in.open("themes/searchbox.css");
        if(in.is_open())
        {
            while(std::getline(in,tmp))
            {
                style+=tmp;
            }
        }
        in.close();

        setStyleSheet(style.c_str());
}

SearchBox::~SearchBox()
{
    delete ui;
}

void SearchBox::on_toolButton_clicked()
{
    setVisible(false);
}
