#include "TDBClopesAdmin.h"

TDBClopesAdmin::TDBClopesAdmin(QWidget* parent) :
    QDialog(parent)
{
    setWindowTitle("Gestion des clopes");

    clopes_list = new TDBClopesList(this);
    clopes_list->fill();
    clopes_list->show();

    mod_clopes_button = new QPushButton("Modifier...", this);
    create_clopes_button = new QPushButton("Nouvelles clopes...", this);
    delete_clopes_button = new QPushButton("Supprimer", this);
    ok_button = new QPushButton("OK", this);

    vlayout = new QVBoxLayout(this);

    vlayout->insertWidget(0, clopes_list, 1);
    vlayout->insertWidget(1, mod_clopes_button, 0);
    vlayout->insertWidget(2, create_clopes_button, 0);
    vlayout->insertWidget(3, delete_clopes_button, 0);
    vlayout->insertWidget(4, ok_button, 0);



    connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
    connect(mod_clopes_button, SIGNAL(pressed()), this, SLOT(mod_clopes_pressed()));
    connect(create_clopes_button, SIGNAL(pressed()), this, SLOT(create_clopes_pressed()));
    connect(delete_clopes_button, SIGNAL(pressed()), this, SLOT(delete_clopes_pressed()));
}

TDBClopesAdmin::~TDBClopesAdmin()
{
    delete clopes_list;
}

void TDBClopesAdmin::ok_pressed()
{
    accept();
}

void TDBClopesAdmin::mod_clopes_pressed()
{
    if (!clopes_list->currentItem())
        return;

    QString marque = clopes_list->currentItem()->text(0);

    TDBClopesModification cmod(this, marque);

    cmod.exec();

    clopes_list->clear();
    clopes_list->fill();
}

void TDBClopesAdmin::create_clopes_pressed()
{
    TDBClopesCreation ccreate(this);

    ccreate.exec();

    clopes_list->clear();
    clopes_list->fill();
}

void TDBClopesAdmin::delete_clopes_pressed()
{
    if (!clopes_list->currentItem())
        return;

    TDBDatabase::open();

    QSqlQuery query;
    QString marque = clopes_list->currentItem()->text(0);

    query.prepare("DELETE FROM clopes WHERE marque = :marque");
    query.bindValue(":marque", marque);
    query.exec();

    TDBDatabase::close();

    clopes_list->clear();
    clopes_list->fill();

}

