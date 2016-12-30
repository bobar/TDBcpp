#ifndef TDBCLOPESADMIN_H
#define TDBCLOPESADMIN_H

#include <iostream>

#include <QLabel>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDialog>
#include <QVBoxLayout>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBClopesModification.h"
#include "TDBClopesCreation.h"
#include "TDBClopesList.h"

class TDBClopesAdmin : public QDialog
{
    Q_OBJECT

    TDBClopesList* clopes_list;

    private:

    QPushButton* ok_button;
    QPushButton* mod_clopes_button;
    QPushButton* create_clopes_button;
    QPushButton* delete_clopes_button;
    QVBoxLayout* vlayout;
    public:

    TDBClopesAdmin(QWidget* parent);
    ~TDBClopesAdmin();

    private slots:
        void ok_pressed();
    void mod_clopes_pressed();
    void create_clopes_pressed();
    void delete_clopes_pressed();
};

#endif
