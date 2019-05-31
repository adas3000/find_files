// findfatFiles.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include "ManageFile.h"
#include "File.h"
#include "Manager.h"

namespace fs = std::experimental::filesystem;


int main()
{
	//ManageFile manageE("E:/");
	//File *fws;
	std::string drive;
	int Limit_MB;

	std::cout << "Write patch to search :(endup with /) \n";
	std::cin >> drive;
	std::cout << "From how many MB start searching? : \n";
	std::cin >> Limit_MB;

	if (drive.size() < 3 && drive.size() >= 2)
	{
		drive += "/";
	}
	else if (drive.size() < 2)
	{
		drive += ":";
		drive += "/";
	}


	Manager manage(drive,Limit_MB);


	while (true)
	{
		if(manage.deleteone());
		std::cout << "GoodBye ! \n";
		system("cls");
	}


    return 0;
}

