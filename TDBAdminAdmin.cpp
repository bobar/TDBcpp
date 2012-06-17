#include "TDBAdminAdmin.h"

TDBAdminAdmin::TDBAdminAdmin(QWidget* parent) :
  QDialog(parent)
{
  admin_list = new TDBAdminList(this);
  admin_list->fill();
  admin_list->show();

  mod_admin_button = new QPushButton("Modifier...", this);
  create_admin_button = new QPushButton("Nouvel admin...", this);
  delete_admin_button = new QPushButton("Supprimer", this);
  ok_button = new QPushButton("OK", this);

  vlayout = new QVBoxLayout(this);

  vlayout->insertWidget(0, admin_list, 1);
  vlayout->insertWidget(1, mod_admin_button, 0);
  vlayout->insertWidget(2, create_admin_button, 0);
  vlayout->insertWidget(3, delete_admin_button, 0);
  vlayout->insertWidget(4, ok_button, 0);

  

  connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
  connect(mod_admin_button, SIGNAL(pressed()), this, SLOT(mod_admin_pressed()));
  connect(create_admin_button, SIGNAL(pressed()), this, SLOT(create_admin_pressed()));
  connect(delete_admin_button, SIGNAL(pressed()), this, SLOT(delete_admin_pressed()));
}

TDBAdminAdmin::~TDBAdminAdmin()
{
  delete admin_list;
}

void TDBAdminAdmin::ok_pressed()
{
  accept();
}

void TDBAdminAdmin::mod_admin_pressed()
{
  if (!admin_list->currentItem())
    return;

  QString trigramme = admin_list->currentItem()->text(0);

  TDBAdminModification admod(this, trigramme);

  admod.exec();

  admin_list->clear();
  admin_list->fill();
}

void TDBAdminAdmin::create_admin_pressed()
{
  TDBAdminCreation adcreate(this);

  adcreate.exec();

  admin_list->clear();
  admin_list->fill();
}

void TDBAdminAdmin::delete_admin_pressed()
{
  if (!admin_list->currentItem())
    return;

  TDBDatabase::open();
  
  QSqlQuery query;
  query.prepare("SELECT id FROM accounts WHERE trigramme = :trig");
  query.bindValue("trig", admin_list->currentItem()->text(0));
  query.exec();
  query.first();
  int id = query.record().value("id").toInt();

  query.prepare("DELETE FROM admins WHERE id = :id");
  query.bindValue(":id", id);
  query.exec();

  admin_list->clear();
  admin_list->fill();
  
  TDBDatabase::close();

}

