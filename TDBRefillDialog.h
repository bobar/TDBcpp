#ifndef TDBREFILLDIALOG_H
#define TDBREFILLDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QValidator>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>

#include "TDBApplication.h"

class TDBRefillDialog : public QDialog
{
  Q_OBJECT

 private:

  QGridLayout* layout;
  QLabel* money_label;
  QLabel* reason_label;

  QLineEdit* money_edit;
  QComboBox* reason_combo;
  QValidator* valid;

  QPushButton* ok_button;
  QPushButton* cancel_button;

 public:
  TDBRefillDialog(QWidget* parent);
  ~TDBRefillDialog();
  int money() {return money_edit->text().toDouble()*100+0.5;}
  QString reason();

  public slots:
  void ok_pressed();
  void cancel_pressed();
};

#endif
