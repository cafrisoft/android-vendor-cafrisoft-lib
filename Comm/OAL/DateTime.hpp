#ifndef COMM_OAL_DATETIME_HPP__
#define COMM_OAL_DATETIME_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace OAL {

        /*
            https://ko.wikipedia.org/wiki/%ED%98%91%EC%A0%95_%EC%84%B8%EA%B3%84%EC%8B%9C

            UTC : Coordinated Universal Time  
                  From 1972/01/01 00:00:00 

            Utc : 그리니치 평균시 
                  UTC와 Utc는 초의 소수점 단위에서 차이남 


        */
        class DateTime : public Base::Object {

        public:
            static const time_t _SecondPerDay = 3600 * 24;

        public:
            static time_t GetUtcTime();
            static time_t GetUtcTime(int utcYear, int utcMon, int utcDay, int utcHour = 0, int utcMin = 0, int utcSec = 0);
            static time_t GetUtcTime_KST(int kstYear, int kstMon, int kstDay, int kstHour = 0, int kstMin = 0, int kstSec=0);
            static time_t GetUtcTime_KST(struct CommDateTime dt);
            static time_t GetUtcTime_KST_SqlFmtDate(std::string strDate);  // ex1) 2020-11-19
            static time_t GetUtcTime_KST_SqlFmtDateTime(std::string strDateTime);  // ex1) 2020-11-19 19:42:24
            static time_t GetUtcTime_KST_YYYYMMDD_HHMMSS(int yyyyMmDd, int hhMmSs);  // ex) yyyyMmDd:20201119, hhMmSs:194224 
            static time_t GetUtcTime_KST_YYYYMMDD(int yyyyMmDd);  // ex) yyyyMmDd:20201119
            static time_t GetUtcMaxTime();
            static time_t GetUtcMinTime();

            //Utc(UTC)
            static int GetUtcYear(time_t utcTime);
            static int GetUtcMonth(time_t utcTime);
            static int GetUtcDay(time_t utcTime);
            static int GetUtcHour(time_t utcTime);
            static int GetUtcMinute(time_t utcTime);
            static int GetUtcSecond(time_t utcTime);
            static std::string GetUtcTimeString(time_t utcTime);
            static struct CommDateTime GetUtcCommDateTime(time_t utcTime);

            //Local
            static int GetLocalYear(time_t utcTime);
            static int GetLocalMonth(time_t utcTime);
            static int GetLocalDay(time_t utcTime);
            static int GetLocalHour(time_t utcTime);
            static int GetLocalMinute(time_t utcTime);
            static int GetLocalSecond(time_t utcTime);

            //KST
            static int GetKstYear(time_t utcTime);
            static int GetKstMonth(time_t utcTime);
            static int GetKstDay(time_t utcTime);
            static int GetKstHour(time_t utcTime);
            static int GetKstMinute(time_t utcTime);
            static int GetKstSecond(time_t utcTime);
            static int GetKstYYYYMMDD(time_t utcTime);  //return format YYYYMMDD
            static int GetKstHHMMSS(time_t utcTime);  //return format HHMMSS
            static long long GetKst_YYYYMMDD_HHMMSS(time_t utcTime);  //return format yyyyMmDdHhMmSs
            static struct CommDateTime GetKstCommDateTime(time_t utcTime);
            
            static std::string GetKstDateString(time_t utcTime = DateTime::GetUtcTime());
            static std::string GetKstTimeString(time_t utcTime = DateTime::GetUtcTime());
            static std::string GetKstDateTimeString(time_t utcTime = DateTime::GetUtcTime());      //Format0 XXXX-XX-XX XX:XX:XX
            static std::string GetKstDateTimeStringFmt1(time_t utcTime = DateTime::GetUtcTime());  //Format1 XX-XX-XX_XX:XX:XX
            static std::string GetKstDateTimeStringFileName(time_t utcTime = DateTime::GetUtcTime());  //Format1 XXXXXX_XXXXXX
            static std::string GetKstMonthDayTimeString(time_t utcTime = DateTime::GetUtcTime());      //Format0 XX-XX XX:XX:XX

            static int GetLocalTimeOffsetHour();
            static bool IsKstDayEqual(time_t t1, time_t t2);
            static long long GetSecondCountPerDay(); //하루에 해당하는 초값을 구한다.

            static int GetPackTime(time_t utcTime);
            static int GetPackTime(int kstYear, int kstMon, int kstDay, int kstHour = 0, int kstMin = 0, int kstSec = 0);
            static int GetPtYear(int packTime);
            static int GetPtMonth(int packTime);
            static int GetPtDay(int packTime);
            static int GetPtHour(int packTime);
            static int GetPtMinute(int packTime);
            static int GetPtSecond(int packTime);
            static struct CommDateTime GetPtCommDateTime(int packTime);
            static time_t GetPtTime(int packTime);
        };


    }; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

