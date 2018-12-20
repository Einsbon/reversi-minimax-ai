#pragma once

class Board
{
private:
	int turnCount;
	bool isBlack; //�������� ���� �����̰ų� �������� ���� ��쿡 ��.
	int **playingBoard; // 8*8 ũ���� �迭. ���� �÷����ϰ��ִ� ���带 ��Ÿ��. ��=0. ��=1.��=2
	bool **movableBoard; // 8*8 ũ���� �迭. �� ��ǥ�� ������ ���� �� �ִ� ��� true.
public:
	Board(void);
	Board(Board &B); 
	~Board(void);
	void put(int xpos, int ypos);
	bool putableCheck(int xpos, int ypos) const;
	int movableCheck();
	void setBoard(Board &B);
	void resetBoard(void);
	template <typename T> void boardCopy(T **copyBoard, T ** const pboard);
	void changeTurn(void);
	int getPlayingBoard(int xpos, int ypos) const;
	bool getMovableBoard(int xpos, int ypos) const;
	bool getIsBlackTurn(void) const; //�������� ���� �����̸� true
	int getTurnCount(void) const; //�������� ���� �����̸� true
};