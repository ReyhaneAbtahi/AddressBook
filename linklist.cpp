#include "linklist.h"

linklist *head=nullptr,*rear=nullptr;

linklist::linklist()
{

}

linklist::~linklist()
{
    delete[] this;
}

void linklist::push()
{
    this->next=nullptr;
    if(head==nullptr){
        head=this;
        rear=this;
    }
    else {
        rear->next=this;
        rear=this;
    }
}

void linklist::remove()
{
    linklist *temp,*last;
    for(temp=head,last=nullptr;temp!=nullptr;last=temp,temp=temp->next)
        if(this->name==temp->name&&last!=nullptr){
            last->next=temp->next;
            if(last->next==nullptr)
                rear=last;
            break;
        }
        else if (this->name==temp->name&&last==nullptr) {
            head=temp->next;
        }
}

void linklist::edit(QString oldname)
{
    linklist *temp;
    for(temp=head;temp!=nullptr&&temp->name!=oldname;temp=temp->next);
    temp->name=this->name;
    temp->address=this->address;
}

linklist *linklist::getnext()
{
    linklist *temp;
    for(temp=head;temp!=nullptr&&temp->name!=this->name;temp=temp->next);
    temp=temp->next;
    if(temp!=nullptr)
        return temp;
    else
        return head;
}

linklist *linklist::getprevious()
{
    linklist *temp;
    if(this->name==head->name)
        return rear;
    for(temp=head;temp!=nullptr&&temp->next->name!=this->name;temp=temp->next);
    return temp;
}

int linklist::search()
{
    linklist *temp;
    for(temp=head;temp!=nullptr;temp=temp->next)
        if(this->name==temp->name)
            return 1;
    return -1;
}

QString linklist::find()
{
    linklist *temp;
    for(temp=head;temp!=nullptr;temp=temp->next)
        if(this->name==temp->name)
            return temp->address;
    return NULL;
}

int status(){
    linklist *temp;
    int counter=0;
    for(temp=head;temp!=nullptr;temp=temp->next,counter++);
    return counter;
}

void write(QDataStream& out)
{
    linklist *temp;
   // out<<head;
    for(temp=head;temp!=nullptr;temp=temp->next){
        out<<temp->name;
        out<<temp->address;
    }
}

linklist* read(QDataStream &in)
{
    while (head!=nullptr) {
        head->remove();
    }
    while(1){
        linklist *temp=new linklist;
        in>>temp->name;
        if(temp->name=="")
            return head;
        in>>temp->address;
        temp->push();
    }
}
