#pragma once
#include "FileInfo.h"
#include "SearchTree.h"
#include <fstream>
#include "VirtualFileSystem.h"
using namespace std;
class VirtualFileSystem
{
public:
	SearchTree<FileInfo> tree_vfs;//contains all the files stored in the VFS file - the stored in real hard disk
	VirtualFileSystem()
	{
		/*
		The following lines put values into the binary file and write them into the tree structure
		so I can demonstrate the system running
		*/
		string sss = "vfs.txt";
		FileInfo x(sss, (OpenType)0, "xxx");
		sss = "filename.txt";
		FileInfo c(sss, (OpenType)0, "ccc");
		this->tree_vfs.add(x);
		this->tree_vfs.add(c);
		ofstream vfsFile1("VirtualFileSystem.bin", ios::binary);
		vfsFile1.write((char*)&this->tree_vfs, sizeof(SearchTree<FileInfo>));
		vfsFile1.close();

		ifstream vfsFile2("VirtualFileSystem.bin", ios::binary);
		vfsFile2.read((char*)&this->tree_vfs, sizeof(SearchTree<FileInfo>));
		vfsFile2.close();
	}
	~VirtualFileSystem()
	{
		ofstream vfsFile1("VirtualFileSystem.bin", ios::binary);
		vfsFile1.write((char*)&this->tree_vfs, sizeof(SearchTree<FileInfo>));
		vfsFile1.close();
	}
};
static VirtualFileSystem vfs;
