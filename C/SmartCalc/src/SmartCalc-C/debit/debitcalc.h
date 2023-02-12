#ifndef DEBITCALC_H
#define DEBITCALC_H

#include <QDialog>
#include <QMessageBox>

#include "../mainwindow.h"

namespace Ui {
class DebitCalc;
}

class DebitCalc : public QDialog {
  Q_OBJECT

public:
  explicit DebitCalc(QWidget *parent = nullptr);
  ~DebitCalc();

private slots:
  void on_result_button_clicked();

  void on_kapital_proc_clicked(bool checked);

  void on_size_of_deposit_currentIndexChanged(int index);

  void on_hz_output_currentIndexChanged(int index);

private:
  Ui::DebitCalc *ui;

public:
  int globalTer = 1;
  int globalPeriod = 1;
  int globalKap = 0;
};

#endif // DEBITCALC_H
