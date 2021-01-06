#include "Wrapper.h"
#include "Constants.h"

Wrapper::Wrapper() {
	isAnswered = false;
    isAnsweredSecond = false;

    ifstream readCoord;
    readCoord.open(coords_filename, std::ios::in | std::ios::binary);
    if (!readCoord) {
        cout << "Opening file failed" << endl;
    }

    readCoord.seekg(0, std::ios::beg);
    readCoord.read(reinterpret_cast<char*>(&questionCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&answerCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorHintCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorHintUsedCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorTargetCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorHintSecondCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorHintUsedSecondCoord), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&anchorLikeQuestionCoord), sizeof(Coordinates));

    Coordinates buff, buff2;
    readCoord.read(reinterpret_cast<char*>(&buff), sizeof(Coordinates));
    readCoord.read(reinterpret_cast<char*>(&firstAnswer), sizeof(Coordinates));
    int addHeight = (buff.height - (numOfAnswers * firstAnswer.height)) / (numOfAnswers - 1) + firstAnswer.height;
    this->secondAnswer = Coordinates(firstAnswer.x, firstAnswer.y + addHeight, firstAnswer.width, firstAnswer.height);
    this->thirdAnswer = Coordinates(firstAnswer.x, secondAnswer.y + addHeight, firstAnswer.width, firstAnswer.height);
    this->fourthAnswer = Coordinates(firstAnswer.x, thirdAnswer.y + addHeight, firstAnswer.width, firstAnswer.height);

    int subtractCoord = subtractCoef * firstAnswer.height;
    int subtractCoordThirdFourthAnswer = subtractCoefThirdAnswer * firstAnswer.height;
    //int subtractCoordFourthAnswer = subtractCoefFourthAnswer * firstAnswer.height;
    this->readFirstAnswer = Coordinates(firstAnswer.x + subtractCoord, firstAnswer.y + subtractCoord, firstAnswer.width - (2 * subtractCoord), firstAnswer.height - (2 * subtractCoord));
    this->readSecondAnswer = Coordinates(secondAnswer.x + subtractCoord, secondAnswer.y + subtractCoord, secondAnswer.width - (2 * subtractCoord), secondAnswer.height - (2 * subtractCoord));
    this->readThirdAnswer = Coordinates(thirdAnswer.x + subtractCoord, thirdAnswer.y + subtractCoord, thirdAnswer.width - (2 * subtractCoord), thirdAnswer.height - subtractCoordThirdFourthAnswer);
    this->readFourthAnswer = Coordinates(fourthAnswer.x + subtractCoord, fourthAnswer.y + subtractCoordThirdFourthAnswer, fourthAnswer.width - (2 * subtractCoord), fourthAnswer.height - subtractCoord - subtractCoordThirdFourthAnswer);

    //questionCoord.print();
    //answerCoord.print();
    //anchorHintCoord.print();
    //anchorHintUsedCoord.print();
    //anchorTargetCoord.print();
    //anchorHintSecondCoord.print();
    //anchorHintUsedSecondCoord.print();
    //anchorLikeQuestionCoord.print();

    //firstAnswer.print();
    //secondAnswer.print();
    //thirdAnswer.print();
    //fourthAnswer.print();

    //readFirstAnswer.print();
    //readSecondAnswer.print();
    //readThirdAnswer.print();
    //readFourthAnswer.print();

    readCoord.clear();
    readCoord.close();

	this->anchorHint = Image(anchorHint_filename, anchorHintCoord);
	this->anchorHintUsed = Image(anchorHintUsed_filename, anchorHintUsedCoord);
	this->anchorTarget = Image(anchorTarget_filename, anchorTargetCoord);

    this->anchorHintSecond = Image(anchorHintSecond_filename, anchorHintSecondCoord);
    this->anchorHintUsedSecond = Image(anchorHintUsedSecond_filename, anchorHintUsedSecondCoord);
    this->anchorLikeQuestion = Image(anchorLikeQuestion_filename, anchorLikeQuestionCoord);

    //this->anchorFirstArrowObsolete = Image(anchorFirstArrowObsolete_filename, AnchorArrowObsolete);
    //this->anchorSecondArrowObsolete = Image(anchorSecondArrowObsolete_filename, AnchorArrowObsolete);
    //this->anchorThirdArrowObsolete = Image(anchorThirdArrowObsolete_filename, AnchorArrowObsolete);


	this->tesseract_ptrQ = std::unique_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI());
	this->tesseract_ptrQ->Init(tessdataInitPath, questionTessData); //+eng
	this->tesseract_ptrQ->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK); // default - PSM_SINGLE_BLOCK - slightly better/PSM_AUTO

	this->tesseract_ptrA = std::unique_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI());
	this->tesseract_ptrA->Init(tessdataInitPath, answerTessData);
	this->tesseract_ptrA->SetPageSegMode(tesseract::PSM_SINGLE_LINE); 
	this->tesseract_ptrA->SetVariable("tessedit_char_blacklist", numBlackList); 
	this->tesseract_ptrA->SetVariable("tessedit_char_whitelist", numWhiteList);
	this->tesseract_ptrA->SetVariable("classify_bln_numeric_mode", "1");

    this->tesseract_ptrQSecond = std::unique_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI());
    this->tesseract_ptrQSecond->Init(tessdataInitPath, questionTessData); //+eng
    this->tesseract_ptrQSecond->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK); // default - PSM_SINGLE_BLOCK - slightly better/PSM_AUTO

    this->tesseract_ptrASecond = std::unique_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI());
    this->tesseract_ptrASecond->Init(tessdataInitPath, questionTessData); //+eng
    this->tesseract_ptrASecond->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK); // default - PSM_SINGLE_BLOCK - slightly better/PSM_AUTO

    double diagonalQ = sqrt(pow(this->questionCoord.width, 2) + pow(this->questionCoord.height, 2));
    double tesseractCoef = diagonalQ / diagonalQ_const; //diagonalQ_const / diagonalQ;
	this->coefQ = coefQ_const * tesseractCoef;
	this->coefA = coefA_const * tesseractCoef;
    //cout << diagonalQ_const << " " << diagonalQ << " " << tesseractCoef << " " << coefQ << " " << coefA << endl;

    double compareCountCoef = diagonalQ / diagonalQ_const;
    this->hintCompareCount   = hintCompareCount_const * compareCountCoef;
    this->targetCompareCount = targetCompareCount_const * compareCountCoef;
    this->answerCompareCount = answerCompareCount_const * compareCountCoef;

    writeQuestion.open(questions_filename, std::ios::out | std::ios::binary | std::ios::app);
    if (!writeQuestion) {
        cout << "Opening " << questions_filename << " failed" << endl;
    }

    readWriteQuestionHashed.open(questionsHashed_filename, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
    if (!readWriteQuestionHashed) {
        cout << "Opening " << questionsHashed_filename << " failed" << endl;
    }

    writeQuestionSecond.open(questionsSecond_filename, std::ios::out | std::ios::binary | std::ios::app);
    if (!writeQuestionSecond) {
        cout << "Opening " << questionsSecond_filename << " failed" << endl;
    }

    readWriteQuestionSecondHashed.open(questionsSecondHashed_filename, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
    if (!readWriteQuestionSecondHashed) {
        cout << "Opening " << questionsSecondHashed_filename << " failed" << endl;
    }

    writeLog.open(log_filename, std::ios::out | std::ios::app);
    if (!writeLog) {
        cout << "Opening " << log_filename << " failed" << endl;
    }

    readQuestion.open(questions_filename, std::ios::in | std::ios::binary);
    if (!readQuestion) {
        cout << "opening file " << questions_filename <<" failed" << endl;
    }

    readQuestionSecond.open(questionsSecond_filename, std::ios::in | std::ios::binary);
    if (!readQuestionSecond) {
        cout << "opening file " << questionsSecond_filename << " failed" << endl;
    }

    //this->isRunning = true;
    this->isFirstQuestionType = true;
    this->rightAnswerIndex = 0;

    //this->distanceTable = new int*[questionSize];
    //for (int i = 0; i < questionSize; ++i)
    //    this->distanceTable[i] = new int[questionSize];

    for (int i = 0; i < questionSize; i++) {
        this->distanceTable[i][0] = i;
    }

    for (int j = 0; j < questionSize; j++) {
        this->distanceTable[0][j] = j;
    }
}

Wrapper::~Wrapper() {
    cout << "~Wrapper" << endl;
    this->tesseract_ptrQ->End();
    this->tesseract_ptrA->End();
    this->tesseract_ptrQSecond->End();
    this->tesseract_ptrASecond->End();

    writeQuestion.close();
    readWriteQuestionHashed.close();
    writeQuestionSecond.close();
    readWriteQuestionSecondHashed.close();
    writeLog.close();

    readQuestion.close();
    readQuestionSecond.close();

    //for (int i = 0; i < questionSize; ++i)
    //    delete[] this->distanceTable[i];
    //delete[] this->distanceTable;
}

void Wrapper::readScreen(bool isQuestion, bool isFirstQuestionType) {
#if defined _WIN32 || defined _WIN64
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bool blackAndWhite = (isQuestion ? blackAndWhiteQuestion : blackAndWhiteAnswer);
    double coef = (isQuestion ? coefQ_const : coefA_const);
    Coordinates& coord = (isQuestion ? questionCoord : answerCoord);

    Image Img = Image(coord, coef, blackAndWhite); //screenshot of coordinates

#else
    Image Img = Image(some_pixel_pointer, 200, 200); //pointer to pixels..
#endif

    std::unique_ptr<tesseract::TessBaseAPI>& tesseract_ptr = ((!isFirstQuestionType) ? this->tesseract_ptrQSecond : (isQuestion ? this->tesseract_ptrQ : this->tesseract_ptrA));

    tesseract_ptr->SetImage(Img.GetPixels(), Img.GetWidth(), Img.GetHeight(), Img.GetBytesPerPixel(), Img.GetBytesPerScanLine()); //Fixed this line..
    tesseract_ptr->SetSourceResolution(81.59);
    //Pix* pix = tesseract_ptr->GetThresholdedImage();
    //pixWrite("tessinput2.tif", pix, IFF_TIFF_G4);


    char* buff = tesseract_ptr->GetUTF8Text();

    if (isQuestion) {
        if (isFirstQuestionType) {
            strncpy_s(qa.question, questionSize, buff, questionSize - 1);
            writeLog << qa.question;
        }
        else {
            strncpy_s(qa2.question, questionSize, buff, questionSize - 1);
            writeLog << qa2.question;
        }
        writeLog.flush();
        //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        if (this->checkQuestion(isHashedQuestion, isFirstQuestionType)) {
            //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            //cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " check_Question" <<endl;
            if (isFirstQuestionType) {
                //this->enterAnswer(qah.answer);

                // when using Damerau-Levenshtein distance
                this->enterAnswer(atoi(qabuff.answer));
                //std::cout << qah.answer << std::endl;
            }
            else {
                // develop programmatic mouse click - too slow for reading all the answers
                //cout << "check second question type" << endl;
            }
        }
        else {

        }
    }
    else {
        if (isFirstQuestionType) {
            strncpy_s(qa.answer, answerSize, buff, answerSize - 1);
            writeLog << atoi(qa.answer);
        }
        else {
            //strncpy_s(qa2.answer, answerSizeSecond, buff, answerSizeSecond - 1);
            //writeLog << qa2.answer;
        }
        writeLog.flush();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //std::cout << (isQuestion ? "Question" : "Answer") << " read for " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] " << coef << std::endl;
    if (isQuestion) {
        //writeLog << (this->isAnswered ? (isFirstQuestionType ? std::to_string(qah.answer) : qa2h.answer) : "NA");

        //writeLog << (isFirstQuestionType ? (this->isAnswered ? std::to_string(qah.answer) : "NA") : (this->isAnsweredSecond ? qa2h.answer : "NA"));

        // when using Damerau-Levenshtein distance
        writeLog << (isFirstQuestionType ? (this->isAnswered ? (qabuff.answer) : "NA") : (this->isAnsweredSecond ? qa2buff.answer : "NA"));
    }
    writeLog << " -> " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / double(1000) << "s" << std::endl;
    writeLog.flush();

    //pixDestroy(&pix);
    delete[] buff;
}

void Wrapper::readAnswerSecond() {
    Image rightAnswerImage;
    switch (this->rightAnswerIndex) {
    case 1: rightAnswerImage = this->ImgFirstAnswer; break;
    case 2: rightAnswerImage = this->ImgSecondAnswer; break;
    case 3: rightAnswerImage = this->ImgThirdAnswer; break;
    case 4: rightAnswerImage = this->ImgFourthAnswer; break;
    default:;
    }
    //cout << "write second type question" << endl;
    tesseract_ptrASecond->SetImage(rightAnswerImage.GetPixels(), rightAnswerImage.GetWidth(), rightAnswerImage.GetHeight(), rightAnswerImage.GetBytesPerPixel(), rightAnswerImage.GetBytesPerScanLine()); //Fixed this line..
    tesseract_ptrASecond->SetSourceResolution(81.59);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //Pix* pix = tesseract_ptrASecond->GetThresholdedImage();
    //pixWrite("tessinput.tif", pix, IFF_TIFF_G4);
    //pixDestroy(&pix);

    char* buff = tesseract_ptrASecond->GetUTF8Text();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    strncpy_s(qa2.answer, answerSizeSecond, buff, answerSizeSecond - 1);
    writeLog << qa2.answer << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / double(1000) << "[s]" << endl;
    writeLog.flush();
    delete[] buff;
}

void Wrapper::findAnswerSecond() {
    this->ImgFirstAnswer = Image(readFirstAnswer, coefA_const, blackAndWhiteAnchors);
    this->ImgSecondAnswer = Image(readSecondAnswer, coefA_const, blackAndWhiteAnchors);
    this->ImgThirdAnswer = Image(readThirdAnswer, coefA_const, blackAndWhiteAnchors);
    this->ImgFourthAnswer = Image(readFourthAnswer, coefA_const, blackAndWhiteAnchors);

    //Image ImgFirstAnswerOld = ImgFirstAnswer, ImgSecondAnswerOld = ImgSecondAnswer, 
    //    ImgThirdAnswerOld = ImgFirstAnswer, ImgFourthAnswerOld = ImgFourthAnswer;

    //Image ImgFirstAnswerOld, ImgSecondAnswerOld, ImgThirdAnswerOld, ImgFourthAnswerOld;

    Image ImgFirstAnswerOld = Image(firstAnswer, coefAnchor_const, blackAndWhiteAnchors);
    Image ImgSecondAnswerOld = Image(secondAnswer, coefAnchor_const, blackAndWhiteAnchors);
    Image ImgThirdAnswerOld = Image(thirdAnswer, coefAnchor_const, blackAndWhiteAnchors);
    Image ImgFourthAnswerOld = Image(fourthAnswer, coefAnchor_const, blackAndWhiteAnchors);

    unsigned short firstAnswerNumChanges = 0, secondAnswerNumChanges = 0, thirdAnswerNumChanges = 0, fourthAnswerNumChanges = 0;

    Image ImgAnswer;

    bool isRightAnswerIndexSet = false;
    bool isAnswerSecondRead = false;
    unsigned short firstAnswerNumChangesCopy = 0, secondAnswerNumChangesCopy = 0;

    while (true) {
        ImgAnswer = Image(firstAnswer, coefAnchor_const, blackAndWhiteAnchors);
        if (!(ImgFirstAnswerOld.Compare(ImgAnswer, answerCompareCount))) {
            firstAnswerNumChanges++;
            ImgFirstAnswerOld = ImgAnswer;
        }
        ImgAnswer = Image(secondAnswer, coefAnchor_const, blackAndWhiteAnchors);
        if (!(ImgSecondAnswerOld.Compare(ImgAnswer, answerCompareCount))) {
            secondAnswerNumChanges++;
            ImgSecondAnswerOld = ImgAnswer;
        }
        ImgAnswer = Image(thirdAnswer, coefAnchor_const, blackAndWhiteAnchors);
        if (!(ImgThirdAnswerOld.Compare(ImgAnswer, answerCompareCount))) {
            thirdAnswerNumChanges++;
            ImgThirdAnswerOld = ImgAnswer;
        }
        ImgAnswer = Image(fourthAnswer, coefAnchor_const, blackAndWhiteAnchors);
        if (!(ImgFourthAnswerOld.Compare(ImgAnswer, answerCompareCount))) {
            fourthAnswerNumChanges++;
            ImgFourthAnswerOld = ImgAnswer;
        }

        if (!isRightAnswerIndexSet) {
            if (firstAnswerNumChanges > 5) {
                this->rightAnswerIndex = 1;
                //return;
                isRightAnswerIndexSet = true;
                //begin = std::chrono::steady_clock::now();
            }
            else if (secondAnswerNumChanges > 5) {
                this->rightAnswerIndex = 2;
                //return;
                isRightAnswerIndexSet = true;
                //begin = std::chrono::steady_clock::now();
            }
            else if (thirdAnswerNumChanges > 5) {
                this->rightAnswerIndex = 3;
                //return;
                isRightAnswerIndexSet = true;
                //begin = std::chrono::steady_clock::now();
            }
            else if (fourthAnswerNumChanges > 5) {
                this->rightAnswerIndex = 4;
                //return;
                isRightAnswerIndexSet = true;
                //begin = std::chrono::steady_clock::now();
            }
            firstAnswerNumChangesCopy = firstAnswerNumChanges;
            secondAnswerNumChangesCopy = secondAnswerNumChanges;
        }

        if (isRightAnswerIndexSet) {
            if (!isAnswerSecondRead) {
                this->readAnswerSecond();
                isAnswerSecondRead = true;
            }
            if (firstAnswerNumChanges > firstAnswerNumChangesCopy && secondAnswerNumChanges > secondAnswerNumChangesCopy) {
                //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();;
                //cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " wait after answer real " << endl;
                return;
            }
        }

        sleep_until(system_clock::now() + milliseconds(50));
    }

}

void Wrapper::writeQuestionSecondToFile() {
    if (!(this->isAnsweredSecond)) {
        this->qa2h.hash = std::hash<std::string>{} (this->qa2.question);
        strncpy_s(qa2h.answer, answerSizeSecond, qa2.answer, answerSizeSecond - 1);
        //this->qa2h.answer = this->qa2.answer;

        writeQuestionSecond.seekp(0, std::ios::end);
        writeQuestionSecond.write(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
        writeQuestionSecond.flush();

        readWriteQuestionSecondHashed.seekp(0, std::ios::end);
        readWriteQuestionSecondHashed.write(reinterpret_cast<char*>(&qa2h), sizeof(QuestionAnswerSecondHashed));
        readWriteQuestionSecondHashed.flush();
    }
}

void Wrapper::writeQuestionToFile() {
    if (!(this->isAnswered)) {
        //if (this->isFirstQuestionType) {
            this->qah.hash = std::hash<std::string>{} (this->qa.question);
            this->qah.answer = atoi(this->qa.answer);

            writeQuestion.seekp(0, std::ios::end);
            writeQuestion.write(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
            writeQuestion.flush();

            readWriteQuestionHashed.seekp(0, std::ios::end);
            readWriteQuestionHashed.write(reinterpret_cast<char*>(&qah), sizeof(QuestionAnswerHashed));
            readWriteQuestionHashed.flush();
    }
    else if (atoi(qa.answer) != atoi(qabuff.answer)) {
        int qaAnswer = atoi(qa.answer), qabuffAnswer = atoi(qabuff.answer);
        if (qaAnswer > qabuffAnswer && qaAnswer > maxSingleDigit) {
            readQuestion.seekg(-1 * sizeof(QuestionAnswer), std::ios::cur);

            fstream changeQuestionAnswer;
            changeQuestionAnswer.open(questions_filename, std::ios::out | std::ios::binary | std::ios::in);
            if (!changeQuestionAnswer) {
                cout << "Opening " << questions_filename << " for  changing question answer failed" << endl;
            }

            changeQuestionAnswer.seekp(readQuestion.tellg(), std::ios::beg);
            changeQuestionAnswer.write(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
            changeQuestionAnswer.flush();
            changeQuestionAnswer.close();

            readQuestion.clear();

            writeLog << "Answer changed to "<< qaAnswer << "!" << endl;
            writeLog.flush();
        }
    }
}

// For reading English questions and better accuracy in question finding
// we can use Damerau-Levenshtein distance with a threshold. It is too time consuming
// for larger question files, so in the future we'll maybe have to come back to hashing

bool Wrapper::checkQuestion(bool isHashed, bool isFirstQuestionType) {
    if (isFirstQuestionType) {
        //size_t hash = (isHashed ? (qah.hash) : (std::hash<string>{} (qa.question)));
        //readWriteQuestionHashed.seekg(0, std::ios::beg);
        //while (readWriteQuestionHashed.read(reinterpret_cast<char*>(&qah), sizeof(QuestionAnswerHashed))) {
        //    if (hash == qah.hash) {
        //        readWriteQuestionHashed.clear();
        //        this->isAnswered = true;
        //        return true;
        //    }
        //}

        //this->isAnswered = false;
        //readWriteQuestionHashed.clear();


        // Damerau-Levenshtein distance with a threshold
        readQuestion.seekg(0, std::ios::beg);
        int findQuestionLen = strlen(qa.question);

        while (readQuestion.read(reinterpret_cast<char*>(&qabuff), sizeof(QuestionAnswer))) {
            if (this->DamerauLevenshteinDistance(qa.question, qabuff.question, findQuestionLen, strlen(qabuff.question), threshold) < threshold) {
                readQuestion.clear();
                this->isAnswered = true;
                return true;
            }
        }

        this->isAnswered = false;
        readQuestion.clear();

    }
    else {
        //size_t hash = (isHashed ? (qa2h.hash) : (std::hash<string>{} (qa2.question)));
        //readWriteQuestionSecondHashed.seekg(0, std::ios::beg);
        //while (readWriteQuestionSecondHashed.read(reinterpret_cast<char*>(&qa2h), sizeof(QuestionAnswerSecondHashed))) {
        //    if (hash == qa2h.hash) {
        //        readWriteQuestionSecondHashed.clear();
        //        this->isAnsweredSecond = true;
        //        return true;
        //    }
        //}

        //this->isAnsweredSecond = false;
        //readWriteQuestionSecondHashed.clear();

        // Damerau-Levenshtein distance with a threshold
        readQuestionSecond.seekg(0, std::ios::beg);
        int findQuestionLen = strlen(qa2.question);

        while (readQuestionSecond.read(reinterpret_cast<char*>(&qa2buff), sizeof(QuestionAnswerSecond))) {
            if (this->DamerauLevenshteinDistance(qa2.question, qa2buff.question, findQuestionLen, strlen(qa2buff.question), threshold) < threshold) {
                readQuestionSecond.clear();
                this->isAnsweredSecond = true;
                return true;
            }
        }

        this->isAnsweredSecond = false;
        readQuestionSecond.clear();
    }

    return false;
}

//bool Wrapper::timeToTakeAnswer() {
//    Image Img = Image(this->DC, AnchorArrowObsolete, coefAnchor_const, blackAndWhiteAnchors_Obsolete);
//
//    return Img.Compare(this->anchorFirstArrowObsolete, arrowCompareCountObsolete) || 
//        Img.Compare(this->anchorSecondArrowObsolete, arrowCompareCountObsolete) || 
//        Img.Compare(this->anchorThirdArrowObsolete, arrowCompareCountObsolete);
//}

bool Wrapper::timeToTakeQuestion() {
    Image ImgHint = Image(anchorHintCoord, coefAnchor_const, blackAndWhiteAnchors); //screenshot of coordinates
    Image ImgHintUsed = Image(anchorHintUsedCoord, coefAnchor_const, blackAndWhiteAnchors);

    if (ImgHint.Compare(this->anchorHint, hintCompareCount) || ImgHintUsed.Compare(this->anchorHintUsed, hintCompareCount)) {
        this->isFirstQuestionType = constBoolFirstTypeQuestion;
        return true;
    }
    else {
        return false;
    }

    //return ImgHint.Compare(this->anchorHint, hintCompareCount) || ImgHintUsed.Compare(this->anchorHintUsed, hintCompareCount);
}

bool Wrapper::timeToTakeQuestionSecond() {
    Image ImgHintSecond = Image(anchorHintSecondCoord, coefAnchor_const, blackAndWhiteAnchors); //screenshot of coordinates
    Image ImgHintUsedSecond = Image(anchorHintUsedSecondCoord, coefAnchor_const, blackAndWhiteAnchors);

    if (ImgHintSecond.Compare(this->anchorHintSecond, hintCompareCount) || ImgHintUsedSecond.Compare(this->anchorHintUsedSecond, hintCompareCount)) {
        this->isFirstQuestionType = !constBoolFirstTypeQuestion;
        return true;
    }
    else {
        return false;
    }

    //return ImgHintSecond.Compare(this->anchorHintSecond, hintCompareCount) || ImgHintUsedSecond.Compare(this->anchorHintUsedSecond, hintCompareCount);
}

bool Wrapper::timeToTakeQuestionThird() {
    Image ImgLikeQuestion = Image(anchorLikeQuestionCoord, coefAnchor_const, blackAndWhiteAnchors); //screenshot of coordinates

    if (ImgLikeQuestion.Compare(this->anchorLikeQuestion, hintCompareCount)) {
        if (this->waitToTakeAnswer()) {
            this->isFirstQuestionType = constBoolFirstTypeQuestion;
        }
        else {
            this->isFirstQuestionType = !constBoolFirstTypeQuestion;
        }
        //cout << "true" << endl;
        return true;
    }
    else {
        //cout << "false" << endl;
        return false;
    }

}



bool Wrapper::waitToTakeAnswer() {
    Image Img = Image(anchorTargetCoord, coefAnchor_const, blackAndWhiteAnchors);

    if (Img.Compare(this->anchorTarget, targetCompareCount)) {
        this->isFirstQuestionType = constBoolFirstTypeQuestion;
        return true;
    }
    else {
        return false;
    }

    //return Img.Compare(this->anchorTarget, targetCompareCount);
}

//void Wrapper::triviadorHack() {
//    while (true) {
//        while (!(this->timeToTakeQuestion()) && !(this->waitToTakeAnswer())) {
//            sleep_until(system_clock::now() + milliseconds(100));
//        }
//
//        std::thread readAsyncQ([&] { readScreen(questionBool); }); // better than std::async
//        //std::future<void> readAsyncQ = std::async(std::launch::async, [&] { readScreen(questionBool); });
//        // Obsolete
//        //while (!timeToTakeAnswer(495, 550, 31, 31, DC)) {
//        //    sleep_until(system_clock::now() + milliseconds(100));
//        //}
//        //sleep_until(system_clock::now() + milliseconds(300));
//
//        while (!waitToTakeAnswer()) {
//            sleep_until(system_clock::now() + milliseconds(100));
//        }
//        while (waitToTakeAnswer()) {
//            sleep_until(system_clock::now() + milliseconds(100));
//        }
//
//        sleep_until(system_clock::now() + milliseconds(300));
//
//        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//
//        std::thread readAsyncA([&] { readScreen(!questionBool); });
//        //std::future<void> readAsyncA = std::async(std::launch::async, [&] { readScreen(!questionBool); });
//
//
//        //readAsyncQ.get();
//        //readAsyncA.get();
//
//        readAsyncQ.join();
//        readAsyncA.join();
//
//        if (!(this->isAnswered)) {
//            this->writeQuestionToFile();
//        }
//
//        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//
//        //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() / 1000 << "[ms]" << std::endl;
//
//        sleep_until(system_clock::now() + milliseconds(waitAfterAnswerMilli - std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()));
//    }
//}

void Wrapper::triviadorHack() {
    std::thread readAsyncQ;
    std::atomic<bool> doneReadAsyncQ(true);

    std::thread readAsyncQSecond;
    std::atomic<bool> doneReadAsyncQSecond(true);

    while (true) {
        while (!(this->timeToTakeQuestion()) && !(this->waitToTakeAnswer()) && !(this->timeToTakeQuestionSecond()) && !(this->timeToTakeQuestionThird())) {
            sleep_until(system_clock::now() + milliseconds(100));
        }

        __int64 waitTime = 0;
        if (this->isFirstQuestionType) {
            if (doneReadAsyncQ) {
                readAsyncQ = std::thread([&] { readScreen(questionBool, constBoolFirstTypeQuestion); });
                doneReadAsyncQ = false;

                while (!waitToTakeAnswer()) {
                    sleep_until(system_clock::now() + milliseconds(100));
                }
                while (waitToTakeAnswer()) {
                    sleep_until(system_clock::now() + milliseconds(100));
                }

                sleep_until(system_clock::now() + milliseconds(500));
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                std::thread readAsyncA([&] { readScreen(!questionBool, constBoolFirstTypeQuestion); });
                readAsyncA.join();

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                waitTime = waitAfterAnswerMilli - std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

                std::thread writeQuestionToFileAsync([&] { readAsyncQ.join(); writeQuestionToFile(); doneReadAsyncQ = true; });
                writeQuestionToFileAsync.detach();
                sleep_until(system_clock::now() + milliseconds(waitTime));
            }
            else {
                writeLog << "Still reading previous question. Restart for faster reading!" << endl;
                writeLog.flush();
                sleep_until(system_clock::now() + milliseconds(waitReadQuestionAnswer));
            }
        }
        else {

            if (doneReadAsyncQSecond) {
                readAsyncQSecond = std::thread([&] { readScreen(questionBool, (!constBoolFirstTypeQuestion)); });
                doneReadAsyncQSecond = false;

                std::thread findAsyncASecond([&] { this->findAnswerSecond(); });
                findAsyncASecond.join();
                sleep_until(system_clock::now() + milliseconds(300));

                waitTime = waitAfterAnswerSecondMilli;
                std::thread writeQuestionSecondToFileAsync([&] { readAsyncQSecond.join(); writeQuestionSecondToFile(); doneReadAsyncQSecond = true; });
                writeQuestionSecondToFileAsync.detach();

                //sleep_until(system_clock::now() + milliseconds(waitTime));
            }
            else {
                writeLog << "Still reading previous question. Restart for faster reading!" << endl;
                writeLog.flush();
                sleep_until(system_clock::now() + milliseconds(waitReadQuestionAnswer));
            }          
        }
    }
}

void Wrapper::readQuestions() {
    //ofstream ostreamHashed;

    //ostreamHashed.open(testQuestionsHashedOutput_filename, std::ios::out);
    //if (!ostreamHashed)
    //    cout << "opening" << testQuestionsHashedOutput_filename << "failed" << endl;

    ofstream ostream;

    ostream.open(testQuestionsOutput_filename, std::ios::out);
    if (!ostream)
        cout << "opening" << testQuestionsOutput_filename << "failed" << endl;

    ifstream readQuestions;
    readQuestions.open(questions_filename, std::ios::in | std::ios::binary);
    if (!readQuestions)
        cout << "opening" << questions_filename << "failed" << endl;

    //readWriteQuestionHashed.seekg(0, std::ios::beg);
    //while (readWriteQuestionHashed.read(reinterpret_cast<char*>(&qah), sizeof(QuestionAnswerHashed))) {
    //    ostreamHashed << qah.answer << endl;
    //    ostreamHashed << "-----------" << endl;
    //}
    //readWriteQuestionHashed.clear();

    while (readQuestions.read(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer))) {
        ostream << qa.question << endl;
        ostream << qa.answer << endl;
        ostream << "----------------------------" << endl;
    }

    //ostreamHashed.close();
    ostream.close();
    readQuestions.close();


    //ofstream ostreamSecondHashed;

    //ostreamSecondHashed.open(testQuestionsSecondHashedOutput_filename, std::ios::out);
    //if (!ostreamSecondHashed)
    //    cout << "opening" << testQuestionsSecondHashedOutput_filename << "failed" << endl;

    ofstream ostreamSecond;

    ostreamSecond.open(testQuestionsSecondOutput_filename, std::ios::out);
    if (!ostreamSecond)
        cout << "opening" << testQuestionsSecondOutput_filename << "failed" << endl;

    ifstream readQuestionsSecond;
    readQuestionsSecond.open(questionsSecond_filename, std::ios::in | std::ios::binary);
    if (!readQuestionsSecond)
        cout << "opening" << questionsSecond_filename << "failed" << endl;

    //readWriteQuestionSecondHashed.seekg(0, std::ios::beg);
    //while (readWriteQuestionSecondHashed.read(reinterpret_cast<char*>(&qa2h), sizeof(QuestionAnswerSecondHashed))) {
    //    ostreamSecondHashed << qa2h.answer << endl;
    //    ostreamSecondHashed << "---------------------------------------" << endl;
    //}
    //readWriteQuestionSecondHashed.clear();

    while (readQuestionsSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond))) {
        ostreamSecond << qa2.question << endl;
        ostreamSecond << qa2.answer << endl;
        ostreamSecond << "----------------------------------------" << endl;
    }

    //ostreamSecondHashed.close();
    ostreamSecond.close();
    readQuestionsSecond.close();
}

bool Wrapper::addQuestions() {
    //ifstream istreamQuestionsHashed;
    ifstream istreamQuestions;

    //istreamQuestionsHashed.open(addQuestionsHashed_filename, std::ios::in | std::ios::binary);
    //if (!istreamQuestionsHashed) {
    //    cout << "opening file failed" << endl;
    //    writeLog << "Opening file for adding questions failed!" << endl;
    //    writeLog.flush();
    //}

    istreamQuestions.open(addQuestions_filename, std::ios::in | std::ios::binary);
    if (!istreamQuestions) {
        writeLog << "Opening file " << addQuestions_filename << " for adding questions failed!" << endl;
        writeLog.flush();
        return false;
    }

    ifstream istreamQuestionsSecond;
    istreamQuestionsSecond.open(addQuestionsSecond_filename, std::ios::in | std::ios::binary);
    if (!istreamQuestionsSecond) {
        writeLog << "Opening file " << addQuestionsSecond_filename << " for adding questions failed!" << endl;
        writeLog.flush();
        return false;
    }

    //QuestionAnswerHashed qahbuf;
    //istreamQuestionsHashed.seekg(0, std::ios::beg);
    //while (istreamQuestionsHashed.read(reinterpret_cast<char*>(&qah), sizeof(QuestionAnswerHashed))) {
    //    qahbuf = qah;
    //    if (!(this->checkQuestion(isHashedQuestionHashed, true))) { // fix later
    //        readWriteQuestionHashed.seekp(0, std::ios::end);
    //        readWriteQuestionHashed.write(reinterpret_cast<char*>(&qahbuf), sizeof(QuestionAnswerHashed));
    //        readWriteQuestionHashed.flush();
    //    }
    //}
    //istreamQuestionsHashed.clear();

    istreamQuestions.seekg(0, std::ios::beg);
    while (istreamQuestions.read(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer))) {
        if (!(this->checkQuestion(isHashedQuestion, constBoolFirstTypeQuestion))) {
            writeQuestion.seekp(0, std::ios::end);
            writeQuestion.write(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
            writeQuestion.flush();
        }
    }
    istreamQuestions.clear();


    istreamQuestionsSecond.seekg(0, std::ios::beg);
    while (istreamQuestionsSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond))) {
        if (!(this->checkQuestion(isHashedQuestion, !constBoolFirstTypeQuestion))) {
            writeQuestionSecond.seekp(0, std::ios::end);
            writeQuestionSecond.write(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
            writeQuestionSecond.flush();
        }
    }
    istreamQuestionsSecond.clear();

    //istreamQuestionsHashed.close();
    istreamQuestions.close();
    istreamQuestionsSecond.close();

    return true;
}

