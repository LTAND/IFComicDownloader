//
//   File name      : log.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-14 22:20:05
//

#ifndef _LOG_LOG_H_
#define _LOG_LOG_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "enum_def.h"
#include "log_handle.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // ��־��ӡģ���ʼ����
    // [in] kRootPath ��־��ŵĸ�·����
    // [in] lowest_level ��ӡ��־�����ض����ޡ����ضȴﵽ�򳬹�������޵���־��Ҫ��ӡ��
    void log_init(const char kRootPath[], eLogLevel lowest_level);

    // ��ӡ debug ���ضȵ���־��
    void log_debug(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // ��ӡ info ���ضȵ���־��
    void log_info(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // ��ӡ warning ���ضȵ���־��
    void log_warning(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // ��ӡ error ���ضȵ���־��
    void log_error(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // ��ӡ critical ���ضȵ���־��
    void log_critical(const LOG_HANDLE *kHandle, const char kFormat[], ...);


#ifdef __cplusplus
}
#endif

#endif
