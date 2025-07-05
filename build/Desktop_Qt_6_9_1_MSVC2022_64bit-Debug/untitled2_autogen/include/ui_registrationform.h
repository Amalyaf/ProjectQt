/********************************************************************************
** Form generated from reading UI file 'registrationform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONFORM_H
#define UI_REGISTRATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationForm
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *loginEdit;
    QLineEdit *nameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *passwordConfirmEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QDialogButtonBox *buttonBox;
    QPushButton *loginButton;

    void setupUi(QWidget *RegistrationForm)
    {
        if (RegistrationForm->objectName().isEmpty())
            RegistrationForm->setObjectName("RegistrationForm");
        RegistrationForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(RegistrationForm);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(RegistrationForm);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        label_2 = new QLabel(RegistrationForm);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        label_3 = new QLabel(RegistrationForm);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        label_4 = new QLabel(RegistrationForm);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        loginEdit = new QLineEdit(RegistrationForm);
        loginEdit->setObjectName("loginEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, loginEdit);

        nameEdit = new QLineEdit(RegistrationForm);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, nameEdit);

        passwordEdit = new QLineEdit(RegistrationForm);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, passwordEdit);

        passwordConfirmEdit = new QLineEdit(RegistrationForm);
        passwordConfirmEdit->setObjectName("passwordConfirmEdit");
        passwordConfirmEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, passwordConfirmEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonBox = new QDialogButtonBox(RegistrationForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        horizontalLayout->addWidget(buttonBox);

        loginButton = new QPushButton(RegistrationForm);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RegistrationForm);

        QMetaObject::connectSlotsByName(RegistrationForm);
    } // setupUi

    void retranslateUi(QWidget *RegistrationForm)
    {
        RegistrationForm->setWindowTitle(QCoreApplication::translate("RegistrationForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("RegistrationForm", "Login:", nullptr));
        label_2->setText(QCoreApplication::translate("RegistrationForm", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("RegistrationForm", "Password:", nullptr));
        label_4->setText(QCoreApplication::translate("RegistrationForm", "Confirm password:", nullptr));
        loginButton->setText(QCoreApplication::translate("RegistrationForm", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationForm: public Ui_RegistrationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONFORM_H
