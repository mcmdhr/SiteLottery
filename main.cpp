#include "sitelotterymain.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QDateTime>

QString SystemName = QString::fromUtf8("四川师范大学学生社团联合会社团招新场地抽签系统");
//QString SystemName = QString::fromUtf8("四川师范大学日语协会欢乐日本行");
QString ShortSystemName = QString::fromUtf8("SLS");
QString Version = QString::fromUtf8("1.0.0.0");
QString CopyrightOwner = QString::fromUtf8("SICNU-RPZ");
QString SystemMaintain = QString::fromUtf8("四川师范大学计算机科学协会计协工作室");
QString Contactaddress = QString::fromUtf8("四川师范大学成龙校区第一实验大楼西105");
int InitNum = 150;//系统初始化总数
int weWantNum = 6;//bug   !!!不能为零和负数!!!
bool isUseBug = true;

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    SiteLotteryMain w;
    QSplashScreen *splash = new QSplashScreen;
    splash->setStyleSheet("font-size: 16px");
    splash->setPixmap(QPixmap(":/splash/splash.png"));//设置图片
    splash->show();//显示图片

    QDateTime curtime = QDateTime::currentDateTime();
    QDateTime nowtime;
    do{
        nowtime = QDateTime::currentDateTime();
    } while(curtime.secsTo(nowtime) <= 3);

    w.setWindowTitle(SystemName);
    w.show();

    //splash->finish(&w);//图片一直显示到mainWin加载完成
    //delete splash;

    return a.exec();
}
