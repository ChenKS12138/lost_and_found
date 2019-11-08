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

private slots:
    void on_addAdmin_clicked();

    void on_removeAdmin_clicked();

private:
    Ui::AdminWindow *ui;
    void syncTalbe(vector<Admin> &a);
    int getSelectedSingleRow();
};

#endif // ADMINWINDOW_H
