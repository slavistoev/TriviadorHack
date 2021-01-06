#pragma once

static const char hint_filename[] = "./anchorTessinput/hint.png";
static const char hintBig_filename[] = "./anchorTessinput/hintbig.png";
static const char hintUsed_filename[] = "./anchorTessinput/hintused.png";
static const char hintUsedBig_filename[] = "./anchorTessinput/hintusedbig.png";
static const char question_filename[] = "./anchorTessinput/question.png";
static const char questionBig_filename[] = "./anchorTessinput/questionbig.png";
static const char answer_filename[] = "./anchorTessinput/answer.png";
static const char answerBig_filename[] = "./anchorTessinput/answerbig.png";
static const char target_filename[] = "./anchorTessinput/target.png";
static const char targetBig_filename[] = "./anchorTessinput/targetbig.png";
static const char hintSecond_filename[] = "./anchorTessinput/hintsecond.png";
static const char hintSecondBig_filename[] = "./anchorTessinput/hintsecondbig.png";
static const char hintSecondUsed_filename[] = "./anchorTessinput/hintsecondused.png";
static const char hintSecondUsedBig_filename[] = "./anchorTessinput/hintsecondusedbig.png";
static const char likeQuestion_filename[] = "./anchorTessinput/likequestion.png";
static const char likeQuestionBig_filename[] = "./anchorTessinput/likequestionbig.png";
static const char answerFirstQuestionSecond_filename[] = "./anchorTessinput/answerfirstquestionsecond.png";
static const char answerFirstQuestionSecondBig_filename[] = "./anchorTessinput/answerfirstquestionsecondbig.png";
static const char answersQuestionSecond_filename[] = "./anchorTessinput/answersquestionsecond.png";
static const char answersQuestionSecondBig_filename[] = "./anchorTessinput/answersquestionsecondbig.png";

//static const char labelSetupBuff_filename[] = "./label.txt";

static double getResizeCoef(bool sameRatio) {
	int xCurRes, yCurRes;
	xCurRes = GetSystemMetrics(SM_CXSCREEN);
	yCurRes = GetSystemMetrics(SM_CYSCREEN);

	DEVMODEW dm;
	long retval = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	int xAbsRes = dm.dmPelsWidth;
	int yAbsRes = dm.dmPelsHeight;

	double diagonalCurRes = sqrt(pow(xCurRes, 2) + pow(yCurRes, 2));
	double diagonalAbsRes = sqrt(pow(xAbsRes, 2) + pow(yAbsRes, 2));

	if (sameRatio) {
		return diagonalCurRes / diagonalAbsRes;
	}
	else {
		return diagonalAbsRes / diagonalCurRes;
	}
}

static const unsigned int xAbsResCompare = 1920;
static const unsigned int yAbsResCompare = 1080;

static double getResizeOtherResolutionCoef() {
	DEVMODEW dm;
	long retval = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	int xAbsRes = dm.dmPelsWidth;
	int yAbsRes = dm.dmPelsHeight;

	double diagonalAbsRes = sqrt(pow(xAbsRes, 2) + pow(yAbsRes, 2));
	double diagonalAbsResCompare = sqrt(pow(xAbsResCompare, 2) + pow(yAbsResCompare, 2));

	return diagonalAbsRes / diagonalAbsResCompare;
}

static const double sameRatioCoef = getResizeCoef(true);
static const double diffRatioCoef = getResizeCoef(false);

static const bool resizeConst = true;
static const double resizeCoef = 3.10;
static const unsigned int waitToCloseHack = 2000;
