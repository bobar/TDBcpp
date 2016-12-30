#include "TDBHistory.h"

TDBHistory::TDBHistory (QWidget* parent) : QTreeWidget(parent)
{
    setColumnCount(3);
    QStringList header_strings;
    header_strings << "Montant" << "Compte" << "Commentaire" << "Admin" << "Date";
    setHeaderLabels(header_strings);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setSortingEnabled(true);

    setFocusPolicy(Qt::NoFocus);
}

void TDBHistory::fill (TDBAccount* account)
{
    // affichage par défaut, effort minimal puisque la fenêtre doit être vide actuellement
    sortByColumn(-1);

    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT price, transactions.id, id2, comment, admin, date, accounts.trigramme as tr2 FROM transactions LEFT JOIN accounts ON accounts.id = transactions.id2 WHERE transactions.id = :id1"
                  "  UNION SELECT -price as price, transactions.id, id2, comment, admin, date, accounts.trigramme as tr2 FROM transactions LEFT JOIN accounts ON accounts.id = transactions.id WHERE transactions.id2= :id2 ORDER BY date DESC");
    query.bindValue(":id1", account->get_id());
    query.bindValue(":id2", account->get_id());
    query.exec();

    if (query.first())
        insert_item(query);

    while (query.next())
        insert_item(query);

    TDBDatabase::close();
}

void TDBHistory::update (TDBAccount* account)
{
    clear();
    fill(account);
}

void TDBHistory::insert_item(QSqlQuery& query)
{
    QStringList item;
    QSqlRecord record;

    record = query.record();
    item.clear();

    int admin_id = record.value("admin").toInt();
    QString admin;

    // si un admin est intervenu dans cette ligne d'historique, on récupère son trigramme pour l'afficher.
    if (admin_id)
    {
        TDBDatabase::open();

        QSqlQuery admin_query;
        admin_query.prepare("SELECT trigramme FROM accounts WHERE id = :id");
        admin_query.bindValue(":id", admin_id);
        admin_query.exec();
        admin_query.first();
        admin = admin_query.record().value("trigramme").toString();

        TDBDatabase::close();
    }
    else
        admin = "";

    item<<QString::number(record.value("price").toDouble()/100, 'f', 2)
    <<record.value("tr2").toString()
    <<record.value("comment").toString()
    <<admin
    <<QDateTime::fromTime_t(record.value("date").toInt()).toString("dd/MM/yyyy hh:mm:ss");

    addTopLevelItem(new QTreeWidgetItem(this, item));
}