void Wrapper::displayImage(Image& Img) {
    BITMAPINFO bmInfo;
    int Bpp = 4;
    bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmInfo.bmiHeader.biWidth = Img.GetWidth();
    bmInfo.bmiHeader.biHeight = -Img.GetHeight();
    bmInfo.bmiHeader.biPlanes = 1;
    bmInfo.bmiHeader.biBitCount = Bpp * 8;
    bmInfo.bmiHeader.biCompression = BI_RGB;
    bmInfo.bmiHeader.biSizeImage = Img.GetWidth() * Img.GetHeight() * Bpp;
    bmInfo.bmiHeader.biXPelsPerMeter = 0;
    bmInfo.bmiHeader.biYPelsPerMeter = 0;
    bmInfo.bmiHeader.biClrUsed = 0;
    bmInfo.bmiHeader.biClrImportant = 0;

    bmInfo.bmiColors[0].rgbBlue = 255;

    CImage im;
    im.Create(Img.GetWidth(), Img.GetHeight(), 24, NULL);

    HDC dc = im.GetDC();
    SetDIBitsToDevice(dc, 0, 0, Img.GetWidth(), Img.GetHeight(), 0, 0, 0, Img.GetHeight(), Img.GetPixels(), &bmInfo, DIB_RGB_COLORS);
    im.Save(L"./tessinput.png");
    im.ReleaseDC();

}

