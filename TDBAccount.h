#ifndef TDBACCOUNT_H
#define TDBACCOUNT_H

#include <stdio.h>

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlField>
#include <QDateTime>
#include <QMessageBox>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAuth.h"
#include "TDBExceptions.h"

enum TDBCat
{
    X_platal,
    X_ancien,
    binet,
    personnel,
    supop,
    autre
};

class TDBAccount
{
protected:
    int id;
    QString trigramme;
    QString name;
    QString first_name;
    QString nickname;
    int category;
    QString casert;
    int balance;
    int turnover;
    int promo;
    QString eMail;
    QString picture;

public:
    TDBAccount(const QString& tri) throw (TDBTrigrammeInconnuException);
    TDBAccount(const QString& tri,
               const QString& n,
               const QString& fn,
               const QString& nn,
               const int cat,
               const QString cst,
               const int init_bal,
               const int p,
               const QString mail,
               const QString pct) throw (TDBTrigrammeException);
    int get_id(void)
    {
        return id;
    }
    QString get_name(void)
    {
        return name;
    }
    QString get_first_name(void)
    {
        return first_name;
    }
    QString get_nickname(void)
    {
        return nickname;
    }
    int get_balance(void)
    {
        return balance;
    }
    int get_turnover(void)
    {
        return (turnover - balance);
    }
    QString get_casert(void)
    {
        return casert;
    }
    int get_category(void)
    {
        return category;
    }
    QString get_category_str(void)
    {
        switch (category)
        {
        case X_platal:
            return "X Platalien";
            break;
        case X_ancien:
            return "X ancien";
            break;
        case binet:
            return "Binet";
            break;
        case personnel:
            return "Personnel";
            break;
        case supop:
            return "Supop";
            break;
        default:
        case autre:
            return "Autre";
            break;
        }
    }
    int get_promo(void)
    {
        return promo;
    }
    QString get_trigramme(void)
    {
        return trigramme;
    }
    QString get_mail(void)
    {
        return eMail;
    }
    QString get_picture(void)
    {
        return picture;
    }
	void refresh_money();
    void sendmail(QString subject, QString body);

    bool transaction(int money, QString reason, TDBAccount* dest_account, int admin_id);
    void modif(const QString& tri,
               const QString& n,
               const QString& fn,
               const QString& nn,
               const int cat,
               const QString cst,
               const int p,
               const QString mail,
               const QString pct) throw (TDBTrigrammeException);
    void erase();
};

#endif
