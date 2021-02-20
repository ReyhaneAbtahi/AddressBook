#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    name_label=new QLabel("Name:");
    address_label=new QLabel("Address:");
    name =new QLineEdit;
    address =new QTextEdit;
    add=new QPushButton("&Add");
    edit=new QPushButton("&Edit");
    remove=new QPushButton("&Remove");
    find=new QPushButton("&Find");
    load=new QPushButton("&Load...");
    load->setToolTip(tr("Load contacts from a file"));
    save=new QPushButton("Sa&ve...");
    save->setToolTip(tr("Save contacts to a file"));
    Export=new QPushButton("E&xport");
    previous=new QPushButton("&Previous");
    next=new QPushButton("&Next");
    submit=new QPushButton("&Submit");
    submit->hide();
    cancel=new QPushButton("&Cancel");
    cancel->hide();
    submit1=new QPushButton("&Submit");
    submit1->hide();
    cancel1=new QPushButton("&Cancel");
    cancel1->hide();
    main_lay=new QGridLayout;
    central=new QWidget;

    main_lay->addWidget(name_label,0,0);
    main_lay->addWidget(name,0,1,1,2);
    main_lay->addWidget(address_label,1,0);
    main_lay->addWidget(address,1,1,10,2);
    main_lay->addWidget(add,1,3);
    main_lay->addWidget(edit,2,3);
    main_lay->addWidget(remove,3,3);
    main_lay->addWidget(find,4,3);
    main_lay->addWidget(load,5,3);
    main_lay->addWidget(save,6,3);
    main_lay->addWidget(Export,7,3);
    main_lay->addWidget(submit,8,3);
    main_lay->addWidget(cancel,9,3);
    main_lay->addWidget(submit1,8,3);
    main_lay->addWidget(cancel1,9,3);
    main_lay->addWidget(previous,11,1);
    main_lay->addWidget(next,11,2);
    setWindowTitle("Simple Address Book");
    name->setPlaceholderText("Name");
    address->setPlaceholderText("Address");
    name->setReadOnly(true);
    address->setReadOnly(true);
    next->setEnabled(false);
    previous->setEnabled(false);
    edit->setEnabled(false);
    remove->setEnabled(false);
    find->setEnabled(false);
    save->setEnabled(false);

    connect(add,SIGNAL(clicked()),this,SLOT(addslot()));
    connect(edit,SIGNAL(clicked()),this,SLOT(editslot()));
    connect(submit,SIGNAL(clicked()),this,SLOT(submitslot()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(cancelslot()));
    connect(submit1,SIGNAL(clicked()),this,SLOT(submit1slot()));
    connect(cancel1,SIGNAL(clicked()),this,SLOT(cancel1slot()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousslot()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextslot()));
    connect(remove,SIGNAL(clicked()),this,SLOT(removeslot()));
    connect(find,SIGNAL(clicked()),this,SLOT(findslot()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveslot()));
    connect(load,SIGNAL(clicked()),this,SLOT(loadslot()));
    connect(Export,SIGNAL(clicked()),this,SLOT(exportslot()));

    central->setLayout(main_lay);
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addslot()
{
    oldname=name->text();
    oldaddress=address->toPlainText();
    name->clear();
    address->clear();
    name->setReadOnly(false);
    address->setReadOnly(false);
    submit->show();
    cancel->show();
    add->setEnabled(false);
    edit->setEnabled(false);
    remove->setEnabled(false);
    find->setEnabled(false);
    load->setEnabled(false);
    save->setEnabled(false);
    Export->setEnabled(false);
    next->setEnabled(false);
    previous->setEnabled(false);
}

void MainWindow::editslot()
{
    oldname=name->text();
    oldaddress=address->toPlainText();
    name->setReadOnly(false);
    address->setReadOnly(false);
    submit1->show();
    cancel1->show();
    add->setEnabled(false);
    edit->setEnabled(false);
    remove->setEnabled(false);
    find->setEnabled(false);
    load->setEnabled(false);
    save->setEnabled(false);
    Export->setEnabled(false);
    next->setEnabled(false);
    previous->setEnabled(false);
}

void MainWindow::submitslot()
{
    QString _name=name->text();
    QString _address=address->toPlainText();
    if(_name==""||_address==""){
        QMessageBox::information(this, tr("Empty Field"),
                   tr("Please enter a name and address."));
        return;
    }
    linklist *t=new linklist;
    t->name=_name;
    t->address=_address;
    if(t->search()==-1){
        t->push();
        QMessageBox::information(this, tr("Add successful"),
                   tr("added to your address book."));
        oldname=_name;
        oldaddress=_address;
    }
    else {
        QMessageBox::information(this, tr("Add Unsuccessful"),
                   tr("Sorry,it exist in your address book."));
    }
    name->setText(oldname);
    address->setText(oldaddress);
    name->setReadOnly(true);
    address->setReadOnly(true);
    submit->hide();
    cancel->hide();
    add->setEnabled(true);
    edit->setEnabled(true);
    remove->setEnabled(true);
    load->setEnabled(true);
    save->setEnabled(true);
    Export->setEnabled(true);
    if(status()>1){
        next->setEnabled(true);
        previous->setEnabled(true);
     }
    if(status()>2)
          find->setEnabled(true);
}

void MainWindow::cancelslot()
{
    name->setText(oldname);
    address->setText(oldaddress);
    name->setReadOnly(true);
    address->setReadOnly(true);
    submit->hide();
    cancel->hide();
    add->setEnabled(true);
    load->setEnabled(true);
    if(status()>0){
        edit->setEnabled(true);
        remove->setEnabled(true);
        Export->setEnabled(true);
    }
    if(status()>=1){
         save->setEnabled(true);
    }
    if(status()>1){
        next->setEnabled(true);
        previous->setEnabled(true);
    }
    if(status()>2)
          find->setEnabled(true);
}

void MainWindow::submit1slot()
{
    linklist *temp=new linklist;
    temp->name=name->text();
    temp->address=address->toPlainText();
    if(temp->name==""||temp->address==""){
        QMessageBox::information(this, tr("Empty Field"),
                   tr("Please enter a name and address."));
        return;
    }
    if(temp->name!=oldname){
        if(temp->search()==1)
            QMessageBox::information(this, tr("Edit Unsuccessful"),
                       tr("Sorry,it exist in your address book."));
        else{
            temp->edit(oldname);
            QMessageBox::information(this, tr("Edit successful"),
                       tr("Edit in your address book."));
            oldname=temp->name;
            oldaddress=temp->address;
        }
    }
    else{
        temp->edit(oldname);
        temp->edit(oldname);
        QMessageBox::information(this, tr("Edit successful"),
                   tr("Edit in your address book."));
        oldname=temp->name;
        oldaddress=temp->address;
    }
    name->setText(oldname);
    address->setText(oldaddress);
    name->setReadOnly(true);
    address->setReadOnly(true);
    submit1->hide();
    cancel1->hide();
    add->setEnabled(true);
    load->setEnabled(true);
    if(status()>0){
        edit->setEnabled(true);
        remove->setEnabled(true);
        save->setEnabled(true);
        Export->setEnabled(true);
    }
    if(status()>1){
        next->setEnabled(true);
        previous->setEnabled(true);
     }
    if(status()>2)
          find->setEnabled(true);
}

void MainWindow::cancel1slot()
{
    name->setText(oldname);
    address->setText(oldaddress);
    name->setReadOnly(true);
    address->setReadOnly(true);
    submit1->hide();
    cancel1->hide();
    add->setEnabled(true);
    load->setEnabled(true);
    if(status()>0){
        edit->setEnabled(true);
        remove->setEnabled(true);
        save->setEnabled(true);
        Export->setEnabled(true);
    }
    if(status()>1){
        next->setEnabled(true);
        previous->setEnabled(true);
    }
    if(status()>2)
          find->setEnabled(true);
}

void MainWindow::nextslot()
{
    linklist *temp=new linklist;
    temp->name=name->text();
    temp->address=address->toPlainText();
    temp=temp->getnext();
    name->setText(temp->name);
    address->setText(temp->address);
}

void MainWindow::previousslot()
{
    linklist *temp=new linklist;
    temp->name=name->text();
    temp->address=address->toPlainText();
    temp=temp->getprevious();
    name->setText(temp->name);
    address->setText(temp->address);
}

void MainWindow::removeslot()
{
    linklist *temp=new linklist;
    temp->name=name->text();
    temp->address=address->toPlainText();
    int button = QMessageBox::question(this,
               tr("Confirm Remove"),
               tr("Are you sure you want to remove this contact?"),
               QMessageBox::Yes | QMessageBox::No);
    if(button==QMessageBox::Yes){
        if(status()>1)
            previousslot();
        else {
           name->setText("");
           address->setText("");
        }
        temp->remove();
        QMessageBox::information(this, tr("Remove Successful"),
                      tr("contact has been removed from your address book."));
    }
    if(status()==0){
        edit->setEnabled(false);
        remove->setEnabled(false);
        save->setEnabled(false);
    }
    if(status()<2){
        next->setEnabled(false);
        previous->setEnabled(false);
    }
    if(status()<3)
        find->setEnabled(false);
}

void MainWindow::findslot()
{
    Dialog *findwindows=new Dialog(this);
    findwindows->show();
    connect(findwindows,SIGNAL(findsignal(linklist *)),this,SLOT(find1slot(linklist *)));
}

void MainWindow::find1slot(linklist *temp)
{
    name->setText(temp->name);
    address->setText(temp->find());
}

void MainWindow::saveslot()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Address Book"), "",
            tr("Address Book (*.abk);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }
           QDataStream out(&file);
                  out.setVersion(QDataStream::Qt_4_5);
                  write(out);
              }
}