void Wrapper::changeAnchorQuestionAnswer(Coordinates coord, const char* filename, unsigned short coordInd) {
    Image Img = Image(coord, coefAnchor_const, blackAndWhiteAnchors);
    this->displayImage(Img);

    fstream changeCoordAnchorQuestionAnswer;
    changeCoordAnchorQuestionAnswer.open(coords_filename, std::ios::out | std::ios::binary | std::ios::in);
    if (!changeCoordAnchorQuestionAnswer) {
        cout << "Opening " << coords_filename << " for  changing anchor coords answer failed" << endl;
    }

    changeCoordAnchorQuestionAnswer.seekp(coordInd * sizeof(Coordinates), std::ios::beg);
    changeCoordAnchorQuestionAnswer.write(reinterpret_cast<char*>(&coord), sizeof(Coordinates));
    changeCoordAnchorQuestionAnswer.flush();
    changeCoordAnchorQuestionAnswer.close();
    
    ofstream changeAnchorQuestionAnswer;
    changeAnchorQuestionAnswer.open(filename, std::ios::binary);
    if (!changeAnchorQuestionAnswer) {
        cout << "Opening file failed" << endl;
        writeLog << "Opening file for changing anchor failed!" << endl;
        writeLog.flush();
    }
    changeAnchorQuestionAnswer.write((char*)&Img.GetPixels()[0], Img.GetSize() * Img.GetPixelSize());
    changeAnchorQuestionAnswer.close();

}

