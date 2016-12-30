#ifndef TDBADMINCREATION_H
#define TDBADMINCREATION_H

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

class TDBAdminCreation : public QDialog
{
    Q_OBJECT

    private:
        QGridLayout* layout;
        QLabel* trigramme_label;
        QLabel* passwd1_label;
        QLabel* passwd2_label;
        QLabel* perm_label;

        QLineEdit* trigramme_edit;
        QLineEdit* passwd1_edit;
        QLineEdit* passwd2_edit;
        QComboBox* perm_combo;

        QPushButton* ok_button;
        QPushButton* cancel_button;

    public:
        TDBAdminCreation(QWidget* parent);
        ~TDBAdminCreation();

        public slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
