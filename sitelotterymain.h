#ifndef SITELOTTERYMAIN_H
#define SITELOTTERYMAIN_H

#include <QMainWindow>
#include "config.h"
#include "InitTotalNumDialog.h"
#include "InitWeWantNumDialog.h"

namespace Ui {
class SiteLotteryMain;
}

class SiteLotteryMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit SiteLotteryMain(QWidget *parent = 0);
    void InitAccess(QString mdbFileAddr);
    void InitSQLSiteNum(int intNumTotal);
    QString getRollResult(void);
    void deleteNum(QString num);
    void ShowLabel(void);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);
    int funFreeNum(void);
    ~SiteLotteryMain();

public:
    QSqlDatabase db;
    bool isSelAccess;
    int UsedNum;
    int FreeNum;

    bool isRanding;
    QTimer *timer;
    bool isUseWantNum;
    bool isInitAccess;

private slots:
    void on_action_about_triggered();

    void on_action_access_triggered();

    void on_pushButton_clicked();

    void UpdateDigUI(void);

    void on_action_TotalSite_triggered();

private:
    Ui::SiteLotteryMain *ui;
};

#endif // SITELOTTERYMAIN_H
