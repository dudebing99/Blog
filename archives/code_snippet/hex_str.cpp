#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

const int8_t HexDigitTable[256] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0xa, 0xb, 0xc, 0xd, 0xe,
    0xf, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

const int8_t HexTable[] = "0123456789abcdef";

std::string Str2Hex(std::string src)
{
    std::string dst;
    dst.reserve(src.size() * 2);

    for (auto itor : src)
    {
        dst.push_back(HexTable[itor >> 4]);
        dst.push_back(HexTable[itor & 0x0f]);
    }

    return dst;
}

std::string Hex2Str(std::string src)
{
    assert(src.size() % 2 == 0);
    std::string dst;
    int8_t c;
    dst.reserve(src.size() / 2);
    for (auto itor = src.begin(); itor != src.end(); ++ itor)
    {
        c = (HexDigitTable[*itor++] << 4) | HexDigitTable[*itor];
        dst.push_back(c);
    }

    return dst;
}


int main()
{
    std::string src = "hello world";
    std::string dst = Str2Hex(src);
    std::cout << dst << std::endl;
    std::cout << Hex2Str(dst) << std::endl;

    return 0;
}