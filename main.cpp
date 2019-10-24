#include <iostream>
#include <Windows.h>
#include "Item.h"
#include "Folder.h"
#include "Filee.h"
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <conio.h>

using namespace std;

int PrintMenu()
{
	int option = 0;
	cout << "Press 1 to make a Folder" << endl;
	cout << "Press 2 to make a File" << endl;
	cout << "Press 3 to delete a Folder" << endl;
	cout << "Press 4 to delete a File" << endl;
	cout << "Press 5 to write a File" << endl;
	cout << "Press 6 to read a File" << endl;
	cout << "Press 7 to change the Directory" << endl;
	cout << "Press 8 to go back" << endl;
	cout << "Press 9 to view contents of the Directory" << endl;
	cout << "Press 10 to Exit" << endl;
	cin >> option;
	return option;
}

string getName() 
{
	string name;
	cout << "Enter name:\t";
	cin.ignore();
	getline(cin,name);
	return name;
}

int main()
{
	Item * root;
	ifstream f("Saved.txt");
	string nameOfFile;
	stack <Item*> folders;
	int option = 0;

	if (f) {
		f >> nameOfFile;		
		nameOfFile.pop_back();
		root = new Folder(nameOfFile,"");
		root->Load(f);
		f.close();
	}
		
	else {
		cout << "Enter name for base directory" << endl;
		cin >> nameOfFile;
		root = new Folder(nameOfFile,"");
	}

	Item * saveRoot = root;
	string currentDirectory = root->getPath()+"\\";
	Item * temp;
	
	while (option != 10) {
		ofstream fout;
		fout.open("Saved.txt");
		saveRoot->Save(fout);
		f.close();

		system("cls");
		string name;
		option =  PrintMenu();
		switch (option) {
			case 1:	{
				name = getName();
				while (name == "") {
					cout << "Enter a valid name!" << endl;
					name = getName();
				}
				if (!(root->SeeExists(name))) {
					temp = new Folder(name,currentDirectory);
					root->setPointer(temp);
					cout << "Folder has been created" << endl;
				}
				else
					cout << "Folder of the name " << name << " already exists." << endl;
				break;
			}

			case 2:	{
				name = getName();
				while (name == "") {
					cout << "Enter a valid name!" << endl;
					name = getName();
				}
				if (!(root->SeeExists(name))) {
					temp = new Filee(name,currentDirectory);
					root->setPointer(temp);
					cout << "File has been created" << endl;
				}
				else
					cout << "File of the name " << name << " already exists." << endl;
				break;
			}

			case 3:	{
				name = getName();
				root->DeleteItem(name);
				break;
				}

			case 4:	{
				name = getName();
				root->DeleteItem(name);
				break;
				}
			
			case 5:	{
				name = getName();
				root->Access(name,"write");
				break;
				}

			case 6:	{
				name = getName();
				root->Access(name,"read");
				break;
				}

			case 7:	{
				name = getName();
				folders.push(root);
				root = root->changeDir(name);
				currentDirectory = root->getPath()+"\\";
				cout << "Current directory now: " << root->getName() << endl;
				break;
				}

			case 8:	{
				if (!(folders.empty())) {
					root = folders.top();
					folders.pop();
					currentDirectory = root->getPath()+"\\";
					cout << "Current directory now: " << root->getName() << endl;
				}
				else
					cout << "You are present in the Base directory, you can not go back further!" << endl;
				break;
				}

			case 9:	{
				root->Show();
				break;
				}

			case 10:	{
				break;
				}
		}
		system("pause");
	}
	system("pause");
}