#include <iostream>
#include <fstream>
#include "Folder.h"
#include <Windows.h>
#include "Filee.h"

using namespace std;

Folder::Folder(string name, string dir){
	this->name = name;
	path = dir+name;
	wstring stemp = wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	CreateDirectory(sw, NULL);
}

void Folder::setPointer(Item* ptr){
	itr.push_back(ptr);
}

void Folder::DeleteItem(string temp){
	bool check = false;
	for (int i = 0; i < itr.size(); i++) {
		if (itr[i]->getName() == temp) {
			itr[i]->Delete();
			vector<Item *>::iterator nth = itr.begin() + i;
			itr.erase(nth);
			check = true;
			cout << "Item has been deleted" << endl;
		}
	}
	itr.shrink_to_fit();
	if (!(check))
		cout << "Item not found in the current directory!" << endl;
}

void Folder::Delete(){
	for (int i = 0; i < itr.size(); i++) {
			itr[i]->Delete();
		}
	wstring stemp = wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	RemoveDirectory(sw); // delete folder
	Folder::~Folder();
}

void Folder::Access(string temp, string option){
	bool check = false;
	for (int i = 0; i < itr.size(); i++) {
		if (itr[i]->getName() == temp) {
			if (option == "write")
				itr[i]->Write();
			else if (option == "read")
				itr[i]->Read();
			check = true;
		}
	}
	if (!(check))
		cout << "Item not found in the current directory!" << endl;
}

void Folder::Show(){
	system("cls");
	cout << "Current Directory:\t" << name << endl;
	cout << "Contents:" << endl;
	for (int i = 0; i < itr.size(); i++)
		cout << itr[i]->getName() << endl;
}

void Folder::Save(ofstream &f){
	f << name << 1 << endl; //1: folder
	
	for (int i = 0; i < itr.size(); i++) 
		itr[i]->Save(f);

	f << "#" << endl;
}

Item * Folder::changeDir(string temp){
	Item * s = NULL;
	bool check = false;
	for (int i = 0; i < itr.size(); i++) {
		if (itr[i]->getName() == temp) {
			if (itr[i]->ifChanged()){
				s = itr[i];
				check = true;
			}
		}
	}
	if (!(check)) {
		cout << "Item not found in the current directory!" << endl;
		return (this);
	}
	return s;
}

bool Folder::ifChanged(){
	return true;
}

void Folder::Load(ifstream & f){
	string nameOfFile, x;
	while (f.good()){
		f >> nameOfFile;
		if (nameOfFile != "#") {
			setPointer(Resume (f, nameOfFile));
		}
	}
	f.close();
}

Item * Folder::Resume(ifstream & f, string nameOfItem){
		string x;
		Item * ptr = NULL;
		x = nameOfItem.back();
		nameOfItem.pop_back();
		if ( x == "1")
			ptr = new Folder (nameOfItem, path + "\\");
		else if ( x == "0")
			ptr = new Filee (nameOfItem, path + "\\");
		while (true) {
			f >> nameOfItem;
		if (nameOfItem == "#")
			return ptr;
		else
			ptr->setPointer(ptr->Resume(f, nameOfItem));
		}
}

bool Folder::SeeExists(string name){
	for (int i = 0; i < itr.size(); i++) {
		if (itr[i]->getName() == name) {
			return true;
		}
	}
		return false;
}

Folder::~Folder(void){
	vector<Item*>().swap(itr);
	itr.shrink_to_fit();
}
