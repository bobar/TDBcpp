#include "TDBTrigrammeCreationDialog.h"

TDBTrigrammeCreationDialog::TDBTrigrammeCreationDialog(QWidget* parent) :
    QDialog(parent), account(0)
{
    valid = new QDoubleValidator(this);
    layout = new QGridLayout(this);

    trigramme_label = new QLabel(tr("Trigramme"), this);
    layout->addWidget(trigramme_label, 0, 0);

    name_label = new QLabel(tr("Nom"), this);
    layout->addWidget(name_label, 1, 0);

    trig_status_label = new QLabel("...", this);
    layout->addWidget(trig_status_label, 0, 2);

    first_name_label = new QLabel(tr("Prénom"), this);
    layout->addWidget(first_name_label, 2, 0);

    nickname_label = new QLabel(tr("Surnom"), this);
    layout->addWidget(nickname_label, 3, 0);

    casert_label = new QLabel(tr("Casert"), this);
    layout->addWidget(casert_label, 4, 0);

    balance_label = new QLabel(tr("Solde initial"), this);
    layout->addWidget(balance_label, 5, 0);

    category_label = new QLabel(tr("Categorie"), this);
    layout->addWidget(category_label, 6, 0);

    promo_label = new QLabel(tr("Promo"), this);
    layout->addWidget(promo_label, 7, 0);

    mail_label = new QLabel(tr("Mail"), this);
    layout->addWidget(mail_label, 8, 0);

    picture_label = new QLabel(tr("Photal"), this);
    layout->addWidget(picture_label, 9, 0);

    trigramme_edit = new QLineEdit(this);
    trigramme_edit->setValidator(new TDBTrigrammeValidator(this));
    layout->addWidget(trigramme_edit, 0, 1);

    name_edit = new QLineEdit(this);
    layout->addWidget(name_edit, 1, 1);

    first_name_edit = new QLineEdit(this);
    layout->addWidget(first_name_edit, 2, 1);

    nickname_edit = new QLineEdit(this);
    layout->addWidget(nickname_edit, 3, 1);

    casert_edit = new QLineEdit(this);
    layout->addWidget(casert_edit, 4, 1);

    balance_edit = new QLineEdit(this);
    balance_edit->setValidator(valid);
    layout->addWidget(balance_edit, 5, 1);

    category_combo = new QComboBox(this);

    category_combo->addItem("X platalien", X_platal);
    category_combo->addItem("X ancien", X_ancien);
    category_combo->addItem("Binet", binet);
    category_combo->addItem("Personnel", personnel);
    category_combo->addItem("Supop", supop);
    category_combo->addItem("Autre", autre);

    layout->addWidget(category_combo, 6, 1);

    promo_edit = new QLineEdit(this);
    promo_edit->setInputMask("9999");
    layout->addWidget(promo_edit, 7, 1);


    mail_edit = new QLineEdit(this);
    layout->addWidget(mail_edit, 8, 1);

    picture_edit = new QLineEdit(this);
    layout->addWidget(picture_edit, 9, 1);

    ok_button = new QPushButton("OK", this);
    layout->addWidget(ok_button, 10, 0);

    cancel_button = new QPushButton("Cancel", this);
    layout->addWidget(cancel_button,10,1);

    photo_button = new QPushButton("Ouvrir...", this);
    layout->addWidget(photo_button,9,2);

    setLayout(layout);


    connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
    connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
    connect(photo_button, SIGNAL(pressed()), this, SLOT(open_photo()));
    connect(trigramme_edit, SIGNAL(textChanged(const QString&)), this, SLOT(check_trig(const QString&)));
}

TDBTrigrammeCreationDialog::~TDBTrigrammeCreationDialog()
{
}

void TDBTrigrammeCreationDialog::check_trig(const QString& text)
{
    if (text.length() != 3)
    {
        trig_status_label->setText("...");
        return;
    }

    TDBDatabase::open();

    QSqlQuery query;
    QSqlRecord record;
    query.prepare("SELECT COUNT(trigramme) as c FROM accounts WHERE trigramme = :tri");
    query.bindValue(":tri", trigramme_edit->text());
    query.exec();
    query.first();
    record = query.record();



    if (record.value("c").toInt() > 0)
    {
        trig_status_label->setText("prout");
    }
    else
    {
        trig_status_label->setText("OK");
    }

    TDBDatabase::close();

}


void TDBTrigrammeCreationDialog::cancel_pressed()
{
    reject();
}

void TDBTrigrammeCreationDialog::ok_pressed()
{
    TDBDatabase::open();

    QSqlQuery query;
    QSqlRecord record;
    query.prepare("SELECT COUNT(trigramme) as c FROM accounts WHERE trigramme = :tri");
    query.bindValue(":tri", trigramme_edit->text());
    query.exec();
    query.first();
    record = query.record();


    if (record.value("c").toInt() > 0)
    {
        TDBApplication::critical(this, "Trigramme existant");
        return;
    }


    if (trigramme_edit->text().length() != 3)
    {
        TDBApplication::critical(this, "Trigramme incomplet");
        return;
    }

    int cat = category_combo->itemData(category_combo->currentIndex()).toInt();

    try
    {
        account = new TDBAccount(trigramme_edit->text(),
                name_edit->text(),
                first_name_edit->text(),
                nickname_edit->text(),
                cat,
                casert_edit->text(),
                0,//(int)(balance_edit->text().toDouble()*100+0.5), c'est TDBMainWindow qui s'occupe de mettre l'argent dessus
                promo_edit->text().toInt(),
                mail_edit->text(),
                picture_edit->text());
    }
    catch (TDBTrigrammeException)
    {
        TDBDatabase::close(true);
        account = 0;
    }

    TDBDatabase::close();

    accept();
}


void TDBTrigrammeCreationDialog::open_photo()
{
    QString path = QFileDialog::getOpenFileName(this,
            tr("Photo"), "", tr("Images (*.png *.jpg *.bmp)"));

    if (path != "")
    {
        picture_edit->setText(path);
    }
}

int TDBTrigrammeCreationDialog::money()
{
    return (int)(balance_edit->text().toDouble()*100+0.5);
}
