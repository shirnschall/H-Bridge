#ifndef COMPILEROUTPUT_H
#define COMPILEROUTPUT_H

#include <QWidget>

namespace Ui {
class compilerOutput;
}

class compilerOutput : public QWidget
{
    Q_OBJECT

public:
    explicit compilerOutput(QWidget *parent = 0);
    ~compilerOutput();

signals:
    void updateIssues(std::vector<QString>);

public slots:
    void compile(std::string,std::string,std::string,std::string);

private:
    Ui::compilerOutput *ui;
    void parseError(QString, QString);
};

#endif // COMPILEROUTPUT_H
