#ifndef COMM_DRAW2D_TXT_FREETYPE_HPP__
#define COMM_DRAW2D_TXT_FREETYPE_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/Draw2D/Fourcc.hpp>

namespace Comm {
    namespace Draw2D {
        namespace Txt {

            namespace FreeType {

                void Draw(unsigned char* pImage, int picWidth, int picHeight, int stride, Fourcc fourcc, std::string strTxt);
                
            };  //namespace Bmp

        }; //namespace File
    }; //namespace Draw2D
}; //namespace Comm

#endif
