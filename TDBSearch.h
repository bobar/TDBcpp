#ifndef TDBSEARCH_H
#define TDBSEARCH_H

#include <iostream>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

#include "TDBApplication.h"

#include "TDBSearchList.h"

class TDBSearch : public QDialog
{
    Q_OBJECT

    TDBSearchList* search_list;

    private:

    QLineEdit* search_string;
    QPushButton* ok_button;
    QPushButton* cancel_button;
    QPushButton* search_button;
    QVBoxLayout* vlayout;

    public:

    TDBSearch(QWidget* parent);
    ~TDBSearch();
    QString trigramme();

    private slots:
        void ok_pressed();
    void search_pressed();
    void cancel_pressed();
    void trigramme_double_clicked(QTreeWidgetItem * item, int column);
};

#endif
