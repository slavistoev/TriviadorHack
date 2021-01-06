#pragma once
#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1

//static const char anchorHint_filename[] = "../IOFiles/anchors/anchorHint.dat";
//static const char anchorHintUsed_filename[] = "../IOFiles/anchors/anchorHintUsed.dat";
//static const char anchorTarget_filename[] = "../IOFiles/anchors/anchorTarget.dat";
////static const char anchorFirstArrowObsolete_filename[] = "./anchors/anchorFirstArrowObsolete.dat";
////static const char anchorSecondArrowObsolete_filename[] = "./anchors/anchorSecondArrowObsolete.dat";
////static const char anchorThirdArrowObsolete_filename[] = "./anchors/anchorThirdArrowObsolete.dat";
//static const char emptyQuestionAnwser_filename[] = "../IOFiles/anchors/emptyQuestionAnwser.dat";
//
//static const char anchorHintSecond_filename[] = "../IOFiles/anchors/anchorHintSecond.dat";
//static const char anchorHintUsedSecond_filename[] = "../IOFiles/anchors/anchorHintUsedSecond.dat";
//static const char anchorLikeQuestion_filename[] = "../IOFiles/anchors/anchorLikeQuestion.dat";
////static const char anchorLikeQuestionTarget_filename[] = "../OIFiles/anchors/anchorLikeQuestionTarget.dat"; //obsolete
//
//static const char testQuestionsOutput_filename[] = "../IOFiles/see_questions/questions.txt";
//static const char testQuestionsHashedOutput_filename[] = "./questionshashed.txt";
//static const char testQuestionsSecondOutput_filename[] = "../IOFiles/see_questions/questionssecond.txt";
//static const char testQuestionsSecondHashedOutput_filename[] = "./questionssecondhashed.txt";
//
//static const double coefQ_const = 0.67;     // these 3 coefficients are taken from tests
//static const double diagonalQ_const = 612;  // conducted on a 1920/1080 resolution machine
//static const double coefA_const = 1;        // they give the best results
//static const double coefAnchor_const = 1;
//
//static const char numBlackList[] = "!?##$%&*()<>_-+=/:;'\"ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz"; //АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя
//static const char numWhiteList[] = "0123456789";
//
//static const char tessdataInitPath[] = "../IOFiles/tesseract/tessdata";
//
//static const char questionTessData[] = "rus";
//static const char answerTessData[] = "eng";
//
//struct Coordinates {
//    int x;
//    int y;
//    int width;
//    int height;
//
//    Coordinates(int x, int y, int width, int height) {
//        this->x = x;
//        this->y = y;
//        this->width = width;
//        this->height = height;
//    }
//
//    Coordinates() {}
//
//    void print() {
//        cout << x << " " << y << " " << width << " " << height << endl;
//    }
//};
//
//static const char coords_filename[] = "../IOFiles/coords/coords.dat";
//static const unsigned short questionCoordInd = 0;
//static const unsigned short answerCoordInd = 1;
//static const unsigned short AnchorHintInd = 2;
//static const unsigned short AnchorHintUsedInd = 3;
//static const unsigned short AnchorTargetCoordInd = 4;
//static const unsigned short anchorHintSecondCoordInd = 5;
//static const unsigned short anchorHintUsedSecondCoordInd = 6;
//static const unsigned short anchorLikeQuestionCoordInd = 7;
//static const unsigned short answersQuestionSecondInd = 8;
//static const unsigned short answerFirstQuestionSecondInd = 9;
//
//static const int hintCompareCount_const = 3000;     // these 3 counts are taken from tests
//static const int targetCompareCount_const = 1000;   // conducted on a 1920/1080 resolution machine
//static const int answerCompareCount_const = 500;    // they give the best results
////static const int arrowCompareCountObsolete = 200;
//
//static const bool blackAndWhiteQuestion = false;
//static const bool blackAndWhiteAnswer = false;
//static const bool blackAndWhiteAnchors = false;
////static const bool blackAndWhiteAnchors_Obsolete = true;
//
//static const int questionSize = 241;
//static const int answerSize = 11;
//static const int answerSizeSecond = 100;
//
//static const char questions_filename[] = "../IOFiles/questions/questions.dat"; 
//static const char questionsHashed_filename[] = "../IOFiles/questions/questionshashed.dat";
//static const char addQuestions_filename[] = "../IOFiles/questions_to_copy/questions.dat";
//static const char addQuestionsSecond_filename[] = "../IOFiles/questions_to_copy/questionssecond.dat";
//static const char addQuestionsHashed_filename[] = "../IOFiles/questions_to_copy/questionshashed.dat";
//static const char questionsSecond_filename[] = "../IOFiles/questions/questionssecond.dat";
//static const char questionsSecondHashed_filename[] = "../IOFiles/questions/questionssecondhashed.dat";
//
//static const bool questionBool = true;
//
//static const int waitAfterAnswerMilli = 8000;
//static const int waitAfterAnswerSecondMilli = 3000;
//static const int waitForQuestionReadMilli = 8000;
//static const int waitReadQuestionAnswer = 1000;
//
//static const bool isHashedQuestion = false;
//static const bool isHashedQuestionHashed = true;
//static const bool constBoolFirstTypeQuestion = true;
//
//static const char log_filename[] = "../IOFiles/log.txt";
//static const int threshold = 3;
//
//static const unsigned short maxSingleDigit = 9;
//
//static const unsigned short numOfAnswers = 4;
//static const double subtractCoef = 0.15;
//static const double subtractCoefThirdAnswer = 0.27;
//static const double subtractCoefFourthAnswer = 0.31;
//
//static const char buff_filename[] = "./buff.dat";

