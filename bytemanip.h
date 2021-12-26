#pragma once

#include <iostream>
#include <fstream>
int32_t getBytes(short byteNumber, std::ifstream& image);

int32_t getBytes(short byteNumber, std::ifstream& image)
{
    int32_t value = 0;
    int32_t excludes = 0;
    int32_t bytes[byteNumber];

    for (int i = 0; i < byteNumber; i++) {
        bytes[i] = image.get();
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