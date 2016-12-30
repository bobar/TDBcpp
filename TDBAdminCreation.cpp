#include "TDBAdminCreation.h"

TDBAdminCreation::TDBAdminCreation(QWidget* parent) :
  QDialog(parent)
{
  setWindowTitle("Création d'un admin");
  trigramme_label = new QLabel("Trigramme", this);
  passwd1_label = new QLabel("Mot de passe", this);
  passwd2_label = new QLabel("Vérification", this);
  perm_label = new QLabel("Niveau", this);
 
  trigramme_edit = new QLineEdit(this);
  trigramme_edit->setInputMask(">NNN");

  perm_combo = new QComboBox(this);

  perm_combo->addItem("Pékin", pekin);
  perm_combo->addItem("Ami du BôB", ami_du_bob);
  perm_combo->addItem("Ancien BôBarman", bobarman);
  perm_combo->addItem("BôBarman", root);
  perm_combo->setCurrentIndex(perm_combo->findData(pekin));

  passwd1_edit = new QLineEdit(this);
  passwd1_edit->setEchoMode(QLineEdit::Password);
  passwd2_edit = new QLineEdit(this);
  passwd2_edit->setEchoMode(QLineEdit::Password);

  layout = new QGridLayout(this);
  layout->addWidget(trigramme_label, 0, 0);
  layout->addWidget(trigramme_edit, 0, 1);
  layout->addWidget(passwd1_label, 1, 0);
  layout->addWidget(passwd1_edit, 1, 1);
  layout->addWidget(passwd2_label, 2, 0);
  layout->addWidget(passwd2_edit, 2, 1);
  layout->addWidget(perm_label, 3, 0);
  layout->addWidget(perm_combo, 3, 1);
 

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button,4, 0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button,4, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
}

TDBAdminCreation::~TDBAdminCreation()
{

}

void TDBAdminCreation::cancel_pressed()
{
  reject();
}

void TDBAdminCreation::ok_pressed()
{
  int perm = perm_combo->itemData(perm_combo->currentIndex()).toInt();
  int id;

  TDBDatabase::open();
  
  QSqlQuery query;
  query.prepare("SELECT id FROM accounts WHERE trigramme = :trig");
  query.bindValue("trig", trigramme_edit->text());

  query.exec();
  if (!query.first())
    reject();

  id = query.record().value("id").toInt();

  if (passwd1_edit->text() == passwd2_edit->text())

  query.prepare("INSERT INTO admins (id, permissions, passwd) VALUES (:id, :perm, :passwd)");
  query.bindValue(":perm", perm);
  query.bindValue(":id", id);
  query.bindValue(":passwd", QCryptographicHash::hash(QByteArray().append(passwd1_edit->text()), QCryptographicHash::Md5).toHex());

  query.exec();
  
  TDBDatabase::close();

  accept();
}
