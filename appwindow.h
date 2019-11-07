#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include "recordlib.h"

namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(Admin a,QWidget *parent = 0);
    ~AppWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_confirmRecord_clicked();

private:
    Ui::AppWindow *ui;
};

#endif // APPWINDOW_H
