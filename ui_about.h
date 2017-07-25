/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *Subject;
    QLabel *Version;
    QLabel *label;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(176, 68);
        Subject = new QLabel(About);
        Subject->setObjectName(QStringLiteral("Subject"));
        Subject->setGeometry(QRect(30, 0, 131, 21));
        Version = new QLabel(About);
        Version->setObjectName(QStringLiteral("Version"));
        Version->setGeometry(QRect(80, 20, 41, 16));
        label = new QLabel(About);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 110, 16));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Dialog", Q_NULLPTR));
        Subject->setText(QApplication::translate("About", "Wavefront object loader", Q_NULLPTR));
        Version->setText(QApplication::translate("About", "v 0.12", Q_NULLPTR));
        label->setText(QApplication::translate("About", "By Emmanuel Renquin", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
