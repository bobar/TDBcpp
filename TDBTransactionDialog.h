#ifndef TDBTRANSACTIONDIALOG_H
#define TDBTRANSACTIONDIALOG_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QDialog>
#include <QGridLayout>
#include <QValidator>

#include "TDBApplication.h"

class TDBTransactionDialog : public QDialog
{
  Q_OBJECT

 private:

  QGridLayout* layout;
  QLabel* money_label;
  QLabel* reason_label;

  QLineEdit* money_edit;
  QLineEdit* reason_edit;
  QValidator* valid;

  QPushButton* ok_button;
  QPushButton* cancel_button;

 public:
  TDBTransactionDialog(QWidget* parent, QString title, QString initial = QString());
  ~TDBTransactionDialog();
  int money() {return money_edit->text().toDouble()*100+0.5;}
  QString reason() {return reason_edit->text();}

  public slots:
  void ok_pressed();
  void cancel_pressed();
};

#endif
