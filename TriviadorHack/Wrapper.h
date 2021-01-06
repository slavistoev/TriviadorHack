#pragma once
#include "Image.h"
#include "TriviadorHack.h"
#include "Constants.h"

struct QuestionAnswer {
    char question[questionSize];
    char answer[answerSize];
};

struct QuestionAnswerHashed {
    size_t hash;
    int answer;
};

struct QuestionAnswerSecond {
    char question[questionSize];
    char answer[answerSizeSecond];
};

struct QuestionAnswerSecondHashed {
    size_t hash;
    char answer[answerSizeSecond];
};

//#define DllExport   __declspec( dllexport )  
class Wrapper {
public:
    Wrapper();
    ~Wrapper();

    void readScreen(bool isQuestion, bool isFirstQuestionType);
    void findAnswerSecond();

    void writeQuestionToFile();
    void writeQuestionSecondToFile();
    bool checkQuestion(bool isHashed, bool isFirstQuestionType);
    void readQuestions();

    bool timeToTakeQuestion();
    bool timeToTakeQuestionSecond();
    bool timeToTakeQuestionThird();
    //bool timeToTakeAnswer();
    bool waitToTakeAnswer();

    void triviadorHack(bool& goOn);

    bool addQuestions();

    void changeAnchorQuestionAnswer(Coordinates coord, const char* filename, unsigned short coordInd);

    std::string& getOutput();
    //bool getIsRunning();
    bool getIsAnswered();

    void enterAnswer(int anw);

    void readAnswerSecond();

    int DamerauLevenshteinDistance(char* str1, char* str2, int m, int n, int threshold);
    int minmin(int x, int y, int z);

    bool changeQuestion(char* question, char* answer);

    int keyPressed(int key);
    bool mouseButtonPressed(int& x, int& y);
    void displayImage(Image& img);

    void test();
private:
    QuestionAnswer qa;
    QuestionAnswerHashed qah;
    QuestionAnswerSecond qa2;
    QuestionAnswerSecondHashed qa2h;

    // Damerau-Levenshtein distance with a threshold
    QuestionAnswer qabuff;
    QuestionAnswerSecond qa2buff;

    bool isAnswered;
    bool isAnsweredSecond;

    Image anchorHint;
    Image anchorHintUsed;
    Image anchorTarget;

    Image anchorHintSecond;
    Image anchorHintUsedSecond;
    Image anchorLikeQuestion;

    //Image anchorFirstArrowObsolete;
    //Image anchorSecondArrowObsolete;
    //Image anchorThirdArrowObsolete;

    Image ImgFirstAnswer;
    Image ImgSecondAnswer;
    Image ImgThirdAnswer;
    Image ImgFourthAnswer;

    Coordinates questionCoord;
    Coordinates answerCoord;
    Coordinates anchorHintCoord;
    Coordinates anchorHintUsedCoord;
    Coordinates anchorTargetCoord;

    Coordinates anchorHintSecondCoord;
    Coordinates anchorHintUsedSecondCoord;
    Coordinates anchorLikeQuestionCoord;

    Coordinates firstAnswer;
    Coordinates secondAnswer;
    Coordinates thirdAnswer;
    Coordinates fourthAnswer;

    Coordinates readFirstAnswer;
    Coordinates readSecondAnswer;
    Coordinates readThirdAnswer;
    Coordinates readFourthAnswer;

    std::unique_ptr<tesseract::TessBaseAPI> tesseract_ptrQ;
    std::unique_ptr<tesseract::TessBaseAPI> tesseract_ptrA;
    std::unique_ptr<tesseract::TessBaseAPI> tesseract_ptrQSecond;
    std::unique_ptr<tesseract::TessBaseAPI> tesseract_ptrASecond;

    double coefQ;
    double coefA;

    unsigned int hintCompareCount;
    unsigned int targetCompareCount;
    unsigned int answerCompareCount;

    ofstream writeQuestion;
    fstream readWriteQuestionHashed;
    ofstream writeQuestionSecond;
    fstream readWriteQuestionSecondHashed;
    ofstream writeLog;

    // when using Damerau-Levenshtein distance
    ifstream readQuestion;
    ifstream readQuestionSecond;

    std::string output;
    //bool isRunning;
    bool isFirstQuestionType; // you input the answer

    void pressKey(unsigned short key);
    unsigned short rightAnswerIndex;
    //int** distanceTable;
    int distanceTable[questionSize][questionSize];
};
