#include "TDBTransactionDialog.h"

TDBTransactionDialog::TDBTransactionDialog(QWidget* parent, QString title, QString initial) :
  QDialog(parent)
{
  setWindowTitle(title);

  valid = new QDoubleValidator(this);
  money_label = new QLabel("Montant", this);
  money_edit = new QLineEdit(initial.append(" "), this); // hack sordide
  money_edit->setSelection(1,1);
  money_edit->setValidator(valid);

  reason_label = new QLabel("Commentaire", this);
  reason_edit = new QLineEdit(this);

  layout = new QGridLayout(this);
  layout->addWidget(money_label, 0,0);
  layout->addWidget(money_edit, 0, 1);
  layout->addWidget(reason_label, 1, 0);
  layout->addWidget(reason_edit, 1, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2,0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));

  money_edit->setFocus(Qt::PopupFocusReason);
  money_edit->setSelection(1,1);
}

TDBTransactionDialog::~TDBTransactionDialog()
{
  delete layout;
  delete money_label;
  delete reason_label;
  delete money_edit;
  delete reason_edit;
  delete ok_button;
  delete cancel_button;
  delete valid;
}

void TDBTransactionDialog::cancel_pressed()
{
  reject();
}

void TDBTransactionDialog::ok_pressed()
{
  accept();
}
