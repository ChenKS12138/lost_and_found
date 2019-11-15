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

    void on_sortByLost_clicked();

    void on_sortByFound_clicked();

    void on_exportRecord_clicked();

    void on_export_last_week_clicked();

private:
    Ui::AppWindow *ui;
    bool isSortByLostDesc = true;
    bool isSortByFoundDesc = true;
    void syncTable(vector<Record> &allRecord);
    int getSelectedSingleRow();
};

#endif // APPWINDOW_H
