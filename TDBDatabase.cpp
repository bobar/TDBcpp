#include "TDBDatabase.h"

TDBDatabase* default_db;

int TDBDatabase::open_count = 0;

TDBDatabase::TDBDatabase(QString host, QString database, QString login) : db (QSqlDatabase::addDatabase("QMYSQL"))
{
    QString pw("mythemec");
    if(!host.isNull() || !database.isNull() || !login.isNull())
    {
        TDBPasswordDialog pwd;
        pwd.exec();
        pw = pwd.get_pw();
    }

    db.setDatabaseName(database.isNull()?"tdb":database);
    db.setUserName(login.isNull()?"bobar":login);
    db.setPassword(pw);
    db.setHostName(host.isNull()?"localhost":host);
    default_db = this;
}

void TDBDatabase::open()
{
    bool act = false;
    // need to open
    if(TDBDatabase::open_count == 0 || !default_db->db.isOpen())
    {
        TDBDatabase::open_count = 0;
        act = true;

        if (!default_db->db.open())
        {
            qDebug() << QSqlDatabase::drivers();
            QMessageBox::critical(0, "zou.sql", default_db->db.lastError().text());
            return;
        }
    }

    TDBDatabase::open_count++;
}

void TDBDatabase::close(bool force)
{
    bool act = false;
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
            act = true;
        }

        TDBDatabase::open_count = 0;
    }
}

TDBDatabase::~TDBDatabase()
{
    default_db = 0;
}
