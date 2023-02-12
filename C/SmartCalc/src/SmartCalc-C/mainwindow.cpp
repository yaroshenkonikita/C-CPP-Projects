#include "mainwindow.h"

#include "credit/creditcalc.h"
#include "debit/debitcalc.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  init_ui();
  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(button_digit_pressed()));
  connect(ui->Button_X, SIGNAL(clicked()), this, SLOT(button_const_pressed()));
  connect(ui->Button_dot, SIGNAL(clicked()), this, SLOT(button_dot_pressed()));
  connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(button_oper_pressed()));
  connect(ui->Button_sin, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_cos, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_tan, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_atan, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_asin, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_acos, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_pow, SIGNAL(clicked()), this, SLOT(button_oper_pressed()));
  connect(ui->Button_log, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_ln, SIGNAL(clicked()), this,
          SLOT(button_function_pressed()));
  connect(ui->Button_plus, SIGNAL(clicked()), this,
          SLOT(button_unar_pressed()));
  connect(ui->Button_minus, SIGNAL(clicked()), this,
          SLOT(button_unar_pressed()));
  connect(ui->Button_devide, SIGNAL(clicked()), this,
          SLOT(button_oper_pressed()));
  connect(ui->Button_multiply, SIGNAL(clicked()), this,
          SLOT(button_oper_pressed()));
  connect(ui->Button_eller, SIGNAL(clicked()), this,
          SLOT(button_const_pressed()));
  connect(ui->Button_pi, SIGNAL(clicked()), this, SLOT(button_const_pressed()));
  connect(ui->Button_Clear, SIGNAL(clicked()), this, SLOT(clear_all_strings()));
  connect(ui->Button_bracket_open, SIGNAL(clicked()), this,
          SLOT(button_bracket_pressed()));
  connect(ui->Button_bracket_close, SIGNAL(clicked()), this,
          SLOT(button_bracket_pressed()));
}

void MainWindow::init_ui() {
  MainWindow::clear_all_strings();
  MainWindow::setFixedSize(513, 474);
  set_xy_graph();
}

void MainWindow::set_xy_graph() {
  x.clear();
  y.clear();
  ui->widget->clearPlottables();
  ui->widget->clearItems();
  x_sb = ui->spinBox_X->value();
  y_sb = ui->spinBox_Y->value();
  if (ui->onlyPlus_x_box->checkState()) {
    ui->widget->xAxis->setRange(0, x_sb);
  } else {
    ui->widget->xAxis->setRange(-x_sb, x_sb);
  }
  if (ui->onlyPlus_y_box->checkState()) {
    ui->widget->yAxis->setRange(0, y_sb);
  } else {
    ui->widget->yAxis->setRange(-y_sb, y_sb);
  }
}

void MainWindow::is_empty() {
  if (_stringCalc.isEmpty()) {
    add_any("0");
    number = true;
  }
}

void MainWindow::button_dot_pressed() {
  if (otvet) {
    clear_all_strings();
  }
  is_empty();
  if (dot > 0) {
    QString buff;
    _error_val(&buff, 4);
    ui->Calc_Label_Main->setText(buff);
  } else {
    if (constt) {
      add_any("*");
    }
    if (oper || !number) {
      add_any("0");
    }
    add_any(".");
    dot++;
    number = false;
    oper = 0;
    constt = false;
    unar = false;
  }
}

void MainWindow::button_unar_pressed() {
  is_empty();
  QPushButton *button = (QPushButton *)sender();
  if (dot == 1) {
    add_any("0");
  }
  if (oper) {
    if (_stringLabel.back() == '+' || _stringLabel.back() == '-') {
      _stringLabel.chop(1);
      _stringCalc.chop(1);
      oper--;
    }
  }
  add_any(button->text());
  unar = true;
  oper++;
  number = false;
  constt = false;
  otvet = false;
  dot = 0;
}