std::string& Wrapper::getOutput() {
    return this->output;
}

//void Wrapper::changeIsRunning(bool boolVal) {
//    this->isRunning = boolVal;
//}

//std::thread Wrapper::getThreadFunc(bool isQuestion) {
//    std::thread readAsync([&] { readScreen(isQuestion); }); // better than std::async
//    //cout << "before return" << endl;
//    return readAsync;
//}

//bool Wrapper::getIsRunning() {
//    return this->isRunning;
//}

bool Wrapper::getIsAnswered() {
    return this->isAnswered;
}

void Wrapper::pressKey(unsigned short key) {
    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;

    // Pause for 5 seconds.
    //Sleep(5000);

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "A" key
    ip.ki.wVk = key;//0x41; // virtual-key code for the "a" key
    //cout << typeid(ip.ki.wVk).name() << endl;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

    // Exit normally
}

void Wrapper::enterAnswer(int anw) {
    std::string ans_str = std::to_string(anw);

    for (int i = 0; i < answerSize; i++) {
        this->pressKey(VK_BACK);
    }

    for (char c : ans_str) {
        this->pressKey(c);
        //sleep_until(system_clock::now() + milliseconds(500));
    }
    //sleep_until(system_clock::now() + milliseconds(1000));

    this->pressKey(VK_RETURN);
}

