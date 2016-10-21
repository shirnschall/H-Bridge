#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QWidget>

namespace Ui {
class SearchBox;
}

class SearchBox : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = 0);
    ~SearchBox();

private slots:
    void on_toolButton_clicked();

private:
    Ui::SearchBox *ui;
};

#endif // SEARCHBOX_H
