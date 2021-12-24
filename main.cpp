#include <iostream>
#include <fstream>

using namespace std;

int32_t getBytes(short byteNumber)
{
    int32_t value = 0;
    char bytes[4];
    for(int i = 0; i < byteNumber; i++)
        value |= (int32_t)bytes[i] << i * 8;
    return value;
}



int main()
{
    ifstream bmp("joker.bmp");
    if(!bmp.is_open())
        return 404;

    if(bmp.get() != 'B' || bmp.get() != 'M')
        return 1;


    cout<<"END\n";
    return 0;
}
