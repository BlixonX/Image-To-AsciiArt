/* NOTES

 Bytes sum of headers = 54 bytes

   NOTES */
#include "bytemanip.h"

using namespace std;

int main()
{
    ifstream bmp("joker.bmp");
    if(!bmp.is_open())
        return 404;

    if(bmp.get() != 'B' || bmp.get() != 'M')
        return 1;

    u_int32_t fileByteSize = getBytes(4, bmp);
    cout<<fileByteSize<<endl;


    cout<<"END\n";
    return 0;
}
