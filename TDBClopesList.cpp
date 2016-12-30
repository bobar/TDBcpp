#include "TDBClopesList.h"

TDBClopesList::TDBClopesList (QWidget* parent) : QTreeWidget(parent)
{
    setColumnCount(2);
    QStringList header_strings;
    header_strings << "Marque" << "Prix";
    setHeaderLabels(header_strings);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

TDBClopesList::~TDBClopesList ()
{
    ;
}

void TDBClopesList::fill ()
{
    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT marque, prix FROM clopes ORDER BY marque");
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

void TDBClopesList::insert_item(QSqlQuery& query)
{
    QStringList item;
    QSqlRecord record;

    record = query.record();
    item.clear();

    item<<record.value("marque").toString()
        <<QString::number(record.value("prix").toInt()/100.0, 'f', 2);

    insertTopLevelItem(0,new QTreeWidgetItem(this, item));
}
