#ifndef TDBHISTORY_H
#define TDBHISTORY_H

#include <QSqlQuery>
#include <QStringList>
#include <QSqlRecord>
#include <QDateTime>
#include <QTreeWidget>
#include <QEvent>

#include "TDBApplication.h"

#include "TDBAccount.h"


class TDBHistory : public QTreeWidget
{
private:
    void insert_item(QSqlQuery& query);

public:
    TDBHistory(QWidget* parent);

    void fill(TDBAccount* account);
    void update(TDBAccount* account);
    void remove_last();
};

#endif
