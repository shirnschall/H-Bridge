#include "compileroutput.h"
#include "ui_compileroutput.h"

#include <QProcess>
#include <QTime>
#include <QRegExp>
#include <QDebug>

compilerOutput::compilerOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::compilerOutput)
{
    ui->setupUi(this);


}

compilerOutput::~compilerOutput()
{
    delete ui;
}

void compilerOutput::compile(std::string mmcu, std::string port, std::string programmer, std::string baudrate)
{
//compile
    QProcess* process = new QProcess(this);
    ui->plainTextEdit->appendPlainText(QTime::currentTime().toString() + "  C:\\WinAVR-20100110\\bin\\avr-gcc -g -Os -mmcu=" + QString::fromStdString(mmcu) + " -c build.c");
    process->start("C:\\WinAVR-20100110\\bin\\avr-gcc -g -Os -mmcu=" + QString::fromStdString(mmcu) + " -c build.c");
    process->waitForFinished();
    QString error = process->readAllStandardError();
    QString output = process->readAllStandardOutput();
    if(error.length()>2)
        ui->plainTextEdit->appendPlainText(error);
    if(output.length()>2)
        ui->plainTextEdit->appendPlainText(output);
    if(error.length()>2 || output.length()>2)
    {
        //parse error
        parseError(error,output);
        goto error;
    }
//link
    ui->plainTextEdit->appendPlainText(QTime::currentTime().toString() + "  C:\\WinAVR-20100110\\bin\\avr-gcc -g -mmcu=" + QString::fromStdString(mmcu) + " -o build.elf build.o");
    process->start("C:\\WinAVR-20100110\\bin\\avr-gcc -g -mmcu=" + QString::fromStdString(mmcu) + " -o build.elf build.o");
    process->waitForFinished();
    error = process->readAllStandardError();
    output = process->readAllStandardOutput();
    if(error.length()>2)
        ui->plainTextEdit->appendPlainText(error);
    if(output.length()>2)
        ui->plainTextEdit->appendPlainText(output);
    if(error.length()>2 || output.length()>2)
        goto error;
//hex file
    ui->plainTextEdit->appendPlainText(QTime::currentTime().toString() + "  C:\\WinAVR-20100110\\bin\\avr-objcopy -j .text -j .data -O ihex build.elf build.hex");
    process->start("WinAVR-20100110\\bin\\avr-objcopy -j .text -j .data -O ihex build.elf build.hex");
    process->waitForFinished();
    error = process->readAllStandardError();
    output = process->readAllStandardOutput();
    if(error.length()>2)
        ui->plainTextEdit->appendPlainText(error);
    if(output.length()>2)
        ui->plainTextEdit->appendPlainText(output);
    if(error.length()>2 || output.length()>2)
        goto error;
//upload
    ui->plainTextEdit->appendPlainText(QTime::currentTime().toString() + "  C:\\WinAVR-20100110\\bin\\avrdude ");
    process->start("C:\\WinAVR-20100110\\bin\\avrdude -p " + QString::fromStdString(mmcu) + " -c " + QString::fromStdString(programmer) + " -P " + QString::fromStdString(port) + " -b " + QString::fromStdString(baudrate) + " -v -U flash:w:build.hex");
    process->waitForFinished();
    error = process->readAllStandardError();
    output = process->readAllStandardOutput();
    if(error.length()>2)
        ui->plainTextEdit->appendPlainText(error);
    if(output.length()>2)
        ui->plainTextEdit->appendPlainText(output);

    error: ;

//    //compile and upload
//    std::string command = " -p " + ui->comboBox->currentText().toStdString() + " -c " + ui->comboBox_3->currentText().toStdString() + " -P " + ui->comboBox_2->currentText().toStdString() + " -b " + ui->comboBox_4->currentText().toStdString() + " -v -U flash:w:build.hex & set /P ANSWER=Enter to continue...";
//    qDebug() << command.c_str();
//    system(command.c_str());

}

void compilerOutput::parseError(QString error,QString output)
{
    std::vector<QString> lines;
    QString tmp;
    for(int i=0;i<error.length();++i)
    {
        if(error[i]=='\n')
        {
            lines.push_back(tmp);
            tmp="";
        }
        else if(error[i]=='\r')
        {

        }
        else
        {
            tmp+=error[i];
        }
    }
    for(int i=0;i<output.length();++i)
    {
        if(output[i]=='\n')
        {
            lines.push_back(tmp);
            tmp="";
        }
        else if(output[i]=='\r')
        {

        }
        else
        {
            tmp+=output[i];
        }
    }

    //regex for errors
    QRegExp rx("\\bbuild.c:\\d*: error: .*");
    QRegExp issues("\\bbuild.c:\\d*: error: ");
    std::vector<QString> issuesList;

    for(int i=0;i<lines.size();++i)
    {
        if(lines[i].contains(rx))
        {
            issuesList.push_back(lines[i].remove(issues));
        }
    }

    updateIssues(issuesList);
}
