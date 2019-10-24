#pragma once
#include <string>
#include "Item.h"
using namespace std;

class Filee:public Item
{
public:
	Filee(string,string);
	string getPath(){
		return path;
	}
	void Delete();
	void Write();
	void Read();
	bool ifChanged();
	void Save(ofstream &f);
	~Filee(void);
private:
	string path;
};

