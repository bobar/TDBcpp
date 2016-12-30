#ifndef TDBCLOPESLIST_H
#define TDBCLOPESLIST_H

#include <QSqlQuery>
#include <QStringList>
#include <QSqlRecord>
#include <QObject>
#include <QTreeWidget>
#include <QEvent>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAuth.h"

class TDBClopesList : public QTreeWidget
{
    private:
        void insert_item(QSqlQuery& query);
        void modify_admin(QString trigramme);

    public:
        TDBClopesList(QWidget* parent);
        ~TDBClopesList();

        void fill();
        void update();
};

#endif
