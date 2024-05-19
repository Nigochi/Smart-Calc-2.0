#include "plotwindow.h"

plotwindow::plotwindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::plotwindow) {
  ui->setupUi(this);
}

plotwindow::~plotwindow() { delete ui; }

void plotwindow::on_plot_clicked() {
  emit graphwindow();  // вызываем сигнал на открытие главного окна
}

void plotwindow::on_draw_graph_clicked() {
  x.clear();
  y.clear();
  QString function_text = ui->equation->toPlainText();
  if (function_text == "") {
    ui->equation->setPlainText("0");
  } else {
    QString func_text = function_text;
    step = 0.1;
    result = 0;
    for (count_x = ui->x_from->toPlainText().toDouble();
         count_x <= ui->x_to->toPlainText().toDouble(); count_x += step) {
      QString rep_x = "(x)";
      rep_x.replace("x", QString::number(count_x, 'd'));
      func_text.replace("x", rep_x);
      QByteArray ba = func_text.toLocal8Bit();
      char *src = ba.data();
      QString temp = QString::fromLocal8Bit(src);
      std::string tempString = temp.toStdString();
      s21::Controller controller;
      controller.startCalc(&tempString, &result);
      x.push_back(count_x);
      y.push_back(result);
      func_text = function_text;
    }
  }
  ui->graph->addGraph();
  ui->graph->graph(0)->setData(x, y);
  ui->graph->xAxis->setRange(ui->x_from->toPlainText().toDouble(),
                             ui->x_to->toPlainText().toDouble());
  ui->graph->yAxis->setRange(ui->y_from->toPlainText().toDouble(),
                             ui->y_to->toPlainText().toDouble());
  ui->graph->replot();
}
