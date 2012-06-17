#include "TDBTransfertDialog.h"


TDBTransfertDialog::TDBTransfertDialog(QWidget* parent, QString title, QString trigramme1) :
  QDialog(parent)
{
  setWindowTitle(title);
  t_valid = new TDBTrigrammeValidator(this);
  valid = new QDoubleValidator(this);
  money_label = new QLabel("Montant", this);

  trigramme1_label = new QLabel("De", this);
  trigramme2_label = new QLabel("Vers", this);

  trigramme1_edit = new QLineEdit(trigramme1, this);
  trigramme2_edit = new QLineEdit(this);
  trigramme1_edit->setValidator(t_valid);
  trigramme2_edit->setValidator(t_valid);
  money_edit = new QLineEdit(this);
  money_edit->setValidator(valid);

  reason_label = new QLabel("Commentaire", this);
  reason_edit = new QLineEdit(this);

  layout = new QGridLayout(this);
  layout->addWidget(trigramme1_label, 0,0);
  layout->addWidget(trigramme1_edit, 0, 1);
  layout->addWidget(trigramme2_label, 1,0);
  layout->addWidget(trigramme2_edit, 1, 1);
  layout->addWidget(money_label, 2,0);
  layout->addWidget(money_edit, 2, 1);
  layout->addWidget(reason_label, 3, 0);
  layout->addWidget(reason_edit, 3, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 4,0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 4, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));

  trigramme1_edit->setFocus(Qt::PopupFocusReason);
}

TDBTransfertDialog::~TDBTransfertDialog()
{
  delete layout;
  delete trigramme1_label;
  delete trigramme2_label;
  delete money_label;
  delete reason_label;
  delete trigramme1_edit;
  delete trigramme2_edit;
  delete money_edit;
  delete reason_edit;
  delete ok_button;
  delete cancel_button;
  delete valid;
}

void TDBTransfertDialog::cancel_pressed()
{
  reject();
}

void TDBTransfertDialog::ok_pressed()
{
  accept();
}
