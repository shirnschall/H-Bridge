#include "lcddesigner.h"
#include "ui_lcddesigner.h"
#include <QWidget>
#include <QClipboard>

#include <QDebug>

int matrix[5][8];


lcdDesigner::lcdDesigner(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::lcdDesigner)
{
    ui->setupUi(this);
}

lcdDesigner::~lcdDesigner()
{
    delete ui;
}

void lcdDesigner::on_pushButton_clicked()
{
    if(matrix[0][0]++ % 2 == 0)
        ui->pushButton->setStyleSheet("background-color:white;");
    else
        ui->pushButton->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_2_clicked()
{
    if(matrix[1][0]++ % 2 == 0)
        ui->pushButton_2->setStyleSheet("background-color:white;");
    else
        ui->pushButton_2->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_3_clicked()
{
    if(matrix[2][0]++ % 2 == 0)
        ui->pushButton_3->setStyleSheet("background-color:white;");
    else
        ui->pushButton_3->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_4_clicked()
{
    if(matrix[3][0]++ % 2 == 0)
        ui->pushButton_4->setStyleSheet("background-color:white;");
    else
        ui->pushButton_4->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_5_clicked()
{
    if(matrix[4][0]++ % 2 == 0)
        ui->pushButton_5->setStyleSheet("background-color:white;");
    else
        ui->pushButton_5->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_6_clicked()
{
    if(matrix[0][1]++ % 2 == 0)
        ui->pushButton_6->setStyleSheet("background-color:white;");
    else
        ui->pushButton_6->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_7_clicked()
{
    if(matrix[1][1]++ % 2 == 0)
        ui->pushButton_7->setStyleSheet("background-color:white;");
    else
        ui->pushButton_7->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_8_clicked()
{
    if(matrix[2][1]++ % 2 == 0)
        ui->pushButton_8->setStyleSheet("background-color:white;");
    else
        ui->pushButton_8->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_9_clicked()
{
    if(matrix[3][1]++ % 2 == 0)
        ui->pushButton_9->setStyleSheet("background-color:white;");
    else
        ui->pushButton_9->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_10_clicked()
{
    if(matrix[4][1]++ % 2 == 0)
        ui->pushButton_10->setStyleSheet("background-color:white;");
    else
        ui->pushButton_10->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_11_clicked()
{
    if(matrix[0][2]++ % 2 == 0)
        ui->pushButton_11->setStyleSheet("background-color:white;");
    else
        ui->pushButton_11->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_12_clicked()
{
    if(matrix[1][2]++ % 2 == 0)
        ui->pushButton_12->setStyleSheet("background-color:white;");
    else
        ui->pushButton_12->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_13_clicked()
{
    if(matrix[2][2]++ % 2 == 0)
        ui->pushButton_13->setStyleSheet("background-color:white;");
    else
        ui->pushButton_13->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_14_clicked()
{
    if(matrix[3][2]++ % 2 == 0)
        ui->pushButton_14->setStyleSheet("background-color:white;");
    else
        ui->pushButton_14->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_15_clicked()
{
    if(matrix[4][2]++ % 2 == 0)
        ui->pushButton_15->setStyleSheet("background-color:white;");
    else
        ui->pushButton_15->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_16_clicked()
{
    if(matrix[0][3]++ % 2 == 0)
        ui->pushButton_16->setStyleSheet("background-color:white;");
    else
        ui->pushButton_16->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_17_clicked()
{
    if(matrix[1][3]++ % 2 == 0)
        ui->pushButton_17->setStyleSheet("background-color:white;");
    else
        ui->pushButton_17->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_18_clicked()
{
    if(matrix[2][3]++ % 2 == 0)
        ui->pushButton_18->setStyleSheet("background-color:white;");
    else
        ui->pushButton_18->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_19_clicked()
{
    if(matrix[3][3]++ % 2 == 0)
        ui->pushButton_19->setStyleSheet("background-color:white;");
    else
        ui->pushButton_19->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_20_clicked()
{
    if(matrix[4][3]++ % 2 == 0)
        ui->pushButton_20->setStyleSheet("background-color:white;");
    else
        ui->pushButton_20->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_21_clicked()
{
    if(matrix[0][4]++ % 2 == 0)
        ui->pushButton_21->setStyleSheet("background-color:white;");
    else
        ui->pushButton_21->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_22_clicked()
{
    if(matrix[1][4]++ % 2 == 0)
        ui->pushButton_22->setStyleSheet("background-color:white;");
    else
        ui->pushButton_22->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_23_clicked()
{
    if(matrix[2][4]++ % 2 == 0)
        ui->pushButton_23->setStyleSheet("background-color:white;");
    else
        ui->pushButton_23->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_24_clicked()
{
    if(matrix[3][4]++ % 2 == 0)
        ui->pushButton_24->setStyleSheet("background-color:white;");
    else
        ui->pushButton_24->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_25_clicked()
{
    if(matrix[4][4]++ % 2 == 0)
        ui->pushButton_25->setStyleSheet("background-color:white;");
    else
        ui->pushButton_25->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_26_clicked()
{
    if(matrix[0][5]++ % 2 == 0)
        ui->pushButton_26->setStyleSheet("background-color:white;");
    else
        ui->pushButton_26->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_27_clicked()
{
    if(matrix[1][5]++ % 2 == 0)
        ui->pushButton_27->setStyleSheet("background-color:white;");
    else
        ui->pushButton_27->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_28_clicked()
{
    if(matrix[2][5]++ % 2 == 0)
        ui->pushButton_28->setStyleSheet("background-color:white;");
    else
        ui->pushButton_28->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_29_clicked()
{
    if(matrix[3][5]++ % 2 == 0)
        ui->pushButton_29->setStyleSheet("background-color:white;");
    else
        ui->pushButton_29->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_30_clicked()
{
    if(matrix[4][5]++ % 2 == 0)
        ui->pushButton_30->setStyleSheet("background-color:white;");
    else
        ui->pushButton_30->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_31_clicked()
{
    if(matrix[0][6]++ % 2 == 0)
        ui->pushButton_31->setStyleSheet("background-color:white;");
    else
        ui->pushButton_31->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_32_clicked()
{
    if(matrix[1][6]++ % 2 == 0)
        ui->pushButton_32->setStyleSheet("background-color:white;");
    else
        ui->pushButton_32->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_33_clicked()
{
    if(matrix[2][6]++ % 2 == 0)
        ui->pushButton_33->setStyleSheet("background-color:white;");
    else
        ui->pushButton_33->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_34_clicked()
{
    if(matrix[3][6]++ % 2 == 0)
        ui->pushButton_34->setStyleSheet("background-color:white;");
    else
        ui->pushButton_34->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_35_clicked()
{
    if(matrix[4][6]++ % 2 == 0)
        ui->pushButton_35->setStyleSheet("background-color:white;");
    else
        ui->pushButton_35->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_37_clicked()
{
    QString customByte;
    QString byteName="myByte";
    if(!ui->lineEdit->text().isEmpty())
         byteName = ui->lineEdit->text();
    customByte= "uint8_t " + byteName + "[8] = {\n"
            + "  0b"+ QString::number(matrix[0][0]%2) + QString::number(matrix[1][0]%2) + QString::number(matrix[2][0]%2) + QString::number(matrix[3][0]%2) + QString::number(matrix[4][0]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][1]%2) + QString::number(matrix[1][1]%2) + QString::number(matrix[2][1]%2) + QString::number(matrix[3][1]%2) + QString::number(matrix[4][1]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][2]%2) + QString::number(matrix[1][2]%2) + QString::number(matrix[2][2]%2) + QString::number(matrix[3][2]%2) + QString::number(matrix[4][2]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][3]%2) + QString::number(matrix[1][3]%2) + QString::number(matrix[2][3]%2) + QString::number(matrix[3][3]%2) + QString::number(matrix[4][3]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][4]%2) + QString::number(matrix[1][4]%2) + QString::number(matrix[2][4]%2) + QString::number(matrix[3][4]%2) + QString::number(matrix[4][4]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][5]%2) + QString::number(matrix[1][5]%2) + QString::number(matrix[2][5]%2) + QString::number(matrix[3][5]%2) + QString::number(matrix[4][5]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][6]%2) + QString::number(matrix[1][6]%2) + QString::number(matrix[2][6]%2) + QString::number(matrix[3][6]%2) + QString::number(matrix[4][6]%2) + ",\n"
            + "  0b"+ QString::number(matrix[0][7]%2) + QString::number(matrix[1][7]%2) + QString::number(matrix[2][7]%2) + QString::number(matrix[3][7]%2) + QString::number(matrix[4][7]%2) + "\n};";

    //copy text to clipboard
    QClipboard *cboard= QApplication::clipboard();

    cboard->setText(customByte);

    //qDebug() << customByte;
}

void lcdDesigner::on_pushButton_36_clicked()
{
    for(int i=0;i<5;++i)
    {
        for(int j=0;j<7;++j)
        {
            matrix[i][j]=0;
        }
    }
    ui->pushButton->setStyleSheet("background-color:gray;");
    ui->pushButton_2->setStyleSheet("background-color:gray;");
    ui->pushButton_3->setStyleSheet("background-color:gray;");
    ui->pushButton_4->setStyleSheet("background-color:gray;");
    ui->pushButton_5->setStyleSheet("background-color:gray;");
    ui->pushButton_6->setStyleSheet("background-color:gray;");
    ui->pushButton_7->setStyleSheet("background-color:gray;");
    ui->pushButton_8->setStyleSheet("background-color:gray;");
    ui->pushButton_9->setStyleSheet("background-color:gray;");
    ui->pushButton_10->setStyleSheet("background-color:gray;");
    ui->pushButton_11->setStyleSheet("background-color:gray;");
    ui->pushButton_12->setStyleSheet("background-color:gray;");
    ui->pushButton_13->setStyleSheet("background-color:gray;");
    ui->pushButton_14->setStyleSheet("background-color:gray;");
    ui->pushButton_15->setStyleSheet("background-color:gray;");
    ui->pushButton_16->setStyleSheet("background-color:gray;");
    ui->pushButton_17->setStyleSheet("background-color:gray;");
    ui->pushButton_18->setStyleSheet("background-color:gray;");
    ui->pushButton_19->setStyleSheet("background-color:gray;");
    ui->pushButton_20->setStyleSheet("background-color:gray;");
    ui->pushButton_21->setStyleSheet("background-color:gray;");
    ui->pushButton_22->setStyleSheet("background-color:gray;");
    ui->pushButton_23->setStyleSheet("background-color:gray;");
    ui->pushButton_24->setStyleSheet("background-color:gray;");
    ui->pushButton_25->setStyleSheet("background-color:gray;");
    ui->pushButton_26->setStyleSheet("background-color:gray;");
    ui->pushButton_27->setStyleSheet("background-color:gray;");
    ui->pushButton_28->setStyleSheet("background-color:gray;");
    ui->pushButton_29->setStyleSheet("background-color:gray;");
    ui->pushButton_30->setStyleSheet("background-color:gray;");
    ui->pushButton_31->setStyleSheet("background-color:gray;");
    ui->pushButton_32->setStyleSheet("background-color:gray;");
    ui->pushButton_33->setStyleSheet("background-color:gray;");
    ui->pushButton_34->setStyleSheet("background-color:gray;");
    ui->pushButton_35->setStyleSheet("background-color:gray;");
    ui->pushButton_38->setStyleSheet("background-color:gray;");
    ui->pushButton_39->setStyleSheet("background-color:gray;");
    ui->pushButton_40->setStyleSheet("background-color:gray;");
    ui->pushButton_41->setStyleSheet("background-color:gray;");
    ui->pushButton_42->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_38_clicked()
{

    if(matrix[0][7]++ % 2 == 0)
        ui->pushButton_38->setStyleSheet("background-color:white;");
    else
        ui->pushButton_38->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_39_clicked()
{

    if(matrix[1][7]++ % 2 == 0)
        ui->pushButton_39->setStyleSheet("background-color:white;");
    else
        ui->pushButton_39->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_40_clicked()
{

    if(matrix[2][7]++ % 2 == 0)
        ui->pushButton_40->setStyleSheet("background-color:white;");
    else
        ui->pushButton_40->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_41_clicked()
{

    if(matrix[3][7]++ % 2 == 0)
        ui->pushButton_41->setStyleSheet("background-color:white;");
    else
        ui->pushButton_41->setStyleSheet("background-color:gray;");
}

void lcdDesigner::on_pushButton_42_clicked()
{

    if(matrix[4][7]++ % 2 == 0)
        ui->pushButton_42->setStyleSheet("background-color:white;");
    else
        ui->pushButton_42->setStyleSheet("background-color:gray;");
}
