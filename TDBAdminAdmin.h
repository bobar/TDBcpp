#ifndef TDBADMINADMIN_H
#define TDBADMINADMIN_H

#include <iostream>

#include <QLabel>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDialog>
#include <QVBoxLayout>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAdminModification.h"
#include "TDBAdminCreation.h"
#include "TDBAdminList.h"

class TDBAdminAdmin : public QDialog
{
    Q_OBJECT

    TDBAdminList* admin_list;

    private:

    QPushButton* ok_button;
    QPushButton* mod_admin_button;
    QPushButton* create_admin_button;
    QPushButton* delete_admin_button;
    QVBoxLayout* vlayout;
    public:

    TDBAdminAdmin(QWidget* parent);
    ~TDBAdminAdmin();

    private slots:
        void ok_pressed();
    void mod_admin_pressed();
    void create_admin_pressed();
    void delete_admin_pressed();
};

#endif
