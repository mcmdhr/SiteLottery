#include "InitWeWantNumDialog.h"
#include "ui_initwewantnumdialog.h"

InitWeWantNumDialog::InitWeWantNumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitWeWantNumDialog)
{
    ui->setupUi(this);
}

InitWeWantNumDialog::~InitWeWantNumDialog()
{
    delete ui;
}

void InitWeWantNumDialog::on_pBOK_clicked()
{
    if (ui->lineEditNum->text().isEmpty())
    {
        QMessageBox::warning(NULL, ShortSystemName, QString("未进行设置，默认6！"), QMessageBox::Ok);
    }
    else
    {
        weWantNum = ui->lineEditNum->text().toInt();
    }
    accept();
}
