#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <structures.h>
#include <Facade.h>
//class BigModelManager;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_style_button(pick a);

private slots:
    void on_scaleButton_clicked();


    void on_openButton_clicked();

    void on_shiftButton_clicked();

    void on_ugolButton_clicked();

    void on_doButton_clicked();
    void Scale_slot();
    void Shift_slot();
    void Rotate_slot();
    void Camera_slot();

    void on_cameraButton_clicked();

private:
    QMetaObject::Connection m_connection;
    Facade *facade;


    QLineEdit *x_line_edit;
    QLineEdit *y_line_edit;
    QLineEdit *z_line_edit;
    QPushButton *action_button;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
