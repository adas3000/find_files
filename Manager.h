#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <Windows.h>
#include <conio.h>
#include "File.h"
#include "ManageFile.h"

class Manager
{
private:
	ManageFile * manage;
	File *files;
	std::vector<std::string>data; //znalezione pliki
	std::vector<File>del_data;
	std::vector<std::string>newFiles;
	int limit_MB;
public:
	Manager(std::string startingPath,int limit_MB);
	~Manager();
	bool deleteone();
private:
	bool remove(std::string&& path);
	void changeSlashes(std::string& h);
};

