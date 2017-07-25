/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *MenuFileLoad;
    QAction *actionAbout;
    QWidget *centralwidget;
    QLabel *label_2;
    QDoubleSpinBox *scaleYSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *scaleZSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *scaleXSpinBox;
    QRadioButton *scaleManual;
    QRadioButton *scaleAuto;
    QLineEdit *autoScaleEdit;
    QLineEdit *scaleStepLineEdit;
    QLabel *label_5;
    QFrame *scaleFrame;
    QLabel *scaleFrameLabel;
    QRadioButton *autoRotateRadioButton;
    QFrame *rotateFrame;
    QLabel *rotateFrameLabel;
    QRadioButton *manualRotateRadioButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QButtonGroup *rotateButtonGroup;
    QButtonGroup *scaleButtonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        MenuFileLoad = new QAction(MainWindow);
        MenuFileLoad->setObjectName(QStringLiteral("MenuFileLoad"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 120, 21, 16));
        label_2->setAlignment(Qt::AlignCenter);
        scaleYSpinBox = new QDoubleSpinBox(centralwidget);
        scaleYSpinBox->setObjectName(QStringLiteral("scaleYSpinBox"));
        scaleYSpinBox->setEnabled(false);
        scaleYSpinBox->setGeometry(QRect(130, 140, 62, 22));
        scaleYSpinBox->setDecimals(5);
        scaleYSpinBox->setMinimum(1e-5);
        scaleYSpinBox->setMaximum(1e+6);
        scaleYSpinBox->setSingleStep(1e-5);
        scaleYSpinBox->setValue(1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 120, 21, 16));
        label_3->setAlignment(Qt::AlignCenter);
        scaleZSpinBox = new QDoubleSpinBox(centralwidget);
        scaleZSpinBox->setObjectName(QStringLiteral("scaleZSpinBox"));
        scaleZSpinBox->setEnabled(false);
        scaleZSpinBox->setGeometry(QRect(210, 140, 62, 22));
        scaleZSpinBox->setDecimals(5);
        scaleZSpinBox->setMinimum(1e-5);
        scaleZSpinBox->setMaximum(1e+6);
        scaleZSpinBox->setSingleStep(0.1);
        scaleZSpinBox->setValue(1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 120, 21, 16));
        label_4->setAlignment(Qt::AlignCenter);
        scaleXSpinBox = new QDoubleSpinBox(centralwidget);
        scaleXSpinBox->setObjectName(QStringLiteral("scaleXSpinBox"));
        scaleXSpinBox->setEnabled(false);
        scaleXSpinBox->setGeometry(QRect(50, 140, 62, 22));
        scaleXSpinBox->setDecimals(5);
        scaleXSpinBox->setMinimum(1e-5);
        scaleXSpinBox->setMaximum(1e+6);
        scaleXSpinBox->setSingleStep(1e-5);
        scaleXSpinBox->setValue(1);
        scaleManual = new QRadioButton(centralwidget);
        scaleButtonGroup = new QButtonGroup(MainWindow);
        scaleButtonGroup->setObjectName(QStringLiteral("scaleButtonGroup"));
        scaleButtonGroup->addButton(scaleManual);
        scaleManual->setObjectName(QStringLiteral("scaleManual"));
        scaleManual->setGeometry(QRect(30, 140, 16, 21));
        scaleAuto = new QRadioButton(centralwidget);
        scaleButtonGroup->addButton(scaleAuto);
        scaleAuto->setObjectName(QStringLiteral("scaleAuto"));
        scaleAuto->setGeometry(QRect(30, 170, 82, 18));
        scaleAuto->setChecked(true);
        autoScaleEdit = new QLineEdit(centralwidget);
        autoScaleEdit->setObjectName(QStringLiteral("autoScaleEdit"));
        autoScaleEdit->setEnabled(false);
        autoScaleEdit->setGeometry(QRect(90, 170, 181, 20));
        autoScaleEdit->setMaxLength(7);
        scaleStepLineEdit = new QLineEdit(centralwidget);
        scaleStepLineEdit->setObjectName(QStringLiteral("scaleStepLineEdit"));
        scaleStepLineEdit->setGeometry(QRect(290, 140, 61, 20));
        scaleStepLineEdit->setMaxLength(10);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(300, 120, 46, 13));
        scaleFrame = new QFrame(centralwidget);
        scaleFrame->setObjectName(QStringLiteral("scaleFrame"));
        scaleFrame->setGeometry(QRect(10, 110, 361, 91));
        scaleFrame->setFrameShape(QFrame::StyledPanel);
        scaleFrame->setFrameShadow(QFrame::Raised);
        scaleFrameLabel = new QLabel(scaleFrame);
        scaleFrameLabel->setObjectName(QStringLiteral("scaleFrameLabel"));
        scaleFrameLabel->setGeometry(QRect(10, 0, 31, 21));
        autoRotateRadioButton = new QRadioButton(centralwidget);
        rotateButtonGroup = new QButtonGroup(MainWindow);
        rotateButtonGroup->setObjectName(QStringLiteral("rotateButtonGroup"));
        rotateButtonGroup->addButton(autoRotateRadioButton);
        autoRotateRadioButton->setObjectName(QStringLiteral("autoRotateRadioButton"));
        autoRotateRadioButton->setGeometry(QRect(40, 60, 82, 18));
        autoRotateRadioButton->setChecked(true);
        rotateFrame = new QFrame(centralwidget);
        rotateFrame->setObjectName(QStringLiteral("rotateFrame"));
        rotateFrame->setGeometry(QRect(10, 20, 120, 71));
        rotateFrame->setFrameShape(QFrame::StyledPanel);
        rotateFrame->setFrameShadow(QFrame::Raised);
        rotateFrameLabel = new QLabel(rotateFrame);
        rotateFrameLabel->setObjectName(QStringLiteral("rotateFrameLabel"));
        rotateFrameLabel->setGeometry(QRect(10, 0, 46, 13));
        manualRotateRadioButton = new QRadioButton(rotateFrame);
        rotateButtonGroup->addButton(manualRotateRadioButton);
        manualRotateRadioButton->setObjectName(QStringLiteral("manualRotateRadioButton"));
        manualRotateRadioButton->setGeometry(QRect(30, 20, 82, 18));
        MainWindow->setCentralWidget(centralwidget);
        rotateFrame->raise();
        scaleFrame->raise();
        label_2->raise();
        scaleYSpinBox->raise();
        label_3->raise();
        scaleZSpinBox->raise();
        label_4->raise();
        scaleXSpinBox->raise();
        scaleManual->raise();
        scaleAuto->raise();
        autoScaleEdit->raise();
        scaleStepLineEdit->raise();
        label_5->raise();
        autoRotateRadioButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(MenuFileLoad);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        MenuFileLoad->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        scaleManual->setText(QApplication::translate("MainWindow", "RadioButton", Q_NULLPTR));
        scaleAuto->setText(QApplication::translate("MainWindow", "Auto", Q_NULLPTR));
        scaleStepLineEdit->setText(QApplication::translate("MainWindow", "0,1", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "SpinStep", Q_NULLPTR));
        scaleFrameLabel->setText(QApplication::translate("MainWindow", "Scale", Q_NULLPTR));
        autoRotateRadioButton->setText(QApplication::translate("MainWindow", "Auto", Q_NULLPTR));
        rotateFrameLabel->setText(QApplication::translate("MainWindow", "Rotate", Q_NULLPTR));
        manualRotateRadioButton->setText(QApplication::translate("MainWindow", "Manual", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
