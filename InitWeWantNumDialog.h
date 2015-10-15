#ifndef INITWEWANTNUMDIALOG_H
#define INITWEWANTNUMDIALOG_H

#include <QDialog>
#include "config.h"

namespace Ui {
class InitWeWantNumDialog;
}

class InitWeWantNumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitWeWantNumDialog(QWidget *parent = 0);
    ~InitWeWantNumDialog();

private slots:
    void on_pBOK_clicked();

private:
    Ui::InitWeWantNumDialog *ui;
};

#endif // INITWEWANTNUMDIALOG_H