void MainWindow::button_oper_pressed() {
  is_empty();
  QPushButton *button = (QPushButton *)sender();
  int err = 0;
  if (unar && oper == 2) {
    _stringLabel.chop(1);
    _stringCalc.chop(1);
    unar = false;
    if (_stringLabel.back() == 'd') {
      _stringLabel.chop(3);
      _stringCalc.chop(1);
    } else {
      _stringLabel.chop(1);
      _stringCalc.chop(1);
    }
    oper = 0;
    constt = true;
  } else if (oper == 1 && !unar) {
    if (_stringLabel.back() == 'd') {
      _stringLabel.chop(3);
      _stringCalc.chop(1);
    } else {
      _stringLabel.chop(1);
      _stringCalc.chop(1);
    }
    oper = 0;
    constt = true;
  } else if (unar) {
    err = 1;
  }
  if ((number || constt) && !err) {
    if (dot == 1) {
      add_any("0");
    }
    add_any(button->text());
    oper++;
    number = false;
    constt = false;
    otvet = false;
    dot = 0;
    unar = false;
  } else if (!oper || err) {
    QString buff;
    _error_val(&buff, 1);
    ui->Calc_Label_Main->setText(buff);
  }
}

void MainWindow::button_function_pressed() {
  if (otvet) {
    clear_all_strings();
  }
  QPushButton *button = (QPushButton *)sender();
  if (number || constt) {
    _stringCalc.append("*");
  } else if (dot == 1) {
    add_any("0*");
  }
  add_any(button->text());
  oper = 0;
  number = false;
  constt = false;
  unar = false;
  dot = 0;
}

void MainWindow::button_digit_pressed() {
  if (otvet) {
    clear_all_strings();
  }
  QPushButton *button = (QPushButton *)sender();
  number = true;
  if (dot == 1) {
    dot++;
  }
  if (constt) {
    _stringCalc.append("*");
    constt = false;
  }
  add_any(button->text());
  oper = 0;
  dot = 0;
  unar = false;
}

void MainWindow::button_const_pressed() {
  if (otvet) {
    clear_all_strings();
  }
  QPushButton *button = (QPushButton *)sender();
  if (number || constt) {
    _stringCalc.append("*");
    number = false;
  } else if (dot == 1) {
    add_any("0");
    _stringCalc.append("*");
  }
  if (button->text() == "x") {
    x_count++;
  }
  add_any(button->text());
  constt = true;
  oper = 0;
  dot = 0;
  unar = false;
}

void MainWindow::button_bracket_pressed() {
  if (otvet) {
    clear_all_strings();
  }
  QPushButton *button = (QPushButton *)sender();
  bool flag = 0;
  if ((number || constt) && button->text() == "(") {
    _stringCalc.append("*");
  } else if (dot == 1 && button->text() == "(") {
    add_any("0");
    _stringCalc.append("*");
  } else if (dot == 1) {
    add_any("0");
    number = true;
    constt = false;
    oper = 0;
    dot = 0;
    unar = false;
  }
  if (button->text() == "(") {
    bracket++;
    add_any(button->text());
    flag = true;
    constt = false;
  } else {
    QString buff;
    if (bracket) {
      if (number || constt) {
        bracket--;
        add_any(button->text());
        flag = true;
        constt = true;
      } else {
        _error_val(&buff, 1);
        ui->Calc_Label_Main->setText(buff);
      }
    } else {
      _error_val(&buff, 1);
      ui->Calc_Label_Main->setText(buff);
    }
  }
  if (flag) {
    number = false;
    oper = 0;
    dot = 0;
    unar = false;
  }
}

void MainWindow::clear_all_strings() {
  MainWindow::_stringCalc.clear();
  MainWindow::_stringLabel.clear();
  ui->Calc_Label_Main->setText("0");
  MainWindow::dot = 0;
  MainWindow::bracket = 0;
  MainWindow::x_count = 0;
  MainWindow::number = false;
  MainWindow::oper = 0;
  MainWindow::constt = false;
  MainWindow::otvet = false;
  unar = false;
}

void MainWindow::on_Button_graph_clicked() {
  if (MainWindow::width() == 513) {
    MainWindow::setFixedSize(1000, 474);
  } else {
    MainWindow::setFixedSize(513, 474);
  }
}