void Wrapper::test() {
    //ofstream writeCoord;
    //writeCoord.open(coords_filename, std::ios::out | std::ios::binary | std::ios::app);
    //if (!writeCoord) {
    //    cout << "Opening coord file 1 failed" << endl;
    //}

    ////Coordinates questionCoord2 = { 486, 375, 602, 110 };
    ////Coordinates answerCoord2 = { 667, 500, 251, 56 };
    ////Coordinates AnchorHintAndHintUsedCoord2 = { 415, 695, 105, 90 };
    ////Coordinates AnchorTargetCoord2 = { 662, 500, 262, 56 };
    //Coordinates questionCoord2(486, 375, 602, 110);
    //Coordinates answerCoord2 (667, 500, 251, 56);
    //Coordinates AnchorHintAndHintUsedCoord2(415, 695, 105, 90);
    //Coordinates AnchorTargetCoord2(662, 500, 262, 56);

    //writeCoord.write(reinterpret_cast<char*>(&questionCoord2), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&answerCoord2), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&AnchorHintAndHintUsedCoord2), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&AnchorHintAndHintUsedCoord2), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&AnchorTargetCoord2), sizeof(Coordinates));

    //Coordinates all(560, 515, 455, 318);
    //Coordinates single(560, 515, 455, 70);

    //writeCoord.write(reinterpret_cast<char*>(&anchorHintSecondCoord22), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&anchorHintUsedSecondCoord22), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&anchorLikeQuestionCoord22), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&all), sizeof(Coordinates));
    //writeCoord.write(reinterpret_cast<char*>(&single), sizeof(Coordinates));

    //writeCoord.close();

    // fix secondquestionshashed
    //ifstream readQuestionsSecond;
    //readQuestionsSecond.open(questionsSecond_filename, std::ios::in | std::ios::binary);
    //if (!readQuestionsSecond)
    //    cout << "opening" << questionsSecond_filename << "failed" << endl;

    //ofstream writeCoord;
    //writeCoord.open("./questionssecond.dat", std::ios::out | std::ios::binary | std::ios::app);
    //if (!writeCoord) {
    //    cout << "Opening coord file 1 failed" << endl;
    //}

    //int i = 0;
    //while (readQuestionsSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond)) && i < 319) {
    //    //if (this->checkQuestion(isHashedQuestion, !constBoolFirstTypeQuestion)) {

    //    //}
    //    //else {
    //    //    this->writeQuestionSecondToFile();
    //    //}
    //    i++;
    //    writeCoord.write(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
    //}

    //readQuestionsSecond.close();
    //writeCoord.close();

    //check readspeed

    //ofstream writecoord;
    //writecoord.open("./testquestionssecond.dat", std::ios::out | std::ios::binary | std::ios::app);
    //if (!writecoord) {
    //    cout << "opening coord file 1 failed" << endl;
    //}

    //ofstream writecoord2;
    //writecoord2.open("./testquestionssecondhashed.dat", std::ios::out | std::ios::binary | std::ios::app);
    //if (!writecoord2) {
    //    cout << "opening coord file 1 failed" << endl;
    //}

    //ifstream writecoord;
    //writecoord.open("./testquestionssecond.dat", std::ios::in | std::ios::binary);
    //if (!writecoord) {
    //    cout << "opening coord file 1 failed" << endl;
    //}

    //ifstream writecoord2;
    //writecoord2.open("./testquestionssecondhashed.dat", std::ios::in | std::ios::binary);
    //if (!writecoord2) {
    //    cout << "opening coord file 1 failed" << endl;
    //}

    //ifstream readQuestionsSecond;
    ////readQuestionsSecond.open(questionsSecond_filename, std::ios::in | std::ios::binary);
    ////if (!readQuestionsSecond)
    ////    cout << "opening" << questionsSecond_filename << "failed" << endl;
    //readQuestionsSecond.open("./testquestionssecond.dat", std::ios::in | std::ios::binary);
    //if (!readQuestionsSecond) {
    //    cout << "opening coord file 1 failed" << endl;
    //}

    //readQuestionsSecond.seekg((15 * sizeof(QuestionAnswerSecond)), std::ios::beg);
    //readQuestionsSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
    //readQuestionsSecond.clear();
    //readQuestionsSecond.seekg(0, std::ios::beg);
    //char cmpstr[questionSize];
    ////char cmpstr[] = "Това е тестов стринг!";
    //strncpy_s(cmpstr, questionSize, qa2.question, questionSize - 1);
    ////for (int i = 20; i < 60; i++) {
    ////    cmpstr[i] = ' ';
    ////}
    //int len = strlen(cmpstr);

    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //while (readQuestionsSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond))) {
    //    //cout << this->DamerauLevenshteinDistance(qa2.question, cmpstr, strlen(qa2.question), len, 10) << endl;
    //    this->DamerauLevenshteinDistance(qa2.question, cmpstr, strlen(qa2.question), len, 10);
    //    /*if (!strcmp(qa2.question, cmpstr)) {
    //        cout << "same" << endl;
    //    }*/
    //    /*for (int i = 0; i < 100; i++) {
    //        writeCoord.write(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
    //    }*/
    //}
    //readQuestionsSecond.clear();

    //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

    //readQuestionsSecond.close();
    //size_t hash = 0;

    //std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    //writecoord2.seekg(0, std::ios::beg);
    //while (writecoord2.read(reinterpret_cast<char*>(&qa2h), sizeof(QuestionAnswerSecondHashed))) {
    //    if (hash == qa2h.hash) {
    //        cout << "same hash" << endl;
    //    }
    //    /*for (int i = 0; i < 100; i++) {
    //        writeCoord2.write(reinterpret_cast<char*>(&qa2h), sizeof(QuestionAnswerSecondHashed));
    //    }*/
    //}
    //writecoord2.clear();

    //std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    //cout << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() << endl;

    //writecoord.close();
    //writecoord2.close();










    //readQuestion.seekg(10 * sizeof(QuestionAnswer), std::ios::beg);
    //readQuestion.read(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
    //readQuestion.clear();

    ////char findQuestion[questionSize];
    ////strncpy_s(findQuestion, questionSize, qa.question, questionSize - 1);
    //int findQuestionLen = strlen(qa.question);
    //
    //readQuestion.seekg(0, std::ios::beg);
    //while (readQuestion.read(reinterpret_cast<char*>(&qabuff), sizeof(QuestionAnswer))) {
    //    cout << "1" << endl;
    //    if (this->DamerauLevenshteinDistance(qa.question, qabuff.question, findQuestionLen, strlen(qabuff.question), threshold) < threshold) {
    //        break;
    //    }
    //}

    //readQuestion.clear();
    //cout << qabuff.answer << endl;
    //strncpy_s(qa.answer, answerSize, "5000", 5);
    //int size = sizeof(QuestionAnswer);
    //readQuestion.seekg(-1 * sizeof(QuestionAnswer), std::ios::cur);

    //fstream changeQuestionAnswer;
    //changeQuestionAnswer.open(questions_filename, std::ios::out | std::ios::binary | std::ios::in);
    //if (!changeQuestionAnswer) {
    //    cout << "Opening " << questions_filename << " failed" << endl;
    //}

    //changeQuestionAnswer.seekp(readQuestion.tellg(), std::ios::beg);
    //changeQuestionAnswer.write(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
    //changeQuestionAnswer.flush();
    //changeQuestionAnswer.close();

    //readQuestion.read(reinterpret_cast<char*>(&qabuff), sizeof(QuestionAnswer));
    //cout << qa.answer << " " << qabuff.answer << endl;
    //readQuestion.clear();
}

