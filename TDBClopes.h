#ifndef TDBCLOPES_H
#define TDBCLOPES_H

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>

#include "TDBApplication.h"

#include "TDBDatabase.h"

class TDBClopes : public QDialog
{
    Q_OBJECT

    private:
        int montant;
        int quantite;

        QGridLayout* layout;
        QLabel* marque_label;
        QLabel* quantite_label;
        QComboBox* marque_combo;
        QSpinBox* quantite_spin;

        QPushButton* ok_button;
        QPushButton* cancel_button;

        QString marque;

    public:
        TDBClopes(QWidget* parent);
        ~TDBClopes();
        QString get_marque() {return marque;}
        int money() {return montant;};
        int get_quantite() { return quantite;}
        private slots:
            void ok_pressed();
        void cancel_pressed();
};

#endif
