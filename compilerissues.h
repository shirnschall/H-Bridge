#ifndef COMPILERISSUES_H
#define COMPILERISSUES_H

#include <QWidget>

namespace Ui {
class compilerIssues;
}

class compilerIssues : public QWidget
{
    Q_OBJECT

public:
    explicit compilerIssues(QWidget *parent = 0);
    ~compilerIssues();

public slots:
    void update(std::vector<QString>);

private:
    Ui::compilerIssues *ui;
};

#endif // COMPILERISSUES_H
