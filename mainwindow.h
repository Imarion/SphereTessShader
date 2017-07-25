#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "SphereTessShader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_MenuFileLoad_triggered();    
    void on_scaleXSpinBox_valueChanged(double arg1);
    void on_scaleYSpinBox_valueChanged(double arg1);
    void on_scaleZSpinBox_valueChanged(double arg1);
    void on_scaleManual_clicked();
    void on_scaleAuto_clicked();

    void on_scaleStepLineEdit_textChanged(const QString &arg1);
    void on_manualRotateRadioButton_clicked();
    void on_autoRotateRadioButton_clicked();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *uiMainWindow;
    //Ui::About      *uiAboutDlg;

    GlWindow *MyGlWindow;

    void     setGlWindowScale();
    void     setManualScaletoAuto();
    void     setScaleStep();
    double   calculateStep(double val);

    void closeEvent (QCloseEvent *);    
};

#endif // MAINWINDOW_H
