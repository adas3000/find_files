#include "stdafx.h"
#include "Manager.h"


Manager::Manager(std::string startingPath,int limit_MB)
{
	this->limit_MB = limit_MB;

	std::cout << "File searching...Please wait\nIn disk which have a lot of files it may take a few minutes.\n";

	std::clock_t start = clock();
	manage = new ManageFile(startingPath,limit_MB);
	data = manage->Get_Files();
	std::clock_t finish = clock();

	std::cout << "File searching finished!\n";
	std::cout << "Searching time : " << (finish - start) / CLOCKS_PER_SEC << " seconds.\n";
	files = new File[data.size()];
	std::cout << data.size() << " files have been searched.\n";

	start = clock();
	
	del_data = manage->Get_Del_Files();
	finish = clock();
}


Manager::~Manager()
{
	delete manage;
}

bool Manager::deleteone()
{
	if(del_data.size()==1)
		std::cout << "Choose the file you would like to delete" << "1\n";
	else
	std::cout << "Choose the file you would like to delete" << "(1-" << del_data.size() << ")\n";;


	for (int i = 0; i < del_data.size(); i++){
		std::cout << i + 1 << "." << del_data[i].getFileName() << " size(GB) : " << del_data[i].getGBSize() << "\n";
	}

	int which;
	char mquit;
	std::cin >> which;

	

	std::cout << del_data[which - 1].getFileName() << "\n";

	std::cout << "For sure ? q to cancel ,esc to quit\n";
	std::cin >> mquit;

	if (mquit == 'q')
		return false;
	else if (mquit == 27) // ESCAPE
		exit(0);
	
	SetFileAttributesA(LPCSTR(del_data[which - 1].getPath().c_str()), FILE_ATTRIBUTE_NORMAL);

	int check = std::remove(del_data[which - 1].getPath().c_str());

	if (!(check!=0)) // means check == 0
	{
		try
		{
			del_data.erase(del_data.begin() + (which - 1));
			std::cout << "File deleted\n";
		}
		catch (std::exception& er)
		{
			std::cout << "General exception : " << er.what() << "\n";
		}
	}
	else
	std::cout << "Cannot delete the file!\n";

	
	


	std::cout << "Continue...\n";
	//std::cin >> mquit;
	char c = _getch();

	return false;
}
bool Manager::remove(std::string&& path)
{
	changeSlashes(path);
	//std::cout << path << "\n";
//	return false;
	std::fstream f(path, std::fstream::out | std::fstream::trunc);

	if (!f)
	{
		std::cout << "Cannot open file : " << path << "\n";;
		return false;
	}
	
	f.flush();
	f.close();

	if (std::remove(path.c_str()) == 0)return true;
	std::cout << "Cannot delete file : " << path << "\n";
	return false;
}

void Manager::changeSlashes(std::string& h)
{
	for (int i = 0; i < h.size(); i++)
		if (h[i] == 92) h[i] = 47;
		else if (h[i] == 47) h[i] = 92;

}
