#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include "users.h"
#include "chat.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();
    void setUsers(std::shared_ptr<Chat> dbptr);

signals:
    void loginRequested();
    void accepted(int userId, QString name);
    void rejected();
private slots:
    void on_loginButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RegistrationForm *ui;
    std::shared_ptr<Chat> m_dbPtr;
};

#endif // REGISTRATIONFORM_H
