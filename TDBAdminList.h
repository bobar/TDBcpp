#ifndef TDBADMINLIST_H
#define TDBADMINLIST_H

#include <QSqlQuery> 
#include <QStringList>
#include <QSqlRecord> 
#include <QObject>
#include <QTreeWidget>
#include <QEvent>
#include <QSqlQuery> 

#include "TDBDatabase.h"
#include "TDBApplication.h"

#include "TDBAuth.h"

class TDBAdminList : public QTreeWidget
{
 private:
  void insert_item(QSqlQuery& query);
  void modify_admin(QString trigramme);

 public:
  TDBAdminList(QWidget* parent);
  ~TDBAdminList();

  void fill();
  void update();
};

#endif