int Wrapper::DamerauLevenshteinDistance(char* str1, char* str2, int m, int n, int threshold) {
    // Fill d[][] in bottom up manner 
    int min = INT_MAX;
    int ins, rem, rep;


    for (int i = 1; i <= m; i++) {
        int minCurrVal = INT_MAX;
        for (int j = 1; j <= n; j++) {

            // If last characters are same, ignore last char 
            // and recur for remaining string 
            if (str1[i - 1] == str2[j - 1]) {
                min = this->distanceTable[i - 1][j - 1];

                // If the last character is different, consider all 
                // possibilities and find the minimum 
            }
            else {
                ins = this->distanceTable[i][j - 1];
                rem = this->distanceTable[i - 1][j];
                rep = this->distanceTable[i - 1][j - 1];
                //this->distanceTable[i][j] = 1 + this->minmin(this->distanceTable[i][j - 1], // Insert 
                //    this->distanceTable[i - 1][j], // Remove 
                //    this->distanceTable[i - 1][j - 1]); // Replace 

                min = (ins > rem) ? (rem > rep ? rep : rem) : (ins > rep ? rep : ins);
                min++;

            }
            this->distanceTable[i][j] = min;
            if (min < minCurrVal) {
                minCurrVal = min;
            }

        }
        if (minCurrVal > threshold) {
            return INT_MAX;
        }
    }

    return this->distanceTable[m][n];
}

