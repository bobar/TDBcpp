#ifndef TDBAUTHDIALOG_H
#define TDBAUTHDIALOG_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QSqlQuery> 
#include <QString>
#include <QVariant>
#include <QSqlRecord> 
#include <QCryptographicHash>
#include <QByteArray>
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QValidator>

// included by TDBApplication.h
// #include "TDBApplication.h"
#include <QDebug>
#include "TDBDatabase.h"

class TDBAuthDialog : public QDialog
{
  Q_OBJECT

 private:
  int admin;
  int perm;

  QGridLayout* layout;
  QLabel* trigramme_label;
  QLabel* passwd_label;
  QLineEdit* trigramme_edit;
  QLineEdit* passwd_edit;

  QPushButton* ok_button;
  QPushButton* cancel_button;

 public:
  TDBAuthDialog(QWidget* parent = 0);
  ~TDBAuthDialog();

  int get_admin();
  int get_perm();
  
  public slots:
  void ok_pressed();
  void cancel_pressed();
};

#endif
