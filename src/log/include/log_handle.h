//
//   File name      : log_handle.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-15 14:02:40
//

#ifndef _LOG_HANDLE_H_
#define _LOG_HANDLE_H_ 1

// Inherited header
// ...

// C system headers
#include <stddef.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "../../os_api/include/data_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    // ��¼��־��ӡ�̶���Ϣ�Ľṹ�塣
    // �����ֶ���ͷ�ļ��ﲻ�ɼ���
    typedef struct
    {
        unsigned char dummy[256];
    }LOG_HANDLE;

    // ��ʼ��LOG_HANDLE����ִ�иú�����ֱ��ʹ�ã��ᷢ������Ԥ�ϵ����⡣
    void log_handle_init(LOG_HANDLE *handle);

    // ����LOG_HANDLE���ݵĽӿڡ��̲߳���ȫ��
    // [ in ] kName: ������������Ϊ�գ��������ᵼ�º���ִ��ʧ�ܡ�
    // [ in ] value: ����ֵ��
    // ���������ͬ�������Ĳ�ֵͬʱ�������õ�ֵ�Ḳ�������õ�ֵ��
    // ���ú�ı���������־�а����״����õ�˳���ӡ������
    void log_handle_set_int(LOG_HANDLE *handle, const char kName[], int value);
    void log_handle_set_uint64(LOG_HANDLE *handle, const char kName[], ULL value);
    void log_handle_set_string(LOG_HANDLE *handle, const char kName[], const char kValue[]);

    // ��LOG_HANDLE�е������������л���
    // [ in ] buffer_size: ��������Ļ�������С��
    // [ in, out ] ret_buffer: ��������Ļ������׵�ַ��
    // [ in ] kHandle: Ҫ���л����ݵ�LOG_HANDLEָ�롣
    // ����������������������������������ȷ�����������һ���ֽ���'\0'��
    void log_handle_serialize_data(size_t buffer_size, char ret_buffer[], const LOG_HANDLE *kHandle);

#ifdef __cplusplus
}
#endif

#endif
