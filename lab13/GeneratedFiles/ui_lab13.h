/********************************************************************************
** Form generated from reading UI file 'lab13.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB13_H
#define UI_LAB13_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab13Class
{
public:

    void setupUi(QWidget *lab13Class)
    {
        if (lab13Class->objectName().isEmpty())
            lab13Class->setObjectName(QStringLiteral("lab13Class"));
        lab13Class->resize(600, 400);

        retranslateUi(lab13Class);

        QMetaObject::connectSlotsByName(lab13Class);
    } // setupUi

    void retranslateUi(QWidget *lab13Class)
    {
        lab13Class->setWindowTitle(QApplication::translate("lab13Class", "lab13", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab13Class: public Ui_lab13Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB13_H
