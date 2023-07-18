#include "FileInfo.h"

void FileInfo::Init(string pathname, OpenType type)//this function initial the values of the infoFile object
{
	this->filePath = pathname;
	this->type = type;
	//the next lines extract the file name fron the path name
	size_t found = pathname.rfind("/");
	if (found != string::npos)
	{
		const string basePath = pathname.substr(0, found + 1);
		if (found != pathname.length())
		{
			this->fileName = pathname.substr(found + 1, pathname.length() - found - 1);
		}
			}
	else
	{
		this->fileName = pathname;
	}





}


/*
The following functions are operator overlaps for comparison operators to 
allow the program to use generic binary search trees
*/
bool FileInfo::operator== (const FileInfo& param) const {
	return  this->fileName == param.fileName && this->filePath == param.filePath;
}
bool FileInfo::operator<= (const FileInfo& param) const {
	return this->fileName <= param.fileName;

}
bool FileInfo::operator >= (const FileInfo& param) const {
	return this->fileName >= param.fileName;

}
bool FileInfo::operator> (const FileInfo& param) const {

	return this->fileName > param.fileName;
}
bool FileInfo::operator< (const FileInfo& param) const {

	return this->fileName <  param.fileName;
}