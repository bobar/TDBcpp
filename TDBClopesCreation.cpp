#include "TDBClopesCreation.h"

TDBClopesCreation::TDBClopesCreation(QWidget* parent) :
  QDialog(parent)
{
  setWindowTitle("Création de clopes");
  marque_label = new QLabel("Marque", this);
  prix_label = new QLabel("Prix", this);

  marque_edit = new QLineEdit(this);

  prix_edit = new QLineEdit(this);


  layout = new QGridLayout(this);
  layout->addWidget(marque_label, 0, 0);
  layout->addWidget(prix_label, 1, 0);
  layout->addWidget(marque_edit, 0, 1);
  layout->addWidget(prix_edit, 1, 1);
    
  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2, 0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
}

TDBClopesCreation::~TDBClopesCreation()
{

}

void TDBClopesCreation::cancel_pressed()
{
  reject();
}

void TDBClopesCreation::ok_pressed()
{
  TDBDatabase::open();

  QSqlQuery query;
  query.prepare("INSERT INTO clopes (marque, prix) VALUES (:marque, :prix)");
  query.bindValue(":marque", marque_edit->text());
  query.bindValue(":prix", (int)(prix_edit->text().toDouble()*100+0.5));
  query.exec();
  
  TDBDatabase::open();

  accept();
}
