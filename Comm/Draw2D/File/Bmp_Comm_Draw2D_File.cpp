#include <Comm/Global/BuildOptions.h>
#include <Comm/Draw2D/File/Bmp.hpp>

namespace Comm {
    namespace Draw2D {
        namespace File {

            namespace Bmp {

                #define BMP_HEADER_MARKER  (('M' << 8) | 'B')

#if (CommOS == CommOS_WIN)
                #include <pshpack2.h>
#endif

                typedef struct tagMMPBITMAPFILEHEADER {
                    unsigned short    bfType;
                    unsigned int   bfSize;
                    unsigned short    bfReserved1;
                    unsigned short    bfReserved2;
                    unsigned int   bfOffBits;

#if (CommOS == CommOS_WIN)
                }MMPBITMAPFILEHEADER;
                #include <poppack.h>
#elif (CommOS == CommOS_LINUX)
                } __attribute__((packed)) MMPBITMAPFILEHEADER;
#else
#error "ERROR : need attribute packed of OS "
#endif

                    typedef struct MMPBITMAPINFOHEADER
                    {
                        unsigned int      biSize;
                        long       biWidth;
                        long       biHeight;
                        unsigned short       biPlanes;
                        unsigned short       biBitCount;
                        unsigned int      biCompression;
                        unsigned int      biSizeImage;
                        long       biXPelsPerMeter;
                        long       biYPelsPerMeter;
                        unsigned int      biClrUsed;
                        unsigned int      biClrImportant;
                    }MMPBITMAPINFOHEADER;


                #define MMP_BI_RGB        0L
                #define MMP_BI_RLE8       1L
                #define MMP_BI_RLE4       2L
                #define MMP_BI_BITFIELDS  3L
                #define MMP_BI_JPEG       4L
                #define MMP_BI_PNG        5L



                bool SaveFile(std::string fileName, int picWidth, int picHeight, unsigned char* p_image, Fourcc fourcc) {

                    int rgb_stride;
                    bool bRet = false;

                    /* check stride */
                    switch (fourcc) {
                        case Fourcc::IMAGE_BGR888:
                        case Fourcc::IMAGE_RGB888:
                            rgb_stride = COMM_BYTE_ALIGN(picWidth * 3, 4);
                            break;
                        case Fourcc::IMAGE_ARGB8888:
                        case Fourcc::IMAGE_ABGR8888:
                        case Fourcc::IMAGE_BGRA8888:
                        case Fourcc::IMAGE_RGBA8888:
                            rgb_stride = picWidth * 4;
                            break;

                        case Fourcc::IMAGE_RGB10BIT_BIG_ENDIAN:
                            rgb_stride = picWidth * 2 * 3;
                            break;

                        default:
                            assert(1);
                    }
                    
                    bRet  = SaveFile(fileName, picWidth, picHeight, rgb_stride, p_image, fourcc);
                    
                    return bRet;
                }

