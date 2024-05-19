#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

#include "ui_plotwindow.h"

#include "../controller/controller.h"

namespace Ui {
class plotwindow;
}

class plotwindow : public QWidget {
    Q_OBJECT
public:
    explicit plotwindow(QWidget *parent = nullptr);
    ~plotwindow();

signals:
 void graphwindow();

private slots:
  void on_plot_clicked();
  void on_draw_graph_clicked();

 private:
  Ui::plotwindow *ui;

  double step, count_x, result;
  QVector<double> x, y;
};

#endif // PLOT_H
