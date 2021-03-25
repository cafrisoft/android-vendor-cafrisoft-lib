#include <Comm/OAL/DateTime.hpp>


#define DATETIME_TMYEAR_BASE 1900
#define DATETIME_TMYEAR_TO_GMTYEAR(y) (y+DATETIME_TMYEAR_BASE)
#define DATETIME_GMTYEAR_TO_TMYEAR(y) (y-DATETIME_TMYEAR_BASE)

#define DATETIME_TMMONTH_TO_GMTMONTH(m) (m+1)
#define DATETIME_GMTMONTH_TO_TMMONTH(m) (m-1)


namespace Comm {
    namespace OAL {

        #define KST_OFFSET  (3600*9)

        time_t DateTime::GetUtcMaxTime() {
            
            return 0xFFFFFFFFFFFFFFFF;
        }
        
        time_t GetUtcMinTime() {
        
            return 0;
        }

        time_t DateTime::GetUtcTime() {
        
            ASSERT_CHECK_TIME_T_64BIT;

            return time(NULL);
        }

        time_t DateTime::GetUtcTime(int gmtYear, int gmtMon, int gmtDay, int gmtHour, int gmtMin, int gmtSec) {
        
            struct tm tm;

            ASSERT_CHECK_TIME_T_64BIT;

            memset(&tm, 0x00, sizeof(tm));

            tm.tm_year = DATETIME_GMTYEAR_TO_TMYEAR(gmtYear);
            tm.tm_mon = DATETIME_GMTMONTH_TO_TMMONTH(gmtMon);
            tm.tm_mday = gmtDay;
            tm.tm_hour = gmtHour;
            tm.tm_min = gmtMin;
            tm.tm_sec = gmtSec;

#if (CommOS==CommOS_WIN)
            return _mkgmtime(&tm);
#elif (CommOS==CommOS_LINUX || CommOS==CommOS_ANDROID)
            return timegm(&tm);
#else
#error "Select OS"
#endif

        }

        time_t DateTime::GetUtcTime_KST(int kstYear, int kstMon, int kstDay, int kstHour, int kstMin, int kstSec) {
        
            time_t utcTime = DateTime::GetUtcTime(kstYear, kstMon, kstDay, kstHour, kstMin, kstSec);
            time_t kstTime = utcTime - KST_OFFSET;
            return kstTime;
        }

        // Format ex1) 2020-11-19
        time_t DateTime::GetUtcTime_KST_SqlFmtDate(std::string strDateTime) {

            char szBuf[128];
            int year, month, day;
            char* a;

            strcpy(szBuf, strDateTime.c_str());

            //year
            a = szBuf;
            a[4] = '\0';
            year = atoi(a);

            //month;
            a = &a[5];
            a[2] = '\0';
            month = atoi(a);

            //day
            a = &a[3];
            a[2] = '\0';
            day = atoi(a);

            return GetUtcTime_KST(year, month, day);
        }

        // Format ex1) 2020-11-19 19:42:24
        time_t DateTime::GetUtcTime_KST_SqlFmtDateTime(std::string strDateTime) {
        
            char szBuf[128];
            int year, month, day, hour, min, sec;
            char* a;

            strcpy(szBuf, strDateTime.c_str());

            //year
            a = szBuf;
            a[4] = '\0';
            year = atoi(a);

            //month;
            a = &a[5];
            a[2] = '\0';
            month = atoi(a);

            //day
            a = &a[3];
            a[2] = '\0';
            day = atoi(a);

            //hour
            a = &a[3];
            a[2] = '\0';
            hour = atoi(a);

            //min
            a = &a[3];
            a[2] = '\0';
            min = atoi(a);

            //sec
            a = &a[3];
            a[2] = '\0';
            sec = atoi(a);

            return GetUtcTime_KST(year, month, day, hour, min, sec);
        }

