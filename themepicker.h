#ifndef THEMEPICKER_H
#define THEMEPICKER_H

#include <QDialog>

namespace Ui {
class ThemePicker;
}

class ThemePicker : public QDialog
{
    Q_OBJECT

public:
    explicit ThemePicker(QWidget *parent = 0);
    ~ThemePicker();

private:
    Ui::ThemePicker *ui;
};

#endif // THEMEPICKER_H
