//
//   File name      : DirectoryOperator.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 10:15:26
//

// Implemented header
#include "../include/DirectoryOperator.h"

// C system headers
#include <windows.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

// ע�ͼ��������֡�
bool DirectoryOperator::deleteDirectory(const std::string &kPath)
{
    char cmd[128] = "rmdir /S /Q \"";
    strcat(cmd, kPath.c_str());
    strcat(cmd, "\"");
    system(cmd);
    return true;
}

// ע�ͼ��������֡�
bool DirectoryOperator::createDirectory(const std::string &kPath)
{
    char cmd[128] = "mkdir \"";
    strcat(cmd, kPath.c_str());
    strcat(cmd, "\"");
    system(cmd);
    return true;
}

// ע�ͼ��������֡�
std::list<std::string> DirectoryOperator::getFilesInDirectory(const std::string &kRootPath)
{
    std::list<std::string> result;
    char search_modal[MAX_PATH] = { '\0' };
    strcat(search_modal, kRootPath.c_str());
    strcat(search_modal, "*");

    WIN32_FIND_DATAA wfd;
    HANDLE hIterator = FindFirstFileA(search_modal, &wfd);
    if (INVALID_HANDLE_VALUE == hIterator)
    {
        fprintf(stderr, "Error: FindFirstFileA(%s) failed.", search_modal);
        return result;
    }

    while (1)
    {
        if (0 == strcmp(wfd.cFileName, "."))
        {   // ��ǰĿ¼
            ;
        }
        else if (0 == strcmp(wfd.cFileName, ".."))
        {   // ��һ��Ŀ¼
            ;
        }
        else if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {   // ��Ŀ¼�������ļ���
            ;
        }
        else
        {   // ���ļ���
            result.push_back(kRootPath + wfd.cFileName);
        }

        if (!FindNextFileA(hIterator, &wfd))
        {
            if (ERROR_NO_MORE_FILES == GetLastError())
            {
                break;
            }
            fprintf(stderr, "Error: FindNextFileA(%s) failed.\n", search_modal);
            break;
        }
    }
    if (!FindClose(hIterator))
    {
        fprintf(stderr, "Error: FindClose failed. (%s)", search_modal);
    }
    return result;
}
