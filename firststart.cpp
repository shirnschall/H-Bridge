#include "firststart.h"
#include "ui_firststart.h"
#include <QFileDialog>

firstStart::firstStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstStart)
{
    ui->setupUi(this);
}

firstStart::~firstStart()
{
    delete ui;
}

void firstStart::on_pushButton_2_clicked()
{
    if(ui->stackedWidget->currentIndex()!=ui->stackedWidget->count())
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

void firstStart::on_pushButton_clicked()
{
    if(ui->stackedWidget->currentIndex()!=0)
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

void firstStart::on_pushButton_4_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Select avr-gcc.exe"), ui->lineEdit->text(), "avr-gcc (avr-gcc.exe);;All (*.*)");
    ui->lineEdit->setText(filename);
}

void firstStart::on_pushButton_5_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Select avrdude.exe"), ui->lineEdit_2->text(), "avr-gcc (avrdude.exe);;All (*.*)");
    ui->lineEdit_2->setText(filename);
}

void firstStart::on_pushButton_6_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Select avr-objcopy.exe"), ui->lineEdit_3->text(), "avr-objcopy (avr-objcopy.exe);;All (*.*)");
    ui->lineEdit_3->setText(filename);
}

void firstStart::on_pushButton_7_clicked()
{
    QString dirname = QFileDialog::getExistingDirectory(this,tr("Select lib folder"),ui->lineEdit_4->text(),QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->lineEdit_4->setText(dirname);
}
