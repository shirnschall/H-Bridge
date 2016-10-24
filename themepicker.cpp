#include "themepicker.h"
#include "ui_themepicker.h"
#include "mainwindow.h"

#include <fstream>

#include <QRegularExpression>
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
        if(it.fileName()!="." && it.fileName()!=".." && it.fileName()!="main.css"&& it.fileName()!="codeeditor.css"&& it.fileName()!="themepicker.css")
            ui->listWidget->addItem(it.fileName());
    }
}

ThemePicker::~ThemePicker()
{
    delete ui;
}

void ThemePicker::on_buttonBox_accepted()
{
    std::vector<QString> files{"main.css","themepicker.css","codeeditor.css"};

    std::string path = "themes/" + ui->listWidget->currentItem()->text().toStdString();
    //replace default.css with new style
    for(int i=0;i<3;++i)
    {
        const QString stylesheet = "themes/" + files[i];
        if(QFile::remove(stylesheet))
        {
            //reading in new stylesheet
            std::string style="";
            std::string tmp;
            std::ifstream in;
            in.open(path + "/" + files[i].toStdString());
            if(in.is_open())
            {
                while(std::getline(in,tmp))
                {
                    style+=tmp+'\n';
                }
            }
            in.close();

            //copy new style
            std::ofstream file;
            file.open("themes/" + files[i].toStdString());
            if(file.is_open())
                file << style.c_str();
            file.close();
        }
    }


    this->close();
}
