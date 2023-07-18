#pragma once
#include "FileInfo.h"
#include "VirtualFileSystem.h"
using namespace std;

class VFSfile
{
	
public:
	 
	FileInfo myFileInfo;//the file details obj
	VFSfile(string pathName, OpenType type)//ctor
	{
		myFileInfo.Init(pathName, type);//initial the values
	}
	VFSfile()//def ctor
	{
	
	}
	void open();//open a file - prepare thr file for reading or writing
	string read();//return a the file contents as a text 
	void write(string text);//write the file content as a text
	bool IsWellFile();//return if the file is opened weel
	void close();//close the file
	void seekg(int offset, Location location = (Location)0);//move the offset for reading
	int tellg() { return this->myFileInfo.offsetG; }//return the reading offset location
	void seekp(int offset, Location location = (Location)0);//move the offset for writing
	void deleteFile();//delete file
	int tellp() { return this->myFileInfo.offsetP; }//return the writing offset location
};

