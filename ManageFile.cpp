#include "stdafx.h"
#include "ManageFile.h"


ManageFile::ManageFile(std::string from, int mb_limit) :
	from(from), mb_limit(mb_limit)
{
	GetFilsFromDirectory(files, from, folders_toCheck);

	//std::cout << "Szukam plikow...\n";

	//std::vector<std::string>DelThose;

	while (!folders_toCheck.empty())
	{
		auto i = folders_toCheck.end()-1;
		std::string f = *i;
		folders_toCheck.pop_back();
		GetFilsFromDirectory(files, f, folders_toCheck);
	}
	
}

ManageFile::ManageFile(std::string from, int limit, std::vector<FILE>&TO):
	from(from)
{
	GetFilsFromDirectory(files, from, folders_toCheck);
	//in future..
	while (!folders_toCheck.empty())
	{
		auto i = folders_toCheck.end() - 1;
		std::string f = *i;
		folders_toCheck.pop_back();
		GetFilsFromDirectory(files, f, folders_toCheck);
	}



}


ManageFile::~ManageFile()
{
}

std::vector<std::string> ManageFile::GetFilsFromDirectory(std::string & directory, std::vector<std::string>& Check)
{
	fs::path dir(directory);

	fs::directory_iterator iter(directory),end;
	
	std::vector<std::string> temp;
	for (iter; iter != end; iter++)
	{
		
		bool is_directory = fs::is_directory(iter->path()); 
		if (!is_directory)
			temp.push_back(iter->path().string());
		else
			Check.push_back(iter->path().string());
	}

	return temp;
}

void ManageFile::GetFilsFromDirectory(std::vector<std::string>& AddTO, std::string& directory, std::vector<std::string>& Check)
{
	try
	{
		fs::path dir(directory);
		fs::directory_iterator iter(directory), end;
		bool is_directory;
		for (iter; iter != end; iter++)
		{
				is_directory = fs::is_directory(iter->path());
				if (!is_directory)
				{
					AddTO.push_back(iter->path().string());
					temp_file.setPath(*(AddTO.end()-1));

					if (temp_file.getMBSize() >= mb_limit)
						del_those.push_back(temp_file);
				}
				else
					//if(isBiggerThanLimit(iter->path().string()))
					Check.push_back(iter->path().string());
				

		}
	}
	catch (const fs::filesystem_error& er)
	{
		std::cerr << "filesystem error ! " << er.what() << "\n";
	}
	catch (const std::exception& er)
	{
		std::cout << "General exception : " << er.what() << "\n";
	}
	catch (...)
	{
		std::cout << "Unkown exception \n";
	}

}

bool ManageFile::isBiggerThanLimit(std::string&&  path)
{
	std::size_t size = 0;

	fs::path hel(path + "/");

	for (fs::recursive_directory_iterator it(hel); it != fs::recursive_directory_iterator(); it++)
	{
	//	std::cout << *it << "\n";
		if (!fs::is_directory(*it))
		{
			size += fs::file_size(*it);
		}
	}
	float kb_size = ceil(size / 1024.0f);
	float mb_size = float(kb_size / 1024.0f);

	if (mb_size >= mb_limit)
		return true;

	return false;
}
