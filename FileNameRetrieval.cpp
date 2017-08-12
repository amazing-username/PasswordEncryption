#include<iostream>
#include"boost/filesystem.hpp"
#include"FileNameRetrieval.h"
#include"FolderStructure.h"

FileNameRetrieval::FileNameRetrieval() { }

std::vector<std::string> FileNameRetrieval::fileNameContainer() const { return fileNames; }
std::vector<std::string> FileNameRetrieval::passwordNameContainer() const { return passwordNames; }
void FileNameRetrieval::retrieveFileNames() 
{ 
	boost::filesystem::path directory(FolderStructure::keyDirectory);
	boost::filesystem::directory_iterator beg(directory), end;

	for (; beg!=end; ++beg)
		if (beg->path().extension()==".txt")
			fileNames.push_back(beg->path().filename().string());
}
void FileNameRetrieval::retrievePasswordNames()
{
	boost::filesystem::path directory(FolderStructure::passwordDirectory);
	boost::filesystem::directory_iterator beg(directory), end;

	for (; beg!=end; ++beg)
		if (beg->path().extension()==".txt")
			passwordNames.push_back(beg->path().filename().string());
}
