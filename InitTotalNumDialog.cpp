#include "InitTotalNumDialog.h"
#include "ui_inittotalnumdialog.h"

InitTotalNumDialog::InitTotalNumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitTotalNumDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(SystemName);
}

InitTotalNumDialog::~InitTotalNumDialog()
{
    delete ui;
}

void InitTotalNumDialog::on_pBOK_clicked()
{
    if (ui->lineEditTotal->text().isEmpty())
    {
        QMessageBox::warning(NULL, ShortSystemName, QString("未进行初始化，总数默认%1！").arg(InitNum), QMessageBox::Ok);
    }
    else
    {
        InitNum = ui->lineEditTotal->text().toInt();
    }
    accept();
}