void MainWindow::loadslot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Address Book"), "",
           tr("Address Book (*.abk);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {

           QFile file(fileName);

           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }

           QDataStream in(&file);
           in.setVersion(QDataStream::Qt_4_5);
           linklist* temp=read(in);
           name->setText(temp->name);
           address->setText(temp->address);
    }
    Export->setEnabled(true);
    if(status()>0){
        edit->setEnabled(true);
        remove->setEnabled(true);
        save->setEnabled(true);
    }
    if(status()>1){
        next->setEnabled(true);
        previous->setEnabled(true);
    }
    if(status()>2){
        find->setEnabled(true);
    }
}

void MainWindow::exportslot()
{
      QString _name = name->text();
      QString _address = address->toPlainText();
      QString firstName;
      QString lastName;
      QStringList nameList;

      int index = _name.indexOf(" ");

      if (index != -1) {
          nameList = _name.split(QRegExp("\\s+"), QString::SkipEmptyParts);
          firstName = nameList.first();
          lastName = nameList.last();
      } else {
          firstName = _name;
          lastName = "";
      }

      QString fileName = QFileDialog::getSaveFileName(this,
          tr("Export Contact"), "",
          tr("vCard Files (*.vcf);;All Files (*)"));

      if (fileName.isEmpty())
          return;

      QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly)) {
             QMessageBox::information(this, tr("Unable to open file"),
                 file.errorString());
             return;
         }

         QTextStream out(&file);
         out << "BEGIN:VCARD" << "\n";
            out << "VERSION:2.1" << "\n";
            out << "N:" << lastName << ";" << firstName << "\n";

            if (!nameList.isEmpty())
               out << "FN:" << nameList.join(" ") << "\n";
            else
               out << "FN:" << firstName << "\n";
            _address.replace(";", "\\;", Qt::CaseInsensitive);
               _address.replace("\n", ";", Qt::CaseInsensitive);
               _address.replace(",", " ", Qt::CaseInsensitive);

               out << "ADR;HOME:;" << _address << "\n";
               out << "END:VCARD" << "\n";

               QMessageBox::information(this, tr("Export Successful"),
                   tr("contact has been exported as a vCard."));
}
