//File: code_processor.cpp
//Name: Josephine Rich
//Date: October 26, 2021

//Description: This program implements all the Code_Processor class methods.
//It keeps track of Users, Codes, and Prizes in maps.

#include<code_processor.hpp>
#include<iostream>
#include<string>
#include<map>
#include<set>
#include<fstream>
using namespace std;

bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity) {
	
	Prize *p;
	map<string, Prize *>::const_iterator pit;

	//checking points
	if(points <= 0) return false;
	//cheching quantity
	if(quantity <= 0) return false;
	//checking the id
	for(pit=Prizes.begin(); pit != Prizes.end(); pit++) {
		if(pit->first == id) return false;
	}

	//allocating memory for a new instance of the Prize class
	p = new Prize;

	//setting all the data in the prize class
	p->id = id;
	p->description = description;
	p->points = points;
	p->quantity = quantity;

	//inserting the new prize into the map
	Prizes.insert(make_pair(id, p));

	return true;
}

bool Code_Processor::New_User(const string &username, const string &realname, int starting_points) {
	User *u;
	map<string, User *>::const_iterator nit;

	//checking if username already exists
	nit = Names.find(username);
	if(nit != Names.end()) return false;

	//checking starting_points 
	if(starting_points < 0) return false;

	//allocating memory for a new instance of the User class
	u = new User;

	//setting the data in the User class
	u->username = username;
	u->realname = realname;
	u->points = starting_points;

	//inserting the new user into the Names map
	Names.insert(make_pair(username, u));
	
	return true;
}

bool Code_Processor::Delete_User(const string &username) {
	User *u;
	map<string, User*>::iterator nit;
	set<string>::iterator it;
	
	//checking that user exists
	nit = Names.find(username);
	if(nit == Names.end()) return false;
	else u = nit->second;

	if(u->phone_numbers.size() == 0){}
	else{
		//erasing all of the user's phone number by calling Remove_Phone()
		while(u->phone_numbers.size() != 0) {
			it = u->phone_numbers.begin();
			Remove_Phone(username, *it);
		}
	}

	//erasing user from Names
	Names.erase(username);

	//deleting the user pointer
	delete u;

	return true;
}

bool Code_Processor::Add_Phone(const string &username, const string &phone) {
	map<string, User *>::iterator pit;
	set<string>::iterator it;
	User *u;
	
	pit = Phones.find(phone);
	//phone already exists
	if(pit != Phones.end()) return false;

	//looking for user in names
	pit = Names.find(username);
	//username doesn't exist
	if(pit == Names.end()) return false;
	u = pit->second;
	if(u->username == username) {
		//checking phone number in the set phone_numbers
		it = u->phone_numbers.find(phone);
		//phone_number already exists
		if(it != u->phone_numbers.end()) return false;
		else {
			//inserting the phone nubmer into the set phone_numbers
			u->phone_numbers.insert(phone);
			//inserting the phone number into the map Phones
			Phones.insert(make_pair(phone, u));
			return true;
		}
	}
	else return false;
}

bool Code_Processor::Remove_Phone(const string &username, const string &phone) {
	map<string, User *>::iterator pit;
	set<string>::iterator it;
	User *u;

	pit = Phones.find(phone);
	//did not find phone
	if(pit == Phones.end()) return false;
	//found phone
	u = pit->second;
	if(u->username != username) return false;
	if(u->username == username) {
		it = u->phone_numbers.find(phone);
		if(it == u->phone_numbers.end()) return false;
		else {
			//deleting the phone number from phone_numbers
			u->phone_numbers.erase(it);
			//also deleting phone number from Phones map
			Phones.erase(pit);
			return true;
		}
	}
	return false;
}

string Code_Processor::Show_Phones(const string &username) const {
	string phoneNums;
	map<string, User *>::const_iterator nit;
	set<string>::iterator it;
	User *u;

	nit = Names.find(username);
	//did not find user
	if(nit == Names.end()) return "BAD USER";
	//user found
	else {
		u = nit->second;
		//checking size of phone_numbers
		if(u->phone_numbers.size() == 0) return "";
		//phone_numbers size is bigger than 0 so pushing back on to the string phone_nums
		for(it = u->phone_numbers.begin(); it != u->phone_numbers.end(); it++) {
			phoneNums += *it  + "\n";
		}

		return phoneNums;
	}
}

