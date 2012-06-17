#include "TDBMainWindow.h"

void TDBMainWindow::reset_turnover()
{
	TDBDatabase::open();

    QSqlQuery query;

    try
    {
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (QMessageBox::question (this, "Warning", "Purger les chiffres d'affaire ?", QMessageBox::Yes | QMessageBox::No) ==  QMessageBox::Yes)
    {
        query.prepare("UPDATE accounts SET turnover = balance");
        query.exec();
    }
    update_money_display();

	TDBDatabase::close();
}

void TDBMainWindow::export_database()
{
    try
    {
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Export"), "");

    if (dirName.isEmpty())
        return;

    QString base_name = dirName.append("/").append(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

    QString tri_name = base_name;
    tri_name.append("_trigrammes.csv");
    QString tra_name = base_name;
    tra_name.append("_transactions.csv");
    QString rec_name = base_name;
    rec_name.append("_comptes_bob.csv");

    QFile file_tri(tri_name, this);

    file_tri.open(QIODevice::WriteOnly);
    QTextStream out_tri(&file_tri);
	
	TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT * FROM accounts");

    int count;
    int i;
    query.exec();
    if (query.first())
    {
        count = query.record().count();
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";

    }
    while (query.next())
    {
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";
    }

    file_tri.close();



    QFile file_tra(tra_name, this);

    file_tra.open(QIODevice::WriteOnly);
    QTextStream out_tra(&file_tra);
    query.prepare("SELECT * FROM transactions");

    query.exec();
    if (query.first())
    {
        count = query.record().count();
        for (i = 0; i < count; i++)
        {
            out_tra<<query.record().value(i).toString()<<"\t";
        }
        out_tra<<query.record().value(count).toString()<<"\n";

    }
    while (query.next())
    {
        for (i = 0; i < count; i++)
        {
            out_tra<<query.record().value(i).toString()<<"\t";
        }
        out_tra<<query.record().value(count).toString()<<"\n";
    }

    file_tra.close();


    QFile file_rec(rec_name, this);

    file_rec.open(QIODevice::WriteOnly);
    QTextStream out_rec(&file_rec);

    query.prepare("SELECT * FROM transactions WHERE id = 1 OR id2 = 1;");

    query.exec();
    if (query.first())
    {
        count = query.record().count();
        for (i = 0; i < count; i++)
        {
            out_rec<<query.record().value(i).toString()<<"\t";
        }
        out_rec<<query.record().value(count).toString()<<"\n";

    }
    while (query.next())
    {
        for (i = 0; i < count; i++)
        {
            out_rec<<query.record().value(i).toString()<<"\t";
        }
        out_rec<<query.record().value(count).toString()<<"\n";
    }

    file_rec.close();


    if (QMessageBox::question (this, "Warning", "Purger les historiques ?", QMessageBox::Yes | QMessageBox::No) ==  QMessageBox::Yes)
    {
        query.prepare("DELETE FROM transactions");
        query.exec();
    }

	TDBDatabase::close();
}

void TDBMainWindow::export_trigramme()
{
    try
    {
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    TDBTrigrammeDialog trigramme_dialog(this);
    if (!trigramme_dialog.exec())
        return;

    QString trigramme = trigramme_dialog.trigramme();

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Export"), "");

    if (dirName.isEmpty())
        return;

    QString base_name = dirName.append("/").append(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

    QString tri_name = base_name;
    (tri_name.append("_").append(trigramme)).append(".csv");


    QFile file_tri(tri_name, this);

    file_tri.open(QIODevice::WriteOnly);
    QTextStream out_tri(&file_tri);
	
	TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT * FROM accounts WHERE trigramme = :trigramme");

    query.bindValue(":trigramme", trigramme);

    int count;
    int i;
    query.exec();

    if (!query.first())
        return;
    count = query.record().count();
    for (i = 0; i < count; i++)
    {
        out_tri<<query.record().value(i).toString()<<"\t";
    }
    out_tri<<query.record().value(count).toString()<<"\n";

    int id = query.record().value("id").toInt();

    std::cout<<id<<std::endl;

    query.prepare("SELECT * FROM transactions WHERE id = :id or id2 = :id2");
    query.bindValue(":id", id);
    query.bindValue(":id2", id);

    query.exec();
    if (query.first())
    {
        count = query.record().count();
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";

    }
    while (query.next())
    {
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";
    }

	TDBDatabase::close();

    file_tri.close();
}

void TDBMainWindow::export_positivation()
{
    try
    {
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }
    int seuil = QInputDialog::getDouble(this, "Positivation", "Seuil :");


    QString dirName = QFileDialog::getExistingDirectory(this, tr("Export"), "");

    if (dirName.isEmpty())
        return;

    QString base_name = dirName.append("/").append(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

    QString tri_name = base_name;
    tri_name.append("_positivation").append(".csv");




    QFile file_tri(tri_name, this);

    file_tri.open(QIODevice::WriteOnly);
    QTextStream out_tri(&file_tri);
	
	TDBDatabase::open();

    QSqlQuery query;
    query.prepare("SELECT trigramme, name, first_name, nickname, promo, balance/100, casert FROM accounts WHERE balance < :seuil AND trigramme != 'BOB' AND status = 0 ORDER BY balance ASC");
    query.bindValue(":seuil", seuil);

    int count;
    int i;
    query.exec();
    if (query.first())
    {
        count = query.record().count();
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";

    }
    while (query.next())
    {
        for (i = 0; i < count; i++)
        {
            out_tri<<query.record().value(i).toString()<<"\t";
        }
        out_tri<<query.record().value(count).toString()<<"\n";
    }

    file_tri.close();

	TDBDatabase::close();
}
