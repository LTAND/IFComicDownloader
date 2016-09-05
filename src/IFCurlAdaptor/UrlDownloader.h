//
//   File name      : UrlDownloader.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:30:09
//

#ifndef _IFCURLADAPTOR_URLDOWNLOADERBASE_H_
#define _IFCURLADAPTOR_URLDOWNLOADERBASE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>
#include <boost/shared_ptr.hpp>

// Headers from other projects
#include "IFDataType/DataHolder.h"

// Headers of current project
// ...

class UrlDownloader
{
public:
    UrlDownloader(){}
    virtual ~UrlDownloader(){}

    // ����url��ָ����ļ���ֱ����ȫ�������
    // �������ص����ݰ�
    // ������ز�����ת��ʧ���ˣ��׳�����ʧ��ԭ����쳣
    // @kURL���ɿ�
    // @kRefererURL��@kCookie�ɿգ���ʾû�С�
    virtual DATAHOLDER_PTR Download(const std::string &kURL, const std::string &kRefererURL, const std::string &kCookie) = 0;

protected:
private:
};

typedef boost::shared_ptr<UrlDownloader> URLDOWNLOADER_PTR;

#endif
