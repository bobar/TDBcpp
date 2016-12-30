#include "TDBTrigrammeDialog.h"

TDBTrigrammeDialog::TDBTrigrammeDialog(QWidget* parent, QString initial) :
        QDialog(parent)
{
    setWindowTitle("Trigramme");
    valid = new TDBTrigrammeValidator(this);
    label = new QLabel("Trigramme", this);

    trigramme_edit = new QLineEdit(this);
    trigramme_edit->setText( initial.toUpper() );

    trigramme_edit->setValidator(valid);

    connect(trigramme_edit, SIGNAL(textChanged(QString)),
            this, SLOT(trigrammeChanged(QString)));

    layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(trigramme_edit);

    setLayout(layout);

#if win32
    // fait bugger sous 'nux, pas moyen d'avoir le curseur sans sélectionner
    trigramme_edit->setFocus(Qt::PopupFocusReason);
#endif
    trigramme_edit->setCursorPosition( initial.length() );
}

TDBTrigrammeDialog::~TDBTrigrammeDialog()
{
    delete label;
    delete trigramme_edit;
    delete layout;
}

void TDBTrigrammeDialog::trigrammeChanged(QString trigramme)
{
    if (trigramme.length() == 3)
    {
        accept();
        return;
    }
}

QString TDBTrigrammeDialog::trigramme()
{
    return trigramme_edit->text();
}
