#pragma once
#include <string>
#include <iostream>
using namespace std;

class Item
{
public:
	Item(void);
	string getName(){
		return name;
	};
	virtual string getPath() = 0;
	virtual void setPointer(Item*){};
	virtual void Delete() = 0;
	virtual void Write(){
		cout << "For writing to a Folder, change to respective directory and use option 1" << endl;};
	virtual void Read(){
		cout << "For reading a Folder, change to respective directory and use option 9" << endl;};
	virtual void Access(string, string){};
	virtual void DeleteItem(string){};
	virtual void Show(){};
	virtual Item* changeDir(string){
		return NULL;};
	virtual bool ifChanged(){
		return 0;
	}
	virtual void Save(ofstream &f){};
	virtual Item * Resume(ifstream &f, string){
		return NULL;
	}
	virtual void Load(ifstream &f){};
	virtual bool SeeExists(string){
	return false;};
	~Item(void);

protected:
	string name;
};

