#include "TDBMainWindow.h"

TDBMainWindow::TDBMainWindow() : QWidget()
{
    setWindowTitle("TDB2.1");
    QString banque = TDBApp->default_bank();
    bob_bank_button = new QPushButton(banque=="BOB"?"BôB":banque, this);
    binet_bank_button = new QPushButton("TDB2.1", this);
    this->setStyleSheet(TDBApp->default_style());

    QFont bank_button_font(bob_bank_button->font());
    bank_button_font.setBold(true);
    if (bank_button_font.pixelSize() > 0)
        bank_button_font.setPixelSize(bank_button_font.pixelSize() * 3);
    else
        bank_button_font.setPointSize(bank_button_font.pointSize() * 3);

    bob_bank_button->setFont(bank_button_font);
    binet_bank_button->setFont(bank_button_font);
    binet_bank_button->setFlat(true);
    last_conso_montant = 0;
    last_conso_bank = 0;
    current_account = 0;
    bob_is_bank = true;

    try
    {
        TDBDatabase::open();
        default_bank_account = new TDBAccount(banque);
        TDBDatabase::close();
    }
    catch (TDBTrigrammeInconnuException)
    {
        TDBDatabase::close(true);
        TDBApplication::critical(this,"Pas de compte banque, arrêt");
        exit(1);
        qApp->exit(1);
    }

    //etron = new TDBEtron();

    current_bank_account = default_bank_account;

    temp_bank_account = 0;

    enter_trigramme_action = new QAction("Entrer un trigramme", this);
    transaction_action = new QAction("Débiter un compte", this);
    create_trigramme_action = new QAction("Créer un trigramme", this);
    create_trigramme_action->setShortcut(QKeySequence("Ctrl+N"));
    modif_trigramme_action = new QAction("Modifier un trigramme", this);
    modif_trigramme_action->setShortcut(QKeySequence("Ctrl+M"));
    quit_action = new QAction("Quitter", this);
    refill_action = new QAction("Approvisioner", this);
    refill_action->setShortcut(QKeySequence("+"));
    batch_action = new QAction("Débiter plusieurs comptes depuis un fichier", this);
    batch_action->setShortcut(QKeySequence("Ctrl+B"));


    //son_action = new QAction("Plapp", this);
    //zde_action = new QAction("Zdé", this);
    //pch_action = new QAction("Pchhht", this);
    //mail_action = new QAction("Mail", this);
    //mail_action->setEnabled(false);
    //mathis_action = new QAction("Mathis", this);

    //toggle_etron_action = new QAction("Étron indisponible", this);
    //toggle_etron_action->setEnabled(false);

    transfert_action = new QAction("Transfert", this);
    transfert_action ->setShortcut(QKeySequence("Ctrl+T"));
    admin_admin_action = new QAction("Comptes admin", this);
    passwd_action = new QAction("Changer de mot de passe", this);
    export_action = new QAction("Exporter", this);
    reset_turnover_action = new QAction("Réinitialiser chiffres d'affaires", this);
    set_bank_action = new QAction("Début de soirée", this);
    remove_bank_action = new QAction("Fin de soirée", this);
    remove_bank_action->setEnabled(false);
    erase_trigramme_action = new QAction("Supprimer un trigramme", this);
    search_action = new QAction("Rechercher un trigramme", this);
    search_action->setShortcut(QKeySequence("Ctrl+F"));
    clopes_admin_action = new QAction("Gestion des clopes", this);
    clopes_action = new QAction("Acheter des clopes", this);
    clopes_action->setShortcut(QKeySequence("Ctrl+C"));
    //all_lights_on_action = new QAction("Tout allumer", this);
    //all_lights_off_action = new QAction("Tout éteindre", this);


    trigramme_export_action = new QAction("Exporter le trigramme", this);
    positivation_export_action = new QAction("Positivation", this);
    cancel_action = new QAction("Annuler", this);
    cancel_action->setShortcut(Qt::Key_Backspace);//QKeySequence("Ctrl+Z"));
    cancel_action->setEnabled(false);

    //connect(mail_action, SIGNAL(triggered()), this, SLOT(mail()));
    connect(quit_action, SIGNAL(triggered()), this, SLOT(close()));

    connect(enter_trigramme_action, SIGNAL(triggered()), this, SLOT(ask_trigramme()));
    connect(transaction_action, SIGNAL(triggered()), this, SLOT(achat()));
    connect(create_trigramme_action, SIGNAL(triggered()), this, SLOT(create_trigramme()));
    connect(modif_trigramme_action, SIGNAL(triggered()), this, SLOT(modif_trigramme()));
    connect(refill_action, SIGNAL(triggered()), this, SLOT(refill()));
    connect(batch_action, SIGNAL(triggered()), this, SLOT(batch_achats()));
    connect(transfert_action, SIGNAL(triggered()), this, SLOT(transfert()));
    connect(admin_admin_action, SIGNAL(triggered()), this, SLOT(admin_admin()));
    connect(passwd_action, SIGNAL(triggered()), this, SLOT(admin_passwd()));
    connect(export_action, SIGNAL(triggered()), this, SLOT(export_database()));
    connect(reset_turnover_action, SIGNAL(triggered()), this, SLOT(reset_turnover()));
    connect(set_bank_action, SIGNAL(triggered()), this, SLOT(ask_bank_account()));
    connect(remove_bank_action, SIGNAL(triggered()), this, SLOT(remove_bank()));
    connect(binet_bank_button, SIGNAL(pressed()), this, SLOT(binet_bank()));
    connect(bob_bank_button, SIGNAL(pressed()), this, SLOT(bob_bank()));
    connect(erase_trigramme_action, SIGNAL(triggered()), this, SLOT(delete_trigramme()));
    connect(search_action, SIGNAL(triggered()), this, SLOT(search_trigramme()));
    connect(clopes_admin_action, SIGNAL(triggered()), this, SLOT(clopes_admin()));
    connect(clopes_action, SIGNAL(triggered()), this, SLOT(achat_clopes()));
    connect(trigramme_export_action, SIGNAL(triggered()), this, SLOT(export_trigramme()));
    connect(positivation_export_action, SIGNAL(triggered()), this, SLOT(export_positivation()));
    connect(cancel_action, SIGNAL(triggered()), this, SLOT(cancel()));
    //connect(son_action, SIGNAL(triggered()), this, SLOT(son()));
    //connect(zde_action, SIGNAL(triggered()), this, SLOT(zde()));
    //connect(mathis_action, SIGNAL(triggered()), this, SLOT(mathis()));
    //connect(pch_action, SIGNAL(triggered()), this, SLOT(pch()));
    //connect(toggle_etron_action, SIGNAL(triggered()), etron, SLOT(toggle()));
    //connect(etron, SIGNAL(changed(int)), this, SLOT(etron_changed(int)));
    //connect(all_lights_on_action, SIGNAL(triggered()), this, SLOT(all_lights_on()));
    //connect(all_lights_off_action, SIGNAL(triggered()), this, SLOT(all_lights_off()));

    menubar = new QMenuBar(this);
    account_menu = new QMenu(tr("Compte"), this);
    account_menu->addAction(enter_trigramme_action);
    account_menu->addAction(search_action);
    account_menu->addAction(transaction_action);
    account_menu->addAction(clopes_action);
    account_menu->addAction(cancel_action);
    account_menu->addAction(quit_action);
    menubar->addMenu(account_menu);

    admin_menu = new QMenu(tr("Gestion"), this);
    admin_menu->addAction(refill_action);
    admin_menu->addAction(transfert_action);
    admin_menu->addAction(batch_action);
    admin_menu->addAction(create_trigramme_action);
    admin_menu->addAction(modif_trigramme_action);
    admin_menu->addAction(erase_trigramme_action);
    menubar->addMenu(admin_menu);

    root_menu = new QMenu(tr("Admin"), this);

    root_menu->addAction(admin_admin_action);
    root_menu->addAction(passwd_action);
    root_menu->addAction(export_action);
    root_menu->addAction(reset_turnover_action);
    root_menu->addAction(set_bank_action);
    root_menu->addAction(remove_bank_action);
    root_menu->addAction(clopes_admin_action);
    root_menu->addAction(trigramme_export_action);
    root_menu->addAction(positivation_export_action);

    menubar->addMenu(root_menu);

    toolbar = new QToolBar(this);
    toolbar->addAction(cancel_action);
    toolbar->addAction(clopes_action);
    //toolbar->addAction(son_action);
    //toolbar->addAction(zde_action);
    //toolbar->addAction(mathis_action);
    //toolbar->addAction(pch_action);
    //toolbar->addAction(toggle_etron_action);
    //toolbar->addAction(all_lights_on_action);
    //toolbar->addAction(all_lights_off_action);


    layout0 = new QVBoxLayout(this);
    layout0->setMenuBar(menubar);

    layout = new QHBoxLayout(this);

    layout0->addWidget(toolbar);

    layout0->addLayout(layout);

    history = new TDBHistory(this);
    layout->addWidget(history, 2);

    infos_layout = new QVBoxLayout();

    bank_layout = new QHBoxLayout();
    bob_bank_button->setCheckable(true);
    binet_bank_button->setCheckable(true);

    bob_bank_button->setAutoExclusive(true);
    binet_bank_button->setAutoExclusive(true);
    bob_bank_button->setChecked(true);
    binet_bank_button->setEnabled(false);
    bank_layout->addWidget(bob_bank_button, 1);
    bank_layout->addWidget(binet_bank_button, 1);


    infos_layout->addLayout(bank_layout);
    label_trigramme = new QLabel(this);
    label_trigramme->setMinimumWidth(400);
    label_trigramme->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    infos_layout->addWidget(label_trigramme, 1);

    label_name = new QLabel(this);
    label_name->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    label_name->setWordWrap(true);
    infos_layout->addWidget(label_name, 1);

    label_balance = new QLabel(this);
    label_balance->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    infos_layout->addWidget(label_balance, 1);

    label_turnover = new QLabel(this);
    label_turnover->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    infos_layout->addWidget(label_turnover, 1);

    label_picture = new QLabel(this);
    label_picture->setAlignment(Qt::AlignHCenter);
    infos_layout->addWidget(label_picture, 1);

    layout->addLayout(infos_layout);
    setLayout(layout0);

    showMaximized();
    setFocus(Qt::OtherFocusReason);

    //etron->get_state();
}

