#include "TDBClopesModification.h"

TDBClopesModification::TDBClopesModification(QWidget* parent, QString m) : QDialog(parent)
{
  setWindowTitle("Modification de clopes");
  layout = new QGridLayout(this);
  marque_label = new QLabel("marque", this);
  prix_label = new QLabel("prix", this);
  marque_edit = new QLineEdit();
  prix_edit = new QLineEdit();
  prix_edit->setValidator(new QDoubleValidator(this));
  ok_button = new QPushButton("OK", this);
  cancel_button = new QPushButton("Annuler", this);

  marque = m;

  TDBDatabase::open();

  QSqlQuery query;
  query.prepare("SELECT prix/100 as prix FROM clopes WHERE marque = :marque");
  query.bindValue(":marque", marque);

  query.exec();
  query.first();

  TDBDatabase::close();

  marque_edit->setText(marque);
  prix_edit->setText(query.record().value("prix").toString());
  

  layout->addWidget(marque_label, 0, 0);
  layout->addWidget(prix_label, 1, 0);

  layout->addWidget(marque_edit, 0, 1);
  layout->addWidget(prix_edit, 1, 1);

  layout->addWidget(ok_button, 2, 0);
  layout->addWidget(cancel_button, 2, 1);

  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
}

TDBClopesModification::~TDBClopesModification()
{}


void TDBClopesModification::cancel_pressed()
{
  reject();
}

void TDBClopesModification::ok_pressed()
{
  TDBDatabase::open();

  QSqlQuery query;
  query.prepare("UPDATE clopes SET marque = :marque, prix = :prix WHERE marque = :oldmarque");
  query.bindValue(":marque", marque_edit->text());
  query.bindValue(":prix", (int)(prix_edit->text().toDouble()*100+0.5));
  query.bindValue(":oldmarque", marque);

  query.exec();

  TDBDatabase::close();

  accept();
}
