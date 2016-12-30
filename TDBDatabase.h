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
    TDBDatabase(QString host, QString database, QString login);
    ~TDBDatabase();
    //static TDBDatabase* default_db;
};

#endif
