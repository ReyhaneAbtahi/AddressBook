#ifndef LINKLIST_H
#define LINKLIST_H

#include <QString>
#include <QFileDialog>

class linklist
{
public:
    linklist();
    ~linklist();
    void push();
    void remove();
    void edit(QString);
    linklist *getnext();
    linklist *getprevious();
    int search();
    QString find();
    int status();
    linklist *next;
    QString name;
    QString address;
};
int status();
void write(QDataStream&);
linklist* read(QDataStream&);
#endif // LINKLIST_H
