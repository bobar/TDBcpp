#include "TDBSearch.h"

TDBSearch::TDBSearch(QWidget* parent) :
    QDialog(parent)
{
    search_list = new TDBSearchList(this);
    search_list->show();
    search_string = new QLineEdit(this);
    search_button = new QPushButton("Rechercher", this);
    ok_button = new QPushButton("OK", this);
    cancel_button = new QPushButton("Annuler", this);

    vlayout = new QVBoxLayout(this);
    vlayout->insertWidget(1, search_string, 1);

    vlayout->insertWidget(1, search_list, 1);
    vlayout->insertWidget(2, search_button, 0);
    vlayout->insertWidget(3, ok_button, 0);
    vlayout->insertWidget(4, cancel_button, 0);

    connect(ok_button, SIGNAL(pressed()), this, SLOT(ok_pressed()));
    connect(search_button, SIGNAL(pressed()), this, SLOT(search_pressed()));
    connect(cancel_button, SIGNAL(pressed()), this, SLOT(cancel_pressed()));
    connect(search_list, SIGNAL(itemDoubleClicked (QTreeWidgetItem *, int)),
            this, SLOT(trigramme_double_clicked(QTreeWidgetItem *, int)));
}

TDBSearch::~TDBSearch()
{
    delete search_list;
}

void TDBSearch::ok_pressed()
{
    accept();
}
void TDBSearch::cancel_pressed()
{
    reject();
}

void TDBSearch::search_pressed()
{
    search_list->clear();
    search_list->fill(QString(search_string->text()));
}

QString TDBSearch::trigramme()
{
    if (!search_list->currentItem())
        return QString();

    return search_list->currentItem()->text(0);
}

void TDBSearch::trigramme_double_clicked(QTreeWidgetItem * item, int column)
{
    if (column >= 0)
        accept();
}
