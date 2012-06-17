#include "TDBApplication.h"
#include "TDBMainWindow.h"

int main (int argc, char** argv)
{
    int i = 0;
    QStringList options = TDBApplication::parse(argc, argv, &i);

    if( i != 0 )
        exit(i<0?0:i);

    QString dbc = options.at(0), abc = options.at(1), bt = options.at(2), host = options.at(3), db = options.at(4), login = options.at(5);

    if(abc.isNull())
        abc = QString("background-color: #ff9911;");
    if(bt.isNull())
        bt = QString("BOB");

    TDBApplication app(argc, argv, host, db, login);

    TDBMainWindow mythe(dbc, abc, bt);
    mythe.show();


    return app.exec();
}
