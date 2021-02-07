#include "Cmd.hpp"
#include <Comm/Draw2D/Txt/FreeType.hpp>
#include <Comm/Draw2D/File/Bmp.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace AppControlShell {
    namespace Cmd {

        bool Draw2D::GenBmpWithText(int argc, const char** argv) {

            const int picWidth = 1920;
            const int picHeight = 3680;
            const int picStride = picWidth * 3;
            const Comm::Draw2D::Fourcc fourcc = Comm::Draw2D::Fourcc::IMAGE_BGR888;
            const int picByteSize = picStride * picHeight;

            unsigned char* pImage = new unsigned char[picByteSize];
            assert(pImage);
            
            for (int iImg = 1; iImg <= 28; iImg++) {

                std::string strTxt = Comm::Utils::StringFormat("TC7-%02d", iImg);
                std::string imgFileName = Comm::Utils::StringFormat("d:\\work\\TC7-%02d.bmp", iImg);
                memset(pImage, 0xFF, picByteSize);

                Comm::Draw2D::Txt::FreeType::Draw(pImage, picWidth, picHeight, picStride, fourcc, strTxt);
                Comm::Draw2D::File::Bmp::SaveFile(imgFileName, picWidth, picHeight, pImage, fourcc);
            }

            delete[] pImage;

            return true;
        }

    }
};