TDBMainWindow::~TDBMainWindow()
{
}

void TDBMainWindow::ask_trigramme(QString key)
{
    // la key c'est si jamais on tape une lettre sur la fenêtre principale
    // ça ouvre la boîte avec déjà une lettre dedans

    TDBTrigrammeDialog trigramme_dialog(this, key);
    if (trigramme_dialog.exec())
        set_current_account(trigramme_dialog.trigramme());
}

void TDBMainWindow::set_current_account(const QString& trigramme)
{
    TDBAccount* new_account = 0;

    try
    {
        new_account = new TDBAccount(trigramme);
    }
    catch (TDBTrigrammeInconnuException e)
    {
        TDBDatabase::close(true);
        TDBApplication::critical(this, e.what());
        return;
    }

    if (current_account)
    {
        clear();
        last_conso_bank = 0;
        last_clopes = QString();
        cancel_action->setEnabled(false);
        delete current_account;
    }

    current_account = new_account;

    //mail_action->setEnabled(true);

    update();

    history->fill(current_account);
}

void TDBMainWindow::keyPressEvent(QKeyEvent* e)
{
    // ferme le compte actif
    if (e->key() == Qt::Key_Escape && e->modifiers() == Qt::NoModifier)
    {
        e->accept();
        last_conso_bank = 0;
        last_clopes = QString();
        cancel_action->setEnabled(false);
        delete current_account;
        current_account = 0;
        //mail_action->setEnabled(false);
        clear();
        return;
    }
    else if (e->key() == Qt::Key_Tab && (e->modifiers() == Qt::ControlModifier ||  e->modifiers() == Qt::NoModifier) )
    {
        if (bob_is_bank && temp_bank_account)
            binet_bank();
        else if (!bob_is_bank)
            bob_bank();
    }
    else if (e->key() == Qt::Key_Left && e->modifiers() == Qt::NoModifier && !bob_is_bank)
        bob_bank();

    else if (e->key() == Qt::Key_Right && e->modifiers() == Qt::NoModifier && bob_is_bank && temp_bank_account)
        binet_bank();

    else if (e->modifiers() == Qt::NoModifier || e->modifiers() == Qt::KeypadModifier)
    {
        QString key = e->text();
        if (key.isEmpty() || !key.at(0).isPrint())
        {
            e->ignore();
            return;
        }

        // conso si un chiffre ou point est entré et un compte actif
        bool num = key.contains(QRegExp("[0-9.]"));
        if(!current_account && num)
        {
            e->ignore();
            return;
        }
        e->accept();

        if (current_account && num)
            achat(key);
        else
            // ouvre un compte
            ask_trigramme(key);
    }
}

