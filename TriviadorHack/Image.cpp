#include "Image.h"

void Image::ConvertToGreyScale() {
    int stride = 4 * width;
    int rowIndex;
    int colIndex;

    int red, green, blue, best;

    for (int row = 0; row < height; row++) {
        rowIndex = row * stride;
        for (int col = 0; col < width; col++) {
            colIndex = 4 * col;

            /*Pixels[rowIndex + colIndex] *= 0.07;
            Pixels[rowIndex + colIndex + 1] *= 0.72;
            Pixels[rowIndex + colIndex + 2] *= 0.21;*/

            Pixels[rowIndex + colIndex] *= 0.30;
            Pixels[rowIndex + colIndex + 1] *= 0.59;
            Pixels[rowIndex + colIndex + 2] *= 0.11;

            /*red = Pixels[rowIndex + colIndex];
            green = Pixels[rowIndex + colIndex + 1];
            blue = Pixels[rowIndex + colIndex + 2];

            best = (std::max)((std::max)(red, green), blue);

            Pixels[rowIndex + colIndex] = best;a
            Pixels[rowIndex + colIndex + 1] = best;
            Pixels[rowIndex + colIndex + 2] = best;*/
        }
    }
}

Image::Image() {}

void Image::RemoveNoise() {
    std::uint8_t arrR[9];
    std::uint8_t arrG[9];
    std::uint8_t arrB[9];
    int stride = 4 * width;
    int rowIndex;
    int colIndex;
    for (int row = 1; row < height - 2; row++) {
        rowIndex = row * stride;
        for (int col = 1; col < width - 1; col++) {
            colIndex = 4 * col;
            int indent = rowIndex + colIndex;
            arrR[0] = Pixels[indent - 4];
            arrR[1] = Pixels[indent + 4];
            arrR[2] = Pixels[indent];
            arrR[3] = Pixels[indent - stride - 4];
            arrR[4] = Pixels[indent - stride + 4];
            arrR[5] = Pixels[indent - stride];
            arrR[6] = Pixels[indent + stride - 4];
            arrR[7] = Pixels[indent + stride + 4];
            arrR[8] = Pixels[indent + stride];

            arrG[0] = Pixels[indent - 4 + 1];
            arrG[1] = Pixels[indent + 4 + 1];
            arrG[2] = Pixels[indent + 1];
            arrG[3] = Pixels[indent - stride - 4 + 1];
            arrG[4] = Pixels[indent - stride + 4 + 1];
            arrG[5] = Pixels[indent - stride + 1];
            arrG[6] = Pixels[indent + stride - 4 + 1];
            arrG[7] = Pixels[indent + stride + 4 + 1];
            arrG[8] = Pixels[indent + stride + 1];

            arrB[0] = Pixels[indent - 4 + 2];
            arrB[1] = Pixels[indent + 4 + 2];
            arrB[2] = Pixels[indent + 2];
            arrB[3] = Pixels[indent - stride - 4 + 2];
            arrB[4] = Pixels[indent - stride + 4 + 2];
            arrB[5] = Pixels[indent - stride + 2];
            arrB[6] = Pixels[indent + stride - 4 + 2];
            arrB[7] = Pixels[indent + stride + 4 + 2];
            arrB[8] = Pixels[indent + stride + 2];

            /*std::sort(arrR, arrR + 9, std::greater<int>());
            std::sort(arrG, arrG + 9, std::greater<int>());
            std::sort(arrB, arrB + 9, std::greater<int>());*/
            /*Pixels[rowIndex + colIndex] = arrR[4];
            Pixels[rowIndex + colIndex + 1] = arrG[4];
            Pixels[rowIndex + colIndex + 2] = arrB[4];*/

            int sumR = 0, sumG = 0, sumB = 0;
            sumR = std::accumulate(arrR, arrR + 9, sumR);
            sumG = std::accumulate(arrG, arrG + 9, sumG);
            sumB = std::accumulate(arrB, arrB + 9, sumB);

            Pixels[rowIndex + colIndex] = sumR / 9;
            Pixels[rowIndex + colIndex + 1] = sumG / 9;
            Pixels[rowIndex + colIndex + 2] = sumB / 9;
        }
    }
}

void Image::Flip(void* In, void* Out, int width, int height, unsigned int Bpp)
{
    unsigned long Chunk = (Bpp > 24 ? width * 4 : width * 3 + width % 4);
    unsigned char* Destination = static_cast<unsigned char*>(Out);
    unsigned char* Source = static_cast<unsigned char*>(In) + Chunk * (height - 1);

    while (Source != In)
    {
        std::memcpy(Destination, Source, Chunk);
        Destination += Chunk;
        Source -= Chunk;
    }
}

