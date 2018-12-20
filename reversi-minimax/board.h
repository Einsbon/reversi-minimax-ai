#pragma once

class Board
{
private:
	int turnCount;
	bool isBlack; //검은색이 놓을 차례이거나 검은색이 놓는 경우에 참.
	int **playingBoard; // 8*8 크기의 배열. 현재 플레이하고있는 보드를 나타냄. 무=0. 흑=1.백=2
	bool **movableBoard; // 8*8 크기의 배열. 그 좌표가 다음에 놓을 수 있는 경우 true.
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
	bool getIsBlackTurn(void) const; //검은색이 놓을 차례이면 true
	int getTurnCount(void) const; //검은색이 놓을 차례이면 true
};