        // ex) yyyyMmDd:20201119, hhMmSs:194224 
        time_t DateTime::GetUtcTime_KST_YYYYMMDD_HHMMSS(int yyyyMmDd, int hhMmSs) {
            
            int year, month, day, hour, min, sec;
            
            //year
            year = yyyyMmDd / 10000;
            assert((year >= 1900) && (year <= 2999));

            //month;
            month = (yyyyMmDd / 100) % 100;
            assert((month >= 1) && (month <= 12));

            //day
            day = yyyyMmDd % 100;
            assert((day >= 1) && (day <= 31));

            //hour
            hour = hhMmSs / 10000;
            assert((hour >= 0) && (hour < 24));

            //min
            min = (hhMmSs / 100) % 100;
            assert((min >= 0) && (min < 60));

            //sec
            sec = hhMmSs % 100;
            assert((sec >= 0) && (sec < 60));
            
            return GetUtcTime_KST(year, month, day, hour, min, sec);
        }

        time_t DateTime::GetUtcTime_KST_YYYYMMDD(int yyyyMmDd) {
            return GetUtcTime_KST_YYYYMMDD_HHMMSS(yyyyMmDd, 0);
        }

        int DateTime::GetUtcYear(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            int year;

            year = DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year);
            assert(year >= 1970);

            return year;
        }

        int DateTime::GetUtcMonth(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;


            struct tm* tm = gmtime((const time_t*)&utcTime);
            int mon = DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon);

            assert((mon >= 1) && (mon <= 12));