void TDBMainWindow::achat(QString initial)
{
    TDBTransactionDialog trans_dialog(this, "Achat", initial);
    int admin_id = 0;

    if (!init_action())
        return;

    if (trans_dialog.exec())
    {

        /*
        if ((trans_dialog.money() > current_account->get_balance()))
        {
        	QString text;
        	text.append(current_account->get_first_name())
        	  .append(" ")
        	  .append(current_account->get_name())
        	  .append(" est en négatif");

        	pid_t pid = fork();
        	if (pid == 0)
        	{
        		execlp("aoss", "aoss", "espeak", "-vfr",
        		   text.toAscii().constData(), NULL);
        	}
        }*/

        if (trans_dialog.money() < 0 || trans_dialog.money() > 2000 || // ça évite la merde
                (trans_dialog.money() > current_account->get_balance() &&
                 current_account->get_category()) != X_platal) // si c'est un pékin on fascise
            try
            {
                admin_id = TDBApplication::auth(this, ami_du_bob);
            }
            catch (TDBAuthException e)
            {
                return;
            }

        if (current_account->transaction(- trans_dialog.money(), trans_dialog.reason(), current_bank_account, admin_id))
        {
            history->update(current_account);
            update_money_display();

            last_conso_montant = - trans_dialog.money();
            last_conso_bank = current_bank_account;
            last_clopes = QString();
            cancel_action->setEnabled(true);
            //on revient au BôB pour la banque, ça fascise les binets et pas le BôB, mais en fait non
            //bob_bank();
        }
    }
}

