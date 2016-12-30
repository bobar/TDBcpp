#include "TDBAdminList.h"

TDBAdminList::TDBAdminList (QWidget* parent) : QTreeWidget(parent)
{
  setColumnCount(3);
  QStringList header_strings;
  header_strings << "Trigramme" << "Nom" << "Niveau";
  setHeaderLabels(header_strings);
  setSelectionMode(QAbstractItemView::SingleSelection);
}

TDBAdminList::~TDBAdminList ()
{
  ;
}

void TDBAdminList::fill ()
{
  TDBDatabase::open();
  
  QSqlQuery query;
  query.prepare("SELECT accounts.trigramme as tri, accounts.nickname as nick, admins.permissions as perm FROM accounts JOIN admins ON accounts.id = admins.id ORDER BY perm DESC, tri DESC");
  query.exec();

  if(query.first())
    {
      insert_item(query);
    }
  while(query.next())
    {
      insert_item(query);
    }
  
  TDBDatabase::close();
}

void TDBAdminList::insert_item(QSqlQuery& query)
{
  QStringList item;
  QSqlRecord record;
  
  record = query.record();
  item.clear();

  item<<record.value("tri").toString()
      <<record.value("nick").toString();

  switch(record.value("perm").toInt())
    {
    case pekin:
      item<<"pékin";
      break;
    case ami_du_bob:
      item<<"Ami du BôB";
      break;
    case bobarman:
      item<<"Ancien BôBarman";
      break;
    case root:
      item<<"BôBarman";
      break;
    }
  insertTopLevelItem(0,new QTreeWidgetItem(this, item));
}
