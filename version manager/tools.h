#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "dirent.h"
#include <string.h>
#include <filesystem>
#include <Windows.h>
using std::vector;
using std::ofstream;
using std::ifstream;
using std::string;
static class tools
{
public:
	static void copyFile(string srcPath, string dstPath);
	static bool copyDir(string srcPath, string dstPath);
	static string getNameFromPath(string path);
	static bool isDirectoryExists(string path);
	static bool mkDir(string path);
	static vector<string> getDirValues(string path);
	static bool deleteDir(string path);



};

