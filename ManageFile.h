#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "File.h"

namespace fs = std::experimental::filesystem;

class ManageFile
{
private:
	std::vector<std::string> files;
	std::vector<std::string> folders_toCheck;
	std::vector<File>del_those;// do usuniecia szukanie w funkcji void GetFilesFromDirectory
	std::string from;
	std::string current_dir;
	bool has_dir;
	File temp_file;
	int mb_limit;
public:
	ManageFile(std::string from,int mb_limit = 0);
	ManageFile(std::string from,int limit,std::vector<FILE>&TO);
	~ManageFile();
	std::vector<std::string>&Get_Files() { return files; }
	int GetFilesCount() { return files.size(); }
	std::vector<File>&Get_Del_Files(){return del_those;}
private:
	std::vector<std::string>GetFilsFromDirectory(std::string& directory,std::vector<std::string>& Check);
	void GetFilsFromDirectory(std::vector<std::string>& AddTO,std::string& directory,std::vector<std::string>& Check);
	bool isBiggerThanLimit(std::string&& path);
};