bool Image::Compare(Image& img, int val) {
    std::vector<std::int16_t> res;
    res.resize(this->GetSize());
    std::transform(this->GetVectorPixels().begin(), this->GetVectorPixels().end(), img.GetVectorPixels().begin(), res.begin(), std::minus<std::uint8_t>());

    int count = 0;
    for (int i = 0; i < res.size(); i++) {
        if (res[i] != 0) {
            count++;
        }
    }

    return count < val;
}

#if defined _WIN32 || defined _WIN64
Image::Image(Coordinates& coord, double coef, bool blackAndWhite) : Pixels(), width(coord.width), height(coord.height), BitsPerPixel(32)
{
    HWND SomeWindowHandle = GetDesktopWindow();
    HDC DC = GetDC(SomeWindowHandle);

    BITMAP Bmp = { 0 };
    HBITMAP hBmp = reinterpret_cast<HBITMAP>(GetCurrentObject(DC, OBJ_BITMAP));

    if (GetObject(hBmp, sizeof(BITMAP), &Bmp) == 0)
        throw std::runtime_error("BITMAP DC NOT FOUND.");

    RECT area = { coord.x, coord.y, coord.x + width, coord.y + height };
    HWND Window = WindowFromDC(DC);
    GetClientRect(Window, &area);

    HDC MemDC = GetDC(nullptr);
    HDC SDC = CreateCompatibleDC(MemDC);
    HBITMAP hSBmp = CreateCompatibleBitmap(MemDC, width, height);
    DeleteObject(SelectObject(SDC, hSBmp));

    if (!BitBlt(SDC, 0, 0, width, height, DC, coord.x, coord.y, SRCCOPY)) { //SRCCOPY
        std::cout << "BitBlt fail!" << std::endl;
    }


    HDC MemDC2 = GetDC(nullptr);
    HDC SDC2 = (blackAndWhite ? CreateCompatibleDC(NULL) : CreateCompatibleDC(MemDC2));
    HBITMAP hSBmp2 = (blackAndWhite ? CreateCompatibleBitmap(SDC2, width * coef, height * coef) : CreateCompatibleBitmap(MemDC2, width * coef, height * coef));

    DeleteObject(SelectObject(SDC2, hSBmp2));
    SetStretchBltMode(SDC2, STRETCH_HALFTONE); //HALFTONE


    if (!StretchBlt(SDC2, 0, 0, width * coef, height * coef, SDC, 0, 0, width, height, SRCCOPY)) { //NOTSRCCOPY
        std::cout << "StretchBlt fail!" << std::endl;
    }
    width = width * coef;
    height = height * coef;

    //int i = 0;
    //CImage new_image;
    //new_image.Attach(hSBmp2);
    //new_image.Save(_T("./tessinput.tif"));
    //std::string file("./tessinput." + std::to_string(i) + "tif");
    //new_image.Save(_T(("./tessinput." + std::to_string(i) + "tif").c_str()));
    //new_image.Detach();


    unsigned int data_size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    std::vector<std::uint8_t> Data(data_size);
    this->Pixels.resize(data_size);

    BITMAPINFO Info = { sizeof(BITMAPINFOHEADER), static_cast<long>(width), static_cast<long>(height), 1, BitsPerPixel, BI_RGB, data_size, 0, 0, 0, 0 };
    if (!GetDIBits(SDC2, hSBmp2, 0, height, &Data[0], &Info, DIB_RGB_COLORS)) { // &Data[0]
        std::cout << "GetDiBits fail!" << std::endl;
    }
    this->Flip(&Data[0], &Pixels[0], width, height, BitsPerPixel);
    //this->RemoveNoise();
    /*if (!blackAndWhite) {
        this->ConvertToGreyScale();
    }*/

    DeleteDC(SDC);
    DeleteObject(hSBmp);
    DeleteObject(hBmp);
    ReleaseDC(nullptr, MemDC);
    DeleteDC(SDC2);
    DeleteObject(hSBmp2);
    ReleaseDC(nullptr, MemDC2);
    ReleaseDC(SomeWindowHandle, DC);
}
#endif

#if defined _WIN32 || defined _WIN64
Image::Image(const char* fileName,Coordinates& coord) : Pixels(), width(coord.width), height(coord.height), BitsPerPixel(32) {
    unsigned int data_size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    this->Pixels.resize(data_size);

    ifstream stream(fileName, std::ios::binary);
    stream.read((char*)&GetPixels()[0], GetSize() * GetPixelSize());
    stream.close();
}
#endif