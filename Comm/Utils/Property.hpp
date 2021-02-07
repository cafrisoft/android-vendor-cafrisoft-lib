#ifndef COMM_UTILS_PROPERTY_HPP__
#define COMM_UTILS_PROPERTY_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/Thread.hpp>
#include <Comm/OAL/CriticalSection.hpp>
#include <Comm/OAL/Mutex.hpp>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/FileSys.hpp>

namespace Comm {
    namespace Utils {

        namespace Property {

            class CS {

                CLASS_SINGLETON_PATTERN_DECLARE_C1(CS);

            private:
                std::shared_ptr<Comm::OAL::Mutex> _Mutex;

            public:
                CS();

                bool Lock();
                bool Unlock();
            };

            template<class Type> bool SaveValue(std::string strFileName, Type value) {

                bool bRet = false;

                //CS::Inst()->Lock();

                FILE* fp = fopen(strFileName.c_str(), "wb");
                if (fp) {
                    int wrsz = (int)fwrite(&value, 1, sizeof(Type), fp);
                    fflush(fp);
                    fclose(fp);
                    if (wrsz == sizeof(Type)) {
                        bRet = true;
                    }
                    else {
                        PRINTF("[Comm::Utils::Property::SaveValue] Fail to save \n");
                    }
                }
                else {
                    PRINTF("[Comm::Utils::Property::SaveValue] Fail to open (%s)\n", strFileName.c_str());
                }

                //CS::Inst()->Unlock();

                return bRet;
            }

            template<class Type> Type LoadValue(std::string strFileName, Type defaultValue) {

                Type value = defaultValue;
                const int retryCnt = 30;

                for (int iTry = 0; iTry < retryCnt; iTry++) {

                    FILE* fp = fopen(strFileName.c_str(), "rb");
                    if (fp) {
                        Type rdValue;
                        int rdsz = (int)fread(&rdValue, 1, sizeof(Type), fp);
                        fclose(fp);
                        if (rdsz == sizeof(Type)) {
                            value = rdValue;
                            break;
                        }
                        //else {
                            //PRINTF("[Comm::Utils::Property::LoadValue] Fail to read \n");
                        //}
                    }
                    else {
                        /*
                        2020-08-20
                        Property 파일이 없으면 Retry하지 않는다. 
                        Retry시도하는 경우, Status Notify하는데 많은 시간이 걸린다. 
                        */
                        break;
                    }
                    Comm::OAL::Thread::Sleep(10);
                }

                return value;
            }

            bool SaveString(std::string strFileName, std::string strValue);
            std::string LoadString(std::string strFileName);

            bool SaveData(std::string strFileName, /*In*/const void* dataBuf, int dataSize);
            bool LoadData(std::string strFileName, /*Out*/unsigned char* dataBuf, int dataBufMaxByteSize, /*OUT*/ int* dataSize);


            class Object : Comm::Base::Object {

            public:
                enum class ValueType {
                    String = 0,
                    LongLong
                };

                static std::shared_ptr<Object> CreateObject(ValueType valueType, const char* name, const char* value);

            private:
                std::string _Name;
                ValueType _ValueType;

            protected:
                Object(const char* name, ValueType valueType);

            public:
                bool IsThisName(const char* name);
                std::string GetName();

                virtual bool SetValueString(const char* value) = 0;
                virtual bool SetValueString(std::string strValue) = 0;

                virtual std::string GetValueString() = 0;
                virtual long long GetValueLongLong() = 0;
            };

            class ObjectString : public Object {

            private:
                std::string _Value;

            public:
                ObjectString(const char* name, const char* value);

                virtual bool SetValueString(const char* value);
                virtual bool SetValueString(std::string strValue);
                virtual std::string GetValueString();
                virtual long long GetValueLongLong();
            };

        };

    }; //namespace Utils
}; // namespace Comm {

#endif //COMM_UTILS_PROPERTY_HPP__
