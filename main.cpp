/* NOTES

 Bytes sum of headers = 54 bytes

   NOTES */
#include "bytemanip.h"

using namespace std;

int main()
{
    ifstream bmp("");
    ofstream output("output.txt");

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
    u_int32_t imageSize; //UNKNOWN

    skipBytes(4, bmp);
    pixelWidth = get4Bytes(bmp);
    pixelHeight = get4Bytes(bmp);
    skipBytes(2, bmp);
    colorDepth = get2Bytes(bmp);
    compression = get4Bytes(bmp);
    imageSize = get4Bytes(bmp);

    skipBytes(8, bmp); //0x26 (4) and 0x2A (4) (horizontal and vertical resolution of the image (pixel per metre))

    skipBytes(8, bmp); // 0x2E (4) and 0x32 (4) (the number of color in the color palette and the number of important colors used)
    //END OF BITMAP-INFO-HEADER

    cout<< "fileByteSize: " << fileByteSize << endl;
    cout<< "pixelArrayOffset: " << pixelArrayOffset << endl;
    cout<< "pixelWidth: " << pixelWidth << endl;
    cout<< "pixelHeight: " << pixelHeight << endl;
    cout<< "colorDepth: " << colorDepth << endl;
    cout<< "compression: " << compression << endl;
    cout<< "imageSize: " << imageSize << endl;
    cout<<"\npixel offset minus read bytes: "<<pixelArrayOffset-54<<endl;

    for (int i = 0; i < pixelArrayOffset-54; i++)
        bmp.get();

    char padding = ((pixelWidth * 3)%4);
    if(padding)
        padding = 4 - padding;

    cout<<"padding: "<<(int)padding<<endl;

    /*
    for (int i = 0; i < 20; i++)
        cout<<bmp.get()<<','<<bmp.get()<<','<<bmp.get()<<endl;
    */

    char image[pixelHeight][pixelWidth];

    for (int height = 0; height < pixelHeight; height++)
    {
        for (int widthIndex = 0; widthIndex < pixelWidth; widthIndex++)
            image[height][widthIndex] = charFromBrightness(resolvePixelBrightness(bmp));
        skipBytes(padding, bmp); //padding skip
    }

    for (int height = pixelHeight-1; height >= 0 ; height--)
    {
        for (int widthIndex = 0; widthIndex < pixelWidth; widthIndex++)
            output<< image[height][widthIndex];
        output<<endl;
    }

    output.close();
    cout<<"END\n";
    return 0;
}
