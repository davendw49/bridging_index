#include "getFileName.h"
#include <string.h>

string getPath()
{
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    string current_working_dir(buff);
    return current_working_dir;
}

// For windows
/*
void GetFileName(string path, vector<string> &filesName) {
    //file handle
    intptr_t hFile = 0;
    //file info
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)    //添加文件格式后缀
    {
        do {
            if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                filesName.push_back(p.assign(path).append("\\").append(fileinfo.name));
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}*/

void GetFileName(string path, vector<string> &filesName)
{
    cout << "[FILEPATH CHAECKING: ] scaning path: " << path << endl;
    struct dirent **namelist;
    int i, n;
    const char *str = path.c_str();
    string p;
    n = scandir(str, &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        for (i = 0; i < n; i++)
        {
            //            printf("%s\n", namelist[i]->d_name);
            if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0)
            {
                filesName.push_back(p.assign(path).append("/").append(namelist[i]->d_name));
            }
            free(namelist[i]);
        }
    }
    //    free(namelist);
}

void getFileName(const string &type)
{
    string path = getPath() + type; // file folder path
    vector<string> filesName;
    ofstream file_out("filename.txt"); // open text file
    GetFileName(path, filesName);      // get file text

    for (size_t i = 0; i < filesName.size(); i++) // output the file name
    {
        file_out << filesName[i].c_str() << endl;
    }
    file_out.close(); // close file
}
