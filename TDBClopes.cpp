#include "TDBClopes.h"

TDBClopes::TDBClopes(QWidget* parent) :
  QDialog(parent)
{
  marque_combo = new QComboBox(this);

  TDBDatabase::open();

  QSqlQuery query;
  query.prepare("SELECT marque, prix FROM clopes");

  query.exec();
  if(query.first())
  marque_combo->addItem(query.record().value("marque").toString());

  while(query.next())
	marque_combo->addItem(query.record().value("marque").toString());

  TDBDatabase::close();

  setWindowTitle("Achat clopes");
  marque_label = new QLabel("Marque", this);
  quantite_label = new QLabel("Quantité", this);
  quantite_spin = new QSpinBox(this);
  quantite_spin->setValue(1);
  quantite_spin->setMinimum(1);

  layout = new QGridLayout(this);
  layout->addWidget(marque_label, 0, 0);
  layout->addWidget(quantite_label, 1, 0);

  layout->addWidget(marque_combo, 0, 1);
  layout->addWidget(quantite_spin, 1, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2, 0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
}

TDBClopes::~TDBClopes()
{
}

void TDBClopes::cancel_pressed()
{
  reject();
}

void TDBClopes::ok_pressed()
{
  TDBDatabase::open();

  marque = marque_combo->currentText();
  quantite = quantite_spin->value();

  QSqlQuery query;

  query.prepare("SELECT prix FROM clopes WHERE marque = :marque");
  query.bindValue(":marque", marque);
  query.exec();

  query.first();
  montant = query.record().value("prix").toInt() * quantite;

  TDBDatabase::close();

  accept();
}
