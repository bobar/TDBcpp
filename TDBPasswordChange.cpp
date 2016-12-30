#include "TDBPasswordChange.h"

TDBPasswordChange::TDBPasswordChange(QWidget* parent, int i) :
  QDialog(parent), id(i)
{
  setWindowTitle("Modification du mot de passe");
  passwd1_label = new QLabel("Nouveau mot de passe", this);
  passwd1_edit = new QLineEdit(this);
  passwd1_edit->setEchoMode(QLineEdit::Password);

  passwd2_label = new QLabel("Vérification", this);
  passwd2_edit = new QLineEdit(this);
  passwd2_edit->setEchoMode(QLineEdit::Password);

  layout = new QGridLayout(this);
  layout->addWidget(passwd1_label, 0, 0);
  layout->addWidget(passwd1_edit, 0, 1);
  layout->addWidget(passwd2_label, 1, 0);
  layout->addWidget(passwd2_edit, 1, 1);

  ok_button = new QPushButton("OK", this);
  layout->addWidget(ok_button, 2, 0);
  cancel_button = new QPushButton("Cancel", this);
  layout->addWidget(cancel_button, 2, 1);

  setLayout(layout);
  passwd1_edit->setFocus(Qt::PopupFocusReason);

  connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
}

TDBPasswordChange::~TDBPasswordChange()
{
  delete layout;
  delete passwd1_label;
  delete passwd2_label;
  delete passwd1_edit;
  delete passwd2_edit;
  delete ok_button;
  delete cancel_button;
}

void TDBPasswordChange::cancel_pressed()
{
  reject();
}

void TDBPasswordChange::ok_pressed()
{
  if (passwd1_edit->text() == passwd2_edit->text())
    {
	  TDBDatabase::open();

      QSqlQuery query;
      query.prepare("UPDATE admins SET passwd = :passwd WHERE id = :id");
      query.bindValue(":passwd", QCryptographicHash::hash(QByteArray().append(passwd1_edit->text()), QCryptographicHash::Md5).toHex());
      query.bindValue(":id", id);
      query.exec();
      accept();

	  TDBDatabase::close();
    }
  reject();
}
