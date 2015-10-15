#ifndef INITTOTALNUMDIALOG_H
#define INITTOTALNUMDIALOG_H

#include <QDialog>
#include "config.h"

namespace Ui {
class InitTotalNumDialog;
}

class InitTotalNumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitTotalNumDialog(QWidget *parent = 0);
    ~InitTotalNumDialog();

private slots:
    void on_pBOK_clicked();

private:
    Ui::InitTotalNumDialog *ui;
};

#endif // INITTOTALNUMDIALOG_H
