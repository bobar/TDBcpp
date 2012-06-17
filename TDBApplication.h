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

#define TDBApp (TDBApplication*)qApp

class TDBApplication : public QApplication
{
    Q_OBJECT

private:
    TDBDatabase* database;

public:
    TDBApplication (int argc, char ** argv, QString host, QString db, QString login);
    ~TDBApplication ();

	static QStringList parse(int argc, char ** argv, int* status);
    static int auth(QWidget* parent, int auth_level);
    static void critical(QWidget* parent, QString text);
	static void usage(char name[]);
};

#endif
