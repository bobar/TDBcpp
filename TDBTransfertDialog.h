#ifndef TDBTRANSFERTDIALOG_H
#define TDBTRANSFERTDIALOG_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QDialog>
#include <QGridLayout>
#include <QValidator>

#include "TDBApplication.h"

#include "TDBTrigrammeDialog.h"

class TDBTransfertDialog : public QDialog
{
  Q_OBJECT

 private:

  QGridLayout* layout;

  QLabel* trigramme1_label;
  QLabel* trigramme2_label;
  QLabel* money_label;
  QLabel* reason_label;

  QLineEdit* trigramme1_edit;
  QLineEdit* trigramme2_edit;
  QLineEdit* money_edit;
  QLineEdit* reason_edit;
  QValidator* valid;
  QValidator* t_valid;


  QPushButton* ok_button;
  QPushButton* cancel_button;

 public:
  TDBTransfertDialog(QWidget* parent, QString title, QString trigramme1 = QString());
  ~TDBTransfertDialog();
  int money() {return money_edit->text().toDouble()*100+0.5;}
  QString reason() {return reason_edit->text();}
  QString trigramme1() {return trigramme1_edit->text();}
  QString trigramme2() {return trigramme2_edit->text();}


  public slots:
  void ok_pressed();
  void cancel_pressed();
};

#endif
