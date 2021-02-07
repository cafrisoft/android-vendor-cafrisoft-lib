#ifndef COMM_DRAW2D_FILE_BMP_HPP__
#define COMM_DRAW2D_FILE_BMP_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/Draw2D/Fourcc.hpp>

namespace Comm {
    namespace Draw2D {
        namespace File {

            namespace Bmp  {

                //char** GetName(Fourcc fourcc, char** buf);
                bool SaveFile(std::string fileName, int picWidth, int picHeight, unsigned char* p_image, Fourcc fourcc);
                bool SaveFile(std::string fileName, int picWidth, int picHeight, int rgbRealStride, unsigned char* p_image, Fourcc fourcc);
                bool LoadInfo(std::string fileName, int* picWidth, int* picHeight, Fourcc* fourcc, int* stride);
                bool LoadFile(std::string fileName, unsigned char* p_image, int image_max_size);

            };  //namespace Bmp

        }; //namespace File
    }; //namespace Draw2D
}; //namespace Comm

#endif
