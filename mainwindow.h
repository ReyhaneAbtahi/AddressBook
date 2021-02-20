#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <linklist.h>
#include <dialog.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void addslot();
    void editslot();
    void submitslot();
    void cancelslot();
    void submit1slot();
    void cancel1slot();
    void nextslot();
    void previousslot();
    void removeslot();
    void findslot();
    void find1slot(linklist *);
    void saveslot();
    void loadslot();
    void exportslot();

private:
    QString oldname,oldaddress;
    QLabel *name_label;
    QLabel *address_label;
    QLineEdit *name;
    QTextEdit *address;
    QPushButton *add;
    QPushButton *edit;
    QPushButton *remove;
    QPushButton *find;
    QPushButton *load;
    QPushButton *save;
    QPushButton *Export;
    QPushButton *next;
    QPushButton *previous;
    QPushButton *cancel;
    QPushButton *submit;
    QPushButton *cancel1;
    QPushButton *submit1;
    QGridLayout *main_lay;
    QWidget *central;
};
#endif // MAINWINDOW_H
