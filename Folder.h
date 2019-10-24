#pragma once
#include <string>
#include "Item.h"
#include <vector>

using namespace std;

class Folder:public Item
{
public:
	Folder(string,string);
	string getPath(){
		return path;
	}
	void setPointer(Item*);
	void Delete();
	void DeleteItem(string);
	Item* changeDir(string);
	bool ifChanged();
	void Show();
	void Access(string, string);
	void Save(ofstream &f);
	Item * Resume(ifstream &f,string);
	void Load(ifstream &f);
	bool SeeExists(string);
	~Folder(void);
private:
	vector <Item*> itr;
	string path;
};

