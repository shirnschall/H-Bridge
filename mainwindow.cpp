#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filebrowser.h"
#include "searchbox.h"
#include "serialmonitor.h"
#include <themepicker.h>
#include <codeeditor.h>


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cstdio>
#include <memory>
#include <stdio.h>
#include <chrono>

#include <QMutex>
#include <QProgressBar>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

QMutex mutex;

using namespace std;

std::vector<std::string>    wordsToComplete,
                            defaultWordlist,
                            type    {"class" , "struct" , "double" , "int" , "void" , "long" , "float" , "short" , "unsigned" , "extern" , "char" };

std::vector<std::vector<std::string>> functions;



std::vector<std::string> locations{};

string exec(string);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //adding the lineedit:
    ui->toolBar->addWidget(ui->label);
    ui->toolBar->addWidget(ui->lineEdit);

    //set style:
    setStyleSheet(getFileContent("themes/main.css").c_str());
    //setsettings/autocomplete
    getSettings();

    //add and hide searchBox
    searchBox = new SearchBox(this);
    searchBox->setVisible(false);
    searchBox->raise();

    //add new document
    MainWindow::on_actionNew_triggered();

    //hide debug window:
    //ui->plainTextEdit->setVisible(false);
    //ui->treeWidget->setVisible(false);
    ui->widget->setVisible(false);
    ui->widget->setStyleSheet(getFileContent("themes/serialmonitor.css").c_str());

    //start parseText as a new thread and continue searching for new vars/functions etc
    std::thread t1(&MainWindow::parseText,this);
    t1.detach();
    //t1.join();

        functions.resize(type.size());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRun_triggered()
{
    //save
    on_actionSave_triggered();

    //compile and run
    std::string command="make clean & make all & main.exe & set /P ANSWER=Enter to continue...";
    system(command.c_str());

}

void MainWindow::on_actionNew_triggered()
{
    ui->listWidget->addItem("untitled document");
    ui->stackedWidget->addWidget(new CodeEditor(0,this,"#include <avr/io.h>\n#include <stdint.h>\n\n\n\nint main(void) {\n    \n    DDRB  = 0xFF;\n    PORTB = 0x03;\n    \n    \n    \n    return 0;\n}",&wordsToComplete));
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    locations.push_back("");
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if(ui->listWidget->count()>0)
    {
        ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
    }
}

void MainWindow::CodeEditorTextChanged()
{
        if(ui->listWidget->count()>0&&ui->listWidget->selectedItems().length()!=0&&!ui->listWidget->currentItem()->text().endsWith('*'))
        {
            ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text()+"*");
        }
}

void MainWindow::on_actionSave_triggered()
{
    if(locations.at(ui->listWidget->currentRow())!="")
    {
        ofstream file;
        file.open(locations.at(ui->listWidget->currentRow()).c_str());
        CodeEditor *current =dynamic_cast<CodeEditor *>(ui->stackedWidget->currentWidget());
        if(current)
        {
            file << current->toPlainText().toStdString().c_str();
        }
        file.close();

        if(ui->listWidget->currentItem()->text().endsWith('*'))
        {
            ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text().remove(ui->listWidget->currentItem()->text().length()-1,1));
        }
    }
    else
    {
        MainWindow::on_actionSave_As_triggered();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    //get filename
    QString filename=QFileDialog::getSaveFileName(this, tr("Save As"), "", "All files (*.*);;C++ (*.cpp)");
    if(filename!="")
    {
        std::cout<<filename.toStdString().c_str()<<std::endl;

        //write to file
        ofstream file;
        file.open(filename.toStdString().c_str());
        CodeEditor *current =dynamic_cast<CodeEditor *>(ui->stackedWidget->currentWidget());
        if(current)
        {
            file << current->toPlainText().toStdString().c_str();
        }
        file.close();

        //save location
        locations.at(ui->listWidget->currentRow())=filename.toStdString();

        //rename listitem:
        QString name{""};
        for(int i=0;i<filename.length();++i)
        {
            if(filename.at(i)!='/')
            {
                name+=filename.at(i);
            }
            else
            {
                name="";
            }
        }
        ui->listWidget->item(ui->listWidget->currentRow())->setText(name);

        if(ui->listWidget->currentItem()->text().endsWith('*'))
        {
            ui->listWidget->currentItem()->setText(ui->listWidget->currentItem()->text().remove(ui->listWidget->currentItem()->text().length()-1,1));
        }
    }

}

