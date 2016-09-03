//
//   File name      : SystemTime.h
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-22 10:54:39
//

#ifndef _FINDNOSERVERLITE_SYSTEMTIME_H_
#define _FINDNOSERVERLITE_SYSTEMTIME_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
#include "IFMacros/DevelopMacros.h"

// Headers of current project
// ...

#define SYSTEMTIME_WEEKDAY_CHANGE(x) ((0 == x)?(7):(x))

class SystemTime
{
    unsigned int year_;
    unsigned int month_;
    unsigned int day_;

    unsigned int hour_;
    unsigned int minute_;
    unsigned int second_;

    unsigned int microsecond_;

    unsigned int day_of_week_;

public:
    SystemTime();
    ~SystemTime(){};

    // ʱ��������1970-1-1�Ժ�3000-1-1֮ǰ���������Ƽ��¡�
    int Init(
        unsigned int year,
        unsigned int month,
        unsigned int day,
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned int microsecond,
        unsigned int day_of_week
    );

    unsigned int year()        const {return year_;}        // from AD
    unsigned int month()       const {return month_;}       // 1 - 12
    unsigned int day()         const {return day_;}         // 1 - 31
    unsigned int hour()        const {return hour_;}        // 0 - 23
    unsigned int minute()      const {return minute_;}      // 0 - 59
    unsigned int second()      const {return second_;}      // 0 - 59
    unsigned int microsecond() const {return microsecond_;} // 0 - 999,999
    unsigned int day_of_week() const {return day_of_week_;} // 1 - 7

    // ��������������1970-1-1��ʼ��΢����������0��ʾ����
    unsigned __int64 GetMicroSecond() const;

    // ��������Ƿ����Ҫ���º���Ҫ���������׼����
    static int IsValidDate(unsigned int year, unsigned int month, unsigned int day);

    static int IsLeapYear(unsigned int year);

    // ת����YYYY-MM-DD hh:mm:ss.xxx�ĸ�ʽ���ַ�����
    const std::string toString() const;

protected:
private:
    DISALLOW_COPY_AND_ASSIGN(SystemTime);
};

#endif
