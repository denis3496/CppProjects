/*
 * main.cpp
 *
 *  Created on: 30 kwi 2019
 *      Author: Denis
 */
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <ctime>

using namespace std;

//stworzyc struct
//size-wlasciwosc matrycy podawana przez uzytkownika

struct listElement{
	int data;
	listElement* next;
};

class list{ //single linked list
public:
	list():head(0),cursor(0){} //constructor
	~list(); //destructor
	void prepend(int n);
	int getElement(){return cursor->data;}
	void advance(){cursor=cursor->next;}
	void print();
	void release();
private:
	listElement* head;//header
	listElement* cursor;
};

void list::release(){
	cursor= head;
	while(head!=nullptr){
		cursor= head->next;
		delete head;
		head=cursor;
	}
}

void list::prepend(int n){
	listElement *temp= new listElement;	//new class object. object is described in struct by 2 params.
	temp->next=head;
	temp->data=n;

	if(head==nullptr) cursor=head=temp;
	else head=temp;//header is pointing to new element
}

list::~list(){
	cout<<"destructor called"<<endl;
	release();//march thru list and delete
}

void list::print(){
	listElement *tempHeader = head;
	while(tempHeader!=nullptr){
		cout<<tempHeader->data<<",";
		head=head->next;
		tempHeader=head;
	}
		cout<<"###"<<endl;
}


int main(){
	list a,b;
	a.prepend(8);
	a.prepend(9);
	cout<<"list A"<<endl;
	a.print();
	for(int i=0;i<40;++i)
		b.prepend(i*i);
	cout<<"list B"<<endl;
	b.print();


return 0;
}