void TDBMainWindow::transfert()
{
    // c'est compliqué ce truc, en gros ça peut être indépendant du compte actif
    QString trig = QString();
    TDBAccount* account_1;
    TDBAccount* account_2;
    int admin_id = 0;

    try
    {
        admin_id = TDBApplication::auth(this, ami_du_bob);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (current_account != 0)
    {
        trig = current_account->get_trigramme();
        account_1 = current_account;
    }

    TDBTransfertDialog trans_dialog(this, "Transfert", trig);

    if (!trans_dialog.exec())
        return;


    try
    {
        account_1 = new TDBAccount(trans_dialog.trigramme1());
    }
    catch (TDBTrigrammeInconnuException e)
    {
        TDBDatabase::close(true);
        TDBApplication::critical(this, e.what());
        return;
    }

    try
    {
        account_2 = new TDBAccount(trans_dialog.trigramme2());
    }
    catch (TDBTrigrammeInconnuException e)
    {
        TDBDatabase::close(true);
        TDBApplication::critical(this, e.what());
        return;
    }

    if (account_1->transaction(- trans_dialog.money(), trans_dialog.reason(), account_2, admin_id) && current_account)
    {
        history->update(current_account);
    }

    delete account_2;
    if (current_account == 0)
        delete account_1;
    else
        update_money_display();
}

void TDBMainWindow::refill()
{
    TDBRefillDialog trans_dialog(this);
    int admin_id = 0;

    try
    {
        admin_id = TDBApplication::auth(this, ami_du_bob);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (!init_action())
        return;

    if (trans_dialog.exec())
    {
        if (current_account->transaction(trans_dialog.money(), trans_dialog.reason(), default_bank_account, admin_id))
        {
            history->update(current_account);
            update_money_display();
            last_conso_montant = trans_dialog.money();
            last_conso_bank = default_bank_account;
            last_clopes = QString();
            cancel_action->setEnabled(true);
        }
    }
}

void TDBMainWindow::modif_trigramme()
{
    //int admin_id = 0;

    try
    {
        //admin_id = TDBApplication::auth(this, bobarman);
        TDBApplication::auth(this, bobarman);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (!init_action())
        return;

    TDBTrigrammeModificationDialog modif_dialog(this, current_account);

    modif_dialog.exec();

    update();
}

void TDBMainWindow::create_trigramme()
{
    int admin_id = 0;

    try
    {
        admin_id = TDBApplication::auth(this, bobarman);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    TDBTrigrammeCreationDialog tri_dialog(this);
    if (tri_dialog.exec())
    {
        tri_dialog.get_account()->transaction(tri_dialog.money(), QString("Création de compte"), default_bank_account, admin_id);
    }

    // à voir si on rend le compte créé actif
}

// c'est clear, enfin clair quoi
void TDBMainWindow::clear()
{
    label_trigramme->setText(QString());
    label_name->setText(QString());
    label_balance->setText(QString());
    label_turnover->setText(QString());
    label_picture->setText(QString(" "));
    history->clear();
}

void TDBMainWindow::update_money_display()
{
    current_account->refresh_money();

    // putain c'est illisible, ça update le money display
    double money = (double)current_account->get_balance();
    if (money < 0.0)
        label_balance->setText(QString("<font size=+10><b style=\"color: red\">%1</b></font>")
                               .arg((double)current_account->get_balance()/100, 0, 'f', 2));
    else
        label_balance->setText(QString("<font size=+10><b>%1</b></font>")
                               .arg((double)current_account->get_balance()/100, 0, 'f', 2));

    label_turnover->setText(QString("%1e dépensés depuis dernier reset")
                            .arg((double)current_account->get_turnover()/100, 0, 'f', 2));
}

void TDBMainWindow::update()
{
    label_trigramme->setText(QString("<font size=+5><b>%1</b></font>")
                             .arg(current_account->get_trigramme()));

    QString label_text = QString("<font size=+2><b>%1 %2 ")
                         .arg(current_account->get_name())
                         .arg(current_account->get_first_name());

    if (current_account->get_nickname().size() > 0)
        label_text.append(QString("(%1) ").arg(current_account->get_nickname()));

    if (current_account->get_promo() > 0)
        label_text.append(QString::number(current_account->get_promo()));

    label_text.append(QString("</b></font>"));

    label_name->setText(label_text);


    QImage picture(current_account->get_picture());
    if (!picture.isNull())
        label_picture->setPixmap(QPixmap::fromImage(picture).scaled(200,300,Qt::KeepAspectRatio));

    update_money_display();
}

void TDBMainWindow::admin_admin()
{
    //int admin_id = 0;

    try
    {
        //admin_id = TDBApplication::auth(this, root);
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    TDBAdminAdmin admin(this);
    admin.exec();
}

void TDBMainWindow::admin_passwd()
{
    int admin_id = 0;

    try
    {
        admin_id = TDBApplication::auth(this, pekin);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    TDBPasswordChange pwdch(this, admin_id);
    pwdch.exec();
}

void TDBMainWindow::set_bank(TDBAccount* new_bank_account)
{
    if (temp_bank_account)
        delete temp_bank_account;

    temp_bank_account = new_bank_account;

    binet_bank_button->setText(new_bank_account->get_trigramme());
    binet_bank_button->setEnabled(true);
    binet_bank_button->setFlat(false);
    remove_bank_action->setEnabled(true);
}

void TDBMainWindow::remove_bank()
{
    try
    {
        TDBApplication::auth(this, ami_du_bob);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (last_conso_bank == temp_bank_account)
    {
        last_conso_bank = 0;
        cancel_action->setEnabled(false);
    }

    delete temp_bank_account;
    temp_bank_account = 0;
    binet_bank_button->setText("TDB2.1");

    binet_bank_button->setEnabled(false);
    binet_bank_button->setFlat(true);

    bob_bank();
    remove_bank_action->setEnabled(false);
}

void TDBMainWindow::binet_bank()
{
    current_bank_account = temp_bank_account;

    binet_bank_button->setChecked(true);
    bob_is_bank = false;

    this->setStyleSheet(TDBApp->alternate_style());
}

void TDBMainWindow::bob_bank()
{
    current_bank_account = default_bank_account;

    bob_bank_button->setChecked(true);
    bob_is_bank = true;

    this->setStyleSheet(TDBApp->default_style());
}

void TDBMainWindow::ask_bank_account()
{
    try
    {
        TDBApplication::auth(this, ami_du_bob);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    TDBTrigrammeDialog trigramme_dialog(this);

    if (trigramme_dialog.exec())
    {
        // oups il faudrait rattraper l'exception
        TDBAccount* new_bank = new TDBAccount(trigramme_dialog.trigramme());
        if (new_bank->get_category() == binet)
            set_bank(new TDBAccount(trigramme_dialog.trigramme()));
    }
}


void TDBMainWindow::delete_trigramme()
{
    //int admin_id = 0;

    try
    {
        //admin_id = TDBApplication::auth(this, bobarman);
        TDBApplication::auth(this, bobarman);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if (!init_action())
        return;

    bool ok = (QMessageBox::question (this, "TDB",
                                      QString("Effacer le trigramme ")
                                      .append(current_account->get_trigramme())
                                      .append(" (")
                                      .append(current_account->get_name())
                                      .append(" ")
                                      .append(current_account->get_first_name())
                                      .append(") ?"),
                                      QMessageBox::Yes | QMessageBox::No) ==  QMessageBox::Yes);

    if (!ok)
        return;

    // vérifie si le compte est bien à zéro, ça évite les conneries
    if (current_account->get_balance() == 0)
    {
        current_account->erase();
        last_conso_bank = 0;
        last_clopes = QString();
        cancel_action->setEnabled(false);
        delete current_account;
        current_account = 0;
        clear();
    }
    else
    {
        TDBApplication::critical(this, QString("Trigramme non vide, annulation de l'effacement"));
    }
}

void TDBMainWindow::search_trigramme()
{
    TDBSearch search(this);

    if (search.exec())
    {
        QString trig = search.trigramme();
        if (!trig.isEmpty())
            set_current_account(trig);
    }
}

void TDBMainWindow::achat_clopes()
{
    if (!init_action())
        return;

    int admin_id = 0;

    TDBClopes achclopes(this);

    if (!achclopes.exec())
        return;

    if (achclopes.money() > 2000 || // ça évite la merde
            (achclopes.money() > current_account->get_balance() &&
             current_account->get_category()) != X_platal) // si c'est un pékin on fascise
        try
        {
            admin_id = TDBApplication::auth(this, ami_du_bob);
        }
        catch (TDBAuthException e)
        {
            return;
        }

    if (current_account->transaction(-achclopes.money(), achclopes.get_marque(), default_bank_account, admin_id))
    {
        history->update(current_account);
        update_money_display();
        last_conso_montant = - achclopes.money();
        last_conso_bank = default_bank_account;
        last_clopes = achclopes.get_marque();
        last_clopes_quantite = achclopes.get_quantite();
        cancel_action->setEnabled(true);
    }
    return;
}

bool TDBMainWindow::init_action()
{
    if (current_account == 0)
        ask_trigramme();

    if (current_account == 0)
        return false;

    return true;
}

void TDBMainWindow::batch_achats()
{
    int admin_id = 0;

    try
    {
        admin_id = TDBApplication::auth(this, ami_du_bob);
    }
    catch (TDBAuthException e)
    {
        return;
    }

    if(!init_action())
        return;

    if(current_account->get_category() != binet)
    {
        QMessageBox::critical(this, "Erreur de trigramme", "Le bénéficiaire n'est pas un binet !");
        return;
    }

    QString path = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Comma Separated Values (*.csv)");

    if (path==NULL)
        return;

    QFile file (path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur de lecture", "Erreur à l'ouverture du fichier.");
        return;
    }

    QTextStream in (&file);
    QStringList lines;

    while(!in.atEnd())
        lines << in.readLine();

    TDBBatchDialog verif((QWidget*)this, &lines, current_account, admin_id);

    if(verif.exec() == QDialog::Accepted && lines.size() > 0)
    {
        QFile rejected( path.replace(path.length()-4, 4, "_refuses.csv") );

        if (!rejected.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(this, "Erreur de lecture", "Erreur à l'ouverture du fichier.");
            return;
        }

        QTextStream out (&rejected);

        QListIterator<QString> javaIter( lines );
        while( javaIter.hasNext() )
            out << (QString)javaIter.next() << "\n";

        QMessageBox::information((QWidget*)this, QString("Trigrammes non débités"),
                                 QString("Lignes ignorées %1 lignes ont été ignorées et stockées dans le fichier :\n%2").arg(lines.size()).arg(rejected.fileName())
                                );
    }

    history->update(current_account);
    update_money_display();
}

void TDBMainWindow::clopes_admin()
{
    try
    {
        TDBApplication::auth(this, root);
    }
    catch (TDBAuthException e)
    {
        return;
    }


    TDBClopesAdmin cadmin(this);
    cadmin.exec();
}

void TDBMainWindow::cancel()
{
    TDBDatabase::open();

    if (!last_conso_bank)
        return;

    current_account->transaction(- last_conso_montant, QString("Annulation"), last_conso_bank, 0);
    history->update(current_account);
    update_money_display();

    if (last_clopes.size() > 0)
    {
        QSqlQuery query;
        query.prepare("UPDATE clopes SET quantite = quantite - :quantite WHERE marque = :marque");
        query.bindValue(":quantite", last_clopes_quantite);
        query.bindValue(":marque", last_clopes);
        query.exec();
    }

    TDBDatabase::close();

    last_conso_bank = 0;
    last_clopes = QString();
    cancel_action->setEnabled(false);
}
/*
void TDBMainWindow::son()
{
  QString path = "/home/bobar/tdb2/sons/";
  QDir rep(path);
  QStringList files = rep.entryList();

  if (files.size() > 2)
    {

      int f = rand()%(files.size() -2);
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("ogg123", "ogg123", path.append(files[f+2]).toAscii().constData(), NULL);
	}
    }
}

void TDBMainWindow::zde()
{
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("ogg123", "ogg123", "/home/bobar/tdb2/sons/zde.ogg", NULL);
	}
}

void TDBMainWindow::mathis()
{
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("ogg123", "ogg123", "/home/bobar/tdb2/sons/mathis.ogg", NULL);
	}
	}

void TDBMainWindow::pch()
{
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("ogg123", "ogg123", "/home/bobar/tdb2/sons/pchhh.ogg", NULL);
	}
}
*/
void TDBMainWindow::mail()
{
    //current_account->sendmail("Sujet", "Body\n");
}
/*
void TDBMainWindow::etron_changed(int state)
{
  toggle_etron_action->setEnabled(true);
  switch(state)
    {
    case -1:
      toggle_etron_action->setText("Étron indisponible");
      break;
    case 0:
      toggle_etron_action->setText("Ouvrir le BôB");
      break;
    case 1:
      toggle_etron_action->setText("Fermer le BôB");
      break;
    }
}
*/
/*
void TDBMainWindow::all_lights_on()
{
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("heyu", "heyu", "allon", "A", NULL);
	}
}

void TDBMainWindow::all_lights_off()
{
      pid_t pid = fork();
      if (pid == 0)
	{
	  execlp("heyu", "heyu", "alloff", "A", NULL);
	}
}
*/