int Wrapper::minmin(int x, int y, int z) {
    return (std::min)(x, (std::min)(y, z));
}

bool Wrapper::changeQuestion(char* question, char* answer) {
    bool foundQuestion = false;

    fstream changeQuestionAnswer;
    changeQuestionAnswer.open(questions_filename, std::ios::out | std::ios::binary | std::ios::in);
    if (!changeQuestionAnswer) {
        cout << "Opening " << questions_filename << " for  changing question answer failed" << endl;
    }

    readQuestion.seekg(0, std::ios::beg);
    int findQuestionLen = strlen(question);

    while (readQuestion.read(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer))) {
        //cout << this->DamerauLevenshteinDistance(qa.question, question, strlen(qa.question), findQuestionLen, 500) << endl;
        if (this->DamerauLevenshteinDistance(qa.question, question, strlen(qa.question), findQuestionLen, threshold) < threshold) {
            foundQuestion = true;
            break;
        }
    }
    readQuestion.clear();

    if (foundQuestion) {
        if (!strcmp(answer, "")) {
            strncpy_s(qa.question, questionSize, "", 0);
            //cout << qa.question << endl;
        }
        else {
            strncpy_s(qa.question, questionSize, question, questionSize - 1);
            strncpy_s(qa.answer, answerSize, answer, answerSize - 1);
        }

        readQuestion.seekg(-1 * sizeof(QuestionAnswer), std::ios::cur);

        changeQuestionAnswer.seekp(readQuestion.tellg(), std::ios::beg);
        changeQuestionAnswer.write(reinterpret_cast<char*>(&qa), sizeof(QuestionAnswer));
        changeQuestionAnswer.flush();

        changeQuestionAnswer.close();
        readQuestion.clear();
    }
    else {
        fstream changeQuestionAnswerSecond;
        changeQuestionAnswerSecond.open(questionsSecond_filename, std::ios::out | std::ios::binary | std::ios::in);
        if (!changeQuestionAnswerSecond) {
            cout << "Opening " << questionsSecond_filename << " for  changing question answer failed" << endl;
        }

        readQuestionSecond.seekg(0, std::ios::beg);

        while (readQuestionSecond.read(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond))) {
            //cout << this->DamerauLevenshteinDistance(qa.question, question, strlen(qa.question), findQuestionLen, 500) << endl;
            if (this->DamerauLevenshteinDistance(qa2.question, question, strlen(qa2.question), findQuestionLen, threshold) < threshold) {
                foundQuestion = true;
                break;
            }
        }
        readQuestionSecond.clear();

        if (foundQuestion) {
            if (!strcmp(answer, "")) {
                strncpy_s(qa2.question, questionSize, "", 0);
            }
            else {
                strncpy_s(qa2.question, questionSize, question, questionSize - 1);
                strncpy_s(qa2.answer, answerSizeSecond, answer, answerSizeSecond - 1);
            }

            readQuestionSecond.seekg(-1 * sizeof(QuestionAnswerSecond), std::ios::cur);

            changeQuestionAnswerSecond.seekp(readQuestionSecond.tellg(), std::ios::beg);
            changeQuestionAnswerSecond.write(reinterpret_cast<char*>(&qa2), sizeof(QuestionAnswerSecond));
            changeQuestionAnswerSecond.flush();

            changeQuestionAnswerSecond.close();
            readQuestionSecond.clear();
        }
    }

    return foundQuestion;
}

int Wrapper::keyPressed(int key) {
    return (GetAsyncKeyState(key) & (0x8000 != 0)); //(0x8000 != 0)
}

bool Wrapper::mouseButtonPressed(int& x, int& y) {
    if (keyPressed(VK_LBUTTON)) {
        printf("%s\n", "Click left");
        LPPOINT cursor_pos = new tagPOINT;
        GetCursorPos(cursor_pos);
        x = cursor_pos->x;
        y = cursor_pos->y;
        cout << x << " " << y << endl;
        return true;;
    }

    return false;
}