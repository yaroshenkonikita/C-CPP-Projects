#include "debitcalc.h"

#include "ui_debitcalc.h"

DebitCalc::DebitCalc(QWidget *parent) : QDialog(parent), ui(new Ui::DebitCalc) {
  ui->setupUi(this);
  DebitCalc::setFixedSize(695, 507);
}

DebitCalc::~DebitCalc() { delete ui; }

void DebitCalc::on_result_button_clicked() {
  QList<QLineEdit *> r1 = {ui->lineEdit_r1_1, ui->lineEdit_r1_2,
                           ui->lineEdit_r1_3, ui->lineEdit_r1_4,
                           ui->lineEdit_r1_5, ui->lineEdit_r1_6,
                           ui->lineEdit_r1_7, ui->lineEdit_r1_8,
                           ui->lineEdit_r1_9, ui->lineEdit_r1_10},
                     r2 = {ui->lineEdit_r2_1, ui->lineEdit_r2_2,
                           ui->lineEdit_r2_3, ui->lineEdit_r2_4,
                           ui->lineEdit_r2_5, ui->lineEdit_r2_6,
                           ui->lineEdit_r2_7, ui->lineEdit_r2_8,
                           ui->lineEdit_r2_9, ui->lineEdit_r2_10},
                     w1 = {ui->lineEdit_w1_1, ui->lineEdit_w1_2,
                           ui->lineEdit_w1_3, ui->lineEdit_w1_4,
                           ui->lineEdit_w1_5, ui->lineEdit_w1_6,
                           ui->lineEdit_w1_7, ui->lineEdit_w1_8,
                           ui->lineEdit_w1_9, ui->lineEdit_w1_10},
                     w2 = {ui->lineEdit_w2_1, ui->lineEdit_w2_2,
                           ui->lineEdit_w2_3, ui->lineEdit_w2_4,
                           ui->lineEdit_w2_5, ui->lineEdit_w2_6,
                           ui->lineEdit_w2_7, ui->lineEdit_w2_8,
                           ui->lineEdit_w2_9, ui->lineEdit_w2_10};
  int countR = 0, errorUi = 0, countW = 0;
  double wi1[10] = {0}, wi2[10] = {0}, re1[10] = {0}, re2[10] = {0};
  for (int i = 0, j = 0; i < 10 && !errorUi; i++) {
    if (!r1.at(i)->text().isEmpty() && !r2.at(i)->text().isEmpty() &&
        !errorUi) {
      bool ok1 = false, ok2 = false;
      re1[j] = r1.at(i)->text().toInt(&ok1);
      re2[j] = r2.at(i)->text().toDouble(&ok2);
      if (ok1 && ok2 && re1[j] < 601 && re1[j] >= 1) {
        j++;
        countR++;
      } else {
        errorUi = 1;
      }
    }
  }
  if (!errorUi) {
    for (int i = 0, k = 0; i < 10; i++) {
      if (!w1.at(i)->text().isEmpty() && !w2.at(i)->text().isEmpty() &&
          !errorUi) {
        bool ok1 = false, ok2 = false;
        wi1[k] = w1.at(i)->text().toInt(&ok1);
        wi2[k] = w2.at(i)->text().toDouble(&ok2);
        if (ok1 && ok2 && wi1[k] < 601 && wi1[k] >= 1) {
          k++;
          countW++;
        } else {
          errorUi = 1;
        }
      }
    }
    if (!errorUi) {
      bool k1 = false, k2 = false, k3 = false, k4 = false;
      double all_sum = ui->summa_vklada_value->text().toDouble(&k1),
             tern = ui->srok_razmesheniya_value->text().toInt(&k2) * globalTer,
             interest = ui->procen_stavka_value->text().toDouble(&k3),
             tax = ui->stavka_naloga_value->text().toDouble(&k4),
             all_interest = 0.0, all_tax = 0.0, all_sum_after = 0.0;
      if (k1 && k2 && k3 && k4) {
        if (globalPeriod == 0) {
          globalPeriod = (int)tern;
        }
        errorUi = deposit_calculator(
            re1, re2, countR, wi1, wi2, countW, all_sum, tern, interest, tax,
            globalPeriod, globalKap, &all_interest, &all_tax, &all_sum_after);
        if (!errorUi) {
          ui->res_procent_value->setText(QString::number(all_interest, 'f', 2));
          ui->tax_value->setText(QString::number(all_tax, 'f', 2));
          ui->itog_sum_value->setText(QString::number(all_sum_after, 'f', 2));
        }
      } else {
        errorUi = 1;
      }
    }
  }
  if (errorUi) {
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

void DebitCalc::on_kapital_proc_clicked(bool checked) {
  if (checked) {
    globalKap = 1;
  } else {
    globalKap = 0;
  }
}

void DebitCalc::on_size_of_deposit_currentIndexChanged(int index) {
  if (index) {
    globalTer = 12;
  } else if (!index) {
    globalTer = 1;
  }
}

void DebitCalc::on_hz_output_currentIndexChanged(int index) {
  if (!index) {
    globalPeriod = 1;
  } else if (index == 1) {
    globalPeriod = 6;
  } else if (index == 2) {
    globalPeriod = 12;
  } else if (index == 3) {
    globalPeriod = 0;
  }
}
