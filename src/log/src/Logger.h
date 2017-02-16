//
//   File name      : Logger.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:13:04
//

#ifndef _LOGGER_H_
#define _LOGGER_H_ 1

// Inherited header
// ...

// C system headers
#include <stdarg.h>

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
#include "../include/enum_def.h"
#include "../include/log_handle.h"

class Logger
{
    eLogLevel lowest_level_;
    std::string root_path_;
public:
    Logger()
    :   lowest_level_(eLogLevel_Error){}
    ~Logger(){}

    void set_lowest_level(eLogLevel lowest_level) { lowest_level_ = lowest_level; }
    void set_root_path(const std::string &kRootPath) { root_path_ = kRootPath; }

    void log(const LOG_HANDLE *kHandle, eLogLevel level, const char kFormat[], va_list ap);
protected:
private:
    // ���ɴ�д����־���ļ����ļ�·����
    std::string generateTargetFileUri();

    // ����־��д�����ڡ�ʱ�䡣
    static void appendDatatime(FILE *fp);

    // ����־��д����־����
    static void appendLevel(FILE *fp, eLogLevel level);

    // ����־��д����־������Ϣ��
    static void appendHandleData(FILE *fp, const LOG_HANDLE *kHandle);

    // ��鵱ǰ��־�ļ��Ƿ������Ҫ��������ǰ��־�ļ����Ӷ��ڲ�����д���ļ����ļ�����ǰ���»�һ����־�ļ�����д�롣
    static bool isLogFileTooLarge(const std::string &kFileUri);

    // ��������ǰ��־�ļ�URIΪ������֡�
    static void renameLogFile(const std::string &kFileUri);

    // ����־���ضȼ���ת��Ϊ�ַ�����ͨ������д�뵽��־�У���
    static const char* getLevelName(eLogLevel level);

    // ��ȡ�µ��ļ�URI�������URI���ڵ�ǰ��־�ļ�����ʱ��������
    static std::string getNewFileUriForRenaming(const std::string &kFileUri);
};

#endif
