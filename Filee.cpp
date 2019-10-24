#include <iostream>
#include "Filee.h"
#include <Windows.h>
#include <fstream>

using namespace std;

Filee::Filee(string name, string dir){
	this->name = name;
	path = dir+name;
	ofstream out;
	out.open(path);

}

void Filee::Delete() {
	wstring stemp = wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();
	DeleteFile(sw); // delete file
}

void Filee::Write(){
	string text = "";
	cout << "Write to your file!\n";
	getline(cin,text);

	ofstream f;
	f.open(path, std::ios_base::app);
	f << text << endl;
	f.close();
}

void Filee::Read(){
	fstream f;
	f.open(path);
	char byte;
	
	f.read(&byte, sizeof(byte));

     while (!f.eof( )) {
          cout << byte;
          f.read(&byte, sizeof(byte));
     }
	cout << endl;
	f.close();
}

bool Filee::ifChanged(){
	return false;
}

void Filee::Save(ofstream & f){
	f << name << 0 << endl; //0 : file
	f << "#" << endl;
}

Filee::~Filee(void){
}
