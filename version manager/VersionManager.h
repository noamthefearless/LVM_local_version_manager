#pragma once
#include "tools.h"
class VersionManager
{
public:



	void start();



private:
	void showProjects();
	void enterProject(string name);
	void showCommits(string name);
	int getNumberOfCommits(string path);
	void clone(string name, int num);
	string getCommitPathFromId(int id, string name);
	string savePath = "C:\\LVM\\projects";
};

