#include "tools.h"




void tools::copyFile(string srcPath, string dstPath)
{
    dstPath += "\\" + getNameFromPath(srcPath);
    CopyFileA(srcPath.c_str(), dstPath.c_str(), FALSE);
}



vector<string> tools::getDirValues(string path)
{
    vector<string> result;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            {
                continue;
            }


            result.push_back(ent->d_name);
        }
    }
    return result;

}







bool tools::copyDir(string srcPath, string dstPath)
{

    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(srcPath.c_str())) != NULL)
    {
        if (dstPath != "")
        {
            dstPath += "\\" + getNameFromPath(srcPath);
        }
        else
        {
            dstPath = getNameFromPath(srcPath);
        }

        mkDir(dstPath);
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {

            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            {
                continue;
            }

            

            if (ent->d_type == DT_REG)
            {
                copyFile(srcPath + "\\" + ent->d_name, dstPath);
            }
            else if (ent->d_type == DT_DIR)
            {
                copyDir(srcPath + "\\" + ent->d_name, dstPath);
            }
        }
        closedir(dir);
        return true;
    }
    return false;
}



bool tools::deleteDir(string path)
{
    if (isDirectoryExists(path))
    {

        if (getDirValues(path).size() > 0)
        {
            DIR* dir;
            struct dirent* ent;
            if ((dir = opendir(path.c_str())) != NULL)
            {
                while ((ent = readdir(dir)) != NULL)
                {
                    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                    {
                        continue;
                    }


                    if (ent->d_type == DT_REG)
                    {
                        DeleteFileA((path + "\\" + ent->d_name).c_str());
                    }
                    else if (ent->d_type == DT_DIR)
                    {
                        deleteDir(path + "\\" + ent->d_name);
                    }
                }
            }
            else
            {
                return false;
            }
        }
        if (RemoveDirectoryA(path.c_str()))
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    else
    {

        return false;
    }
}

bool tools::mkDir(string path)
{
    deleteDir(path);
    if (CreateDirectoryA(path.c_str(), NULL))
    {
        return true;
    }
    else
    {
        return false;
    }
}


string tools::getNameFromPath(string path)
{
   
    size_t lastSlashPos = path.find_last_of("/\\");

    if (lastSlashPos != std::string::npos) {

        std::string filename = path.substr(lastSlashPos + 1);
        return filename;
    }

    return path;
}







bool tools::isDirectoryExists(string path)
{
    DWORD ftyp = GetFileAttributesA(path.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;   // this is a directory!

    }
    return false;    // this is not a directory!
}





