#include "themepicker.h"
#include "ui_themepicker.h"
#include "mainwindow.h"

#include <fstream>

#include <QDirIterator>
#include <QFile>

ThemePicker::ThemePicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemePicker)
{
    ui->setupUi(this);

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(on_buttonBox_accepted()));

    QDirIterator it("themes/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        if(it.fileName()!="." && it.fileName()!=".." && it.fileName()!="default.css")
            ui->listWidget->addItem(it.fileName());
    }
}

ThemePicker::~ThemePicker()
{
    delete ui;
}

void ThemePicker::on_buttonBox_accepted()
{

    if(QFile::remove("themes/default.css"))
    {
        std::string style="";
        std::string tmp;
        std::ifstream in;
        in.open("themes/"+ui->listWidget->currentItem()->text().toStdString());
        if(in.is_open())
        {
            while(std::getline(in,tmp))
            {
                style+=tmp;
            }
        }
        in.close();
        std::ofstream file;
        file.open("themes/default.css");
        if(file.is_open())
            file << style.c_str();
        file.close();
    }

    this->close();
}
