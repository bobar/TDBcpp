#include "TDBAdminModification.h"

TDBAdminModification::TDBAdminModification(QWidget* parent, QString trigramme) :
        QDialog(parent)
{
    int perm;
  
	TDBDatabase::open();
	
    QSqlQuery query;
    query.prepare("SELECT accounts.id as admin_id, permissions FROM admins LEFT JOIN accounts ON accounts.id = admins.id WHERE accounts.trigramme = :trigramme");
    query.bindValue(":trigramme", trigramme);

    query.exec();
    query.first();
    admin_id = query.record().value("admin_id").toInt();
    perm = query.record().value("permissions").toInt();

	TDBDatabase::close();


    setWindowTitle("Modification d'un admin");

    passwd1_label = new QLabel("Mot de passe", this);
    passwd2_label = new QLabel("Vérification", this);
    perm_label = new QLabel("Niveau", this);


    perm_combo = new QComboBox(this);

    perm_combo->addItem("Pékin", pekin);
    perm_combo->addItem("Ami du BôB", ami_du_bob);
    perm_combo->addItem("Ancien BôBarman", bobarman);
    perm_combo->addItem("BôBarman", root);
    perm_combo->setCurrentIndex(perm_combo->findData(perm));

    passwd1_edit = new QLineEdit(this);
    passwd1_edit->setEchoMode(QLineEdit::Password);
    passwd2_edit = new QLineEdit(this);
    passwd2_edit->setEchoMode(QLineEdit::Password);

    layout = new QGridLayout(this);
    layout->addWidget(passwd1_label, 0, 0);
    layout->addWidget(passwd1_edit, 0, 1);
    layout->addWidget(passwd2_label, 1, 0);
    layout->addWidget(passwd2_edit, 1, 1);
    layout->addWidget(perm_label, 2, 0);
    layout->addWidget(perm_combo, 2, 1);

    ok_button = new QPushButton("OK", this);
    layout->addWidget(ok_button, 3, 0);
    cancel_button = new QPushButton("Cancel", this);
    layout->addWidget(cancel_button, 3, 1);

    setLayout(layout);

    connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
    connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
}

TDBAdminModification::~TDBAdminModification()
{
}

void TDBAdminModification::cancel_pressed()
{
    reject();
}

void TDBAdminModification::ok_pressed()
{
    int perm = perm_combo->itemData(perm_combo->currentIndex()).toInt();

	TDBDatabase::open();

    QSqlQuery query;
    query.prepare("UPDATE admins SET permissions = :perm WHERE id = :id");
    query.bindValue(":perm", perm);
    query.bindValue(":id", admin_id);

    query.exec();

    if (!passwd1_edit->text().isEmpty() &&
            passwd1_edit->text() == passwd1_edit->text())
    {
        query.prepare("UPDATE admins SET passwd = :passwd WHERE id = :id");
        query.bindValue(":passwd", QCryptographicHash::hash(QByteArray().append(passwd1_edit->text()), QCryptographicHash::Md5).toHex());
        query.bindValue(":id", admin_id);
        query.exec();
    }

	TDBDatabase::close();

    accept();
}
