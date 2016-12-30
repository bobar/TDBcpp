#include "TDBRefillDialog.h"

TDBRefillDialog::TDBRefillDialog(QWidget* parent) :
  QDialog(parent)
{
  setWindowTitle("Approvisionnement");

  valid = new QDoubleValidator(this);
  money_label = new QLabel("Montant", this);
  money_edit = new QLineEdit(this);
  money_edit->setValidator(valid);

  reason_label = new QLabel("Mode", this);
  reason_combo = new QComboBox(this);

  reason_combo->addItem("Espèce", 1);
  reason_combo->addItem("Chèque", 2);

  layout = new QGridLayout(this);
  layout->addWidget(money_label, 0,0);
  layout->addWidget(money_edit, 0, 1);
  layout->addWidget(reason_label, 1, 0);
  layout->addWidget(reason_combo, 1, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2,0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));

  money_edit->setFocus(Qt::PopupFocusReason);
}

TDBRefillDialog::~TDBRefillDialog()
{
  delete layout;
  delete money_label;
  delete reason_combo;
  delete money_edit;
  delete reason_label;
  delete ok_button;
  delete cancel_button;
  delete valid;
}

void TDBRefillDialog::cancel_pressed()
{
  reject();
}

void TDBRefillDialog::ok_pressed()
{
  accept();
}

QString TDBRefillDialog::reason()
{
  switch(reason_combo->currentIndex())
    {
    case 0:
      return "espèce";
    case 1:
      return "chèque";
    }
  return QString();
}
