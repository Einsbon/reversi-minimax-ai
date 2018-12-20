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
	if (board.getTurnCount() == 64) //���� �� �� ���.
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
		if (blackCount > 32) //�������� �� ���� ���.
		{
			if (isBlack) return (999+ blackCount); else return (-999 - blackCount);
		}
		else if (blackCount == 32) //����� �������� ���� ���� ���.
		{
			return 0;
		}
		else //����� �� ���� ���.
		{
			if (isBlack) return (-999+blackCount); else return (999 - blackCount);
		}
	}
	else
	{
		int score = 0;
		if (isBlack) // �������� ������ ���. �� +, �� -
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
		else // ����� ������ ���. �� -, �� +
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