#ifndef COMM_DRAW2D_FOURCC_HPP__
#define COMM_DRAW2D_FOURCC_HPP__

#include <Comm/Global/BuildOptions.h>

#include <Comm/Draw2D/v4l2_fourcc_def.h>
#include <Comm/Draw2D/v4l2_linux_videodev2.h>

namespace Comm {
    namespace Draw2D {

        enum class Fourcc {

            MMP_FOURCC_UNKNOWN = 0,

            AUDIO_UNKNOWN = COMM_MAKE_FOURCC('A', 'U', 'D', '?'),
            AUDIO_PCM = COMM_MAKE_FOURCC('P', 'C', 'M', ' '),  /* PCM */
            AUDIO_CODEC_PCM_S16LE = COMM_MAKE_FOURCC('P', 'C', 'M', '0'),  /* PCM Codec S16LE */
            AUDIO_MP1 = COMM_MAKE_FOURCC('M', 'P', '1', 'A'),  /* Mpeg Layer 1 */
            AUDIO_MP2 = COMM_MAKE_FOURCC('M', 'P', '2', 'A'),  /* Mpeg Layer 2 */
            AUDIO_MP3 = COMM_MAKE_FOURCC('M', 'P', '3', 'A'),  /* Mpeg Layer 3 */
            AUDIO_VORBIS = COMM_MAKE_FOURCC('V', 'O', 'R', 'B'),  /* Vorbis */
            AUDIO_BSAC = COMM_MAKE_FOURCC('B', 'S', 'A', 'C'),  /* Korea TDMB Audio Bsac */
            AUDIO_AAC = COMM_MAKE_FOURCC('A', 'A', 'C', ' '),  /* AAC */
            AUDIO_AC3 = COMM_MAKE_FOURCC('A', 'C', '3', ' '),  /* AC3 */
            AUDIO_RA_COOK = COMM_MAKE_FOURCC('C', 'O', 'O', 'K'),  /* Real Audio COOK */
            AUDIO_RA_RAAC = COMM_MAKE_FOURCC('R', 'A', 'A', 'C'),  /* Real Audio RAAC */
            AUDIO_RA_SIPR = COMM_MAKE_FOURCC('S', 'I', 'P', 'R'),  /* Real Audio SIPR */
            AUDIO_DTS = COMM_MAKE_FOURCC('D', 'T', 'S', ' '),  /* Real Audio SIPR */
            AUDIO_WMA1 = COMM_MAKE_FOURCC('W', 'M', 'A', '1'),  /* WMA 1 */
            AUDIO_WMA2 = COMM_MAKE_FOURCC('W', 'M', 'A', '2'),  /* WMA 2 */
            AUDIO_WMA_LOSSLESS = COMM_MAKE_FOURCC('W', 'M', 'A', 'L'),  /* WMA LossLess */
            AUDIO_WMA_PRO = COMM_MAKE_FOURCC('W', 'M', 'A', 'P'),  /* WMA Pro */
            AUDIO_WMA_VOICE = COMM_MAKE_FOURCC('W', 'M', 'A', 'V'),  /* WMA Voice */
            AUDIO_FLAC = COMM_MAKE_FOURCC('F', 'L', 'A', 'C'),  /* WMA Voice */
            AUDIO_AMR_NB = COMM_MAKE_FOURCC('A', 'M', 'R', 'N'),  /* AMR NB */
            AUDIO_AMR_WB = COMM_MAKE_FOURCC('A', 'M', 'R', 'W'),  /* AMR NB */
            AUDIO_FFMPEG = COMM_MAKE_FOURCC('F', 'F', 'M', 'A'),  /* Ffmpeg Audio */

            VIDEO_UNKNOWN = COMM_MAKE_FOURCC('V', 'I', 'D', '?'),

            //VIDEO_H264    = V4L2_PIX_FMT_H264,           // "H264" H264 with start codes  
            VIDEO_HEVC = COMM_MAKE_FOURCC('H', 'E', 'V', 'C'),
            //VIDEO_H264_NO_SC  = V4L2_PIX_FMT_H264_NO_SC, //"AVC1"  H264 without start codes
            //VIDEO_H264_MVC    = V4L2_PIX_FMT_H264_MVC,   // "M264"  H264 MVC

