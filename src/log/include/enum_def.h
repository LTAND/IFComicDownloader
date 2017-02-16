//
//   File name      : enum_def.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:07:47
//

#ifndef _ENUM_DEF_H_
#define _ENUM_DEF_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

// ��־���ضȣ�����Խ��Խ���ء�
// DEBUG����ϸ��Ϣ�������Ų����ʱ�Ĵ�ӡ������ĳ���������뿪ĳ����������ӡĳ��������ǰֵ֮����ڴ��У�
// INFO������ȷ�ϳ�������Ԥ�����е���Ϣ�������ȡ�����ļ������ӵ������������п�ʼ�ȵȡ���
// WARNING��ָ��������һЩԤ��������飨����Ԥ���յ���Ӧ��Ϣ���������ʱ����ʱ�˻�û�յ�������ζ���Լ���Զ��ƽ̨�����쳣����
//          ����Ԥ����δ���ᷢ�����ϣ�������̿ռ�����ˣ�����������г�����Ȼ���������У���δ����ִ��Ԥ������ʧ�ܵ������
// ERROR���������������⣬���³����޷��ṩĳЩԤ�����ṩ�Ĺ��ܡ����������������С�
// CRITICAL�����������ش���Ԥʾ�ų����޷��������С�
enum eLogLevel {
    eLogLevel_Debug = 0,
    eLogLevel_Info = 1,
    eLogLevel_Warning = 2,
    eLogLevel_Error = 3,
    eLogLevel_Critical = 4
};

#endif
