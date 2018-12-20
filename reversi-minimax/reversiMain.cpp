#include <iostream>
#include <Windows.h> //콘솔 텍스트의 색을 바꾸기 위해
#include <conio.h> //_getch()를 사용하기 위해
#include "board.h"
#include "evaluator.h"
#include "minimax.h"

enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_Q,
	KEY_R,
	KEY_H,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_A,
};


int keyInput(void)
{
	char ch;
	ch = _getch(); //키보드 입력 --> 문자

	switch (ch)
	{
	case 72: //위화살표
		return KEY_UP;
	case 75: //왼쪽화살표
		return KEY_LEFT;
	case 77: //오른쪽
		return KEY_RIGHT;
	case 80: //아래쪽
		return KEY_DOWN;
	case 32: //스페이스바
		return KEY_SPACE;
	case 'h':
		return KEY_H;
	case 'a':
		return KEY_A;
	case 'r':
		return KEY_R;
	case 'q':
		return KEY_Q;
	case '4':
		return KEY_4;
	case '5':
		return KEY_5;
	case '6':
		return KEY_6;
	case '7':
		return KEY_7;
	case '8':
		return KEY_8;
	}
	return -1;
}

void dispBoard(Board &board, int cursorX, int cursorY, int recentX, int recentY)
{
	int blackCount = 0;
	int whiteCount = 0;
	bool isBlack = board.getIsBlackTurn();

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("▒▒▒▒▒▒▒▒▒▒\n");
	for (int a = 0; a < 8; a++)
	{
		printf("▒");
		for (int b = 0; b < 8; b++)
		{
			if (board.getPlayingBoard(b,a) == 0)
			{
				if (board.getMovableBoard(b,a) == false)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 40);
					if ((b == cursorX) & (a == cursorY))
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 168);
					}
					printf("□");
				}
				else
				{
					if (isBlack)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);
						if ((b == cursorX) & (a == cursorY))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
						}
						printf("※");
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						if ((b == cursorX) & (a == cursorY))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 175);
						}
						printf("※");
					}
				}
			}
			else if (board.getPlayingBoard(b,a) == 1)
			{
				blackCount += 1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);
				if ((b == cursorX) & (a == cursorY))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
				}
				if ((b == recentX) &(a == recentY))
				{
					printf("◆");
				}
				else
				{
					printf("●");
				}
			}
			else if (board.getPlayingBoard(b,a) == 2)
			{
				whiteCount += 1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
				if ((b == cursorX) & (a == cursorY))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 175);
				}
				if ((b == recentX) & (a == recentY))
				{
					printf("◆");
				}
				else
				{
					printf("●");
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("▒\n");
	}
	printf("▒▒▒▒▒▒▒▒▒▒\n\n");
	std::cout << "Black : " << blackCount << std::endl;
	std::cout << "White : " << whiteCount << std::endl;
	if (board.getTurnCount() == 64) {
		if (blackCount > 32) {
			std::cout << "Black Win" << std::endl << std::endl;
		}
		else if (blackCount == 32) {
			std::cout << "draw " << std::endl << std::endl;
		}
		else
		{
			std::cout << "White Win" << std::endl << std::endl;
		}
	}
	else {
		if (isBlack == true) {
			std::cout << "Next turn : Black" << std::endl << std::endl;
		}
		else {
			std::cout << "Next turn : White" << std::endl << std::endl;
		}
	}
}

void printHelp(void) {
	std::cout << "조작법:" << std::endl;
	std::cout << "- 방향키로 커서 조작. 스페이스바로 놓기. " << std::endl;
	std::cout << "- a 키로 ai를 끄거나 켬. 그다음 w를 누르면 하얀색의 인공지능, b를 누르면 흑색의 인공지능." << std::endl;
	std::cout << "- 숫자 4~8 키로 ai가 어느 깊이까지 예측을 할지 설정. 기본=4. " << std::endl;
	std::cout << "- r 키로 재시작. " << std::endl << std::endl;
}

void dispAIState(bool useAI, bool aiIsBlack, int depth) {
	std::cout << "AI: ";
	if (useAI) std::cout << "on "; else std::cout << "off ";
	std::cout << std::endl;
	if (aiIsBlack) std::cout << "(black's ai)"; else std::cout << "white's ai";
	std::cout << std::endl;
	std::cout << "Depth: " << depth << std::endl << std::endl;
}

int main(void)
{
	srand((unsigned int)std::time(NULL));
	Board board;

	AI ai(board);
	int minimaxDepth = 4;

	int cursorX = 0;
	int cursorY = 0;
	int recentX = -1;
	int recentY = -1;

	bool useAI = true;
	bool aiIsBlack = false;

	dispBoard(board, cursorX, cursorY, recentX, recentY);

	int key;
	while (true)
	{
		key = keyInput();
		switch (key)
		{
		case KEY_UP:
			cursorY--;
			if (cursorY < 0) cursorY++;
			break;
		case KEY_DOWN:
			cursorY++;
			if (cursorY > 7) cursorY--;
			break;
		case KEY_RIGHT:
			cursorX++;
			if (cursorX > 7) cursorX--;
			break;
		case KEY_LEFT:
			cursorX--;
			if (cursorX < 0) cursorX++;
			break;
		case KEY_SPACE:
			if (board.getMovableBoard(cursorX, cursorY) == true)
			{
				board.put(cursorX, cursorY);
				recentX = cursorX;
				recentY = cursorY;
				if (board.movableCheck() == 0) {
					board.changeTurn();
					board.movableCheck();
				}

			}
			break;
		case KEY_H:
			board.changeTurn();
			board.movableCheck();
			break;
		case KEY_Q:
			break;
		case KEY_R:
			board.resetBoard();
			break;
		case KEY_A:
			useAI = !useAI;
			break;
		case KEY_4:
			minimaxDepth = 4;
			break;
		case KEY_5:
			minimaxDepth = 5;
			break;
		case KEY_6:
			minimaxDepth = 6;
			break;
		case KEY_7:
			minimaxDepth = 7;
			break;
		case KEY_8:
			minimaxDepth = 8;
			break;
		}
		dispBoard(board, cursorX, cursorY, recentX, recentY);
		dispAIState(useAI, aiIsBlack, minimaxDepth);
		printHelp();
		

		if (useAI) {
			if ((aiIsBlack && board.getIsBlackTurn()) || (!aiIsBlack && !board.getIsBlackTurn())) {
				std::cout << "인공지능이 생각중..." << std::endl;
				ai.set(board);
				ai.startMinimax(minimaxDepth, board.getIsBlackTurn());

				if (ai.firstBoard.nextCount == 0)
				{
					continue;
				}
				int index = rand() % (ai.sameCount+1);
				recentX = ai.firstBoard.nextArray[ai.bestChoiceIndex[index]][0];
				recentY = ai.firstBoard.nextArray[ai.bestChoiceIndex[index]][1];
				
				
				board.put(recentX, recentY);
				board.movableCheck();


				dispBoard(board, cursorX, cursorY, recentX, recentY);
				dispAIState(useAI, aiIsBlack, minimaxDepth);
				printHelp();
			}
		}

	}
}