static const char anchorHint_filename[] = "./IOFiles/anchors/anchorHint.dat";
static const char anchorHintUsed_filename[] = "./IOFiles/anchors/anchorHintUsed.dat";
static const char anchorTarget_filename[] = "./IOFiles/anchors/anchorTarget.dat";
//static const char anchorFirstArrowObsolete_filename[] = "./anchors/anchorFirstArrowObsolete.dat";
//static const char anchorSecondArrowObsolete_filename[] = "./anchors/anchorSecondArrowObsolete.dat";
//static const char anchorThirdArrowObsolete_filename[] = "./anchors/anchorThirdArrowObsolete.dat";
static const char emptyQuestionAnwser_filename[] = "./IOFiles/anchors/emptyQuestionAnwser.dat";

static const char anchorHintSecond_filename[] = "./IOFiles/anchors/anchorHintSecond.dat";
static const char anchorHintUsedSecond_filename[] = "./IOFiles/anchors/anchorHintUsedSecond.dat";
static const char anchorLikeQuestion_filename[] = "./IOFiles/anchors/anchorLikeQuestion.dat";
//static const char anchorLikeQuestionTarget_filename[] = "../OIFiles/anchors/anchorLikeQuestionTarget.dat"; //obsolete

static const char testQuestionsOutput_filename[] = "./IOFiles/see_questions/questions.txt";
static const char testQuestionsHashedOutput_filename[] = "./questionshashed.txt";
static const char testQuestionsSecondOutput_filename[] = "./IOFiles/see_questions/questionssecond.txt";
static const char testQuestionsSecondHashedOutput_filename[] = "./questionssecondhashed.txt";

static const double coefQ_const = 0.67;     // these 3 coefficients are taken from tests
static const double diagonalQ_const = 612;  // conducted on a 1920/1080 resolution machine
static const double coefA_const = 1;        // they give the best results
static const double coefAnchor_const = 1;

static const char numBlackList[] = "!?##$%&*()<>_-+=/:;'\"ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz"; //АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя
static const char numWhiteList[] = "0123456789";

static const char tessdataInitPath[] = "./IOFiles/tesseract/tessdata";

static const char questionTessData[] = "rus";
static const char answerTessData[] = "eng";

struct Coordinates {
    int x;
    int y;
    int width;
    int height;

    Coordinates(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Coordinates() {}

    void print() {
        cout << x << " " << y << " " << width << " " << height << endl;
    }
};

static const char coords_filename[] = "./IOFiles/coords/coords.dat";
static const unsigned short questionCoordInd = 0;
static const unsigned short answerCoordInd = 1;
static const unsigned short AnchorHintInd = 2;
static const unsigned short AnchorHintUsedInd = 3;
static const unsigned short AnchorTargetCoordInd = 4;
static const unsigned short anchorHintSecondCoordInd = 5;
static const unsigned short anchorHintUsedSecondCoordInd = 6;
static const unsigned short anchorLikeQuestionCoordInd = 7;
static const unsigned short answersQuestionSecondInd = 8;
static const unsigned short answerFirstQuestionSecondInd = 9;

static const int hintCompareCount_const = 3000;     // these 3 counts are taken from tests
static const int targetCompareCount_const = 1000;   // conducted on a 1920/1080 resolution machine
static const int answerCompareCount_const = 500;    // they give the best results
//static const int arrowCompareCountObsolete = 200;

static const bool blackAndWhiteQuestion = false;
static const bool blackAndWhiteAnswer = false;
static const bool blackAndWhiteAnchors = false;
//static const bool blackAndWhiteAnchors_Obsolete = true;

static const int questionSize = 241;
static const int answerSize = 11;
static const int answerSizeSecond = 100;

static const char questions_filename[] = "./IOFiles/questions/questions.dat";
static const char questionsHashed_filename[] = "./IOFiles/questions/questionshashed.dat";
static const char addQuestions_filename[] = "./IOFiles/questions_to_copy/questions.dat";
static const char addQuestionsSecond_filename[] = "./IOFiles/questions_to_copy/questionssecond.dat";
static const char addQuestionsHashed_filename[] = "./IOFiles/questions_to_copy/questionshashed.dat";
static const char questionsSecond_filename[] = "./IOFiles/questions/questionssecond.dat";
static const char questionsSecondHashed_filename[] = "./IOFiles/questions/questionssecondhashed.dat";

static const bool questionBool = true;

static const int waitAfterAnswerMilli = 8000;
static const int waitAfterAnswerSecondMilli = 3000;
static const int waitForQuestionReadMilli = 8000;
static const int waitReadQuestionAnswer = 1000;

static const bool isHashedQuestion = false;
static const bool isHashedQuestionHashed = true;
static const bool constBoolFirstTypeQuestion = true;

static const char log_filename[] = "./IOFiles/log.txt";
static const int threshold = 3;

static const unsigned short maxSingleDigit = 9;

static const unsigned short numOfAnswers = 4;
static const double subtractCoef = 0.15;
static const double subtractCoefThirdAnswer = 0.27;
static const double subtractCoefFourthAnswer = 0.31;

static const char buff_filename[] = "./buff.dat";
#endif