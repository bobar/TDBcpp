#ifndef TDBSEARCHLIST_H
#define TDBSEARCHLIST_H

#include <QObject>
#include <QTreeWidget>
#include <QEvent>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlRecord>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAuth.h"

class TDBSearchList : public QTreeWidget
{
    private:
        void insert_item(QSqlQuery& query);
    public:
        TDBSearchList(QWidget* parent);
        ~TDBSearchList();

        void fill(QString string);
        QString current_trigramme();
};

#endif