void MainWindow::on_actionOpen_triggered()
{
    //get filename
    QString filename=QFileDialog::getOpenFileName(this, tr("Save As"), "", "All files (*.*);;C++ (*.cpp)");
    std::cout<<filename.toStdString().c_str()<<std::endl;
    bool open{true};
    //check if fil is open
    for(int i=0;i<locations.size();++i)
    {
        if(locations[i]==filename.toStdString())
        {
            open=false;
            ui->listWidget->setCurrentRow(i);
            break;
        }
    }

    //read file
    std::string fileText{""};
    std::string line{""};
    ifstream file;
    file.open(filename.toStdString().c_str());

    if (open&&file.is_open())
    {
        while(std::getline(file, line))
        {
            fileText+=line+'\n';
        }

        file.close();

        //get filename
        QString name{""};
        for(int i=0;i<filename.length();++i)
        {
            if(filename.at(i)!='/')
            {
                name+=filename.at(i);
            }
            else
            {
                name="";
            }
        }

        //add new widget/listwidget item
        ui->listWidget->addItem(name);
        ui->stackedWidget->addWidget(new CodeEditor(0,this,fileText,&wordsToComplete));
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        locations.push_back(filename.toStdString());
    }
}

void MainWindow::openFile(std::string filename)
{
    bool open{false};
    //check if fil is open
    for(int i=0;i<locations.size();++i)
    {
        if(locations[i]==filename)
        {
            open=true;
            ui->listWidget->setCurrentRow(i);
            break;
        }
    }

    //read file
    std::string fileText{""};
    std::string line{""};
    ifstream file;
    file.open(filename.c_str());

    if (!open&&file.is_open())
    {
        while(std::getline(file, line))
        {
            fileText+=line+'\n';
        }

        file.close();

        //get filename
        QString name{""};
        for(int i=0;i<filename.length();++i)
        {
            if(filename.at(i)!='/')
            {
                name+=filename.at(i);
            }
            else
            {
                name="";
            }
        }

        //add new widget/listwidget item
        ui->listWidget->addItem(name);
        ui->stackedWidget->addWidget(new CodeEditor(0,this,fileText,&wordsToComplete));
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        locations.push_back(filename);
    }
}

std::string MainWindow::getFileContent(std::string filename)
{
    //read file
    std::string fileText{""};
    std::string line{""};
    ifstream file;
    file.open(filename.c_str());

    if (file.is_open())
    {
        while(std::getline(file, line))
        {
            fileText+=line+'\n';
        }

        file.close();

    }
        return fileText;
}

void MainWindow::getSettings()
{
    //read file
    std::string line{""};
    std::string setting{""};

    ifstream file;
    file.open("settings");

    if (file.is_open())
    {
        while(std::getline(file, line))
        {
            setting="";
            for(int i=line.find_first_of(':');i<line.size();++i)
            {
                setting+=line[i];
            }
            if(line.find("autoIndent")==0)
            {

            }
            else if(line.find("autoComplete")==0)
            {

            }
            else if(line.find("syntaxHighlighting")==0)
            {

            }
            else if(line.find("autoCloseBrackets")==0)
            {

            }
            else if(line.find("tabSpace")==0)
            {

            }
            else if(line.find("showUnsaved")==0)
            {

            }
            else if(line.find("autoSave")==0)
            {

            }
            else if(line.find("autoBackup")==0)
            {

            }
            else if(line.find("defaultText")==0)
            {

            }
            else if(line.find("autoCloseBraces")==0)
            {

            }
            else if(line.find("autoCloseQutoes")==0)
            {

            }
            else if(line.find("autoCloseSingleQuotes")==0)
            {

            }
            else if(line.find("quotesAroundSelection")==0)
            {

            }
            else if(line.find("bracketsQroundSelection")==0)
            {

            }
            else if(line.find("bracesAroundSelection")==0)
            {

            }
            else if(line.find("saveOpenDocuments")==0)
            {

            }
            else if(line.find("saveDialogOnExit")==0)
            {

            }
        }
        file.close();
    }

    //autocomplete
    file.open("autocomplete");
    if(file.is_open())
    {

        while(std::getline(file, line))
        {
            if(line.find("//")!=0)
            {
                defaultWordlist.push_back(line);
            }
        }
    }
}

