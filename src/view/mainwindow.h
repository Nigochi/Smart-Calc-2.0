#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <plotwindow.h>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    plotwindow *plot_window;

private slots:
    void digit_numbers();
    void operations();
    void functions();


    void on_pushButton_ce_clicked();
    void on_pushButton_push_x_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_equal_clicked();
    void on_plot_clicked();
};

#endif // MAINWINDOW_H
