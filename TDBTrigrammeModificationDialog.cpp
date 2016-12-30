#include "TDBTrigrammeModificationDialog.h"

TDBTrigrammeModificationDialog::TDBTrigrammeModificationDialog(QWidget* parent, TDBAccount* acc) :
        QDialog(parent), account(acc)
{
    setWindowTitle("Modification de trigramme");

    valid = new QDoubleValidator(this);
    layout = new QGridLayout(this);

    trigramme_label = new QLabel(tr("Trigramme"), this);
    layout->addWidget(trigramme_label, 0, 0);

    name_label = new QLabel(tr("Nom"), this);
    layout->addWidget(name_label, 1, 0);

    first_name_label = new QLabel(tr("Prénom"), this);
    layout->addWidget(first_name_label, 2, 0);

    nickname_label = new QLabel(tr("Surnom"), this);
    layout->addWidget(nickname_label, 3, 0);

    casert_label = new QLabel(tr("Casert"), this);
    layout->addWidget(casert_label, 4, 0);

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
    trigramme_edit->setText(account->get_trigramme());

    layout->addWidget(trigramme_edit, 0, 1);


    name_edit = new QLineEdit(this);
    name_edit->setText(account->get_name());
    layout->addWidget(name_edit, 1, 1);

    first_name_edit = new QLineEdit(this);
    first_name_edit->setText(account->get_first_name());
    layout->addWidget(first_name_edit, 2, 1);

    nickname_edit = new QLineEdit(this);
    nickname_edit->setText(account->get_nickname());
    layout->addWidget(nickname_edit, 3, 1);

    casert_edit = new QLineEdit(this);
    casert_edit->setText(account->get_casert());
    layout->addWidget(casert_edit, 4, 1);

    category_combo = new QComboBox(this);

    category_combo->addItem("X platalien", X_platal);
    category_combo->addItem("X ancien", X_ancien);
    category_combo->addItem("Binet", binet);
    category_combo->addItem("Personnel", personnel);
    category_combo->addItem("Supop", supop);
    category_combo->addItem("Autre", autre);

    category_combo->setCurrentIndex(category_combo->findData(account->get_category()));
    layout->addWidget(category_combo, 6, 1);

    promo_edit = new QLineEdit(this);
    promo_edit->setInputMask("9999");
    promo_edit->setText(QString::number(account->get_promo()));
    layout->addWidget(promo_edit, 7, 1);

    mail_edit = new QLineEdit(this);
    mail_edit->setText(account->get_mail());
    layout->addWidget(mail_edit, 8, 1);

    picture_edit = new QLineEdit(this);
    picture_edit->setText(account->get_picture());
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
}

TDBTrigrammeModificationDialog::~TDBTrigrammeModificationDialog()
{
}

void TDBTrigrammeModificationDialog::cancel_pressed()
{
    reject();
}

void TDBTrigrammeModificationDialog::ok_pressed()
{
    TDBDatabase::open();

    QSqlQuery query;
    QSqlRecord record;
    query.prepare("SELECT COUNT(trigramme) as c FROM accounts WHERE trigramme = :tri");
    query.bindValue(":tri", trigramme_edit->text());
    query.exec();
    query.first();
    record = query.record();

    if (trigramme_edit->text().compare(account->get_trigramme()) != 0)
    {

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
    }
    int cat = category_combo->itemData(category_combo->currentIndex()).toInt();

    try
    {
        account->modif(trigramme_edit->text(),
                       name_edit->text(),
                       first_name_edit->text(),
                       nickname_edit->text(),
                       cat,
                       casert_edit->text(),
                       promo_edit->text().toInt(),
                       mail_edit->text(),
                       picture_edit->text());
    }
    catch (TDBTrigrammeException)
    {
        TDBDatabase::close(true);
    }

    TDBDatabase::close();

    accept();
}


void TDBTrigrammeModificationDialog::open_photo()
{
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Photo"), "", tr("Images (*.png *.jpg *.bmp)"));

    if (path != "")
    {
        picture_edit->setText(path);
    }
}
