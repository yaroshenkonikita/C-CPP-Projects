#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "qcustomplot.h"

extern "C" {
#include "../calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void button_digit_pressed();
  void on_Button_graph_clicked();
  void clear_all_strings();
  void init_ui();
  void button_dot_pressed();
  void button_function_pressed();
  void button_const_pressed();
  void add_any(QString string);
  void button_oper_pressed();
  void button_bracket_pressed();
  void is_empty();
  void _error_val(QString *str, int err);
  void set_xy_graph();
  void button_unar_pressed();
  void add_vektor(char *result_string, double counter);

  void on_CreditCalc_button_clicked();
  void on_DebitCalc_button_clicked();
  void on_Button_supp_err_pressed();
  void on_Button_equal_clicked();

private:
  Ui::MainWindow *ui;
  QString _stringLabel, _stringCalc;
  int bracket, dot, x_count, x_sb, y_sb, oper;
  bool number, constt, otvet, unar;

  QVector<double> x, y;
};
#endif // MAINWINDOW_H
