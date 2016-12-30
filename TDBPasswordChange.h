#ifndef TDBPASSWORDCHANGE_H
#define TDBPASSWORDCHANGE_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDialog>
#include <QValidator>

#include "TDBDatabase.h"
#include "TDBApplication.h"

class TDBPasswordChange : public QDialog
{
    Q_OBJECT

    private:
        int id;

        QGridLayout* layout;
        QLabel* passwd1_label;
        QLabel* passwd2_label;
        QLineEdit* passwd1_edit;
        QLineEdit* passwd2_edit;

        QPushButton* ok_button;
        QPushButton* cancel_button;

    public:
        TDBPasswordChange(QWidget* parent, int i);
        ~TDBPasswordChange();

        public slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
