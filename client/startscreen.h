#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>
#include "client.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<Client> dbPtr = nullptr, QWidget *parent = nullptr);
    ~StartScreen();
    void setLoginForm();
    void setRegistrationForm();

    int userId() const;
    QString userName() const;

    std::shared_ptr<Client> getDatabase() const;

public slots:
    void onLoggedIn(uint userId, QString userName);
    void onRejectRequested();

private:
    Ui::StartScreen *ui;
    int m_userId;
    QString m_userName;
    std::shared_ptr<Client> m_dbPtr;
};

#endif // STARTSCREEN_H
