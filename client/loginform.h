#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <memory>
#include "client.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void setUsers(std::shared_ptr<Client> dbPtr);

signals:
    void registerRequested();
    void accepted(int userId, QString name);
    void rejected();
private slots:
    void on_buttonBox_accepted();
    void on_registrationPushButton_clicked();
    void on_buttonBox_rejected();

private:
    Ui::LoginForm *ui;
    std::shared_ptr<Client> m_dbPtr;
};

#endif // LOGINFORM_H
