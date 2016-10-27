#include "compilerissues.h"
#include "ui_compilerissues.h"
#include <QDebug>
#include <QRegExp>

std::vector<int> lines;


compilerIssues::compilerIssues(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::compilerIssues)
{
    ui->setupUi(this);
}

compilerIssues::~compilerIssues()
{
    delete ui;
}

void compilerIssues::update(std::vector<QString> issues)
{
    ui->listWidget->clear();
    lines.clear();

    std::vector<std::string> errors;

    //regex for errors
    QRegExp rx("\\bbuild.c:\\d+: error: .*");
    QRegExp errorRx("\\bbuild.c:\\d+: error: ");
    QRegExp buildcRx("\\bbuild.c:");

    for(int i=0;i<issues.size();++i)
    {
        QString tmp="";
        if(issues[i].contains(rx))
        {
            tmp=issues[i];
            ui->listWidget->addItem(new QListWidgetItem("Line " + tmp.remove(buildcRx)));
            tmp="";
            int j=8;
            do{
                tmp+=issues[i][j++];
            }while(issues[i][j]>47 && issues[i][j]<58);
            lines.push_back(tmp.toInt());
        }
    }
}

void compilerIssues::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    gotoError(lines.at(ui->listWidget->row(item)));
}