                bool SaveFile(std::string fileName, int picWidth, int picHeight, int rgbRealStride, unsigned char* p_image, Fourcc fourcc) {
                
                    bool bRet = false;
                    FILE* fp = NULL;
                    MMPBITMAPFILEHEADER BmpFileHeader;
                    MMPBITMAPINFOHEADER BmpInfoHeader;
                    int wrsz, normal_stride;

                    /* file open */
                    fp = fopen(fileName.c_str(), "wb");
                    assert(fp);
                    

                    /* check stride */
                    switch (fourcc) {
                        case Fourcc::IMAGE_BGR888:
                        case Fourcc::IMAGE_RGB888:
                            normal_stride = COMM_BYTE_ALIGN(picWidth * 3, 4);
                            break;
                        case Fourcc::IMAGE_ARGB8888:
                        case Fourcc::IMAGE_ABGR8888:
                        case Fourcc::IMAGE_RGBA8888:
                        case Fourcc::IMAGE_BGRA8888:
                            normal_stride = picWidth * 4;
                            break;

                        case Fourcc::IMAGE_RGB10BIT_BIG_ENDIAN:
                            normal_stride = COMM_BYTE_ALIGN(picWidth * 3, 4);
                            break;

                        default:
                            assert(1);
                    }


                    /* write file header */
                    BmpFileHeader.bfType = BMP_HEADER_MARKER;
                    BmpFileHeader.bfSize = sizeof(MMPBITMAPFILEHEADER) + sizeof(MMPBITMAPINFOHEADER) + normal_stride * picHeight;
                    BmpFileHeader.bfOffBits = sizeof(MMPBITMAPFILEHEADER) + sizeof(MMPBITMAPINFOHEADER);
                    wrsz = (int)fwrite(&BmpFileHeader, 1, sizeof(MMPBITMAPFILEHEADER), fp);
                    assert(wrsz == sizeof(MMPBITMAPFILEHEADER));
                    

                    /* write infoheader */
                    memset(&BmpInfoHeader, 0, sizeof(BmpInfoHeader));
                    BmpInfoHeader.biSize = sizeof(BmpInfoHeader);
                    BmpInfoHeader.biWidth = picWidth;
                    BmpInfoHeader.biHeight = -picHeight; /* Default : Top=>Bottom */

                    switch (fourcc) {
                        case Fourcc::IMAGE_BGR888:
                        case Fourcc::IMAGE_RGB888:
                            BmpInfoHeader.biPlanes = 1;
                            BmpInfoHeader.biBitCount = 24;
                            BmpInfoHeader.biCompression = MMP_BI_RGB;  // byte imgarray={ B, G, R, B, G, R, .... } 
                            break;

                        case Fourcc::IMAGE_ABGR8888:
                        case Fourcc::IMAGE_ARGB8888:
                        case Fourcc::IMAGE_RGBA8888:
                        case Fourcc::IMAGE_BGRA8888:
                            BmpInfoHeader.biPlanes = 1;
                            BmpInfoHeader.biBitCount = 32;
                            BmpInfoHeader.biCompression = MMP_BI_RGB;
                            break;

                        case Fourcc::IMAGE_RGB10BIT_BIG_ENDIAN:
                            BmpInfoHeader.biPlanes = 1;
                            BmpInfoHeader.biBitCount = 24;
                            BmpInfoHeader.biCompression = MMP_BI_RGB;  // byte imgarray={ B, G, R, B, G, R, .... } 
                            break;

                        default:
                            assert(1);
                    }

                    BmpInfoHeader.biSizeImage = normal_stride * picHeight;
                    wrsz = (int)fwrite(&BmpInfoHeader, 1, sizeof(MMPBITMAPINFOHEADER), fp);
                    assert(wrsz == sizeof(MMPBITMAPINFOHEADER));
                    
                    /* write image data */
                    switch (fourcc) {

                            //  MMP_BI_RGB mean that " byte imgarray={ B, G, R, B, G, R, .... }   BGR888"
                        case Fourcc::IMAGE_RGB888:
                        {
                            unsigned char r, g, b;
                            int w, h, ip;
                            unsigned char* line_dest = (unsigned char*)malloc(normal_stride), * line_dest1;
                            unsigned char* line_src = p_image, * line_src1;

                            assert(line_dest);
                            
                            for (h = 0; h < picHeight; h++) {
                                line_dest1 = line_dest;
                                line_src1 = line_src;
                                for (ip = 0, w = 0; w < picWidth; w++) {
                                    r = *line_src1; line_src1++;
                                    g = *line_src1; line_src1++;
                                    b = *line_src1; line_src1++;

                                    /* set B/G/R order in case of Bitmap File */
                                    *line_dest1 = b; line_dest1++;
                                    *line_dest1 = g; line_dest1++;
                                    *line_dest1 = r; line_dest1++;
                                }

                                line_src += rgbRealStride;
                                wrsz = (int)fwrite(line_dest, 1, normal_stride, fp);
                                assert(wrsz == normal_stride);
                            }

                            free(line_dest);
                        }
                        break;

                        case Fourcc::IMAGE_RGB10BIT_BIG_ENDIAN:
                        {
                            unsigned short r, g, b;
                            int w, h, ip;
                            unsigned char* line_dest = (unsigned char*)malloc(normal_stride), * line_dest1;
                            unsigned short* line_src = (unsigned short*)p_image, * line_src1;

                            assert(line_dest);
                            
                            for (h = 0; h < picHeight; h++) {
                                line_dest1 = line_dest;
                                line_src1 = line_src;
                                for (ip = 0, w = 0; w < picWidth; w++) {
                                    r = *line_src1; line_src1++;
                                    g = *line_src1; line_src1++;
                                    b = *line_src1; line_src1++;

                                    r = COMM_SWAP_U16(r);
                                    g = COMM_SWAP_U16(g);
                                    b = COMM_SWAP_U16(b);

                                    r >>= 2;
                                    g >>= 2;
                                    b >>= 2;

                                    /* set B/G/R order in case of Bitmap File */
                                    *line_dest1 = (unsigned char)b; line_dest1++;
                                    *line_dest1 = (unsigned char)g; line_dest1++;
                                    *line_dest1 = (unsigned char)r; line_dest1++;
                                }
                                
                                line_src += rgbRealStride / 2;
                                wrsz = (int)fwrite(line_dest, 1, normal_stride, fp);
                                assert(wrsz == normal_stride);
                            }

                            free(line_dest);
                            
                        }
                        break;

                        case Fourcc::IMAGE_ARGB8888:
                        {
                            unsigned char r, g, b;
                            int w, h, ip;
                            unsigned char* line_dest = (unsigned char*)malloc(normal_stride), * line_dest1;
                            unsigned char* line_src = p_image, * line_src1;

                            assert(line_dest);

                            for (h = 0; h < picHeight; h++) {
                                line_dest1 = line_dest;
                                line_src1 = line_src;
                                for (ip = 0, w = 0; w < picWidth; w++) {
                                    b = *line_src1; line_src1++;
                                    g = *line_src1; line_src1++;
                                    r = *line_src1; line_src1++;
                                    line_src1++;

                                    /* set B/G/R order in case of Bitmap File */
                                    *line_dest1 = b; line_dest1++;
                                    *line_dest1 = g; line_dest1++;
                                    *line_dest1 = r; line_dest1++;
                                    line_dest1++;
                                }

                                line_src += rgbRealStride;
                                wrsz = (int)fwrite(line_dest, 1, normal_stride, fp);
                                assert(wrsz == normal_stride);
                            }

                            free(line_dest);
                            
                        }
                        break;

                        case Fourcc::IMAGE_ABGR8888:
                        {
                            unsigned char r, g, b;
                            int w, h, ip;
                            unsigned char* line_dest = (unsigned char*)malloc(normal_stride), * line_dest1;
                            unsigned char* line_src = p_image, * line_src1;

                            assert(line_dest);

                            for (h = 0; h < picHeight; h++) {
                                line_dest1 = line_dest;
                                line_src1 = line_src;
                                for (ip = 0, w = 0; w < picWidth; w++) {
                                    r = *line_src1; line_src1++;
                                    g = *line_src1; line_src1++;
                                    b = *line_src1; line_src1++;
                                    line_src1++;

                                    /* set B/G/R order in case of Bitmap File */
                                    *line_dest1 = b; line_dest1++;
                                    *line_dest1 = g; line_dest1++;
                                    *line_dest1 = r; line_dest1++;
                                    line_dest1++;
                                }

                                line_src += rgbRealStride;
                                fwrite(line_dest, 1, normal_stride, fp);
                            }

                            free(line_dest);
                        }
                        break;

                        case Fourcc::IMAGE_RGBA8888:  // array={ R, G, B, A, R, G, B, A, ...... }
                        {
                            unsigned char r, g, b, a;
                            int w, h, ip;
                            unsigned char* line_dest = (unsigned char*)malloc(normal_stride), * line_dest1;
                            unsigned char* line_src = p_image, * line_src1;

                            assert(line_dest);

                            for (h = 0; h < picHeight; h++) {
                                line_dest1 = line_dest;
                                line_src1 = line_src;
                                for (ip = 0, w = 0; w < picWidth; w++) {
                                    r = *line_src1; line_src1++;
                                    g = *line_src1; line_src1++;
                                    b = *line_src1; line_src1++;
                                    a = *line_src1; line_src1++;

                                    /* set B/G/R order in case of Bitmap File */
                                    *line_dest1 = b; line_dest1++;
                                    *line_dest1 = g; line_dest1++;
                                    *line_dest1 = r; line_dest1++;
                                    *line_dest1 = a; line_dest1++;
                                }

                                line_src += rgbRealStride;
                                wrsz = (int)fwrite(line_dest, 1, normal_stride, fp);
                                assert(wrsz == normal_stride);
                            }

                            free(line_dest);
                        }
                        break;
                        
                        default:
                            wrsz = (int)fwrite(p_image, 1, BmpInfoHeader.biSizeImage, fp);
                            assert(wrsz == (int)BmpInfoHeader.biSizeImage);

                    }  // end of switch (fourcc) {

                    if (fp != NULL) {
                        fclose(fp);
                    }

                    return true;

                } // end of bool SaveFile(std::string fileName, int picWidth, int picHeight, int rgbRealStride, unsigned char* p_image, Fourcc fourcc) {


