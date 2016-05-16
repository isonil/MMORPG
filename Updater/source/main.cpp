#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include "md5.h"

bool errorOccured = false;

class ClientFileClass
{
    public:
        std::string path;
        std::string md5;
        int size;

        ClientFileClass() {}
        ClientFileClass(const std::string &newPath, const std::string &newMd5, int newSize)
            :   path(newPath), md5(newMd5), size(newSize) {
        }
};

std::vector <ClientFileClass> clientFile;

void AddToList(const char *path)
{
    std::ifstream in(path, std::ios::binary);
    if(in) {
        std::string buffStr;
        unsigned char fileChar;
        while(in >> std::noskipws >> fileChar) {
            buffStr += fileChar;
        }
        clientFile.push_back(ClientFileClass(path, md5(buffStr), (int)buffStr.size()));
        printf(">%s (%u bytes)\n", path, buffStr.size());
        in.close();
    }
    else {
        printf("Error: Could not open '%s'.\n", path);
        errorOccured = true;
    }
}

void AddToListFrom(const char *path)
{
    size_t pathLen = strlen(path);
    char *findDataBuff = new char [pathLen+5];
    sprintf(findDataBuff, "%s*", path);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(findDataBuff, &findData);
    if(hFind != INVALID_HANDLE_VALUE) {
        if(findData.cFileName != std::string(".") &&
           findData.cFileName != std::string("..") &&
           findData.cFileName != std::string("updater.exe") &&
           findData.cFileName != std::string("Updater.exe") &&
           findData.cFileName != std::string("files.txt") &&
           findData.cFileName != std::string("Files.txt")) {
            if(findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                char *dirPath = new char[pathLen+strlen(findData.cFileName)+5];
                sprintf(dirPath, "%s%s/", path, findData.cFileName);
                AddToListFrom(dirPath);
                delete []dirPath;
            }
            else {
                char *filePath = new char[pathLen+strlen(findData.cFileName)+5];
                sprintf(filePath, "%s%s", path, findData.cFileName);
                AddToList(filePath);
                delete []filePath;
            }
        }
        while(FindNextFile(hFind, &findData)) {
            if(findData.cFileName != std::string(".") &&
               findData.cFileName != std::string("..") &&
               findData.cFileName != std::string("updater.exe") &&
               findData.cFileName != std::string("Updater.exe") &&
               findData.cFileName != std::string("files.txt") &&
               findData.cFileName != std::string("Files.txt")) {
                if(findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    char *dirPath = new char[pathLen+strlen(findData.cFileName)+5];
                    sprintf(dirPath,"%s%s/", path, findData.cFileName);
                    AddToListFrom(dirPath);
                    delete []dirPath;
                }
                else {
                    char *filePath = new char[pathLen+strlen(findData.cFileName)+5];
                    sprintf(filePath, "%s%s", path, findData.cFileName);
                    AddToList(filePath);
                    delete []filePath;
                }
            }
        }
    }
    delete []findDataBuff;
}

int main(int argc, char **argv)
{
    printf("File list updater\n\n");
    printf("Added files:\n");
    AddToListFrom("");
    std::ofstream out("files.txt");
    if(out) {
        out << "files\n";
        for(size_t i=0; i<clientFile.size(); ++i) {
            bool fileOK = true;
            for(size_t j=0; j<clientFile[i].path.size(); ++j) {
                if(clientFile[i].path[j] == ' ') {
                    printf("Error: File path '%s' contains spaces.\n", clientFile[i].path.c_str());
                    fileOK = false;
                    errorOccured = true;
                    break;
                }
            }
            if(fileOK) {
                out << clientFile[i].path << " " << clientFile[i].md5 << " " << clientFile[i].size << "\n";
            }
        }
        out.close();
    }
    else {
        printf("Error: Could not create 'files.txt'.\n");
        errorOccured = true;
    }
    printf("\nDone. Files quantity: %u.\n", clientFile.size());
    if(errorOccured) printf("Some errors occured!\n");
    _getch();
}
