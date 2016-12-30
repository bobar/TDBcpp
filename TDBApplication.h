#ifndef TDBAPPLICATION_H
#define TDBAPPLICATION_H

#include <stdio.h>
#include <iostream>

#include <QRegExp>
#include <QTextCodec>
#include <QLocale>
#include <QApplication>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "TDBDatabase.h"
#include "TDBAuthDialog.h"
#include "TDBExceptions.h"

#define TDBApp ((TDBApplication*)qApp)

class TDBApplication : public QApplication
{
    Q_OBJECT

private:
    TDBDatabase* database;

    QString ds, as, default_trig;

public:
    TDBApplication (int argc, char ** argv);
    ~TDBApplication ();

    int parse();
    void usage(QString name);

    static int auth(QWidget* parent, int auth_level);
    static void critical(QWidget* parent, QString text);

    QString default_style();
    QString alternate_style();
    QString default_bank();
};

#endif
