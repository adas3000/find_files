#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

class File
{
private:
	float size;
	float MB_size;
	std::string path;
	std::string name;
public:
	File(std::string path);
	File() { ; }
	~File();
	float getSize() { return size; }
	float getKBSize() { return ceil(size / 1024); }
	float getMBSize()& { return MB_size; }
	double getGBSize();
	std::string getPath() { return path; }
	std::string getFileName() { return name; }
	void setPath(std::string& path) ;
};

