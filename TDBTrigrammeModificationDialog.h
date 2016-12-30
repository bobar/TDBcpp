#ifndef TDBTRIGRAMMEMODIFICATIONDIALOG_H
#define TDBTRIGRAMMEMODIFICATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QValidator>
#include <QComboBox>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlRecord>

#include "TDBApplication.h"

#include "TDBTrigrammeValidator.h"
#include "TDBAccount.h"

class TDBTrigrammeModificationDialog : public QDialog
{
    Q_OBJECT



    private:

        QGridLayout* layout;

        QLabel* trigramme_label;
        QLabel* name_label;
        QLabel* first_name_label;
        QLabel* nickname_label;
        QLabel* category_label;
        QLabel* promo_label;
        QLabel* mail_label;
        QLabel* picture_label;
        QLabel* casert_label;

        QLineEdit* trigramme_edit;
        QLineEdit* name_edit;
        QLineEdit* first_name_edit;
        QLineEdit* nickname_edit;
        QComboBox* category_combo;
        QLineEdit* promo_edit;
        QLineEdit* mail_edit;
        QLineEdit* picture_edit;
        QLineEdit* casert_edit;

        QValidator* valid;

        QPushButton* ok_button;
        QPushButton* cancel_button;
        QPushButton* photo_button;

        TDBAccount* account;

    public:

        TDBTrigrammeModificationDialog(QWidget* parent, TDBAccount* acc);
        ~TDBTrigrammeModificationDialog();

        private slots:
            void ok_pressed();
        void cancel_pressed();
        void open_photo();
};

#endif
