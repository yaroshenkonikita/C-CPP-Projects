#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_srok_outpay_currentIndexChanged(int index) {
  if (index == 1) {
    globalTer = 12;
  } else if (index == 0) {
    globalTer = 1;
  }
}

void CreditCalc::on_annuitet_clicked() { globalStr = "A"; }

void CreditCalc::on_differen_clicked() { globalStr = "D"; }

void CreditCalc::on_res_button_clicked() {
  bool ok1 = false, ok2 = false, ok3 = false, err = false;
  double sum_credit = ui->sum_credit_value->text().toDouble(&ok1),
         srok = ui->srok_value->text().toInt(&ok2) * globalTer,
         stavka = ui->stavka_value->text().toDouble(&ok3), month = 0.0,
         over = 0.0, all = 0.0;
  if (ok1 && ok2 && ok3 && (srok <= 600 && srok > 0) &&
      (stavka <= 999.0 && stavka > 0.0)) {
    if (globalStr.back() == 'A') {
      err =
          credit_annuity(sum_credit, (double)srok, stavka, &month, &over, &all);
      if (!err) {
        ui->week_pay_value->setText(QString::number(month, 'f', 2));
        ui->overpay_value->setText(QString::number(over, 'f', 2));
        ui->itog_pay_value->setText(QString::number(all, 'f', 2));
      }
    } else if (globalStr.back() == 'D') {
      double month_pay_last = 0.0;
      err = credit_dif(sum_credit, srok, stavka, &month, &month_pay_last, &over,
                       &all);
      if (!err) {
        ui->week_pay_value->setText(QString::number(month, 'f', 2) + " ... " +
                                    QString::number(month_pay_last, 'f', 2));
        ui->overpay_value->setText(QString::number(over, 'f', 2));
        ui->itog_pay_value->setText(QString::number(all, 'f', 2));
      }
    }
  } else {
    err = true;
  }
  if (err) {
    QMessageBox m_MsgBox;
    m_MsgBox.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_MsgBox.setIcon(QMessageBox::Critical);
    m_MsgBox.setText("Ошибка! Введены неправильные данные!");
    m_MsgBox.setStandardButtons(QMessageBox::Retry);
    m_MsgBox.setStyleSheet("QLabel{min-width:270 px; font-size: 13px;} "
                           "QPushButton{ width:25px; font-size: 13px; }");
    if (m_MsgBox.exec() == QMessageBox::Ok)
      m_MsgBox.close();
  }
}
