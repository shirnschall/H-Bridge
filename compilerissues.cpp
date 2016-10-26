#include "compilerissues.h"
#include "ui_compilerissues.h"
#include <QDebug>

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
    for(int i=0;i<issues.size();++i)
    {
        ui->listWidget->addItem(new QListWidgetItem(issues[i]));
        qDebug() << issues[i];
    }
}
