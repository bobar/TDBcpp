#include "TDBDatabase.h"

TDBDatabase *TDBDatabase::default_db = NULL;
int TDBDatabase::open_count = 0;

TDBDatabase::TDBDatabase(QString host, QString database, QString login, QString password)
    : db (QSqlDatabase::addDatabase("QMYSQL"))
{
    if (host.isNull() || login.isNull() || database.isNull())
        qFatal("Error in database information");

    if(password.isNull())
    {
        TDBPasswordDialog pwd;
        pwd.exec();
        password = pwd.get_pw();
    }

    db.setDatabaseName(database);
    db.setUserName(login);
    db.setPassword(password);
    db.setHostName(host);
}

void TDBDatabase::open()
{
    if (default_db == NULL)
        qFatal("Default db was not set\n");

    // need to open
    if(TDBDatabase::open_count == 0 || !default_db->db.isOpen())
    {
        TDBDatabase::open_count = 0;

        if (!default_db->db.open())
        {
            qDebug() << QSqlDatabase::drivers();
            QMessageBox::critical(0, "zou.sql", QString("Impossible de se connecter à la base de données:\n").append(default_db->db.lastError().text()));
            exit(1);
        }
    }

    TDBDatabase::open_count++;
}

void TDBDatabase::close(bool force)
{
    // leave open
    if(!force && TDBDatabase::open_count > 1 && default_db->db.isOpen())
        TDBDatabase::open_count--;

    // closing
    else
    {
        // link not broken
        if(force || TDBDatabase::open_count <= 1)
        {
            default_db->db.close();
        }

        TDBDatabase::open_count = 0;
    }
}

TDBDatabase::~TDBDatabase()
{
    default_db = NULL;
}