            return mon;
        }

        int DateTime::GetUtcDay(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            int day = tm->tm_mday;
            assert((day >= 1) && (day <= 31));

            return day;
        }

        int DateTime::GetUtcHour(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            int hour = tm->tm_hour;
            assert((hour >= 0) && (hour < 24));

            return hour;
        }

        int DateTime::GetUtcMinute(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            int minute = tm->tm_min;
            assert((minute >= 0) && (minute < 60));
            return minute;
        }

        int DateTime::GetUtcSecond(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            int second = tm->tm_sec;
            assert((second >= 0) && (second < 60));
            return second;
        }

        std::string DateTime::GetUtcTimeString(time_t utcTime) {
        
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];

            sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
                DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year),
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }

        struct CommDateTime DateTime::GetUtcCommDateTime(time_t utcTime) {
        
            struct CommDateTime dt;
            
            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = gmtime((const time_t*)&utcTime);

            dt._Year = DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year);
            assert(dt._Year >= 1970);

            dt._Month = DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon);
            assert((dt._Month >= 1) && (dt._Month <= 12));

            dt._Day = tm->tm_mday;
            assert((dt._Day >= 1) && (dt._Day <= 31));

            dt._Hour = tm->tm_hour;
            assert((dt._Hour >= 0) && (dt._Hour < 24));

            dt._Minute = tm->tm_min;
            assert((dt._Minute >= 0) && (dt._Minute < 60));

            dt._Second = tm->tm_sec;
            assert((dt._Second >= 0) && (dt._Second < 60));

            dt._MileSec = 0;

            return dt;
        }

        int DateTime::GetLocalYear(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = localtime((const time_t*)&utcTime);
            int year;

            year = DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year);
            assert(year >= 1970);

            return year;
        }

        int DateTime::GetLocalMonth(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;


            struct tm* tm = localtime((const time_t*)&utcTime);
            int mon = DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon);

            assert((mon >= 1) && (mon <= 12));

            return mon;
        }

        int DateTime::GetLocalDay(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = localtime((const time_t*)&utcTime);
            return tm->tm_mday;
        }

        int DateTime::GetLocalHour(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = localtime((const time_t*)&utcTime);
            return tm->tm_hour;
        }

        int DateTime::GetLocalMinute(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = localtime((const time_t*)&utcTime);
            return tm->tm_min;
        }

        int DateTime::GetLocalSecond(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            struct tm* tm = localtime((const time_t*)&utcTime);
            return tm->tm_sec;
        }

        int DateTime::GetKstYear(time_t utcTime) {
            return DateTime::GetUtcYear(utcTime + KST_OFFSET);
        }

        int DateTime::GetKstMonth(time_t utcTime) {
            return DateTime::GetUtcMonth(utcTime + KST_OFFSET);
        }

        int DateTime::GetKstDay(time_t utcTime) {
            return DateTime::GetUtcDay(utcTime + KST_OFFSET);
        }

        int DateTime::GetKstHour(time_t utcTime) {
            return DateTime::GetUtcHour(utcTime + KST_OFFSET);
        }

        int DateTime::GetKstMinute(time_t utcTime) {
            return DateTime::GetUtcMinute(utcTime + KST_OFFSET);
        }

        int DateTime::GetKstSecond(time_t utcTime) {
            return DateTime::GetUtcSecond(utcTime + KST_OFFSET);
        }

        struct CommDateTime DateTime::GetKstCommDateTime(time_t utcTime) {
        
            return DateTime::GetUtcCommDateTime(utcTime + KST_OFFSET);
        }

        //return format YYYYMMDD
        int DateTime::GetKstYYYYMMDD(time_t utcTime) {
        
            int year = DateTime::GetKstYear(utcTime);
            int month = DateTime::GetKstMonth(utcTime);
            int day = DateTime::GetKstDay(utcTime);
            int value = 0;

            value += year * 10000;
            value += month * 100;
            value += day;

            return value;
        }

        //return format HHMMSS
        int DateTime::GetKstHHMMSS(time_t utcTime) {
        
            int hour = DateTime::GetKstHour(utcTime);
            int minute = DateTime::GetKstMinute(utcTime);
            int second = DateTime::GetKstSecond(utcTime);
            int value = 0;

            value += hour * 10000;
            value += minute * 100;
            value += second;

            return value;
        }

        std::string DateTime::GetKstDateString(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;
            time_t kstTime = utcTime + KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&kstTime);
            char buf[32];

            sprintf(buf, "%04d-%02d-%02d",
                DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year),
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday
            );

            std::string str = buf;
            return str;
        }

        std::string DateTime::GetKstTimeString(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            utcTime += KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];
            

            sprintf(buf, "%02d:%02d:%02d",
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }

        std::string DateTime::GetKstDateTimeString(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            utcTime += KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];


            sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
                DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year),
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }

        std::string DateTime::GetKstMonthDayTimeString(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            utcTime += KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];


            sprintf(buf, "%02d-%02d %02d:%02d:%02d",
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }


        std::string DateTime::GetKstDateTimeStringFmt1(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            utcTime += KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];


            sprintf(buf, "%02d-%02d-%02d_%02d:%02d:%02d",
                (DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year))%100,
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }

        std::string DateTime::GetKstDateTimeStringFileName(time_t utcTime) {

            ASSERT_CHECK_TIME_T_64BIT;

            utcTime += KST_OFFSET;

            struct tm* tm = gmtime((const time_t*)&utcTime);
            char buf[32];


            sprintf(buf, "%02d%02d%02d_%02d%02d%02d",
                (DATETIME_TMYEAR_TO_GMTYEAR(tm->tm_year)) % 100,
                DATETIME_TMMONTH_TO_GMTMONTH(tm->tm_mon),
                tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::string str = buf;
            return str;
        }

        int DateTime::GetLocalTimeOffsetHour() {
        
            time_t t = time(NULL);
            time_t t_gmt = mktime(gmtime((const time_t*)&t));
            time_t t_local = mktime(localtime((const time_t*)&t));
            
            return (int)((t_local - t_gmt) / 3600);
        }

        bool DateTime::IsKstDayEqual(time_t t1, time_t t2) {

            bool bRet = false;

            if (GetKstYear(t1) == GetKstYear(t2)) {

                if (GetKstMonth(t1) == GetKstMonth(t2)) {

                    if (GetKstDay(t1) == GetKstDay(t2)) {
                        bRet = true;
                    }
                }
            }

            return bRet;
        }

        //하루에 해당하는 초값을 구한다.
        long long DateTime::GetSecondCountPerDay() {
            return 3600 * 24;
        }


    }; //end of namespace OAL
}; //end of namespace Comm


