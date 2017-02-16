//
//   File name      : DirectoryOperator.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 10:12:08
//

#ifndef _DIRECTORYOPERATOR_H_
#define _DIRECTORYOPERATOR_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
#include <list>
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class DirectoryOperator
{
public:
    // ɾ��һ��Ŀ¼�������ǲ��ǿյģ���
    static bool deleteDirectory(const std::string &kPath);
    // ����һ��Ŀ¼�����û�и�Ŀ¼��ݹ鴴������
    static bool createDirectory(const std::string &kPath);
    // ��ȡһ��Ŀ¼�µ��ļ��б�������Ŀ¼����
    static std::list<std::string> getFilesInDirectory(const std::string &kRootPath);
protected:
private:
    DirectoryOperator(){}
    ~DirectoryOperator(){}
};

#endif
