#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <DataManager.h>
#include <string>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->openButton, SIGNAL(clicked()), SLOT(Open_slot()));

    ui->groupBox_2->setEnabled(false);
}
void MainWindow::clearold(QString text)
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_style_button(pick a)
{
    switch (a) {
    case pick::pick_mash: {
        ui->scaleButton->setStyleSheet(QString::fromUtf8(
            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "stop: 0 #dadbde, stop: 1 #f6f7fa)"));
        ui->ugolButton->setStyleSheet(QString::fromUtf8(""));
        ui->shiftButton->setStyleSheet(QString::fromUtf8(""));
        break;
    }
    case pick::pick_pov: {
        ui->ugolButton->setStyleSheet(QString::fromUtf8(
            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "stop: 0 #dadbde, stop: 1 #f6f7fa)"));
        ui->shiftButton->setStyleSheet(QString::fromUtf8(""));
        ui->scaleButton->setStyleSheet(QString::fromUtf8(""));
        break;
    }
    case pick::pick_sdvig: {
        ui->shiftButton->setStyleSheet(QString::fromUtf8(
            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "stop: 0 #dadbde, stop: 1 #f6f7fa)"));
        ui->ugolButton->setStyleSheet(QString::fromUtf8(""));
        ui->scaleButton->setStyleSheet(QString::fromUtf8(""));
    }
    }

    return;
}
void MainWindow::on_scaleButton_clicked()
{

    set_style_button(pick::pick_mash);
    QObject::disconnect(ui->doButton, SLOT(Open_slot()));
    QObject::disconnect(ui->doButton, SLOT(Shift_slot()));
    QObject::disconnect(ui->doButton, SLOT(Rotate_slot()));

    QObject::connect(ui->doButton, SIGNAL(clicked()), SLOT(Scale_slot()));
    ui->groupBox_2->setEnabled(true);
    ui->doButton->setText("Масштаб");
    ui->xLabel->setText("Scale");
    ui->ylineEdit->setEnabled(false);
    ui->zlineEdit->setEnabled(false);
}

void MainWindow::Scale_slot()
{
    //bigmodelmanager.cal
    QMessageBox lol;
    lol.setText("sss");
    lol.exec();

}

void MainWindow::Open_slot()
{
}
void MainWindow::Shift_slot()
{
}

void MainWindow::Rotate_slot()
{
}

void MainWindow::on_openButton_clicked()
{
    string sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
                            QDir::currentPath(), "txt models (*.txt)")
                            .toStdString();

    bigmodelmanager.callDataManager(sourceName);
}

void MainWindow::on_shiftButton_clicked()
{

    set_style_button(pick::pick_sdvig);
    QObject::disconnect(ui->doButton, SLOT(Open_slot()));
    QObject::disconnect(ui->doButton, SLOT(Scale_slot()));
    QObject::disconnect(ui->doButton, SLOT(Rotate_slot()));

    QObject::connect(ui->doButton, SIGNAL(clicked()), SLOT(Shift_slot()));
    ui->groupBox_2->setEnabled(true);
    ui->doButton->setText("Сдвиг");
    ui->xLabel->setText("x");
    ui->ylineEdit->setEnabled(true);
    ui->zlineEdit->setEnabled(true);
}

void MainWindow::on_ugolButton_clicked()
{

    set_style_button(pick::pick_pov);
    QObject::disconnect(ui->doButton, SLOT(Open_slot()));
    QObject::disconnect(ui->doButton, SLOT(Scale_slot()));
    QObject::disconnect(ui->doButton, SLOT(Shift_slot()));

    QObject::connect(ui->doButton, SIGNAL(clicked()), SLOT(Rotate_slot()));
    ui->groupBox_2->setEnabled(true);
    ui->doButton->setText("Поворот");
    ui->xLabel->setText("x");
    ui->ylineEdit->setEnabled(true);
    ui->zlineEdit->setEnabled(true);

}

void MainWindow::on_doButton_clicked()
{

}
