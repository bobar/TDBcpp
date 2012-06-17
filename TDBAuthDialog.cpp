#include "TDBAuthDialog.h"

TDBAuthDialog::TDBAuthDialog(QWidget* parent) :
  QDialog(parent)
{
  setWindowTitle("Authentification");
  trigramme_label = new QLabel("Trigramme", this);
  trigramme_edit = new QLineEdit(this); // hack sordide
  trigramme_edit->setInputMask(">NNN");

  passwd_label = new QLabel("Mot de passe", this);
  passwd_edit = new QLineEdit(this);
  passwd_edit->setEchoMode(QLineEdit::Password);

  layout = new QGridLayout(this);
  layout->addWidget(trigramme_label, 0, 0);
  layout->addWidget(trigramme_edit, 0, 1);
  layout->addWidget(passwd_label, 1, 0);
  layout->addWidget(passwd_edit, 1, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2, 0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
  trigramme_edit->setFocus(Qt::PopupFocusReason);
}

TDBAuthDialog::~TDBAuthDialog()
{
  delete layout;
  delete trigramme_label;
  delete trigramme_edit;
  delete passwd_label;
  delete passwd_edit;
  delete ok_button;
  delete cancel_button;
}

void TDBAuthDialog::cancel_pressed()
{
  reject();
}

void TDBAuthDialog::ok_pressed()
{
  TDBDatabase::open();

  QSqlQuery query;
  query.prepare("SELECT accounts.id as admin_id, permissions FROM admins LEFT JOIN accounts ON accounts.id = admins.id WHERE accounts.trigramme = :trigramme AND passwd = :password");
  query.bindValue(":trigramme", trigramme_edit->text());
  query.bindValue(":password", QCryptographicHash::hash(QByteArray().append(passwd_edit->text()), QCryptographicHash::Md5).toHex());

  query.exec();
	
  TDBDatabase::close();
  
  if (query.first())
    {
      admin = query.record().value("admin_id").toInt();
      perm = query.record().value("permissions").toInt();

      accept();
    }
  else
	reject();
}

int TDBAuthDialog::get_admin()
{
  return admin;
}

int TDBAuthDialog::get_perm()
{
  return perm;
}
