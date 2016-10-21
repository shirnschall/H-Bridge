#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;



namespace Ui {
class FileBrowser;
}

class FileBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = 0);

    void fileBrowserAreaPaintEvent(QPaintEvent *event);
    void drawNewItem(std::string);
    int fileBrowserAreaWidth();
    ~FileBrowser();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:

    void updateFileBrowserArea(const QRect &, int);

private:
    Ui::FileBrowser *ui;
};

#endif // FILEBROWSER_H
