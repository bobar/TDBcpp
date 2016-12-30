#ifndef TDBADMINMODIFICATION_H
#define TDBADMINMODIFICATION_H

#include <iostream>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "TDBApplication.h"

#include "TDBDatabase.h"
#include "TDBAuth.h"

class TDBAdminModification : public QDialog
{
    Q_OBJECT

    private:
        int admin_id;

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
        TDBAdminModification(QWidget* parent, QString trigramme);
        ~TDBAdminModification();

        public slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
