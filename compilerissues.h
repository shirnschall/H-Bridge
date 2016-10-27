#ifndef COMPILERISSUES_H
#define COMPILERISSUES_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class compilerIssues;
}

class compilerIssues : public QWidget
{
    Q_OBJECT

public:
    explicit compilerIssues(QWidget *parent = 0);
    ~compilerIssues();

signals:
    void gotoError(int);

public slots:
    void update(std::vector<QString>);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::compilerIssues *ui;
};

#endif // COMPILERISSUES_H
