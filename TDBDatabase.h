#ifndef TDBDATABASE_H
#define TDBDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

// included by TDBApplication.h
#include <QDebug>

#include "TDBPasswordDialog.h"

class TDBDatabase
{
protected:
    QSqlDatabase db;
    static int open_count;
    static TDBDatabase* default_db;
    TDBDatabase(QString host, QString database, QString login, QString password);
    ~TDBDatabase();

public:
    bool transaction ()
    {
        return db.transaction();
    };
    bool commit ()
    {
        return db.commit();
    };
    static void open();
    static void close(bool force = false);

    static inline void setup_db(QString host, QString database, QString login, QString password)
    {
        default_db = new TDBDatabase(host, database, login, password);
    }
    static inline void remove_db()
    {
        delete default_db;
        default_db = NULL;
    }

};

#endif
