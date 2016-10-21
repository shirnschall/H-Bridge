#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QWidget>

namespace Ui {
class serialMonitor;
}

class serialMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit serialMonitor(QWidget *parent = 0);
    ~serialMonitor();

private:
    Ui::serialMonitor *ui;
};

#endif // SERIALMONITOR_H
