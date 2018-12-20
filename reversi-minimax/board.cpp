#include <iostream>
#include "board.h"

Board::Board()
{
	playingBoard = new int*[8];
	movableBoard = new bool*[8];
	for (int i = 0; i < 8; i++)
	{
		playingBoard[i] = new int[8];
		movableBoard[i] = new bool[8];
	}
	resetBoard();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		delete[] playingBoard[i];
		delete[] movableBoard[i];
	}
	delete[] playingBoard;
	delete[] movableBoard;
}

Board::Board(Board & B)
{
	playingBoard = new int*[8];
	movableBoard = new bool*[8];
	for (int i = 0; i < 8; i++)
	{
		playingBoard[i] = new int[8];
		movableBoard[i] = new bool[8];
	}

	isBlack = B.isBlack;
	boardCopy<int>(playingBoard, B.playingBoard);
	boardCopy<bool>(movableBoard, B.movableBoard);
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			playingBoard[i][j] = B.playingBoard[i][j];
			movableBoard[i][j] = B.movableBoard[i][j];
		}
	}
}

void Board::setBoard(Board & B)
{
	this->isBlack = B.isBlack;
	boardCopy<int>(this->playingBoard, B.playingBoard);
	boardCopy<bool>(this->movableBoard, B.movableBoard);
}

void Board::resetBoard()
{
	turnCount = 4;
	isBlack = true; // ó���� �������� ���� ����.
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			playingBoard[i][j] = 0;
			movableBoard[i][j] = false;
		}
	}
	playingBoard[3][3] = 1;
	playingBoard[4][4] = 1;
	playingBoard[3][4] = 2;
	playingBoard[4][3] = 2;


	movableBoard[4][2] = true;
	movableBoard[5][3] = true;
	movableBoard[2][4] = true;
	movableBoard[3][5] = true;
}

int Board::movableCheck()
{
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			movableBoard[i][j] = putableCheck(j, i);
			if (movableBoard[i][j] == true) {
				count++;
			}
		}
	}
	return count;
}

void Board::put(int x, int y)
{
	turnCount++;
	int color;
	if (isBlack == true)
	{
		color = 1;
	}
	else {
		color = 2;
	}

	playingBoard[y][x] = color;

	//�Ʒ��� ����
	int i = 1;
	while (((y + i) < 8) && ((playingBoard[y + i][x] == 1) | (playingBoard[y + i][x] == 2))) //���� ����������
	{
		if (playingBoard[y + i][x] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y + j][x] = color;
			}
			break;
		}
		i++;
	}
	//���� ����
	i = 1;
	while (((y - i) > -1)&&(playingBoard[y - i][x] == 1 | playingBoard[y - i][x] == 2)) //���� ����������
	{
		if (playingBoard[y - i][x] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y - j][x] = color;
			}
			break;
		}
		i++;
	}
	//����
	i = 1;
	while (((x + i) < 8)&&(playingBoard[y][x + i] == 1 | playingBoard[y][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y][x + i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y][x + j] = color;
			}
			break;
		}
		i++;
	}
	//��
	i = 1;
	while (((x - i) > -1)&&(playingBoard[y][x - i] == 1 | playingBoard[y][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y][x - i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y][x - j] = color;
			}
			break;
		}
		i++;
	}
	//�� ��
	i = 1;
	while ((((y - i) > -1) && ((x - i) > -1))&&(playingBoard[y - i][x - i] == 1 | playingBoard[y - i][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y - i][x - i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y - j][x - j] = color;
			}
			break;
		}
		i++;
	}
	//���� ��
	i = 1;
	while ((((y - i) > -1) && ((x + i) < 8))&&(playingBoard[y - i][x + i] == 1 | playingBoard[y - i][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y - i][x + i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y - j][x + j] = color;
			}
			break;
		}
		i++;
	}
	//�� �Ʒ�
	i = 1;
	while ((((y + i) < 8) && ((x - i) > -1))&&(playingBoard[y + i][x - i] == 1 | playingBoard[y + i][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y + i][x - i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y + j][x - j] = color;
			}
			break;
		}
		i++;
	}
	//���� �Ʒ�
	i = 1;
	while ((((y + i) < 8) && ((x + i) < 8))&&(playingBoard[y + i][x + i] == 1 | playingBoard[y + i][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y + i][x + i] == color)
		{
			for (int j = 1; j < i; j++)
			{
				playingBoard[y + j][x + j] = color;
			}
			break;
		}
		i++;
	}
	isBlack = !isBlack;
}

bool Board::putableCheck(int x, int y) const
{
	if (playingBoard[y][x] != 0) { // �̹� ���� ���������� ���� �Ұ�.
		return false;
	}

	int myColor;
	int opponentColor;

	if (isBlack == true)
	{
		myColor = 1;
		opponentColor = 2;
	}
	else {
		myColor = 2;
		opponentColor = 1;
	}

	//put �Լ��� �����. ���� ���� ������ �� �ִٸ� true. 
	//���� ���� ������ �� ������ false.

	//�Ʒ��� ����
	int i = 1;
	while (((y + i) < 8) && (playingBoard[y + i][x] == 1 | playingBoard[y + i][x] == 2)) //���� ����������
	{
		if (playingBoard[y + i][x] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y + j][x] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//���� ����
	i = 1;
	while (((y - i) > -1) && (playingBoard[y - i][x] == 1 | playingBoard[y - i][x] == 2) ) //���� ����������
	{
		if (playingBoard[y - i][x] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y - j][x] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//����
	i = 1;
	while (((x + i) < 8)&&(playingBoard[y][x + i] == 1 | playingBoard[y][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y][x + i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y][x + j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//��
	i = 1;
	while (((x - i) > -1)&&(playingBoard[y][x - i] == 1 | playingBoard[y][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y][x - i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y][x - j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//�� ��
	i = 1;
	while ((((y - i) > -1) && ((x - i) > -1))&&(playingBoard[y - i][x - i] == 1 | playingBoard[y - i][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y - i][x - i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y - j][x - j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//���� ��
	i = 1;
	while ((((y - i) > -1) && ((x + i) < 8))&&(playingBoard[y - i][x + i] == 1 | playingBoard[y - i][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y - i][x + i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y - j][x + j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//�� �Ʒ�
	i = 1;
	while ((((y + i) < 8) && ((x - i) > -1))&&(playingBoard[y + i][x - i] == 1 | playingBoard[y + i][x - i] == 2)) //���� ����������
	{
		if (playingBoard[y + i][x - i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y + j][x - j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}
	//���� �Ʒ�
	i = 1;
	while ((((y + i) < 8) && ((x + i) < 8))&&(playingBoard[y + i][x + i] == 1 | playingBoard[y + i][x + i] == 2)) //���� ����������
	{
		if (playingBoard[y + i][x + i] == myColor)
		{
			for (int j = 1; j < i; j++)
			{
				if (playingBoard[y + j][x + j] == opponentColor) return true;
			}
			break;
		}
		i++;
	}

	return false;
}

template <typename T>
void Board::boardCopy(T **copyBoard, T ** const pboard)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			copyBoard[i][j] = pboard[i][j];
		}
	}
}

void Board::changeTurn(void)
{
	isBlack = !isBlack;
}

int Board::getPlayingBoard(int xpos, int ypos) const
{
	return playingBoard[ypos][xpos];
}

bool Board::getMovableBoard(int xpos, int ypos) const
{
	return movableBoard[ypos][xpos];
}

bool Board::getIsBlackTurn(void) const
{
	return isBlack;
}

int Board::getTurnCount(void) const
{
	return turnCount;
}