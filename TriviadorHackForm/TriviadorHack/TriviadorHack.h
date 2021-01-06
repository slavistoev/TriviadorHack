#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <cstring>
//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <chrono>
#include <atomic> // check thread finsish
#include <thread>
#include <algorithm> // sort + smth else
#include <numeric> // accumulate

#include <cstring>
#include <string>
using std::string;

#include "atlimage.h" // cImage

#include <functional> // greater //std::hash

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;
using std::copy;

#include <stdlib.h> // _mbstrlen_l ne raboti // atoi
#include <cwchar> // wchar
#include <locale> //locale

#include <random>	// random unsigned long num
#include <limits>	//

#define WINVER 0x0500
//#define NOMINMAX // use min/max but cover in parenthesis
#if defined _WIN64 || defined _WIN32
#include <windows.h>
#endif



//#include <future> // async not supported with /clr