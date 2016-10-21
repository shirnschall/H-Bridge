#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

namespace Ui {
class LineNumberArea;
}

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    explicit LineNumberArea(QWidget *parent = 0);
    ~LineNumberArea();

private:
    Ui::LineNumberArea *ui;
};

#endif // LINENUMBERAREA_H
