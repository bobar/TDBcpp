#include "TDBAccount.h"
#include "unused.h"

TDBAccount::TDBAccount(const QString& tri) throw (TDBTrigrammeInconnuException)
{
    TDBDatabase::open();
    QSqlQuery query;
    query.prepare("SELECT * from accounts WHERE trigramme = :trigramme");  // je crois que c'est moche en fait
    query.bindValue(":trigramme", tri);
    query.exec();
    if (!query.first())
    {
        throw TDBTrigrammeInconnuException(tri);
    }
    QSqlRecord record = query.record();
    TDBDatabase::close();

    trigramme = tri;
    id = record.value("id").toInt();
    name = record.value("name").toString();
    first_name = record.value("first_name").toString();
    nickname = record.value("nickname").toString();
    category = record.value("status").toInt();
    casert = record.value("casert").toString();
    promo = record.value("promo").toInt();
    eMail = record.value("mail").toString();
    picture = record.value("picture").toString();
    balance = record.value("balance").toInt();
    turnover = record.value("turnover").toInt();
}

TDBAccount::TDBAccount(const QString& tri,
                       const QString& n,
                       const QString& fn,
                       const QString& nn,
                       const int cat,
                       const QString cst,
                       const int init_bal,
                       const int p,
                       const QString mail,
                       const QString pct) throw (TDBTrigrammeException) :
        id(0), trigramme(tri), name(n), first_name(fn), nickname(nn), category(cat),
        casert(cst), balance(init_bal), promo(p), eMail(mail), picture(pct)
{
    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT MAX(id) as maxid FROM accounts;");
    query.exec();
    query.first();
    QSqlRecord record = query.record();
    id = record.value("maxid").toInt();
    id++;


    query.prepare("INSERT into accounts (id, trigramme, name, first_name, nickname, status, casert, promo, mail, picture, balance, turnover) VALUES (:id, :trigramme, :name, :first_name, :nickname, :status, :casert, :promo, :mail, :picture, :balance, :turnover)");  // je crois que c'est moche en fait
    query.bindValue(":id", id);
    query.bindValue(":trigramme", trigramme);
    query.bindValue(":name", name);
    query.bindValue(":first_name", first_name);
    query.bindValue(":nickname", nickname);
    query.bindValue(":status", category);
    query.bindValue(":casert", casert);
    query.bindValue(":promo", promo);
    query.bindValue(":mail", eMail);
    query.bindValue(":picture", picture);
    query.bindValue(":balance", balance);
    query.bindValue(":turnover", balance);

    if (!query.exec())
        throw TDBTrigrammeExistantException(tri);

    TDBDatabase::close();
}

