#include "TDBApplication.h"

TDBApplication::TDBApplication(int & argc, char ** argv) :
        QApplication (argc, argv)
{
    // default stuff
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
    QRegExp ignores(QString("-(%1)").arg(opts.join("|")), Qt::CaseInsensitive);
    QRegExp ignores_extra_arg(QString("^-(%1)").arg(opts_extra_arg.join("|")), Qt::CaseInsensitive);


    // enfin le vrai boulot
    QString host("localhost"), db("tdb"), login("root"), base_colors, alt_colors;
    bool no_alternate_crap = false, night_style = false;

    QRegExp help("--?h(elp)?", Qt::CaseInsensitive);
    QRegExp dbc("--?(dbc|default-background-colou?r)", Qt::CaseInsensitive);
    QRegExp dfc("--?(dfc|default-front-colou?r)", Qt::CaseInsensitive);
    QRegExp abc("--?(abc|alternate-front-colou?r)", Qt::CaseInsensitive);
    QRegExp afc("--?(afc|alternate-background-colou?r)", Qt::CaseInsensitive);
    QRegExp no_alt_color("--?no(ac|-alternate-colou?rs)", Qt::CaseInsensitive);
    QRegExp night("--?night", Qt::CaseInsensitive);
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
            no_alternate_crap = true;

        else if(night.exactMatch(arg))
            night_style = true;

        else if( ++i == args.size() )
        {
            std::cerr << QString("Erreur de syntaxe vers %1\n").arg(arg).toStdString();
            usage(args.at(0));
            return 1;
        }
        else if(dbc.exactMatch(arg))
            base_colors.append(QString("background-color: %1;").arg(args.at(i)));

        else if(dfc.exactMatch(arg))
            base_colors.append(QString("color: %1;").arg(args.at(i)));

        else if(abc.exactMatch(arg))
            alt_colors.append(QString("background-color: %1;").arg(args.at(i)));

        else if(afc.exactMatch(arg))
            alt_colors.append(QString("color: %1;").arg(args.at(i)));

        else if(hostname.exactMatch(arg))
            host = args.at(i);

        else if(database.exactMatch(arg))
            db = args.at(i);

        else if(credential.exactMatch(arg))
            login = args.at(i);

        else if(bank_trigramme.exactMatch(arg))
            default_trig = args.at(i).toUpper();
        else
        {
            std::cerr << QString("Option %1 non reconnue\n").arg(arg).toStdString();
            //usage(args.at(0));
            //return 2;
        }
    }

    // gestion base de données
    TDBDatabase::setup_db(host, db, login, QString());

    // on créé les style sheets en fonction de ce qui a été donné
    if(!no_alternate_crap && alt_colors.isEmpty())
        alt_colors = QString("background-color: #f93;color:#000;");

    if( (!alt_colors.isEmpty() && no_alternate_crap) || (!base_colors.isEmpty() && night_style) )
    {
        std::cerr << QString("Des options de couleurs contradictoires ont été définies.\n").toStdString();
        usage(args.at(0));
        return 3;
    }
    else if(night_style)
        ds = QString("QWidget{\n\tbackground-color: #222;\n\tcolor: #3F3;\n}\n")
            .append("TDBMainWindow, TDBMainWindow > QLabel, QHeaderView, QToolBar, QToolBar *, QMenuBar, QMenu, QLineEdit{\n\tbackground-color: #555;\n\tcolor: #3F3;\n}\n")
            .append("QMenu::item:enabled:selected, QToolBar *:enabled:hover, QTreeView, TDBMainWindow QPushButton{\n\tbackground-color: rgb(255,255,255,25);color:#0F0;\n}\n")
            .append(":disabled {\n\tcolor: #080;\n}");

    else if(!base_colors.isEmpty())
        ds = QString("QWidget{\n\t%1\n}\n").arg(base_colors)
            .append("QMenu::item:enabled:selected, QToolBar *:enabled:hover, QTreeView, TDBMainWindow QPushButton{\n\tbackground-color: rgb(255,255,255,125);\n}\n");
            //.append(":disabled,QMenu::item::disabled {\n\tbackground-color: rgb(0,0,0,75);\n}");

    else if(!alt_colors.isEmpty())
        as = QString("TDBMainWindow, TDBMainWindow > QLabel, QHeaderView, QToolBar, QToolBar *, QMenuBar, QMenu, QLineEdit{\n\t%1\n}\n").arg(alt_colors)
            .append("QMenu::item:enabled:selected, QToolBar *:enabled:hover, QTreeView, TDBMainWindow QPushButton{\n\tbackground-color: rgb(255,255,255,125);\n}\n");
            //.append(":disabled,QMenu::item::disabled {\n\tbackground-color: rgb(0,0,0,75);\n}");

    ds.append("QToolBar {\n\tspacing: 3px;\n\tpadding: 3px;\n}\n");
    as.append("QToolBar {\n\tspacing: 3px;\n\tpadding: 3px;\n}\n");

    return 0;
}

