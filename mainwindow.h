#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appwindow.h"
#include <QMainWindow>
#include "recordlib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AppWindow *app_win;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void login(Admin a);
};

#endif // MAINWINDOW_H
