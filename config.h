#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>

extern QString Version;
extern QString CopyrightOwner;
extern QString SystemName;
extern QString ShortSystemName;
extern QString SystemMaintain;
extern QString Contactaddress;
extern int InitNum;
extern int weWantNum;
extern bool isUseBug;

#endif // CONFIG_H
