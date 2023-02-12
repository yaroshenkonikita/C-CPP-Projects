#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>
#include <QMessageBox>

#include "../mainwindow.h"

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

  int globalTer = 1;
  QString globalStr = "A";

private slots:
  void on_srok_outpay_currentIndexChanged(int index);

  void on_annuitet_clicked();

  void on_differen_clicked();

  void on_res_button_clicked();

private:
  Ui::CreditCalc *ui;
};

#endif // CREDITCALC_H
