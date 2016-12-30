#ifndef TDBTRIGRAMMEDIALOG_H
#define TDBTRIGRAMMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "TDBApplication.h"

#include "TDBTrigrammeValidator.h"

class TDBTrigrammeDialog : public QDialog
{
    Q_OBJECT

    private:

        QVBoxLayout* layout;
        QLabel* label;
        QLineEdit* trigramme_edit;
        QValidator* valid;

    public:
        TDBTrigrammeDialog(QWidget* parent, QString initial = QString());
        ~TDBTrigrammeDialog();
        QString trigramme();

        public slots:
            void trigrammeChanged(QString trigramme);  // pour envoyer le trigramme quand on atteint 3 lettres
};

#endif
