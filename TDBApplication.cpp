#include "TDBApplication.h"

TDBApplication::TDBApplication(int argc, char ** argv) :
        QApplication (argc, argv)
{
    //QLocale::setDefault(QLocale::c());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("latin1"));

    // default stuff
    abc = QString("TDBMainWindow{background-color: #f91;}");
    dbc = styleSheet();
    default_trig = "BOB";
}

int TDBApplication::parse()
{
    // first rule out QCoreApplication's own args (he doesn't parse them before... dunnoh why)
	QStringList opts;
	QStringList opts_extra_arg;
    #ifdef x11
    opts << "cmap";
    opts_extra_arg << "dograb" << "sync" << "cmap" << "im" << "inputstyle" << "display" << "geometry" << "fn" << "bg" << "fg" << "btn" << "name" << "title" << "visual" << "ncols";
    #endif

    #ifdef QT_DEBUG
    opts << "nograb";
    #endif
    opts << "style=" << "stylesheet=" << "session=" << "qmljsdebugger=";
    opts_extra_arg << "style" << "stylesheet" << "session" << "widgetcount" << "reverse" << "graphicssystem";

    // enfin le vrai boulot
	QRegExp ignores(QString("-(%1)").arg(opts.join("|")), Qt::CaseInsensitive);
	QRegExp ignores_extra_arg(QString("^-(%1)").arg(opts_extra_arg.join("|")), Qt::CaseInsensitive);

	QString host, db, login;

	QRegExp help("--?h(elp)?", Qt::CaseInsensitive);
	QRegExp color("--?(dbc|default-background-colou?r)", Qt::CaseInsensitive);
	QRegExp alt_color("--?(abc|alternate-background-colou?r)", Qt::CaseInsensitive);
	QRegExp no_alt_color("--?no(abc|-alternate-background-colou?r)", Qt::CaseInsensitive);
	QRegExp database("--?(db|database)", Qt::CaseInsensitive);
	QRegExp hostname("--?host", Qt::CaseInsensitive);
	QRegExp credential("--?l(ogin)?", Qt::CaseInsensitive);
	QRegExp bank_trigramme("--?b(anque)?", Qt::CaseInsensitive);

	QStringList args = arguments();

	for(int i = 1; i < args.size(); i++)
	{
		QString arg = args.at(i);

		if(ignores.exactMatch(arg))
            continue;
		if(ignores_extra_arg.indexIn(arg) > -1)
		{
		    i++;
            continue;
		}
		if(help.exactMatch(arg))
		{
			usage(args.at(0));
			return -1;
		}
		else if(no_alt_color.exactMatch(arg))
			abc = QString();

		else if( ++i == args.size() )
		{
			std::cerr << QString("Erreur de syntaxe vers %1\n").arg(arg).toStdString();
			usage(args.at(0));
			return 1;
		}
        else if(color.exactMatch(arg))
            dbc = QString("TDBMainWindow{background-color: %1;}").arg(args.at(++i));

        else if(alt_color.exactMatch(arg))
            abc = QString("TDBMainWindow{background-color: %1;}").arg(args.at(++i));

        else if(hostname.exactMatch(arg))
            host = args.at(++i);

        else if(database.exactMatch(arg))
            db = args.at(++i);

        else if(credential.exactMatch(arg))
            login = args.at(++i);

        else if(bank_trigramme.exactMatch(arg))
            default_trig = args.at(++i).toUpper();
		else
		{
			std::cerr << QString("Option %1 non reconnue\n").arg(arg).toStdString();
			//usage(args.at(0));
			//return 2;
		}
	}

	this->database = new TDBDatabase(host, db, login);

	return 0;
}

void TDBApplication::usage(QString name)
{
	std::cout << name.append(" [-h|--help] [-dbc|--default-background-color color] [-abc|--alternate-background-color color] [-host address] [-l|--login credential] [-db|--database name]\n\n").toStdString();
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

QString TDBApplication::default_style()
{
    return dbc;
}
QString TDBApplication::alternate_style()
{
    return abc;
}
QString TDBApplication::default_bank()
{
    return default_trig;
}