                bool LoadInfo(std::string fileName, int* picWidth, int* picHeight, Fourcc* fourcc, int* stride) {
                
                    int errCnt = 0;
                    FILE* fp = NULL;
                    MMPBITMAPFILEHEADER BmpFileHeader;
                    MMPBITMAPINFOHEADER BmpInfoHeader;
                    int rdsz;

                    if (picWidth != NULL) *picWidth = 0;
                    if (picHeight != NULL) *picHeight = 0;
                    if (stride != NULL) *stride = 0;
                    if (fourcc != NULL) *fourcc = Fourcc::VIDEO_UNKNOWN;

                    /* file open */
                    if (errCnt == 0) {
                        fp = fopen(fileName.c_str(), "rb");
                        if (fp == NULL) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: open file(%s)"), MMP_CLASS_FUNC, bmp_filename));
                        }
                    }

                    /* read file header */
                    if (errCnt == 0) {
                        rdsz = (int)fread(&BmpFileHeader, 1, sizeof(MMPBITMAPFILEHEADER), fp);
                        if (rdsz != sizeof(MMPBITMAPFILEHEADER)) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: read bmp file header"), MMP_CLASS_FUNC));
                        }
                    }

                    /* read info header */
                    if (errCnt == 0) {
                        rdsz = (int)fread(&BmpInfoHeader, 1, sizeof(MMPBITMAPINFOHEADER), fp);
                        if (rdsz != sizeof(MMPBITMAPINFOHEADER)) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: read bmp info header"), MMP_CLASS_FUNC));
                        }
                    }

