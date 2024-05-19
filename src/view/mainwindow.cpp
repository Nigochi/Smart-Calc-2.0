#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot_window = new plotwindow();
    connect(plot_window, &plotwindow::graphwindow, this, &MainWindow::show);

    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));

    connect(ui->add, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->open_bracket, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->close_bracket, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->div, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->mul, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->sub, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pow, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(functions()));

    connect(ui->ce, SIGNAL(clicked()), this, SLOT(on_pushButton_ce_clicked()));
    connect(ui->push_x, SIGNAL(clicked()), this, SLOT(on_pushButton_push_x_clicked()));
    connect(ui->point, SIGNAL(clicked()), this, SLOT(on_pushButton_point_clicked()));
    connect(ui->equal, SIGNAL(clicked()), this, SLOT(on_pushButton_equal_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plot_clicked() {
    plot_window->show();
}

void MainWindow::digit_numbers() {
    if (ui->calc_label->text() == "Error") {
        ui->calc_label->setText("");
    }

    QPushButton* button = (QPushButton*)sender(); // возвращает указатель на объект, отправивший сигнал

    QString new_label = ui->calc_label->text() + button->text();

    ui->calc_label->setText(new_label);
}

void MainWindow::operations() {
    if (ui->calc_label->text() == "Error") {
        ui->calc_label->setText("");
    }

    QPushButton* button = (QPushButton*)sender();

    QString new_label = ui->calc_label->text();

    if (button->text() == "÷"  && !(ui->calc_label->text().endsWith("÷")) && !(ui->calc_label->text().endsWith("/"))) {
        new_label += "/";
    } else if (button->text() == "×" && !(ui->calc_label->text().endsWith("×")) && !(ui->calc_label->text().endsWith("*"))) {
        new_label += "*";
    } else if (button->text() == "-" && !(ui->calc_label->text().endsWith("-"))) {
        new_label += "-";
    } else if (button->text() == "+" && !(ui->calc_label->text().endsWith("+"))) {
        new_label += "+";
    } else if (button->text() == '(') {
        new_label += '(';
    } else if (button->text() == ')') {
        new_label += ')';
    } else if (button->text() == "^" && !(ui->calc_label->text().endsWith("^"))) {
        new_label += "^";
    } else if (button->text() == "mod" && !(ui->calc_label->text().endsWith("mod"))) {
        new_label += "mod";
    }

    ui->calc_label->setText(new_label);
}

void MainWindow::functions() {
    if (ui->calc_label->text() == "Error") {
        ui->calc_label->setText("");
    }

    QPushButton* button = (QPushButton*)sender();

    QString new_label = ui->calc_label->text();

    new_label = ui->calc_label->text() + button->text() + "(";

    ui->calc_label->setText(new_label);
}

void MainWindow::on_pushButton_ce_clicked() {
    ui->calc_label->setText("");
}

void MainWindow::on_pushButton_push_x_clicked() { // REDO
    if (ui->calc_label->text() == "Error") {
        ui->calc_label->setText("");
    }

    QString new_label = ui->edit_x_eq->toPlainText();

    QString text_num = ui->edit_x_eq->toPlainText();
    text_num.toFloat();
    QString str = {text_num};
    QString result = new_label + str;
    ui->calc_label->setText(result);
}

void MainWindow::on_pushButton_point_clicked() {
    if (ui->calc_label->text() == "Error") {
        ui->calc_label->setText("");
    }

    QString new_label;

    if (!ui->calc_label->text().endsWith(".")) {
        new_label = ui->calc_label->text() + ".";
    }

    ui->calc_label->setText(new_label);
}

void MainWindow::on_pushButton_equal_clicked() {
    s21::Controller controller;
    std::string str = ui->calc_label->text().toStdString();
    double result = 0;
      if (controller.startCalc(&str, &result) == 0) {
        ui->calc_label->setText("Error");
      } else {
        QString numberResult = QString::number(result);
        ui->calc_label->setText(numberResult);
      }
}