unsigned int djb_hash(const string &s) {
	size_t i;
	unsigned int h;
	
	h = 5381;

	for(i=0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	
	return h;
}

int Code_Processor::Enter_Code(const string &username, const string &code) {
	set<string>::iterator cit;
	map<string, User *>::iterator nit;
	unsigned int h, points=0;
	User *u;

	//checking if code already exists
	cit = Codes.find(code);
	if(cit != Codes.end()) return -1;

	//checking for user 
	nit = Names.find(username);
	if(nit == Names.end()) return -1;

	//hashing code
	h = djb_hash(code);
	if((h % 17) == 0) points = 10;
	else if((h % 13) == 0) points = 3;
	else return 0;

	//adding points and adding code to Codes
	u = Names.find(username)->second;
	u->points = u->points + points;
	Codes.insert(code);
	
	return points;
}

int Code_Processor::Text_Code(const string &phone, const string &code) {
	set<string>::iterator cit;
	map<string, User *>::iterator pit;
	unsigned int h, points=0;
	User *u;

	//checking if code already exists
	cit = Codes.find(code);
	if(cit != Codes.end()) return -1;

	//checking for user
	pit = Phones.find(phone);
	if(pit == Phones.end()) return -1;

	//hashing code 
	h = djb_hash(code);
	if((h % 17) == 0) points = 10;
	else if((h % 13) == 0) points =3;
	else return 0;

	//adding points and adding code to Codes
	u = pit->second;
	u->points = u->points + points;
	Codes.insert(code);

	return points;
}

bool Code_Processor::Mark_Code_Used(const string &code) {
	unsigned int h;
	set<string>::iterator cit;
	
	//checking for valid code
	h = djb_hash(code);
	if(((h % 17) != 0) && ((h % 13) != 0)) return false;

	//checking if code already exitsts
	cit = Codes.find(code);
	if(cit != Codes.end()) return false;

	//adding code
	Codes.insert(code);

	return true;
}

int Code_Processor::Balance(const string &username) const {
	map<string, User *>::const_iterator nit;
	User *u;

	//finding username 
	nit = Names.find(username);
	if(nit == Names.end()) return -1;
	//setting pointer to user pointer
	u = nit->second;
	//returning the user balance/points
	return u->points;

}

bool Code_Processor::Redeem_Prize(const string &username, const string &prize) {
	User *u;
	Prize *p;
	map<string, User *>::iterator nit;
	map<string, Prize *>::iterator pit;
	bool user_found = false;
	bool prize_found = false;

	//finding the user
	nit = Names.find(username);
	if(nit != Names.end()) {
		user_found = true;
		u = nit->second;
	}
	else return false;

	//finding the prize
	pit = Prizes.find(prize);
	if(pit != Prizes.end()) {
		prize_found = true;
		p = pit->second;
	}
	else return false;

	//if both prize and user are found change the prize quantity and user points
	if(user_found && prize_found) {
		//checking if user points is less than pize points
		if(u->points < p->points) return false;
		//decrementing the prize quanity by 1
		else {
			p->quantity = p->quantity - 1;
			//decrementing user points by prize points
			u->points = u->points - p->points;
		}
		if(p->quantity == 0) {
			//deleting the prize pointer
			delete p;
			//deleting prize form map
			Prizes.erase(pit);
		}
		return true;
	}

	else return false;
}

Code_Processor::~Code_Processor() {
	map<string, User *>::iterator nit;
	map<string, Prize *>::iterator pit;
	User *u;
	Prize *p;

	//deleting all of the user pointers
	for(nit = Names.begin(); nit != Names.end(); nit++) {
		u = nit->second;
		delete u;
	}

	//deletting all of the prize pointers
	for(pit = Prizes.begin(); pit != Prizes.end(); pit++) {
		p = pit->second;
		delete p;
	}
}

bool Code_Processor::Write(const string &filename) const {
	ofstream stream;
	User *u;
	Prize *p;
	map<string, User *>::const_iterator nit;
	map<string, Prize *>::const_iterator pit;
	set<string>::const_iterator it;

	stream.open(filename.c_str());
	if(stream.fail()) return false;
	
	//printing all the users in Names to file
	for(nit = Names.begin(); nit != Names.end(); nit++) {
		u  = nit->second;
	stream << "ADD_USER " << u->username << " " << u->points << " " << u->realname << endl;
	}

	//printing all Prizes to file
	for(pit = Prizes.begin(); pit != Prizes.end(); pit++) {
		p = pit->second;
		stream << "PRIZE " << pit->first << " " << p->points << " " << p->quantity << " " << p->description << endl;
	}

	//printing all phone numbers
	for(nit = Phones.begin(); nit != Phones.end(); nit++) {
			u = nit->second;
			stream << "ADD_PHONE " << u->username << " " << nit->first << endl;
		}

	//printing codes that need to be marked as used
	for(it = Codes.begin(); it != Codes.end(); it++) {
		stream << "MARK_USED " << *it << endl;
	}

	stream.close();
	return true;
}