                    /* check info */
                    if (errCnt == 0) {

                        if (BmpFileHeader.bfType != BMP_HEADER_MARKER) {
                            errCnt++;// mmpResult = MMP_FAILURE;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: Bmp Marker Error"), MMP_CLASS_FUNC));
                        }
                        else {
                            if (picWidth != NULL) {
                                *picWidth = BmpInfoHeader.biWidth;
                            }
                            if (picHeight != NULL) {
                                if (BmpInfoHeader.biHeight < 0) {
                                    *picHeight = BmpInfoHeader.biHeight * (-1);
                                }
                                else {
                                    *picHeight = BmpInfoHeader.biHeight;
                                }
                            }
                            if (fourcc != NULL) {
                                if (BmpInfoHeader.biBitCount == 24) {
                                    //*fourcc = Fourcc::IMAGE_RGB888;
                                    *fourcc = Fourcc::IMAGE_BGR888;  /* 24bit BGR   ex) byte array={ B, G, R, B, G, R, ....} */
                                    if (stride != NULL) *stride = COMM_BYTE_ALIGN(BmpInfoHeader.biWidth * 3, 4);
                                }
                                else if (BmpInfoHeader.biBitCount == 32) {
                                    *fourcc = Fourcc::IMAGE_BGRA8888;
                                    if (stride != NULL) *stride = COMM_BYTE_ALIGN(BmpInfoHeader.biWidth * 4, 4);
                                }
                                else {
                                    errCnt++;// mmpResult = MMP_FAILURE;
                                    //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: Not Support Bitmap Bit Format"), MMP_CLASS_FUNC));
                                }
                            }
                        }
                    }

                    if (errCnt > 0) {
                        if (picWidth != NULL) *picWidth = 0;
                        if (picHeight != NULL) *picHeight = 0;
                        if (stride != NULL) *stride = 0;
                        if (fourcc != NULL) *fourcc = Fourcc::VIDEO_UNKNOWN;
                    }

                    if (fp != NULL) {
                        fclose(fp);
                    }