            //VIDEO_H263    = V4L2_PIX_FMT_H263,  // "H263" 

            //VIDEO_MPEG4   = V4L2_PIX_FMT_MPEG4, // "MPG4" MPEG-4 ES 
            VIDEO_MPEG2 = COMM_MAKE_FOURCC('M', 'P', 'G', '2'),
            VIDEO_MPEG4_V2 = COMM_MAKE_FOURCC('M', 'P', '4', '2'),
            VIDEO_XVID = COMM_MAKE_FOURCC('X', 'V', 'I', 'D'),

            VIDEO_WVC1 = COMM_MAKE_FOURCC('W', 'V', 'C', '1'),  //VC1 Advanced@L3
            VIDEO_WMV3 = COMM_MAKE_FOURCC('W', 'M', 'V', '3'),  //VC1-WMV9 
            VIDEO_WMV2 = COMM_MAKE_FOURCC('W', 'M', 'V', '2'),  //VC1-WMV8 
            VIDEO_WMV1 = COMM_MAKE_FOURCC('W', 'M', 'V', '1'),  //VC1-WMV7 
            VIDEO_MSS1 = COMM_MAKE_FOURCC('M', 'S', 'S', '1'),
            VIDEO_MSS2 = COMM_MAKE_FOURCC('M', 'S', 'S', '2'),

            VIDEO_VP60 = COMM_MAKE_FOURCC('V', 'P', '6', '0'),
            VIDEO_VP6F = COMM_MAKE_FOURCC('V', 'P', '6', 'F'),
            VIDEO_VP6A = COMM_MAKE_FOURCC('V', 'P', '6', 'A'),
            VIDEO_VP80 = COMM_MAKE_FOURCC('V', 'P', '8', '0'),
            VIDEO_VP90 = COMM_MAKE_FOURCC('V', 'P', '9', '0'),

            VIDEO_RV30 = COMM_MAKE_FOURCC('R', 'V', '3', '0'),
            VIDEO_RV40 = COMM_MAKE_FOURCC('R', 'V', '4', '0'),
            VIDEO_RV = COMM_MAKE_FOURCC('R', 'V', 'X', '0'),

            VIDEO_SVQ1 = COMM_MAKE_FOURCC('S', 'V', 'Q', '1'),   //Sorenson 1
            VIDEO_SVQ3 = COMM_MAKE_FOURCC('S', 'V', 'Q', '3'),   //Sorenson 3
            VIDEO_FLV1 = COMM_MAKE_FOURCC('F', 'L', 'V', '1'),   /* Sorenson Spark */

            VIDEO_THEORA = COMM_MAKE_FOURCC('T', 'H', 'E', 'O'),
            //VIDEO_MJPEG    = V4L2_PIX_FMT_MJPEG, // "MJPG"
            //VIDEO_JPEG    =  V4L2_PIX_FMT_JPEG,  // "JPEG"

            VIDEO_MSMPEG4V1 = COMM_MAKE_FOURCC('M', 'S', 'M', '1'),
            VIDEO_MSMPEG4V2 = COMM_MAKE_FOURCC('M', 'S', 'M', '2'),
            VIDEO_MSMPEG4V3 = COMM_MAKE_FOURCC('M', 'S', 'M', '3'),   //Divx3

            VIDEO_INDEO2 = COMM_MAKE_FOURCC('I', 'N', 'D', '2'),   /* Indeo2 */
            VIDEO_INDEO3 = COMM_MAKE_FOURCC('I', 'N', 'D', '3'),   /* Indeo2 */
            VIDEO_INDEO4 = COMM_MAKE_FOURCC('I', 'N', 'D', '4'),   /* Indeo2 */
            VIDEO_INDEO5 = COMM_MAKE_FOURCC('I', 'N', 'D', '5'),   /* Indeo2 */

            VIDEO_TSCC = COMM_MAKE_FOURCC('T', 'S', 'C', 'C'),   /* Indeo2 */
            VIDEO_FFMPEG = COMM_MAKE_FOURCC('F', 'F', 'M', 'V'),  /* Ffmpeg Video */

            IMAGE_UNKNOWN = COMM_MAKE_FOURCC('I', 'M', 'G', '?'),

