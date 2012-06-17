#ifndef TDBBATCHDIALOG_H
#define TDBBATCHDIALOG_H

#include <QtGlobal>
#include <QLocale>
#include <QDialog>
#include <QLabel>
#include <QList>
#include <QGridLayout>
#include <QLineEdit>
#include <QValidator>
#include <QPushButton>
#include <QTreeWidget>
#include <QStringListModel>
#include <QStringList>

#include "TDBApplication.h"

#include "TDBAccount.h"

class TDBBatchDialog : public QDialog
{
    Q_OBJECT

public:
    TDBBatchDialog(QWidget* parent, QStringList* lines, TDBAccount* binet_, int admin_id_);

private:
	void process();

private slots:
	void valider();
	void setSeparator(QString s);

protected:
    QChar educatedGuess();
	QChar separator;
	int admin_id;
	TDBAccount*	binet_account;

	QStringList* rawData;

    QGridLayout* layout;
    QLabel* separator_label;
    QLabel* listView_label;
    QLineEdit* separator_edit;
    QTreeWidget* listView;
    QPushButton* ok_button;
    QPushButton* cancel_button;
};

#endif
