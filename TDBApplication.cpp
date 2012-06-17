#include "TDBApplication.h"

TDBApplication::TDBApplication(int argc, char ** argv, QString host, QString db, QString login) :
        QApplication (argc, argv), database(new TDBDatabase(host, db, login))
{
    //QLocale::setDefault(QLocale::c());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("latin1"));
}

QStringList TDBApplication::parse(int argc, char ** argv, int* s)
{
	QString dbc_, abc_, bt_, host_, db_, login_;
	QRegExp help("--?h(elp)?", Qt::CaseInsensitive);
	QRegExp color("--?(dbc|default-background-colou?r)", Qt::CaseInsensitive);
	QRegExp alt_color("--?(abc|alternate-background-colou?r)", Qt::CaseInsensitive);
	QRegExp no_alt_color("--?no(abc|-alternate-background-colou?r)", Qt::CaseInsensitive);
	QRegExp db("--?(db|database)", Qt::CaseInsensitive);
	QRegExp host("--?host", Qt::CaseInsensitive);
	QRegExp login("--?l(ogin)?", Qt::CaseInsensitive);
	QRegExp bt("--?b(anque)?", Qt::CaseInsensitive);

	for(int i =1; i < argc; i++)
	{
		QString arg(argv[i]);

		if(help.exactMatch(arg))
		{
			usage(argv[0]);
			*s = -1;
			return QStringList();
		}
		else if(no_alt_color.exactMatch(arg))
			abc_ = QString();

		else if( ++i == argc )
		{
			std::cerr << QString("Erreur de syntaxe près de %1\n\n").arg(arg).toStdString();
			usage(argv[0]);
			*s = 1;
			return QStringList();
		}
		else if(color.exactMatch(arg))
			dbc_ = QString("TDBMainWindow{background-color: %1;}").arg(argv[i]);

		else if(alt_color.exactMatch(arg))
			abc_ = QString("TDBMainWindow{background-color: %1;}").arg(argv[i]);

		else if(host.exactMatch(arg))
			host_ = QString(argv[i]);

		else if(db.exactMatch(arg))
			db_ = QString(argv[i]);

		else if(login.exactMatch(arg))
			login_ = QString(argv[i]);

		else if(bt.exactMatch(arg))
			bt_ = QString(argv[i]);

		else
		{
			std::cerr << QString("Option %1 non reconnue\n\n").arg(arg).toStdString();
			usage(argv[0]);
			*s = 1;
			return QStringList();
		}
	}

	QStringList l;
	l << dbc_ << abc_ << bt_ << host_ << db_ << login_;
	return l;
}

void TDBApplication::usage(char name[])
{
	std::cout << QString(name).append(" [-h|--help] [-dbc|--default-background-color color] [-abc|--alternate-background-color color] [-host address] [-l|--login credential] [-db|--database name]\n\n").toStdString();
	std::cout << QString("  -h --help\t\tAffiche cette aide.\n\n").toStdString();
	std::cout << QString("  -b --banque trigramme\tMet 'trigramme' comme compte banque au lieu de BôB\n").toStdString();
	std::cout << QString("  -dbc --default-background-color color\n\t\t\tDonne la couleur 'color' à la fenêtre (format 'rgb(rrr,ggg,bbb)' en décimal ou bien '#RRGGBB' en hexa).\n").toStdString();
	std::cout << QString("  -abc --alternate-background-color color\n\t\t\tDonne la couleur 'color' à la fenêtre quand un binet sert de banque.\n\n").toStdString();
	std::cout << QString("  -noabc --no-alternate-background-color\n\t\t\tMet le style par défaut quand un binet sert de banque.\n\n").toStdString();
	std::cout << QString("  -l --login credential\tMet le login pour la base de données à 'credential'.\n").toStdString();
	std::cout << QString("  -db --database name\tMet la base de données à 'name'.\n").toStdString();
	std::cout << QString("  -host address\t\tMet l'adresse du serveur mysql à 'address'.\n").toStdString();
}

int TDBApplication::auth(QWidget* parent, int auth_level)
{
    TDBAuthDialog auth_dialog(parent);

    if (!auth_dialog.exec() || auth_dialog.get_perm() < auth_level)
    {
        critical(parent, "Erreur d'authentification");
        throw TDBAuthException();
    }

    return auth_dialog.get_admin();
}

void TDBApplication::critical(QWidget* parent, QString text)
{
    QMessageBox::critical(parent, "TDB", text);
}

TDBApplication::~TDBApplication()
{
    TDBDatabase::close(true);
	delete database;
}