            IMAGE_GREY = V4L2_PIX_FMT_GREY, //v4l2_fourcc('G', 'R', 'E', 'Y') /*  8  Greyscale     */
            IMAGE_GREY_ALPHA = COMM_MAKE_FOURCC('G', 'R', 'E', 'A'),  //Gray Alpha   ex)  pixel_array = { G, A, G, A.... }
            IMAGE_ALPHA_GRAY = COMM_MAKE_FOURCC('A', 'G', 'R', 'E'), //Gray Alpha   ex)  pixel_array = { G, A, G, A.... }

            IMAGE_YUV444_P1 = V4L2_PIX_FMT_YUV444_P1, //COMM_MAKE_FOURCC('4','4','4','1'),  /* 24bit Y/U/V 444 Plane 1 Comp1*/
            IMAGE_YUV444M = V4L2_PIX_FMT_YUV444M,     //COMM_MAKE_FOURCC('4','4','4','M'),  /* 24bit Y/U/V 444 Plane 1 Comp3*/
            IMAGE_YCbCr422_P2 = COMM_MAKE_FOURCC('N', 'V', '1', '6'),  /* 16 bit Y/CbCr 4:2:2 Plane 2, V4L2_PIX_FMT_NV16 */
            IMAGE_YCrCb422_P2 = COMM_MAKE_FOURCC('N', 'V', '6', '1'),  /* 16 bit Y/CrCb 4:2:2 Plane 2, V4L2_PIX_FMT_NV61 */


            IMAGE_UYVY = V4L2_PIX_FMT_UYVY, // "UYVY"   YUV 4:2:2 packed, CbYCrY      
            IMAGE_VYUY = V4L2_PIX_FMT_VYUY, //YUV 4:2:2 packed, CrYCbY
            IMAGE_YUYV = V4L2_PIX_FMT_YUYV, //"YUYV" YUV 4:2:2 packed, YCbYCr
            IMAGE_YVYU = V4L2_PIX_FMT_YVYU, //"YVYU"  YUV 4:2:2 packed, YCrYCb

            IMAGE_NV16 = V4L2_PIX_FMT_NV16, // "NV16" YUV 4:2:2 planar, Y/CbCr    16 bit Y/CbCr 4:2:2 Plane 2, V4L2_PIX_FMT_NV16
            IMAGE_NV16V = V4L2_PIX_FMT_NV16V,// "N16V" YUV 2:2:4 planar, Y/CbCr    16 bit Y/CbCr 2:2:4 Plane 2, V4L2_PIX_FMT_NV16V (vertical)
            IMAGE_NV61 = V4L2_PIX_FMT_NV61, // "NV61" YUV 4:2:2 planar, Y/CrCb    16 bit Y/CrCb 4:2:2 Plane 2, V4L2_PIX_FMT_NV61

            IMAGE_YUV422P = V4L2_PIX_FMT_YUV422P, //  "422P"   YUV 4:2:2 3-planar, Y/Cb/Cr
            IMAGE_YUV422PM = V4L2_PIX_FMT_YUV422PM,//  "42PM" Custom  YUV 4:2:2 3-planar, Y/Cb/Cr non-config

            IMAGE_NV12 = V4L2_PIX_FMT_NV12,  //COMM_MAKE_FOURCC('N','V','1','2'),  /* 12  Y/CbCr 4:2:0  2Plane contigous -- one Y, one Cr + Cb interleaved */
            IMAGE_NV12M = V4L2_PIX_FMT_NV12M, //COMM_MAKE_FOURCC('N','M','1','2'),  /* 12  Y/CbCr 4:2:0  2Plane non-contigous */
            IMAGE_NV21 = V4L2_PIX_FMT_NV21,  //COMM_MAKE_FOURCC('N','V','2','1'),  /* 12  Y/CrCb 4:2:0  2Plane contigous -- one Y, one Cr + Cb interleaved*/
            IMAGE_NV21M = V4L2_PIX_FMT_NV21M,  //COMM_MAKE_FOURCC('N','M','2','1'),  /* 12  Y/CrCb 4:2:0  2Plane non-contigous */

