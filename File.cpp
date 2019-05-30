#include "stdafx.h"
#include "File.h"


File::File(std::string path)
{
	setPath(path);
}


File::~File()
{
}


double File::getGBSize()
{
	float temp = getMBSize();
	return double(temp / 1024.0f);
}

void File::setPath(std::string& path)
{
	 this->path = path; 
	 try
	 {
		 size = fs::file_size(this->path);
		 float t = getKBSize();
		 this->MB_size = float(t / 1024.0f);
	 }
	 catch (const fs::filesystem_error& er)
	 {
		 std::cerr << "filesystem error ! " << er.what() << "\n";
	 }
	 catch (const std::exception& er)
	 {
		 std::cout << "General exception : " << er.what() << "\n";
	 }
	 this->name = fs::path(path).filename().string();
}
