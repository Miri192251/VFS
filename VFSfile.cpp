#include "VFSfile.h"

inline bool exists_test(const string& name) {//check if file realy exists in the recived filePath
	ifstream f(name.c_str());
	return f.good();
}

void VFSfile::open()
{
	auto ptr = vfs.tree_vfs.search(this->myFileInfo);
	if (ptr != nullptr)//if the file already exsist in the vfs file
	{
		this->myFileInfo.status = (Status)3; //keep status open
		this->myFileInfo.contents = ptr->value.contents;//keep contents

	}
	else
	{
		if (exists_test(this->myFileInfo.filePath))//check if the file exsist in the file path in the hard disk
		{
			ifstream f(this->myFileInfo.filePath);//open the file
			string text = "";
			while (!f.eof())//copy the text
			{
				text += f.get();
			}
			f.close();//close the file
			this->myFileInfo.status = (Status)3;//change status ti open
			this->myFileInfo.contents = text;//keep the content
			vfs.tree_vfs.add(this->myFileInfo);//insert the file to vfs
		}
		else
		{
			if (this->myFileInfo.type == out)//if file not exsist in the vfs 
			{
				//add new file to the tree with initial values
				vfs.tree_vfs.add(this->myFileInfo);
				this->myFileInfo.status = (Status)3;
				this->myFileInfo.contents = "";
				this->myFileInfo.isNewFile = true;

			}
			else if (this->myFileInfo.type == in)//if want to open the file to read
			{
				cout << "there isnt such a file directory\n";

			}
		}
	}


}

string VFSfile::read()
{
	if ((this->myFileInfo.status == (Status)3 || this->myFileInfo.status == (Status)1) && this->myFileInfo.type == in)//if status is open oe read
	{
		this->myFileInfo.status = (Status)1;//keep status to read
		this->myFileInfo.contents = vfs.tree_vfs.search(this->myFileInfo)->value.contents.substr(this->myFileInfo.offsetG);
		return this->myFileInfo.contents;//assign the content value to the updated value from the vfs file and return it
	}
	else
	{
		string x = "cant accsses the file for reading";
		throw x;
	}
}

void VFSfile::write(string text)
{
	if ((this->myFileInfo.status == (Status)3 || this->myFileInfo.status == (Status)2) && this->myFileInfo.type == out && !this->myFileInfo.isWritten)
	{//if the file status is write or open and the opening type is for writing and no one else write to the file now 
		string finalStr = this->myFileInfo.contents.substr(0, this->myFileInfo.offsetP) + text;//keep the new text
		if (finalStr != this->myFileInfo.contents)//if the text has changed
		{
			(vfs.tree_vfs.search(this->myFileInfo)->value.contents) = finalStr;//assign the file content to the text
			this->myFileInfo.contents = finalStr;
			this->myFileInfo.status = (Status)2;//keep status as write
			this->myFileInfo.isWritten = true;//indicate that some one write to this file now
		}
	}
	else
	{
		string x = "cant accsses the file for writing";
		throw x;
	}





}

bool VFSfile::IsWellFile()//retrun if the obj present a well file
{
	return this->myFileInfo.status != none;
}

void VFSfile::close()
{
	if (this->myFileInfo.status != (Status)0 && this->myFileInfo.status != (Status)4)
	{
		ofstream f;
		if ((this->myFileInfo.status == (Status)2)//if we wrote to the file
			|| (this->myFileInfo.isNewFile))
		{
			f.open(this->myFileInfo.filePath);//open a realy file
			if (!f) { cout << "File could not be opened.\n"; return; }
			f << this->myFileInfo.contents << endl;//insert the text to the real file in the hard disk
			this->myFileInfo.isWritten = false;//stop the flag
		}
		else if ((!this->myFileInfo.isNewFile) && this->myFileInfo.isDeleted)//the file isnt new and was been deleted during the program
		{
			int succsses = remove(&this->myFileInfo.filePath[0]);//remove the file from the directory
		}
	}
	else
	{
		string x = "cant accsses the file for closing";
		throw x;
	}

}

void VFSfile::seekg(int offset, Location location)//move the offset to a specific place 
{
	switch (location)
	{
	case (Location)0:
		if (offset >= 0)//check is the offset is valid value
		{
			this->myFileInfo.offsetG = offset;
		}
		break;
	case (Location)1:
		if (this->tellg() + offset >= 0)//check is the offset is valid value
		{
			this->myFileInfo.offsetG = this->tellg() + offset;
		}
		break;
	case (Location)2:
		if (offset <= 0)//check is the offset is valid value
		{
			this->myFileInfo.offsetG = this->myFileInfo.contents.length() + offset;
		}
		break;
	default:
		break;
	}
}

void VFSfile::seekp(int offset, Location location)//exactly like the prev function
{
	switch (location)
	{
	case (Location)0:
		if (offset >= 0)
		{
			this->myFileInfo.offsetP = offset;
		}
		break;
	case (Location)1:
		if (this->tellg() + offset >= 0)
		{
			this->myFileInfo.offsetP = this->tellg() + offset;
		}
		break;
	case (Location)2:
		if (offset <= 0)
		{
			this->myFileInfo.offsetP = this->myFileInfo.contents.length() + offset;
		}
		break;
	default:
		break;
	}
}

void VFSfile::deleteFile()
{
	this->myFileInfo.isDeleted = true;//change the flag
	vfs.tree_vfs.remove(this->myFileInfo);//remove from the tree
}
