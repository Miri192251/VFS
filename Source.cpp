#pragma once
#include <iostream>
#include "VFSfile.h"
#include "Enums.h"
#include<fstream>
using namespace std;
int main() {
	/*
	Attached is a sample run
	Note that there is additional functionality that was defined and implemented properly
	but was not called here in the main program
	*/
	string fileName = "filename.txt";
	VFSfile f(fileName, in);
	cout << f.myFileInfo.fileName;
	try
	{
		f.open();
		f.read();

		if (!f.IsWellFile()) {
			cout << "file opening failed\n" << endl;
			exit(0);
		}
		string content = f.read();
		VFSfile f1(fileName, out);
		f1.open();
		f1.write("fff");
		string cc = f.read();
		f.close();
		f1.close();
	}
	catch (string ex)
	{
		cout << ex;
	}

	return 0;
}