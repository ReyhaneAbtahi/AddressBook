#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    label=new QLabel("Enter the name of a contact:");
    lineedit=new QLineEdit;
    find=new QPushButton("Find");
    mainlay=new QHBoxLayout;
    mainlay->addWidget(label);
    mainlay->addWidget(lineedit);
    mainlay->addWidget(find);
    find->setDefault(true);
    setWindowTitle("Find a Contact");

    connect(find,SIGNAL(clicked()),this,SLOT(findslot()));

    setLayout(mainlay);
}

Dialog::~Dialog()
{
}

void Dialog::findslot()
{
    QString name=lineedit->text();
    if(name==""){
        QMessageBox::information(this, tr("Empty Field"),
                  tr("Please enter a name."));
              return;
    }
    linklist *temp=new linklist;
    temp->name=name;
    temp->address="";
    if(temp->search()==1){
        emit findsignal(temp);
        close();
    }
    else {
        close();
        QMessageBox::information(this, tr("Contact Not Found"),
                       tr("Sorry,this contact is not in your address book."));
    }
}