void TDBApplication::usage(QString name)
{
    std::cout << QString("\n%1 lance le tdb (mythe !)\n\n").arg(name).toStdString();
    std::cout << QString("Usage : %1").arg(name).toStdString();
    std::cout << QString("\t[-h|--help] [-host address] [-l|--login credential] \n").toStdString();
    std::cout << QString("\t\t\t[-db|--database name] [ color_options ]\n\n").toStdString();

    std::cout << QString("  -h --help\t\tAffiche cette aide\n\n").toStdString();
    std::cout << QString("  -b --banque trigramme\tMet 'trigramme' comme compte banque au lieu de BôB\n").toStdString();

    std::cout << QString("  -l --login credential\tUtilise 'credential' comme login pour la base de données\n").toStdString();
    std::cout << QString("  -db --database name\tUtilise 'name' comme nom de base de données\n").toStdString();
    std::cout << QString("  -host address\t\tUtilise 'address' comme serveur mysql\n").toStdString();

    std::cout << QString("\n Options des couleurs (color_options)\n").toStdString();

    std::cout << QString("  --default-background-color color\tDonne la couleur ``color'' à la fenêtre\n").toStdString();
    std::cout << QString("  -dbc color\n\n").toStdString();

    std::cout << QString("  --default-front-color color\t\tDonne la couleur ``color'' au texte\n").toStdString();
    std::cout << QString("  -dfc color\n\n").toStdString();

    std::cout << QString("  --alternate-background-color color\tDonne la couleur ``color'' à la fenêtre\n").toStdString();
    std::cout << QString("  -abc color\t\t\t\tquand un binet sert de banque.\n\n").toStdString();

    std::cout << QString("  --alternate-front-color color\t\tDonne la couleur ``color'' au texte\n").toStdString();
    std::cout << QString("  -afc color\t\t\t\tquand un binet sert de banque.\n\n").toStdString();

    std::cout << QString("  --no-alternate-colors\t\t\tGarde le style par défaut quand\n").toStdString();
    std::cout << QString("  -noac\t\t\t\t\tun binet sert de banque.\n\n").toStdString();

    std::cout << QString("  --night\t\t\t\tSet de couleurs sombres, parce qu'on\n").toStdString();
    std::cout << QString("\t\t\t\t\taime bien la CK et les hémos\n\n").toStdString();

    std::cout << QString("\tLes couleurs se spécifient au format ``rgb(rrr,ggg,bbb)'', \n").toStdString();
    std::cout << QString("\t``rgb(rrr,ggg,bbb,aaa)'' en décimal (0 à 255, aaa est la\n").toStdString();
    std::cout << QString("\ttransparence alpha) ou bien ``#RRGGBB'' en hexa.\n").toStdString();
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
    TDBDatabase::remove_db();
}

QString TDBApplication::default_style()
{
    return ds;
}
QString TDBApplication::alternate_style()
{
    return as;
}
QString TDBApplication::default_bank()
{
    return default_trig;
}
