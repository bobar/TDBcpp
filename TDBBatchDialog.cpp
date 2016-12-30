#include "TDBBatchDialog.h"

TDBBatchDialog::TDBBatchDialog(QWidget* parent, QStringList *lines, TDBAccount* binet_, int admin_id_) :
        QDialog(parent), admin_id(admin_id_), binet_account(binet_), rawData(lines)
{
    setWindowTitle("Paramètres du fichier texte");
    layout = new QGridLayout(this);

    separator_label = new QLabel("Séparateur", this);
    listView_label = new QLabel("Aperçu du ficher :", this);

    separator_edit = new QLineEdit(this);
    separator_edit->setInputMask("X");
    separator_edit->setMaxLength(1);

    ok_button = new QPushButton("OK", this);
    cancel_button = new QPushButton("Annuler", this);

    listView = new QTreeWidget(this);
    listView->setFixedHeight(600);
    listView->setFixedWidth(600);
    listView->setColumnCount(5);
    QStringList header_strings;
    header_strings << "Ligne" << "Trigramme" << "Nom" << "Montant" << "Erreur";
    listView->setHeaderLabels(header_strings);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setSelectionBehavior(QAbstractItemView::SelectRows);
	listView->hideColumn(0);

    layout->addWidget(separator_label, 0, 0);
    layout->addWidget(separator_edit, 0, 1);
    layout->addWidget(listView_label, 1, 0, 1, 2);
    layout->addWidget(listView, 2, 0, 1, 2);
    layout->addWidget(ok_button, 3, 0);
    layout->addWidget(cancel_button, 3, 1);

    setLayout(layout);

    connect(ok_button, SIGNAL(pressed()), this, SLOT(valider()));
    connect(cancel_button, SIGNAL(pressed()), this, SLOT(reject()));
    connect(separator_edit, SIGNAL(textEdited(QString)), this, SLOT(setSeparator(QString)));

	// devinons le caractère qui sépare les champs
	separator = educatedGuess();
	separator_edit->setText(QString(separator));
	// et lisons ce fichier
	process();
	listView->setFocus(Qt::PopupFocusReason);
}

void TDBBatchDialog::process()
{
	listView->clear();

    QString tri, name, cost1, cost2;
	QStringList processedLine;
	QTreeWidgetItem* shownLine = 0;
    double cost;
    bool ok_read;
	int errcode;
    TDBAccount* user_account;

	TDBDatabase::open();
	for (int i = 0; i < rawData->size(); ++i)
    {
		processedLine.clear();
        tri = rawData->at(i).section(separator, 0, 0).toUpper();
        name = rawData->at(i).section(separator, 1, 1);
        cost1 = rawData->at(i).section(separator, 2, 2);
        cost2 = rawData->at(i).section(separator, 2, 3);
        cost = 0;

		// on ne gère pas les séparateurs dans des guillemets (càd on coupe au milieu de "aaa,bbb"). On les vire, donc.
        if(tri.startsWith('"') && tri.endsWith('"'))
            tri = tri.mid(1, tri.size() -2);

        if(name.startsWith('"') && name.endsWith('"'))
            name = name.mid(1, name.size() -2);

        if(cost1.startsWith('"') && cost1.endsWith('"'))
            cost1 = cost1.mid(1, cost1.size() -2);

        if(cost2.startsWith('"') && cost2.endsWith('"'))
            cost2 = cost2.mid(1, cost2.size() -2);

        // séparateur des centimes , ou . dépend de LOCALE
		// on utilise donc QLocale::German qui reconnaît les deux
		QLocale c(QLocale::German);

		ok_read = false;
		// on essaye de lire sur deux cases si on a un montant à virgule et une ligne "TRI,nom,3,50"
		if(separator == '.' || separator == ',')
			cost = c.toDouble(cost2, &ok_read);

		// cas pas flou, ou échec de lecture sur deux cases ("TRI,nom,3,commentaire" par exemple)
        if( !ok_read )
			cost = c.toDouble(cost1, &ok_read);

		processedLine << QString::number(i) << tri << name << QString::number(cost) ;
		errcode = 2; // fatal

		// erreurs
        if(! ok_read )
			processedLine << QString("Montant illisible");

		else if( tri.length() != 3 )
			processedLine << QString("Trigramme illisible");

		else if ( cost < 0 )
			processedLine << QString("Trigramme négatif");

		else
		{
			try
			{
				user_account = new TDBAccount(tri);

				if( user_account->get_category() == binet )
					processedLine << QString("Trigramme binet");

				// avertissements
				else if(QString::compare(user_account->get_name(), name, Qt::CaseInsensitive) != 0)
				{
					processedLine << QString("Mauvais nom : %1 pour %2").arg(name).arg(user_account->get_name());
					errcode = 1;
				}

				else if(user_account->get_balance() < cost)
				{
					processedLine << QString("Donne un négatif (%1)").arg( (double)(user_account->get_balance() - cost)/100 );
					errcode = 1;
				}

				else if(cost > 20)
				{
					processedLine << QString("Gros montant (%1)").arg(cost);
					errcode = 1;
				}
				// RAS
				else
				{
					processedLine << QString("OK").arg(cost);
					errcode = 0;
				}
			}
			catch(TDBException e)
			{
				//TDBDatabase::close(true);
				// ici on ferme pas tant pis si on perd le compte d'ouvertures
				// on force la fermeture en sortant de la boucle

				processedLine << QString("Trigramme inconnu");
			}
		}
		shownLine = new QTreeWidgetItem(listView, processedLine);

		if(errcode == 0)
			shownLine->setCheckState(1, Qt::Checked);
		else
			shownLine->setCheckState(1, Qt::Unchecked);

		if(errcode == 2)
			shownLine->setDisabled(true);

		listView->addTopLevelItem(shownLine);
    }

	TDBDatabase::close(true);

	listView->setCurrentItem( listView->topLevelItem(0) , 1);
}

void TDBBatchDialog::valider()
{
    QString tri, name, err;
    int cost;
	TDBAccount* user_account;

	TDBDatabase::open();
	QStringList refuses;
	QTreeWidgetItem *line;


	while( (line = listView->takeTopLevelItem(0)) != 0)
	{
		tri = line->text(1);
		name = line->text(2);
		cost = (int) 100*line->text(3).toDouble();
		err = line->text(4);

		if( !line->isDisabled() && line->checkState(1) )
		{
			user_account = new TDBAccount(tri);
			user_account->transaction(-cost,QString(),binet_account,admin_id);
		}
		else
			refuses << QString("%1;%2;%3;%4 ligne %5").arg(tri).arg(name).arg(line->text(3)).arg(err).arg(line->text(0));
	}

    // hop
	rawData->clear();
	*rawData = refuses;

	TDBDatabase::close();
	accept();
}

QChar TDBBatchDialog::educatedGuess()
{
	// ça s'appelle csv après tout
    if(rawData->isEmpty())
        return QChar(',');

	QString guineaPig;
	// j'aime pas prendre la première ligne
	if(rawData->count() == 1)
		guineaPig = rawData->first();
	else
		guineaPig = rawData->at( 1+ (qrand() % (rawData->count() -2)) );

	QChar probable[] = {',', ';', '	'};

	int i, j, max = -1, a;
	for(i=0; i < 3; i++)
	{
		a = guineaPig.count(probable[i]);
		if(a > max)
		{
			max = a;
			j = i;
		}
	}

	return probable[j];
}

void TDBBatchDialog::setSeparator(QString s)
{
	if(s.length() == 0)
		return;

	separator = s.at(0);
	process();
}
