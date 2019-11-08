#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include "recordlib.h"
#include "adminwindow.h"

namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(Admin a,QWidget *parent = 0);
    ~AppWindow();
    AdminWindow *admin_win;

private slots:
    void on_newRecord_clicked();

    void on_confirmRecord_clicked();

    void on_found_clicked();

    void on_manageAdmin_clicked();

    void on_removeAll_clicked();

    void on_removeRecord_clicked();

private:
    Ui::AppWindow *ui;
    void syncTable(vector<Record> &allRecord);
    int getSelectedSingleRow();
};

#endif // APPWINDOW_H
