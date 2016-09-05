//
//   File name      : UrlDownloaderSimple.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-04 19:34:09
//

#ifndef _URLDOWNLOADERSIMPLE_H_
#define _URLDOWNLOADERSIMPLE_H_ 1

// Inherited header
#include "UrlDownloader.h"

// C system headers
// ...

// C++ system headers
#include <string>
#include <boost/shared_ptr.hpp>

// Headers from other projects
#include "IFDataType/DataHolder.h"

// Headers of current project
#include "CurlFunctionPointers.h"

class UrlDownloaderSimple: public UrlDownloader
{
    CurlEasyInit    my_curl_easy_init_;
    CurlEasySetOpt  my_curl_easy_setopt_;
    CurlEasyPerform my_curl_easy_perform_;
    CurlEasyCleanUp my_curl_easy_cleanup_;

    DataHolder buffer_;
    size_t page_total_len_; // ��һʱ��ȡ�ã��������ؽ��ȵļ���
public:
    UrlDownloaderSimple(
        CurlEasyInit    my_curl_easy_init,
        CurlEasySetOpt  my_curl_easy_setopt,
        CurlEasyPerform my_curl_easy_perform,
        CurlEasyCleanUp my_curl_easy_cleanup
    );
    virtual ~UrlDownloaderSimple(){}

    // ����url��ָ����ļ���ֱ����ȫ�������
    // �������ص����ݰ�
    // ������ز�����ת��ʧ���ˣ��׳�����ʧ��ԭ����쳣
    // @kURL���ɿ�
    // @kRefererURL��@kCookie�ɿգ���ʾû�С�
    virtual DATAHOLDER_PTR Download(const std::string &kURL, const std::string &kRefererURL, const std::string &kCookie);

protected:
private:
};

#endif
