#ifndef TDBMAINWINDOW_H
#define TDBMAINWINDOW_H

#include	<iostream>
#include	<math.h>

#include	<QByteArray>
#include	<QCryptographicHash>
#include	<QDateTime>
#include	<QDialog>
#include	<QDir>
#include	<QEvent>
#include	<QFile>
#include	<QFileDialog>
#include	<QFont>
#include	<QHBoxLayout>
#include	<QImage>
#include	<QInputDialog>
#include	<QKeyEvent>
#include	<QLabel>
#include	<QList>
#include	<QMainWindow>
#include	<QMenu>
#include	<QMenuBar>
#include	<QMessageBox>
#include	<QRegExp>
#include	<QSqlError>
#include	<QSqlQuery>
#include	<QSqlRecord>
#include	<QString>
#include	<QStringList>
#include	<QTextStream>
#include	<QToolBar>
#include	<QVBoxLayout>

#include	"TDBApplication.h"

#include	"TDBAccount.h"
#include	"TDBAdminAdmin.h"
#include	"TDBAuth.h"
#include	"TDBBatchDialog.h"
#include	"TDBClopes.h"
#include	"TDBClopesAdmin.h"
#include	"TDBDatabase.h"
#include	"TDBExceptions.h"
#include	"TDBHistory.h"
#include	"TDBPasswordChange.h"
#include	"TDBRefillDialog.h"
#include	"TDBSearch.h"
#include	"TDBTransactionDialog.h"
#include	"TDBTransfertDialog.h"
#include	"TDBTrigrammeCreationDialog.h"
#include	"TDBTrigrammeDialog.h"
#include	"TDBTrigrammeModificationDialog.h"
//#include 	"TDBEtron.h"


class TDBMainWindow : public QWidget // KISS
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent* e);

private:
    // vérifie si un compte est actif, sinon demande un trigramme
    // renvoie true si on a un compte actif, false sinon
    bool init_action();
    // zdéo
    bool bob_is_bank;

    int last_conso_montant;
    TDBAccount* last_conso_bank;
    QString last_clopes;
    int last_clopes_quantite;

    //TDBEtron* etron;

    // historique des consos du compte actif
    TDBHistory* history;

    QMenu* account_menu;
    QAction* enter_trigramme_action;
    QAction* modif_trigramme_action;
    QAction* transaction_action;
    QAction* quit_action;

    QMenu* admin_menu;
    QAction* create_trigramme_action;
    QAction* refill_action;
    QAction* transfert_action;
    QAction* modify_trigramme_action;
    QAction* admin_admin_action;
    QAction* passwd_action;
    QAction* export_action;
    QAction* reset_turnover_action;
    QAction* set_bank_action;
    QAction* remove_bank_action;
    QAction* erase_trigramme_action;
    QAction* search_action;
    QAction* clopes_action;
    QAction* trigramme_export_action;
    QAction* positivation_export_action;
    QAction* cancel_action;
    QAction* batch_action;

    QAction* mail_action;

    QMenu* root_menu;

    QMenu* tools_menu;
    QAction* admin_action;
    QAction* clopes_admin_action;
    QAction* stats_action;

    QAction* son_action;
    QAction* zde_action;
    QAction* pch_action;
    //QAction* toggle_etron_action;

    //QAction* all_lights_on_action;
    //QAction* all_lights_off_action;

    // le layout root
    QVBoxLayout* layout0;
    QHBoxLayout* layout;
    QMenuBar* menubar;

    QToolBar* toolbar;

    // ça c'est tout le bordel à droite
    QVBoxLayout* infos_layout;
    QHBoxLayout* bank_layout;
    QPushButton* bob_bank_button;
    QPushButton* binet_bank_button;
    QLabel* label_trigramme;
    QLabel* label_name;
    QLabel* label_balance;
    QLabel* label_turnover;
    QLabel* label_picture;

    // le compte du BôB
    TDBAccount* default_bank_account;
    // le compte des soirées, généralement NULL
    TDBAccount* temp_bank_account;
    // le compte banque actif, généralement BôB
    TDBAccount* current_bank_account;
    // le compte client actif
    TDBAccount* current_account;

    // zou
    void set_current_account(const QString& trigramme);
    // nettoie tout ce qui est historique et panneau d'infos
    void clear();
    // célemo
    void update();
    // stéou
    void update_money_display();

private slots:

    void ask_trigramme(QString initial = QString());
    void achat(QString initial = QString());
    void create_trigramme();
    void refill();
    void modif_trigramme();
    void transfert();
    void admin_admin();
    void admin_passwd();
    void export_database();
    void reset_turnover();
    void remove_bank();
    void bob_bank();
    void binet_bank();
    void set_bank(TDBAccount* new_bank_account);
    void ask_bank_account();
    void delete_trigramme();
    void search_trigramme();
    void batch_achats();
    void achat_clopes();
    void clopes_admin();
    void export_trigramme();
    void export_positivation();
    void cancel();
    //void son();
    //void zde();
    //void pch();
    void mail();
    //void etron_changed(int state);
    //void all_lights_on();
    //void all_lights_off();

public:
    TDBMainWindow();
    ~TDBMainWindow();
};

#endif