                    return (errCnt == 0) ? true : false;

                } // end of  bool LoadInfo(std::string fileName, int* picWidth, int* picHeight, Fourcc* fourcc, int* stride)


                bool LoadFile(std::string fileName, unsigned char* p_image, int image_max_size) {
                
                    int errCnt = 0;
                    FILE* fp = NULL;
                    MMPBITMAPFILEHEADER BmpFileHeader;
                    MMPBITMAPINFOHEADER BmpInfoHeader;
                    int rdsz, stride;

                    int pic_width, pic_height;
                    Fourcc fourcc;


                    /* file open */
                    if (errCnt == 0) {
                        fp = fopen(fileName.c_str(), "rb");
                        if (fp == NULL) {
                            errCnt++; 
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: open file(%s)"), MMP_CLASS_FUNC, bmp_filename));
                        }
                    }

                    /* read file header */
                    if (errCnt == 0) {
                        rdsz = (int)fread(&BmpFileHeader, 1, sizeof(MMPBITMAPFILEHEADER), fp);
                        if (rdsz != sizeof(MMPBITMAPFILEHEADER)) {
                            errCnt++;
                        }
                    }

                    /* read info header */
                    if (errCnt == 0) {
                        rdsz = (int)fread(&BmpInfoHeader, 1, sizeof(MMPBITMAPINFOHEADER), fp);
                        if(rdsz != sizeof(MMPBITMAPINFOHEADER)) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: read bmp info header"), MMP_CLASS_FUNC));
                        }
                    }

                    /* check info */
                    if (errCnt == 0) {

                        if (BmpFileHeader.bfType != BMP_HEADER_MARKER) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: Bmp Marker Error"), MMP_CLASS_FUNC));
                        }
                        else {

                            pic_width = BmpInfoHeader.biWidth;
                            if (BmpInfoHeader.biHeight < 0) {
                                pic_height = BmpInfoHeader.biHeight * (-1);
                            }
                            else {
                                pic_height = BmpInfoHeader.biHeight;
                            }

                            if (BmpInfoHeader.biBitCount == 24) {
                                fourcc = Fourcc::IMAGE_RGB888;
                                stride = COMM_BYTE_ALIGN(pic_width * 3, 4);

                            }
                            else if (BmpInfoHeader.biBitCount == 32) {
                                fourcc = Fourcc::IMAGE_BGRA8888;
                                stride = pic_width * 4;
                            }
                            else {
                                stride = 0;
                                //mmpResult = MMP_FAILURE;
                                //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: Not Support Bitmap Bit Format"), MMP_CLASS_FUNC));
                            }

                            if (image_max_size < stride * pic_height) {
                                errCnt++;// mmpResult = MMP_FAILURE;
                                //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: image buffer is too smaall (bufsz=%d imagesz=%d (%dx%d bpp%d)"), MMP_CLASS_FUNC,
                                  //  image_max_size, stride * pic_height, pic_width, pic_height, BmpInfoHeader.biBitCount
                                    //));
                            }
                        }
                    }


                    /* Load Data */
                    if (errCnt==0) {

                        int h;
                        unsigned char* src_line, * dst_line;
                        unsigned char* src_data, * dst_data;

                        dst_data = p_image;
                        src_data = (unsigned char*)malloc(stride * pic_height);
                        if (src_data == NULL) {
                            errCnt++;
                            //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: malloc src_data"), MMP_CLASS_FUNC));
                        }
                        else {

                            rdsz = (int)fread(src_data, 1, stride * pic_height, fp);
                            if (rdsz != (stride * pic_height)) {
                                errCnt++;
                                //MMPDEBUGMSG(MMPZONE_ERROR, (TEXT("[CMmpImageTool::%s] FAIL: read data"), MMP_CLASS_FUNC));
                            }
                            else {

                                if (BmpInfoHeader.biHeight > 0) { src_line = src_data + (pic_height - 1) * stride; }
                                else { src_line = src_data; }

                                dst_line = dst_data;

                                for (h = 0; h < pic_height; h++) {
                                    memcpy(dst_line, src_line, stride);

                                    if (BmpInfoHeader.biHeight > 0) { src_line -= stride; }
                                    else { src_line += stride; }
                                    dst_line += stride;
                                }

                            }

                            free(src_data);
                        }
                    }

                    if (fp != NULL) {
                        fclose(fp);
                    }


                    return errCnt == 0 ? true : false;

                } // end of  bool LoadFile(std::string fileName, unsigned char* p_image, int image_max_size)

            };  //namespace Bmp

        }; //namespace File
    }; //namespace Draw2D
}; //namespace Comm
