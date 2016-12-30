#include "TDBSearchList.h"

TDBSearchList::TDBSearchList (QWidget* parent) : QTreeWidget(parent)
{
    setColumnCount(5);
    QStringList header_strings;
    header_strings << "Trigramme" << "Nom" << "Prénom"<< "Surnom" << "Promo";
    setHeaderLabels(header_strings);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

TDBSearchList::~TDBSearchList ()
{
}

void TDBSearchList::fill (QString string)
{
	TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT trigramme, name, first_name, nickname, promo FROM accounts WHERE name LIKE :name OR first_name LIKE :fn OR nickname LIKE :nm");
    query.bindValue(":name", QString("%").append(string).append(QString("%")));
    query.bindValue(":fn", QString("%").append(string).append(QString("%")));
    query.bindValue(":nm", QString("%").append(string).append(QString("%")));


    query.exec();

    if (query.first())
    {
        insert_item(query);
    }
    while (query.next())
    {
        insert_item(query);
    }

	TDBDatabase::close();
}

void TDBSearchList::insert_item(QSqlQuery& query)
{
    QStringList item;
    QSqlRecord record;

    record = query.record();
    item.clear();

    item<<record.value("trigramme").toString()
    <<record.value("name").toString()
    <<record.value("first_name").toString()
    <<record.value("nickname").toString()
    <<record.value("promo").toString();

    insertTopLevelItem(0,new QTreeWidgetItem(this, item));
}
