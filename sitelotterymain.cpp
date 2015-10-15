#include "sitelotterymain.h"
#include "ui_sitelotterymain.h"

SiteLotteryMain::SiteLotteryMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SiteLotteryMain)
{
    ui->setupUi(this);
/*
    ui->label_2->setHidden(true);
    ui->label_3->setHidden(true);
    ui->label_4->setHidden(true);
    ui->label_5->setHidden(true);
    ui->label_Total->setHidden(true);
    ui->label_Used->setHidden(true);
    ui->label_Free->setHidden(true);

*/
    UsedNum = 0;
    FreeNum = InitNum - UsedNum;
    isSelAccess = false;
    ui->action_TotalSite->setEnabled(false);
    ui->pushButton->setEnabled(false);
    isRanding = false;
    isUseWantNum = false;
    isInitAccess = false;

    timer = new QTimer(this);
    timer->setInterval(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDigUI()));
}

void SiteLotteryMain::InitAccess(QString mdbFileAddr)
{
    if (QSqlDatabase::contains("dbconn"))
    {
        db = QSqlDatabase::database("dbconn");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QODBC", "dbconn");
    }
    QString dsn = QString::fromLocal8Bit("DRIVER={Microsoft Access Driver (*.mdb)};"
                                         "FIL={MS Access};DBQ=%1").arg(mdbFileAddr);
    db.setDatabaseName(dsn);
    ui->pushButton->setEnabled(true);
    ShowLabel();
    isInitAccess = true;
}

void SiteLotteryMain::InitSQLSiteNum(int intNumTotal)
{
    if (!db.open())
    {
        QMessageBox::critical(NULL, ShortSystemName, QString("数据库打开失败！"), QMessageBox::Ok);
    }
    else
    {
        for (int i = 0; i <= intNumTotal; i++)
        {
            QSqlQuery query(db);
            QString sqlbuf;
            if (i == 0)
            {
                sqlbuf = tr("delete from tblSiteInitList");
                query.exec(sqlbuf);
            }
            else if ((i == weWantNum) && isUseBug)
            {
                continue;
            }
            else
            {
                sqlbuf = QString("insert into tblSiteInitList(ID) values('%1')").arg(i);
                query.exec(sqlbuf);
            }
        }
        db.close();
    }
    ShowLabel();
    isUseWantNum = false;
    ui->label_showdig->setText("000");
}

QString SiteLotteryMain::getRollResult()
{
    QString ReData;
    if (!db.open())
    {
        QMessageBox::critical(NULL, ShortSystemName, QString("数据库打开失败！"), QMessageBox::Ok);
    }
    else
    {
        QSqlQuery query_s(db);
        QString sqlbuf_s;
        int rnl = 0;
        int rnd;
        QTime time;
        time = QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        rnd = qrand()%1000;
        sqlbuf_s = QString("select TOP 1 * from tblSiteInitList order by Rnd(-%1*ID)").arg(rnd);
        query_s.exec(sqlbuf_s);
        while(query_s.next())
        {
            ReData = query_s.value(0).toString().trimmed();
        }
        rnl = ReData.length();
        db.close();
        for (int i = 0; i < (3 - rnl); i++)
        {
            ReData = "0" + ReData;
        }
        deleteNum(ReData);
    }
    return ReData;
}

void SiteLotteryMain::deleteNum(QString num)
{
    if (!db.open())
    {
        QMessageBox::critical(NULL, ShortSystemName, QString("数据库打开失败！"), QMessageBox::Ok);
    }
    else
    {
        QSqlQuery query(db);
        QString sqlbuf;
        sqlbuf = QString("delete from tblSiteInitList where ID=%1").arg(num);;
        query.exec(sqlbuf);
        db.close();
    }
}

void SiteLotteryMain::ShowLabel()
{
    FreeNum = funFreeNum();
    if (!isUseWantNum && isUseBug)
    {
        FreeNum++;
    }
    UsedNum = InitNum - FreeNum;
    ui->label_Total->setText(QString("%1").arg(InitNum));
    ui->label_Used->setText(QString("%1").arg(UsedNum));
    ui->label_Free->setText(QString("%1").arg(FreeNum));
}

void SiteLotteryMain::closeEvent(QCloseEvent *event)
{
    switch(QMessageBox::question(this, ShortSystemName, "是否退出程序？", QMessageBox::Yes, QMessageBox::No))
    {
    case QMessageBox::Yes:
        event->accept();
        break;
    case QMessageBox::No:
    default:
        event->ignore();
    }
}