            IMAGE_YUV420 = V4L2_PIX_FMT_YUV420, //COMM_MAKE_FOURCC('Y','U','1','2'),  /* V4L2_PIX_FMT_YUV420 12  YUV 4:2:0  3P contigous */
            IMAGE_YUV420M = V4L2_PIX_FMT_YUV420M, //COMM_MAKE_FOURCC('Y','M','1','2'),  /* V4L2_PIX_FMT_YUV420M 12  YUV 4:2:0  3P non contiguous planes - Y, Cb, Cr */

            IMAGE_YVU420 = V4L2_PIX_FMT_YVU420, //COMM_MAKE_FOURCC('Y','V','1','2'),  /* V4L2_PIX_FMT_YVU420 12  YVU 4:2:0  3P contigous */
            IMAGE_YVU420M = V4L2_PIX_FMT_YVU420M, //COMM_MAKE_FOURCC('Y','M','2','1'),  /* V4L2_PIX_FMT_YVU420M 12  YUV 4:2:0  3P non contiguous planes - Y, Cb, Cr */

            //IMAGE_NV12MT    = V4L2_PIX_FMT_NV12MT, //  v4l2_fourcc('T', 'M', '1', '2') /* 12  Y/CbCr 4:2:0 64x32 macroblocks */

            IMAGE_YUV420M_META = COMM_MAKE_FOURCC('Y', 'M', '1', 'M'),

            IMAGE_RGB565 = V4L2_PIX_FMT_RGB565,   /* RGB565 */
            IMAGE_RGB888 = V4L2_PIX_FMT_RGB24,   /* 24bit RGB   ex) byte array={ R, G, B, R, G, B, ....}   */
            IMAGE_BGR888 = V4L2_PIX_FMT_BGR24,   /* 24bit BGR   ex) byte array={ B, G, R, B, G, R, ....} */
            IMAGE_ARGB8888 = V4L2_PIX_FMT_RGB32,   /* XRGB-8888, 32 bpp  ex) byte array={ A, R, G, B, A, R, G, B,  ....}  */
            IMAGE_ABGR8888 = V4L2_PIX_FMT_BGR32,   /* XBGR-8888, 32 bpp  ex) byte array={ A, B, G, R, A, B, G, R,  ....} */

            IMAGE_RGBA8888 = COMM_MAKE_FOURCC('R', 'G', 'B', 'A'),  /* 32bit RGB   ex) byte array={ R, G, B, A, R, G, B, A,  ....}   */
            IMAGE_BGRA8888 = COMM_MAKE_FOURCC('B', 'G', 'R', 'A'),  /* 32bit RGB   ex) byte array={ B, G, R, A, B, G, R, A,  ....}   */

            IMAGE_BGR10BIT_BIG_ENDIAN = COMM_MAKE_FOURCC('B', '1', '0', 'R'),   /* B/G/R   R=0x0123 => Array( 01, 23 ...)  */
            IMAGE_RGB10BIT_BIG_ENDIAN = COMM_MAKE_FOURCC('R', '1', '0', 'B'),   /* R/G/B   R=0x0123 => Array( 01, 23 ...) */

            IMAGE_BGR10BIT_LITTEL_EENDIAN = COMM_MAKE_FOURCC('B', '0', '1', 'R'),   /* B/G/R   R=0x0123 => Array( 01, 23 ...)  */
            IMAGE_RGB10BIT_LITTEL_EENDIAN = COMM_MAKE_FOURCC('R', '0', '1', 'B'),   /* R/G/B   R=0x0123 => Array( 01, 23 ...) */

            IMAGE_YCoCg444 = COMM_MAKE_FOURCC('Y', 'G', '4', '4'),   /* YCoCg 444 */


            /**<Reserved android opaque colorformat. Tells the encoder that
             * the actual colorformat will be  relayed by the
             * Gralloc Buffers.
             * FIXME: In the process of reserving some enum values for
             * Android-specific OMX IL colorformats. Change this enum to
             * an acceptable range once that is done.
             * */
             IMAGE_ANDROID_OPAQUE = COMM_MAKE_FOURCC('A', 'O', 'P', 'A'), //Android Gralloc depend,  Ref OMX_COLOR_FormatAndroidOpaque = 0x7F000789 in OMX_IVCommon.h
        };

    };//namespace Draw2D 
}; //namespace Comm

#endif

