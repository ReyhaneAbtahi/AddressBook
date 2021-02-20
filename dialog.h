#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <linklist.h>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void findslot();

signals:
    void findsignal(linklist *);

private:
    QLabel *label;
    QLineEdit *lineedit;
    QPushButton *find;
    QHBoxLayout *mainlay;
};

#endif // DIALOG_H
