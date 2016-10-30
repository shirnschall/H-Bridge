#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QDialog>

namespace Ui {
class firstStart;
}

class firstStart : public QDialog
{
    Q_OBJECT

public:
    explicit firstStart(QWidget *parent = 0);
    ~firstStart();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::firstStart *ui;
};

#endif // FIRSTSTART_H
