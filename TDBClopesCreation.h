#ifndef TDBCLOPESCREATION_H
#define TDBCLOPESCREATION_H

#include <iostream>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAuth.h"

class TDBClopesCreation : public QDialog
{
    Q_OBJECT

    private:
        QGridLayout* layout;
        QLabel* marque_label;
        QLabel* prix_label;

        QLineEdit* marque_edit;
        QLineEdit* prix_edit;

        QPushButton* ok_button;
        QPushButton* cancel_button;

    public:
        TDBClopesCreation(QWidget* parent);
        ~TDBClopesCreation();

        public slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
