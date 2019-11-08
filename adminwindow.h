#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "recordlib.h"
#include <QMainWindow>
#include<vector>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private:
    Ui::AdminWindow *ui;
    void syncTalbe(vector<Admin> &a);
};

#endif // ADMINWINDOW_H
