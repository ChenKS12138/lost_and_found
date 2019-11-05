#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>

namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = 0);
    ~AppWindow();

private:
    Ui::AppWindow *ui;
};

#endif // APPWINDOW_H
