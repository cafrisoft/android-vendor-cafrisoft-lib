#include <Comm/Draw2D/Txt/FreeType.hpp>
#include <Comm/OAL/Log.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Comm {
    namespace Draw2D {
        namespace Txt {

            namespace FreeType {

                #define  FONT_FILE "c:\\Windows\\Fonts\\Arial.ttf"


                static void draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y, unsigned char* pImage, int picWidht, int picHeight, int stride, Fourcc fourcc) {
                    
                    FT_Int  i, j, p, q;
                    FT_Int  x_max = x + bitmap->width;
                    FT_Int  y_max = y + bitmap->rows;


                    /* for simplicity, we assume that `bitmap->pixel_mode' */
                    /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

                    for (i = x, p = 0; i < x_max; i++, p++)
                    {
                        for (j = y, q = 0; j < y_max; j++, q++)
                        {
                            if (i < 0 || j < 0 ||
                                i >= picWidht || j >= picHeight)
                                continue;

                            int color = bitmap->buffer[q * bitmap->width + p];
                            color = 255 - color;

                            switch (fourcc) {

                                case  Fourcc::IMAGE_ABGR8888:
                                case  Fourcc::IMAGE_ARGB8888:
                                {
                                    unsigned char* p = pImage + (stride * j) + (i * 4);
                                    p[0] = (unsigned char)color;
                                    p[1] = (unsigned char)color;
                                    p[2] = (unsigned char)color;
                                }
                                break;

                                case  Fourcc::IMAGE_RGB888:
                                case  Fourcc::IMAGE_BGR888:
                                {
                                    unsigned char* p = pImage + (stride * j) + (i * 3);
                                    p[0] = (unsigned char)color;
                                    p[1] = (unsigned char)color;
                                    p[2] = (unsigned char)color;
                                }
                                break;

                                case  Fourcc::IMAGE_RGB565:
                                {
                                    unsigned char* p = pImage + (stride * j) + (i * 2);
                                    int c5 = color & 0x1F;
                                    int c6 = color & 0x2F;
                                    unsigned short sv = (unsigned short)((c5 << 11) | (c6 << 5) | c5);

                                    memcpy(p, &sv, 2);
                                }
                                break;

                                default:
                                    assert(0);
                            }

                            //image[j][i] |= bitmap->buffer[q * bitmap->width + p];
                        }
                    }
                }


                void Draw(unsigned char* pImage, int picWidth, int picHeight, int stride, Fourcc fourcc, std::string strTxt) {
                
                    FT_Library    library;
                    FT_Face       face;

                    FT_GlyphSlot  slot;
                    FT_Matrix     matrix;                 /* transformation matrix */
                    FT_Vector     pen;                    /* untransformed origin  */
                    FT_Error      error;

                    
                    double        angle;
                    int           target_height;
                    int           n, num_chars;


                    //filename = argv[1];                           /* first argument     */
                    //text = argv[2];                           /* second argument    */
                    num_chars = (int)strTxt.length();
                    //angle = (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */
                    angle = 0;// (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */
                    target_height = picHeight;

                    error = FT_Init_FreeType(&library);              /* initialize library */
                    assert(error == 0);

                    error = FT_New_Face(library, FONT_FILE, 0, &face);/* create face object */
                    assert(error == 0);

                    
                    /* cmap selection omitted;                                        */
                    /* for simplicity we assume that the font contains a Unicode cmap */

                    

                    /* set up matrix */
                    matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
                    matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
                    matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
                    matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

                    /* the pen position in 26.6 cartesian space coordinates; */
                    /* start at (300,200) relative to the upper left corner  */
                    pen.x = 300 * 64;
                    pen.y = (target_height - 200) * 64;

                    int font_xpos = 0;

                    for (n = 0; n < num_chars; n++)
                    {
                        /* set transformation */
                        FT_Set_Transform(face, &matrix, &pen);

                        FT_UInt idx = FT_Get_Char_Index(face, strTxt[n]);

                        /* use 50pt at 100dpi */
                        //error = FT_Set_Char_Size(face, 50 * 64, 0, 100, 0);                /* set character size */
                        
                        /* use 100pt at 200dpi */
                        error = FT_Set_Char_Size(face, 100 * 64, 0, 200, 0);                /* set character size */
                        //error = FT_Set_Char_Size(face, 100 * 64, 100 * 64, 200, 200);                /* set character size */

                        /* use 150pt at 300dpi */
                        //error = FT_Set_Char_Size(face, 150 * 64, 0, 300, 0);                /* set character size */
                        assert(error == 0);

                        //load Glype
                        error = FT_Load_Glyph(face, idx, FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP);
                        assert(error == 0);

                        //Rendering
                        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
                        assert(error==0);
                                                
                        slot = face->glyph;

                        /* now, draw to our target surface (convert position) */
                        //draw_bitmap(&slot->bitmap, slot->bitmap_left, target_height - slot->bitmap_top,  pImage, picWidth, picHeight, stride, fourcc);
                        //draw_bitmap(&slot->bitmap, 0, 0, pImage, picWidth, picHeight, stride, fourcc);
                        draw_bitmap(&slot->bitmap, slot->bitmap_left, picHeight - slot->bitmap_top + 200, pImage, picWidth, picHeight, stride, fourcc);

                        PRINTF("n=%d slot->bitmap_left=%d \n", n, slot->bitmap_left);

                        font_xpos += slot->bitmap.width;

                        /* increment pen position */
                        pen.x += slot->advance.x;
                        pen.y += slot->advance.y;
                    }

                    FT_Done_Face(face);
                    FT_Done_FreeType(library);
                }

            };  //namespace Bmp

        }; //namespace File
    }; //namespace Draw2D
}; //namespace Comm

