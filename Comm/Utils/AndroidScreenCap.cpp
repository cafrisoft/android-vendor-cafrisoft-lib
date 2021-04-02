#include <Comm/Global/BuildOptions.h>
#define CLOG_TAG "CommUtilsAndroid"
#include <Comm/Utils/Android.hpp>
#include <Comm/OAL/Log.hpp>
#include <Comm/OAL/Thread.hpp>
#include <Comm/OAL/FileSys.hpp>

#if (CommOS==CommOS_ANDROID)
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <binder/ProcessState.h>

#include <gui/SurfaceComposerClient.h>
#include <gui/ISurfaceComposer.h>

#include <ui/DisplayInfo.h>
#include <ui/PixelFormat.h>

#elif (CommOS==CommOS_LINUX)
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#endif


namespace Comm {
    namespace Utils {
                
#if (CommOS==CommOS_ANDROID)
        using namespace android;
        static bool s_isThreadPollRun = false;
#endif

#if 0
        bool Android::ScreenCapture(int x, int y, int widht, int height, unsigned char* imgBuf) {
        
#if (CommOS==CommOS_ANDROID)

            static uint32_t DEFAULT_DISPLAY_ID = ISurfaceComposer::eDisplayIdMain;

            static const uint32_t ORIENTATION_MAP[] = {
                ISurfaceComposer::eRotateNone, // 0 == DISPLAY_ORIENTATION_0
                ISurfaceComposer::eRotate270, // 1 == DISPLAY_ORIENTATION_90
                ISurfaceComposer::eRotate180, // 2 == DISPLAY_ORIENTATION_180
                ISurfaceComposer::eRotate90, // 3 == DISPLAY_ORIENTATION_270
            };

            int32_t displayId = DEFAULT_DISPLAY_ID;

            if (s_isThreadPollRun == false) {
                ProcessState::self()->startThreadPool();
                s_isThreadPollRun = true;
            }

            ScreenshotClient screenshot;
            sp<IBinder> display = SurfaceComposerClient::getBuiltInDisplay(displayId);
            if (display == NULL) {
                fprintf(stderr, "Unable to get handle for display %d\n", displayId);
                return false;
            }

            Vector<DisplayInfo> configs;
            SurfaceComposerClient::getDisplayConfigs(display, &configs);
            int activeConfig = SurfaceComposerClient::getActiveConfig(display);
            if (static_cast<size_t>(activeConfig) >= configs.size()) {
                fprintf(stderr, "Active config %d not inside configs (size %zu)\n",
                    activeConfig, configs.size());
                return 1;
            }

            uint8_t displayOrientation = configs[activeConfig].orientation;
            uint32_t captureOrientation = ORIENTATION_MAP[displayOrientation];

            
            void const* base = NULL;
            uint32_t w, s, h, f;
            size_t size = 0;

            status_t result = screenshot.update(display, Rect(), 0, 0, 0, -1U,
                false, captureOrientation);
            if (result == NO_ERROR) {
                base = screenshot.getPixels();
                w = screenshot.getWidth();
                h = screenshot.getHeight();
                s = screenshot.getStride();
                f = screenshot.getFormat();
                size = screenshot.getSize();

                CLOGD("w=%d h=%d s=%d f=%d \n", w, h, s, f);

                memcpy(imgBuf, base, s * h );
            }


            return true;
#else

            return false;
#endif

        }
#endif

        //#define ANDROID_PLATFORM_SDK_VERSION 28

        bool Android::ScreenCaptureAndRGBVerify(unsigned char r, unsigned char g, unsigned char b) {

#if (CommOS==CommOS_ANDROID  &&  ANDROID_MAJOR_VERSION < 9 )

            bool isVerify = false;

            static uint32_t DEFAULT_DISPLAY_ID = ISurfaceComposer::eDisplayIdMain;

            static const uint32_t ORIENTATION_MAP[] = {
                ISurfaceComposer::eRotateNone, // 0 == DISPLAY_ORIENTATION_0
                ISurfaceComposer::eRotate270, // 1 == DISPLAY_ORIENTATION_90
                ISurfaceComposer::eRotate180, // 2 == DISPLAY_ORIENTATION_180
                ISurfaceComposer::eRotate90, // 3 == DISPLAY_ORIENTATION_270
            };

            int32_t displayId = DEFAULT_DISPLAY_ID;

            if (s_isThreadPollRun == false) {
                ProcessState::self()->startThreadPool();
                s_isThreadPollRun = true;
            }

            ScreenshotClient screenshot;
            sp<IBinder> display = SurfaceComposerClient::getBuiltInDisplay(displayId);
            if (display == NULL) {
                fprintf(stderr, "Unable to get handle for display %d\n", displayId);
                return false;
            }

            Vector<DisplayInfo> configs;
            SurfaceComposerClient::getDisplayConfigs(display, &configs);
            int activeConfig = SurfaceComposerClient::getActiveConfig(display);
            if (static_cast<size_t>(activeConfig) >= configs.size()) {
                fprintf(stderr, "Active config %d not inside configs (size %zu)\n",
                    activeConfig, configs.size());
                return 1;
            }

            uint8_t displayOrientation = configs[activeConfig].orientation;
            uint32_t captureOrientation = ORIENTATION_MAP[displayOrientation];


            void const* base = NULL;
            uint32_t width, stride, height, formatValue;
            size_t size = 0;

            status_t result = screenshot.update(display, Rect(), 0, 0, 0, -1U,
                false, captureOrientation);
            if (result == NO_ERROR) {
                base = screenshot.getPixels();
                width = screenshot.getWidth();
                height = screenshot.getHeight();
                stride = screenshot.getStride();
                formatValue = screenshot.getFormat();
                size = screenshot.getSize();

                
                /*
                    format = 1 => ABGR   Red: 0x000000FF  Blue : 0x00FF0000

                */
                if (formatValue == 1) {

                    unsigned int verifyColor = 0;
                    unsigned int* ibase = (unsigned int*)base;

                    verifyColor |= r << 0;
                    verifyColor |= g << 8;
                    verifyColor |= b << 16;

                    //PRINTF("[Android::ScreenCaptureAndRGBVerify] Width=%d Height=%d Stride=%d \n", width, height, stride);
                    //PRINTF("[Android::ScreenCaptureAndRGBVerify] verifyColor=0x%08X \n", verifyColor);

                    isVerify = true;
                    for (uint32_t h = 0; h < height; h++) {

                        unsigned int* p = &ibase[stride * h];

                        for (uint32_t w = 0; w < width; w++) {
                            unsigned int color = (*p) & 0x00FFFFFF ;
                            if (verifyColor != color) {
                                isVerify = false;
                                PRINTF("[Android::ScreenCaptureAndRGBVerify] Verfiy FAIL:   w=%d h=%d  color=0x%08X  verifyColor=0x%08X \n", w, h, color, verifyColor);
                                break;
                            }

                            p++;
                        }
                        if (isVerify != true) {
                            break;
                        }
                    }


                }
                else {
                    PRINTF("[Android::ScreenCaptureAndRGBVerify] ERROR : Format is Not 1,   w=%d h=%d s=%d f=%d \n", width, height, stride, formatValue);
                }
                
                
            }


            return isVerify;
#else

            return false;
#endif
        }
    };
};
