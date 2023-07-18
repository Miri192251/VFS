#pragma once
using namespace std;
#include <iostream>
//#include "Enums.h"
#include "Tree.h"

class FileInfo
{
public:
	FileInfo()//defoult ctor
	{
	
	}
	int offsetP = 0;//offset for writing
	int offsetG = 0;//offset for reading
	Status status = (Status)none;//file status
	bool isDeleted = false;//is the file was deleted during this program
	bool isNewFile = false;//is the file was created during this program
	bool isWritten = false;//is some one in middle of writing to the file
	OpenType type;//type of the openning propose
	string fileName;//file name
	string filePath;// file path
	string contents;//file content
	FileInfo(string filePath, OpenType type)//set file name and dile path
	{
		Init(filePath, type);
	}
	FileInfo(string filePath, OpenType type , string contents)//set file name and dile path
	{
		this->contents = contents;
		Init(filePath, type);
	}
	void Init(string pathname, OpenType type);
	bool operator == (const FileInfo& vf) const;
	bool operator < (const FileInfo& vf) const;
	bool operator > (const FileInfo& vf) const;
	bool operator <= (const FileInfo& vf) const;
	bool operator >= (const FileInfo& vf) const;

};
