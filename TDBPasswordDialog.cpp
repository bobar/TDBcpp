#include "TDBPasswordDialog.h"

TDBPasswordDialog::TDBPasswordDialog(QWidget* parent) : QDialog(parent)
{
	setWindowTitle("Connexion à la base de données");

	passwd_label = new QLabel("Mot de passe", this);
	passwd_edit = new QLineEdit(this);
	passwd_edit->setEchoMode(QLineEdit::Password);

	layout = new QGridLayout(this);
	layout->addWidget(passwd_label, 0, 0);
	layout->addWidget(passwd_edit, 0, 1);

	ok_button = new QPushButton("OK", this);
	layout->addWidget(ok_button, 1, 0);
	cancel_button = new QPushButton("Cancel", this);
	layout->addWidget(cancel_button, 1, 1);

	setLayout(layout);

	connect(cancel_button, SIGNAL(pressed()), this, SLOT(reject()));
	connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
	passwd_edit->setFocus(Qt::PopupFocusReason);
}

TDBPasswordDialog::~TDBPasswordDialog()
{
}

void TDBPasswordDialog::ok_pressed()
{
	pw = passwd_edit->text();
	accept();
}

QString TDBPasswordDialog::get_pw()
{
	return pw;
}