bool TDBAccount::transaction(int money, QString reason, TDBAccount* dest_account, int admin_id)
{
    // TODO ici parfois le TDBAccount dest_account jean-jacques durablement -- meilleure vérifications à faire ?
    if (id == dest_account->id || dest_account->id == 0)
        return false;

#if 0
    if (balance >= 0.0 && (money + balance) < 0.0)
        sendmail("Tu viens de passer en négatif", "Ramène tes sous");
    else if ((balance >= -20.0 && (money + balance) < -20.0)
             || (balance >= -100.0 && (money + balance) < -100.0)
             || (balance >= -500.0 && (money + balance) < -500.0)
             || (balance >= -1000.0 && (money + balance) < -1000.0))
        sendmail("Tu es toujours en négatif", "Ramène tes sous");
#endif

    balance += money;
    dest_account->balance -= money;

    if( (money > 0) xor (reason == "Annulation") )
        turnover += money;
    else
        dest_account->turnover += money;

    //QSqlDatabase::database().transaction();


    TDBDatabase::open();

    QSqlQuery query1(QSqlDatabase::database());
    query1.prepare("UPDATE accounts SET balance = balance + (:delta) WHERE id = :id");
    query1.bindValue(":delta", money);
    query1.bindValue(":id", id);
    query1.exec();

    QSqlQuery query2(QSqlDatabase::database());
    query2.prepare("INSERT INTO transactions (id, id2, price, comment, admin, date) VALUES (:id, :id2, :price, :comment, :admin, :now)");
    query2.bindValue(":id", id);
    query2.bindValue(":id2", dest_account->id);
    query2.bindValue(":price", money);
    query2.bindValue(":comment", reason);
    query2.bindValue(":admin", admin_id);
    query2.bindValue(":now", QDateTime::currentDateTime().toTime_t());
    query2.exec();

    QSqlQuery query3(QSqlDatabase::database());
    query3.prepare("UPDATE accounts SET balance = balance - (:delta) WHERE id = :id");
    query3.bindValue(":delta", money);
    query3.bindValue(":id", dest_account->id);
    query3.exec();

    if(reason != "Annulation")
    {
        QSqlQuery query4(QSqlDatabase::database());
        query4.prepare("UPDATE accounts SET turnover = turnover + ABS(:delta) WHERE id = :id");
        query4.bindValue(":delta", money);
        query4.bindValue(":id", money>0?id:dest_account->id);
        query4.exec();
    }
    else
    {
        QSqlQuery query4(QSqlDatabase::database());
        query4.prepare("UPDATE accounts SET turnover = turnover - ABS(:delta) WHERE id = :id");
        query4.bindValue(":delta", money);
        query4.bindValue(":id", money<0?id:dest_account->id);
        query4.exec();
    }

    TDBDatabase::close();

    // QSqlDatabase::database().rollback();

    return true;
}

void TDBAccount::refresh_money()
{
    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT balance,turnover FROM accounts WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    query.first();
    QSqlRecord record = query.record();

    balance = record.value("balance").toInt();
    turnover = record.value("turnover").toInt();

    TDBDatabase::close();
}


void TDBAccount::modif(const QString& tri,
                       const QString& n,
                       const QString& fn,
                       const QString& nn,
                       const int cat,
                       const QString cst,
                       const int p,
                       const QString mail,
                       const QString pct) throw (TDBTrigrammeException)
{
    trigramme = tri;
    name = n;
    first_name = fn;
    nickname = nn;
    category = cat;
    casert = cst;
    promo = p;
    eMail = mail;
    picture = pct;

    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("UPDATE accounts SET trigramme = :trigramme, name = :name, first_name = :first_name, nickname = :nickname, status = :status, casert = :casert, promo = :promo, mail = :mail, picture = :picture WHERE id = :id");  // je crois que c'est moche en fait
    query.bindValue(":trigramme", trigramme);
    query.bindValue(":name", name);
    query.bindValue(":first_name", first_name);
    query.bindValue(":nickname", nickname);
    query.bindValue(":status", category);
    query.bindValue(":casert", casert);
    query.bindValue(":promo", promo);
    query.bindValue(":mail", eMail);
    query.bindValue(":picture", picture);
    query.bindValue(":id", id);

    if (!query.exec())
        throw TDBTrigrammeException(tri);

    TDBDatabase::close();
}

void TDBAccount::erase()
{
    TDBDatabase::open();

    QSqlQuery query;
    query.prepare("DELETE FROM accounts WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    TDBDatabase::close();
}

void TDBAccount::sendmail(QString UNUSED(subject), QString UNUSED(body))
{
    /*
    if (eMail.isEmpty())
    {
        QMessageBox::critical(0, QString("Envoi de mail"),
                  QString("Le compte n'a pas d'adresse mail."));
        return;
    }

    FILE* pipe = popen(QString("msmtp ").append(eMail).toAscii().constData(), "w");

    QString sender = QString("BôBar <bobar@frankiz.polytechnique.fr>");

    QString mail;
    mail.append("From: ").append(sender).append("\n");
    mail.append("To: ").append(first_name)
      .append(" ")
      .append(name)
      .append(" <").append(eMail).append(">\n");
    mail.append("Subject: ").append(subject).append("\n\n");
    mail.append(body);

    const char* c_mail = mail.toAscii().constData();

    fprintf(pipe, c_mail);
    pclose(pipe);
    */
}