void MainWindow::on_actionStyle_triggered()
{
    openFile("themes/main.css");
}

void MainWindow::on_actionSettings_triggered()
{
    openFile("settings");
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    //reposition searchbox
    searchBox->move(this->width()-240,ui->menuBar->height()+ui->toolBar->height());
}

void MainWindow::on_actionSearch_triggered()
{

    searchBox->setVisible(true);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("<font color=\"white\" size=\"5\" face=\"consolas\"><center>HBridge 0.3<br /><br />(C) Sebastian Hirnschall 2016<br /><br />Written in Qt C++</center></font>");
    msgBox.setIconPixmap(QPixmap(":/icons/hirnschall.png"));
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setStyleSheet("QMessageBox{background-color:rgb(49,49,49);}");

    msgBox.exec();
}

void MainWindow::on_actionAutocomplete_triggered()
{
    openFile("autocomplete");
}

void MainWindow::on_actionDebug_triggered()
{
    //ui->plainTextEdit->setVisible(true);
    //ui->treeWidget->setVisible(true);
    ui->widget->setVisible(true);

    //std::thread debug(&MainWindow::exec,this,"a.exe", this);
    //debug.detach();


}



//find vars/functions and add them to the completerWordlist for the corresponding CodeEditor
void MainWindow::parseText()
{
    std::string charsToSplit = "(,;:={ \t[*/";

    while(true)
    {
        //sleep 500 miliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CodeEditor *current =dynamic_cast<CodeEditor *>(ui->stackedWidget->currentWidget());
    if(current)
    {
        try{
        std::vector<std::string> wordlist=defaultWordlist;

        for(int i=0;i<current->document()->blockCount();++i)
        {
            std::string line = "",
                        lineWOSpace="";

            mutex.lock();
            line=current->document()->findBlockByNumber(i).text().toStdString();
            mutex.unlock();

            if(line!="")
            {
                for(int k=0;k<line.length();++k)
                {
                    if((line[k]!=' '&&line[k]!='\t')||lineWOSpace!="")
                    {
                        lineWOSpace+=line[k];
                    }
                }

                for(int k=0;k<type.size();++k)
                {
                    if(lineWOSpace != type[k] && lineWOSpace.find(type[k])==0 )
                    {
                        std::string word{""};
                        bool wordStart=false;

                        for(int j=0;j<line.length();++j)
                        {
                            if(!wordStart && lineWOSpace[j]==' ')
                            {
                                wordStart=true;
                            }
                            else if(wordStart && std::find(charsToSplit.begin(),charsToSplit.end(),lineWOSpace[j])==charsToSplit.end())
                            {
                                word+=lineWOSpace[j];
                            }
                            else if(wordStart && std::find(charsToSplit.begin(),charsToSplit.end(),lineWOSpace[j])!=charsToSplit.end())
                            {
                                if(word!="" && type[k] != "struct" && type[k] != "class" && std::find(wordlist.begin(),wordlist.end(),word)==wordlist.end())
                                {
                                    wordlist.push_back(word);
                                }
                                else if(word!="" && std::find(type.begin(),type.end(),word)==type.end())
                                {
                                    wordlist.push_back(word);
                                    type.push_back(word);
                                    functions.resize(functions.size()+1);
                                }
                                word="";
                                if(lineWOSpace[j]=='/'&&lineWOSpace[j+1]=='/')
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }


        }

    mutex.lock();
    wordsToComplete=wordlist;
    mutex.unlock();
        }
        catch(...)
        {

        }
    }
    }
}

void MainWindow::on_actionThemes_triggered()
{
    ThemePicker themeDialog;
    themeDialog.setStyleSheet(getFileContent("themes/default-themepicker.css").c_str());
    themeDialog.setModal(true);
    themeDialog.exec();

    QMessageBox msgBox;
    msgBox.setText("Please restart H-Bridge!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    //setStyleSheet(getFileContent("themes/main.css").c_str());
}
