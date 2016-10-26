#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "codeeditor.h"
#include "searchbox.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:

    void parseText();

signals:
    void runCode(std::string,std::string,std::string,std::string);

public slots:
    void CodeEditorTextChanged();

private slots:
    void on_actionRun_triggered();

    void on_actionNew_triggered();

    void on_listWidget_itemSelectionChanged();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionStyle_triggered();

    void on_actionSettings_triggered();

    void on_actionOpen_triggered();

    void on_actionSearch_triggered();

    void on_actionAbout_triggered();

    void on_actionAutocomplete_triggered();

    void on_actionDebug_triggered();



    void on_actionThemes_triggered();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void openFile(std::string);

    void getSettings();

    std::string getFileContent(std::string);

    Ui::MainWindow *ui;

    SearchBox *searchBox;
};

#endif // MAINWINDOW_H
