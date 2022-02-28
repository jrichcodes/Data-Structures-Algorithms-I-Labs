//File: dlist.hpp
//Name: Josephine Rich
//Date: November 2, 2021

//Description: This program implemetns the double link list class and methods.

#include<dlist.hpp>
#include<iostream>

using namespace std;

Dnode *Dnode::Next() {
	return flink;
}

Dnode *Dnode::Prev() {
	return blink;
}

Dlist::Dlist() {
	sentinel = new Dnode;  /*allocating new memory for the sentinel node */
	sentinel->s = "";      /*setting the string to be empty*/
	
	/*setting flink and blink pointers to itself*/
	sentinel->flink = sentinel; 
	sentinel->blink = sentinel;

	size = 0; /*setting the size*/

}

Dlist::Dlist(const Dlist &d) {
	
	sentinel = new Dnode; /*creating a new sentinel node*/
	sentinel->s = "";     /*setting the string of sentinel*/
	
	/*setting flink and blink pointers to itself*/
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;

	size = 0;  /*setting the size*/
	*this = d; /*calling assignment overload*/
}

Dlist& Dlist::operator = (const Dlist &d) {
	Dnode *tmp; 
	Clear(); 
	/*creating a temporary dlist by traversing d's nodes and pushes each one*/
	for(tmp = d.Begin(); tmp != d.End(); tmp = tmp->flink) Push_Back(tmp->s);
	return *this;
}

Dlist::~Dlist() {
	/*calling clear and destroys the sentinel*/
	Clear();
	delete sentinel;
}

void Dlist::Clear() {
	while(!Empty()) Erase(Begin()); /*while it's not empty (size = 0) delete the first node */
}

bool Dlist::Empty() const {
	return (size == 0);
}

size_t Dlist::Size() const {
	return size;
}

void Dlist::Push_Front(const string &s) {
	Insert_Before(s, Begin()); 
}

void Dlist::Push_Back(const string &s) {
	Insert_After(s, End()->blink);
}

string Dlist::Pop_Front() {
	string s;
	s = Begin()->s; /*retrieving and storing the string of the first node*/
	Erase(Begin()); /*erasing that node*/
	return s;
}

string Dlist::Pop_Back() {
	string s;
	s = End()->blink->s; /*retrieving and storing the string of the last node*/
	Erase(End()->blink); /*erasing that node*/
	return s;
}

Dnode *Dlist::Begin() const {
	return sentinel->flink;
}

Dnode *Dlist::End() const {
	return sentinel;
}

Dnode *Dlist::Rbegin() const {
	return sentinel->blink;
}

Dnode *Dlist::Rend() const {
	return sentinel;
}

void Dlist::Insert_Before(const string &s, Dnode *n) {
	Dnode *newnode;
	Dnode *prev;

	prev = n->blink;               /*setting prev to the node before n*/
	newnode = new Dnode;          /*setting newnode equal to a newly allocated dnode */
	newnode->s = s;              /*setting the right string */
	newnode->flink = n;
	newnode->blink = prev;

	prev->flink = newnode;      /*linking the new node to the previous node */
	n->blink = newnode;         /*linking the new node to the given node's blink */

	size++; /*incrementing the size */
}

void Dlist::Insert_After(const string &s, Dnode *n) {
	Dnode *next;

	next = n->flink; /*getting the node after the given node*/
	Insert_Before(s, next); /*calling insert before on the next node*/
}

void Dlist::Erase(Dnode *n) {
	Dnode *prev;
	Dnode *next;

	prev = n->blink;  /*setting prev to n's blink */
	next = n->flink;  /*setting next to n's flink */

	next->blink = prev; /*setting next blink pointer to prev */
	prev->flink = next; /*setting prev flink pointer to next */

	delete n; /*deleting n node*/

	size--; /*decrementing size*/

}
