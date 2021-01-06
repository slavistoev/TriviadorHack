#pragma once
#include "TriviadorHack.h"
#include "Constants.h"

class Image
{
private:
    std::vector<std::uint8_t> Pixels;
    std::uint32_t width, height;
    std::uint16_t BitsPerPixel;

    void Flip(void* In, void* Out, int width, int height, unsigned int Bpp);

public:
#if defined _WIN32 || defined _WIN64
    Image();
    explicit Image(Coordinates& coord, double coef, bool blackAndWhite);
    explicit Image(const char* fileName,Coordinates& coord);
    bool Compare(Image& img, int val);
    void RemoveNoise();
    void ConvertToGreyScale();
#endif

    inline std::uint16_t GetBitsPerPixel() { return this->BitsPerPixel; }
    inline std::uint16_t GetBytesPerPixel() { return this->BitsPerPixel / 8; }
    inline std::uint16_t GetBytesPerScanLine() { return (this->BitsPerPixel / 8) * this->width; }
    inline int GetWidth() const { return this->width; }
    inline int GetHeight() const { return this->height; }
    inline const std::uint8_t* GetPixels() { return this->Pixels.data(); }
    inline std::vector<std::uint8_t>& GetVectorPixels() { return this->Pixels; }
    inline std::uint_fast32_t GetSize() { return this->Pixels.size(); }
    inline std::uint32_t GetPixelSize() { return sizeof(GetPixels()[0]); }
};
