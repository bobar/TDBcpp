#ifndef TDBCLOPESMODIFICATION_H
#define TDBCLOPESMODIFICATION_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlRecord>

#include "TDBApplication.h"

#include "TDBDatabase.h"

class TDBClopesModification : public QDialog
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

        QString marque;

    public:
        TDBClopesModification(QWidget* parent, QString m);
        ~TDBClopesModification();

        private slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
