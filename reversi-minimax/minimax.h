#pragma once
#include "board.h"
#include "evaluator.h"
#include <iostream>

#include <cstdlib>
#include <ctime>


class PredictionBoard : public  Board
{
public:
	int **nextArray; //������ �� �ִ� [x,y] ��
	int nextCount; //������ �� �ִ� ��� ����

	PredictionBoard(Board &B);
	PredictionBoard(PredictionBoard &P);

	~PredictionBoard();

	void nextCheck();
};

class AI {
public:
	int sameCount = -1;
	int bestChoiceIndex[10] = { 0,0,0,0,0,0,0,0,0,0 };
	//int scoreBoard[8][8] = { 0, };
	PredictionBoard firstBoard;

	AI(Board &B);
	AI(PredictionBoard &P);

	void set(Board &B);

	void startMinimax(int depth, bool isBlack);
	int minimize(PredictionBoard pred, int depth, bool isBlack);
	int maximize(PredictionBoard pred, int depth, bool isBlack);
};