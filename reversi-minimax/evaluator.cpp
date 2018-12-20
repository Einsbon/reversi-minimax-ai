#pragma once
#include "evaluator.h"

const int evaluateBoard[8][8] = {
	{99, -8,  8,  6,  6,  8, -8, 99},
	{-8,-24, -4, -3, -3, -4, -24,-8},
	{ 8, -4,  7,  4,  4,  7, -4,  8},
	{ 6, -3,  4,  0,  0,  4, -3,  6},
	{ 6, -3,  4,  0,  0,  4, -3,  6},
	{ 8, -4,  7,  4,  4,  7, -4,  8},
	{-8,-24, -4, -3, -3, -4, -24,-8},
	{99, -8,  8,  6,  6,  8, -8, 99},
};

int Evaluator::evaluate(Board &board, bool isBlack) {
	if (board.getTurnCount() == 64) //판이 다 찬 경우.
	{
		int blackCount = 0;
		int whiteCount = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board.getPlayingBoard(j, i) == 1) {
					blackCount++;
				}
			}
		}
		if (blackCount > 32) //검은색이 더 많은 경우.
		{
			if (isBlack) return (999+ blackCount); else return (-999 - blackCount);
		}
		else if (blackCount == 32) //흰색과 검은색이 갯수 같은 경우.
		{
			return 0;
		}
		else //흰색이 더 많은 경우.
		{
			if (isBlack) return (-999+blackCount); else return (999 - blackCount);
		}
	}
	else
	{
		int score = 0;
		if (isBlack) // 검은색의 입장인 경우. 검 +, 백 -
		{
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board.getPlayingBoard(j, i) == 1) {
						score += evaluateBoard[i][j];
					}
					else if (board.getPlayingBoard(j, i) == 2)
					{
						score -= evaluateBoard[i][j];
					}
				}
			}
		}
		else // 흰색의 입장인 경우. 검 -, 백 +
		{
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board.getPlayingBoard(j, i) == 1) {
						score -= evaluateBoard[i][j];
					}
					else if (board.getPlayingBoard(j, i) == 2)
					{
						score += evaluateBoard[i][j];
					}
				}
			}
		}
		return score;
	}
}