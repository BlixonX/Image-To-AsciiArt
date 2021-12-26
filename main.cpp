/* NOTES

 Bytes sum of headers = 54 bytes

   NOTES */
#include "bytemanip.h"

using namespace std;

int main()
{
    ifstream bmp("joker.bmp");

    //START OF BITMAP-FILE-HEADER
    //CHECKING IF THE FILE IS ACTUALLY BITMAP FILE

    if(!bmp.is_open())
        return 404;
    if(bmp.get() != 'B' || bmp.get() != 'M')
        return 1;

    u_int32_t fileByteSize;
    u_int32_t pixelArrayOffset;


    fileByteSize = get4Bytes(bmp);
    skipBytes(4, bmp);
    pixelArrayOffset = get4Bytes(bmp);

    //END OF BITMAP-FILE-HEADER

    //START OF BITMAP-INFO-HEADER
    u_int32_t pixelWidth;
    u_int32_t pixelHeight;
    u_int32_t colorDepth;
    u_int32_t compression;
    u_int32_t imageSize;

    skipBytes(4, bmp);
    pixelWidth = get4Bytes(bmp);
    pixelHeight = get4Bytes(bmp);
    skipBytes(2, bmp);
    colorDepth = get2Bytes(bmp);
    compression = get4Bytes(bmp);
    imageSize = get4Bytes(bmp);

    skipBytes(8, bmp); //0x26 (4) and 0x2A (4) (horizontal and vertical resolution of the image (pixel per metre))

    skipBytes(8, bmp); // 0x2E (4) and 0x32 (4) (the number of color in the color paletter and the number of important colors used)
    //END OF BITMAP-INFO-HEADER


    cout<<"END\n";
    return 0;
}