void MainWindow::add_any(QString string) {
  bracket++;
  if (string == "sin") {
    _stringCalc.append("s(");
    _stringLabel.append("sin(");
  } else if (string == "cos") {
    _stringCalc.append("c(");
    _stringLabel.append("cos(");
  } else if (string == "tan") {
    _stringCalc.append("t(");
    _stringLabel.append("tan(");
  } else if (string == "asin") {
    _stringCalc.append("i(");
    _stringLabel.append("asin(");
  } else if (string == "acos") {
    _stringCalc.append("o(");
    _stringLabel.append("acos(");
  } else if (string == "atan") {
    _stringCalc.append("a(");
    _stringLabel.append("atan(");
  } else if (string == "log") {
    _stringCalc.append("g(");
    _stringLabel.append("log(");
  } else if (string == "ln") {
    _stringCalc.append("l(");
    _stringLabel.append("ln(");
  } else if (string == "√") {
    _stringCalc.append("q(");
    _stringLabel.append("√(");
  } else if (string == "mod") {
    _stringCalc.append("m");
    _stringLabel.append("mod");
    bracket--;
  } else if (string == "𝝅") {
    _stringCalc.append("f");
    _stringLabel.append("𝝅");
    bracket--;
  } else {
    _stringCalc.append(string);
    _stringLabel.append(string);
    bracket--;
  }
  ui->Calc_Label_Main->setText(_stringLabel);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Button_supp_err_pressed() {
  if (_stringLabel.isEmpty()) {
    ui->Calc_Label_Main->setText("0");
  } else {
    ui->Calc_Label_Main->setText(_stringLabel);
  }
}

void MainWindow::on_Button_equal_clicked() {
  QString result_QString;
  if (!bracket && !x_count && (number || constt)) {
    int res = 0;
    double result = 0.0;
    is_empty();
    QByteArray string_byte = _stringCalc.toLocal8Bit();
    char *result_string = string_byte.data();
    res = s21_calc(result_string, &result, result);
    clear_all_strings();
    if (!res) {
      result_QString = QString::number(result, 'f', 7);
      number = true;
      while (result_QString.back() == '0') {
        result_QString.chop(1);
      }
      if (result_QString.back() == '.') {
        result_QString.chop(1);
      }
      add_any(result_QString);
      otvet = true;
    } else {
      _error_val(&result_QString, res);
      ui->Calc_Label_Main->setText(result_QString);
    }
  } else if (!bracket && x_count && (number || constt)) {
    MainWindow::setFixedSize(1000, 474);
    set_xy_graph();
    QByteArray string_byte = _stringCalc.toLocal8Bit();
    char *result_string = string_byte.data();
    add_vektor(result_string, 0.0);
    double counter = 0.000001, point = (double)x_sb / 1000.0;
    while (counter < (double)x_sb) {
      add_vektor(result_string, counter);
      counter += point;
    }
    if (!(ui->onlyPlus_x_box->checkState())) {
      counter = -0.000001;
      while (counter > (double)-x_sb) {
        add_vektor(result_string, counter);
        counter -= point;
      }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    otvet = true;
  } else if (bracket) {
    _error_val(&result_QString, 3);
    ui->Calc_Label_Main->setText(result_QString);
  } else {
    _error_val(&result_QString, 1);
    ui->Calc_Label_Main->setText(result_QString);
  }
}

void MainWindow::add_vektor(char *result_string, double counter) {
  int res = 0;
  double result = 0.0;
  x.append(counter);
  res = s21_calc(result_string, &result, counter);
  if (!res) {
    y.append(result);
  } else {
    y.append(NAN);
  }
}

void MainWindow::_error_val(QString *str, int err) {
  if (err == 1) {
    *str = "Некоректное значение";
  } else if (err == 2) {
    *str = "Неправильное уравнение";
  } else if (err == 3) {
    *str = "Нехватает символов ')'";
  } else if (err == 4) {
    *str = "Нельзя ставить больше одной точки";
  } else if (err == 5) {
    *str = "Деление на ноль невозможно";
  } else if (err == 6) {
    *str = "Mod на ноль невозможно";
  } else if (err == 7) {
    *str = "Значение за пределами asin (-1 <= x <= 1)";
  } else if (err == 8) {
    *str = "Значение за пределами acos (-1 <= x <= 1)";
  } else if (err == 9) {
    *str = "Нет корня отрицательного числа";
  } else if (err == 10) {
    *str = "Нет десятичного логарифма x <= 0";
  } else if (err == 11) {
    *str = "Нет натурального логарифма x <= 0";
  } else if (err == 12) {
    *str = "Ошибка вычисления";
  }
}

void MainWindow::on_CreditCalc_button_clicked() {
  this->hide();
  CreditCalc credit_w;
  credit_w.setWindowFlags(credit_w.windowFlags() &
                          ~Qt::WindowContextHelpButtonHint);
  credit_w.exec();
  this->show();
}

void MainWindow::on_DebitCalc_button_clicked() {
  this->hide();
  DebitCalc debit_w;
  debit_w.setWindowFlags(debit_w.windowFlags() &
                         ~Qt::WindowContextHelpButtonHint);
  debit_w.setFixedSize(695, 519);
  debit_w.exec();
  this->show();
}
