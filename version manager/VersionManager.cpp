#include "VersionManager.h"



void VersionManager::showProjects()
{
	vector<string> vec = tools::getDirValues(savePath);
	if (vec.size() > 0)
	{
		std::cout << "\n\n--------------------\nPROJECTS\n--------------------\n";
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << i + 1 << ":	" << vec[i] << std::endl << std::endl;
		}
	}
	else
	{
		std::cout << "no projects were created yet\n";
	}

}


void VersionManager::showCommits(string name)
{
	vector<string> vec = tools::getDirValues(savePath + "\\" + name);
	if (vec.size() > 0)
	{
		std::cout << "\n\n--------------------\nCOMMITS\n--------------------\n";
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << i + 1 << ":	" << vec[i] << std::endl << std::endl;
		}
	}
	else
	{
		std::cout << "no commits were created yet\n";
	}

}


void VersionManager::start()
{
	string choice = "";
	

	while (choice != "lvm exit")
	{
		std::cout << savePath << " >>> ";
		std::getline(std::cin, choice);
		if (choice == "lvm show projects")
		{
			showProjects();
		}
		else if (choice.find("lvm delete ") == 0)
		{
			if (choice == "lvm delete ")
			{
				std::cerr << "ERROR: please enter the name parameter!" << std::endl;
			}
			else
			{
				if (tools::deleteDir(savePath + "\\" + choice.substr(11)))
				{
					std::cout << "the project " << choice.substr(11) << " was successfully deleted" << std::endl;
				}
				else
				{
					std::cerr << "ERROR: the project " << choice.substr(11) << " could not be located, or could not be deleted for some reason" << std::endl;
				}
			}

		}
		else if (choice.find("lvm new project ") == 0)
		{
			if (choice == "lvm new project ")
			{
				std::cerr << "ERROR: please enter the name parameter!" << std::endl;
			}
			else if (tools::isDirectoryExists(savePath + "\\" + choice.substr(16)))
			{
				std::cerr << "ERROR: a project under the same name already exists!" << std::endl;
			}
			else
			{
				if (tools::mkDir(savePath + "\\" + choice.substr(16)))
				{
					std::cout << "new project by the name of " << choice.substr(16) << " was created" << std::endl;
				}
				else
				{
					std::cerr << "ERROR: the project could not be opened" << std::endl;
				}
			}
		}
		else if (choice.find("lvm open ") == 0)
		{
			if (choice == "lvm open ")
			{
				std::cerr << "ERROR: please enter the name parameter!" << std::endl;
			}
			else if (!tools::isDirectoryExists(savePath + "\\" + choice.substr(9)))
			{
				std::cerr << "ERROR: couldn't find the project " << choice.substr(9) << std::endl;
			}
			else
			{
				std::cout << "opening " << choice.substr(9) << "..." << std::endl;
				enterProject(choice.substr(9));
			}
		}
		else if (choice == "lvm open" || choice == "lvm new project" || choice == "lvm delete")
		{
			std::cerr << "ERROR: please enter the name parameter!" << std::endl;
		}
		else
		{
			std::cerr << "ERROR: the command "  << choice << " is unrecognizeable" << std::endl;

		}
	}




}





int VersionManager::getNumberOfCommits(string path)
{
	vector<string> vec = tools::getDirValues(path);

	return vec.size();
}


void VersionManager::enterProject(string name)
{
	int index = 0;
	string choice = "", str = "";
	while (choice != "lvm close project")
	{
		std::cout << name << ": ";
		std::getline(std::cin, choice);
		if (choice == "lvm show commits")
		{
			showCommits(name);
		}
		else if (choice.find("lvm commit ") == 0)
		{
			if (choice == "lvm commit ")
			{
				std::cerr << "ERROR: please enter a discription of the commit" << std::endl;
			}
			else if (!tools::isDirectoryExists(name))
			{
				std::cerr << "ERROR: the local project folder could not be located" << std::endl;
			}
			else
			{
				if (tools::copyDir(name, savePath + "\\" + name))
				{
					std::cout << "commit was seccessful!" << std::endl;
					MoveFileA((savePath + "\\" + name + "\\" + name).c_str(), (savePath + "\\" + name + "\\" + std::to_string(getNumberOfCommits(savePath + "\\" + name)) + "-" + choice.substr(11)).c_str());
				}

			}
		}
		else if (choice == "lvm clone")
		{
			clone(name, -1);
		}
		else if (choice.find("lvm clone ") == 0)
		{
			if (choice == "lvm clone ")
			{
				std::cerr << "ERROR: please the number of the commit to clone" << std::endl;
			}
			else
			{
				str = choice.substr(10);
				try
				{
					index = std::stoi(str);
					if (index > 0)
					{
						clone(name, index);
					}
					else
					{
						std::cerr << "ERROR: the index is invalid!" << std::endl;

					}
				}
				catch (...)
				{
					std::cerr << "ERROR: the index is invalid!" << std::endl;
				}
			}
		}
		else if (choice == "lvm commit")
		{
			std::cerr << "ERROR: please enter a discription of the commit" << std::endl;

		}
		else
		{
			std::cerr << "ERROR: the command " << choice << " is unrecognizeable" << std::endl;

		}




	}




}


void VersionManager::clone(string name, int num)
{
	
	int numOfCommits = 0;
	if (num == -1)
	{
		numOfCommits = getNumberOfCommits(savePath + "\\" + name);
	}
	else
	{
		numOfCommits = num;
	}
	string commitPath = "";
	if (numOfCommits != 0)
	{
		commitPath = getCommitPathFromId(numOfCommits, name);
		tools::deleteDir(name);
		if (tools::copyDir(commitPath, ""))
		{
			MoveFileA(tools::getNameFromPath(commitPath).c_str(), name.c_str());
			std::cout << "clone was seccessful!" << std::endl;
		}
		else
		{
			std::cerr << "ERROR: clone didn't work as expected!" << std::endl;
		}
		
	}
	else
	{
		if (tools::mkDir(name))
		{
			std::cout << "clone was seccessful!" << std::endl;

		}
		else
		{
			std::cerr << "ERROR: clone didn't work as expected!" << std::endl;
		}
	}


}




string VersionManager::getCommitPathFromId(int num, string name)
{
	vector<string> vec = tools::getDirValues(savePath + "\\" + name);
	string numAsStr = std::to_string(num) + "-";
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].find(numAsStr) == 0)
		{
			return savePath + "\\" + name + "\\" + vec[i];
		}
	}
	return "";






}




