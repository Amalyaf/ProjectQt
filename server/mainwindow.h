#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_showAllUsers_clicked();
    void on_showPrvtMessages_clicked();
    void on_showChatMessages_clicked();
    void on_showLogs_clicked();
    void on_blockUser_clicked();
    void on_ConnectChats_clicked();


private:
    Ui::MainWindow *ui;
    Server* server = new Server();
    bool initServer = false;
};

#endif // MAINWINDOW_H
