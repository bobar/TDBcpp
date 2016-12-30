#ifndef TDBPasswordDialog_H
#define TDBPasswordDialog_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>

// included by TDBApplication.h
// #include "TDBApplication.h"
#include <QDebug>

class TDBPasswordDialog : public QDialog
{
	Q_OBJECT

private:
	QGridLayout* layout;
	QLabel* passwd_label;
	QLineEdit* passwd_edit;
	QString pw;

	QPushButton* ok_button;
	QPushButton* cancel_button;

public:
	TDBPasswordDialog(QWidget* parent = 0);
	~TDBPasswordDialog();

	QString get_pw();

public slots:
	void ok_pressed();
};

#endif