void SiteLotteryMain::keyPressEvent(QKeyEvent *e)
{
    if (isInitAccess)
    {
        if ((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_A))
        {
            if (isUseBug)
            {
                InitWeWantNumDialog *dlg = new InitWeWantNumDialog;
                if (dlg->exec() == InitWeWantNumDialog::Accepted)
                {
                    InitSQLSiteNum(InitNum);
                }
            }
        }
    }
}

int SiteLotteryMain::funFreeNum(void)
{
    int ReData;
    QString restr;
    if (!db.open())
    {
        ReData = 0;
        QMessageBox::critical(NULL, ShortSystemName, QString("数据库打开失败！"), QMessageBox::Ok);
    }
    else
    {
        QSqlQuery query_s(db);
        QString sqlbuf_s;
        sqlbuf_s = QString("select count(*) from tblSiteInitList");
        query_s.exec(sqlbuf_s);
        while(query_s.next())
        {
            restr = query_s.value(0).toString().trimmed();
        }
        ReData = restr.toInt();
        db.close();
    }
    return ReData;
}

SiteLotteryMain::~SiteLotteryMain()
{
    delete ui;
}

void SiteLotteryMain::on_action_about_triggered()
{
    QString aboutstring;
    aboutstring = QString("%1\n\n\n"
                          "版本号：%2\n\n"
                          "四川师范大学计算机科学协会 版权所有\n\n"
                          "Copyright 2000-2014 %3. All right reserved.\n\n"
                          "系统维护：%4\n\n"
                          "联系地址：%5").arg(SystemName, Version, CopyrightOwner, SystemMaintain, Contactaddress);
    QMessageBox::about(this,QString::fromUtf8("关于系统"),aboutstring);
}

void SiteLotteryMain::on_action_access_triggered()
{
    QString checkFile;
    if (!isSelAccess)
    {
        QString mdbFile = QFileDialog::getOpenFileName(this, QString("选择Access数据库"), "", QString("mdb数据库(*.mdb)"));
        checkFile = mdbFile.mid(mdbFile.length() - 15, 15);
        if (!mdbFile.isEmpty())
        {
            if (checkFile == "SiteLottery.mdb")
            {
                InitAccess(mdbFile);
                isSelAccess = true;
                ui->action_TotalSite->setEnabled(true);
                ui->action_access->setEnabled(false);
            }
            else
            {
                isSelAccess = false;
                QMessageBox::critical(NULL, ShortSystemName, QString("Access文件选择错误！"), QMessageBox::Ok);
            }
        }
    }
}

void SiteLotteryMain::on_pushButton_clicked()
{
    QString strResult;
    if (isRanding)
    {
        timer->stop();
        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            isRanding = false;
            if (!isUseWantNum)
            {
                isUseWantNum = true;
                int len;
                strResult = QString("%1").arg(weWantNum);
                len = strResult.length();
                for (int i = 0; i < (3 - len); i++)
                {
                    strResult = "0" + strResult;
                }
            }
            else
            {
                strResult = getRollResult();
            }
            ui->label_showdig->setText(strResult);
            ui->pushButton->setText("开  始");
        }
        else
        {
            isRanding = false;
            strResult = getRollResult();
            ui->label_showdig->setText(strResult);
            ui->pushButton->setText("开  始");
        }
        ShowLabel();
    }
    else
    {
        if (FreeNum != 0)
        {
            isRanding = true;
            timer->start();
            ui->pushButton->setText("停  止");
        }
        else
        {
            QMessageBox::critical(NULL, ShortSystemName, QString("抽签完毕，请重新初始化编号！"), QMessageBox::Ok);
        }
    }
}

void SiteLotteryMain::UpdateDigUI()
{
    QString strShow;
    QTime time;
    int rnd;
    int length;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    rnd = qrand()%1000;
    strShow = QString("%1").arg(rnd);
    length = strShow.length();
    for (int i = 0; i < (3 - length); i++)
    {
        strShow = "0" + strShow;
    }
    ui->label_showdig->setText(strShow);
}

void SiteLotteryMain::on_action_TotalSite_triggered()
{
    InitTotalNumDialog *tndlg = new InitTotalNumDialog;
    switch(QMessageBox::question(this, ShortSystemName, "是否初始化编号？", QMessageBox::Yes, QMessageBox::No))
    {
    case QMessageBox::Yes:
        if (tndlg->exec() == InitTotalNumDialog::Accepted)
        {
            InitSQLSiteNum(InitNum);
        }
        break;
    case QMessageBox::No:
    default:
        break;
    }
}
