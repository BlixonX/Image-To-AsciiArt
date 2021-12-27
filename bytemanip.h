#pragma once

#include <iostream>
#include <fstream>

int32_t getBytes(short byteNumber, std::ifstream& file);

int32_t get2Bytes(std::ifstream& file);

int32_t get4Bytes(std::ifstream& file);

void skipBytes(short byteNumber, std::ifstream& file);

char resolvePixelBrightness(std::ifstream& file);

char charFromBrightness(unsigned char brightness);

char invertPixelColor(char pixel);

//######################################

int32_t getBytes(short byteNumber, std::ifstream& file)
{
    int32_t value = 0;
    int32_t excludes = 0;
    int32_t bytes[byteNumber];

    for (int i = 0; i < byteNumber; i++) {
        bytes[i] = file.get();
    }

    for (int i = byteNumber - 1; i >= 0; i--)
        if (!bytes[i])
            excludes++;
        else
            break;

    for (int i = 0; i < byteNumber - excludes; i++)
        value |= bytes[i] << (byteNumber - excludes - 1 - i) * 8;
    return value;
}

int32_t get2Bytes(std::ifstream& file) { return getBytes(2, file); }

int32_t get4Bytes(std::ifstream& file) { return getBytes(4, file); }

void skipBytes(short byteNumber, std::ifstream& file)
{
    for (int i = 0; i < byteNumber; i++)
        file.get();
}

char resolvePixelBrightness(std::ifstream& file)
{
    unsigned char brightest = file.get();
    unsigned char next = file.get();


    if(next > brightest) {
        brightest = next;
    }

    next = file.get();

    if(next > brightest) {
        brightest = next;
    }

    return brightest;
}

char charFromBrightness(unsigned char brightness)
{
    if(brightness >= 200)
        return '@';
    else if (brightness >= 150)
        return '#';
    else if (brightness >= 100)
        return '8';
    else if (brightness >= 50)
        return 'O';

    return ' ';
}

char invertPixelColor(char pixel)
{
    switch (pixel)
    {
        case '@':
            return ' ';
        case ' ':
            return '@';
        case '#':
            return 'O';
        case 'O':
            return '#';
        default:
            return '8';
    }
}