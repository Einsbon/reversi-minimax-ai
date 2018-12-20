#include "minimax.h"

//#define PRINT_MINIMAX

PredictionBoard::PredictionBoard(Board &B) : Board(B) {

}

PredictionBoard::PredictionBoard(PredictionBoard &P) : Board(P) {

}

PredictionBoard::~PredictionBoard() {
	for (int i = 0; i < nextCount; i++)
	{
		delete[] nextArray[i];
	}
	delete[] nextArray;
}


void PredictionBoard::nextCheck() {
	nextCount = movableCheck();

	nextArray = new int*[nextCount];
	for (int i = 0; i < nextCount; i++) {
		nextArray[i] = new int[2];
	}

	int index = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (getMovableBoard(j, i) == true) {
				nextArray[index][0] = j;
				nextArray[index][1] = i;
				index++;
			}
		}
	}
}

AI::AI(Board &B) : firstBoard(B) {

}

AI::AI(PredictionBoard &P) : firstBoard(P) {

}


void AI::set(Board &B) {
	firstBoard.setBoard(B);
}

void AI::startMinimax(int depth, bool isBlack)
{
	sameCount = 0;
	if (depth == 1) {
		firstBoard.nextCheck();
		int maxScore = -9999;
		int eval;

		for (int i = 0; i < firstBoard.nextCount; i++) {
			PredictionBoard nextPred(firstBoard);
			nextPred.put(firstBoard.nextArray[i][0], firstBoard.nextArray[i][1]);

#ifdef PRINT_MINIMAX
			std::cout << "Depth: 1   X: " << firstBoard.nextArray[i][0] + 1;
			std::cout << "   Y: " << firstBoard.nextArray[i][1] + 1;
			std::cout << "   Eval: " << Evaluator::evaluate(nextPred, isBlack) << std::endl;
#endif // PRINT_MINIMAX

			eval = Evaluator::evaluate(nextPred, isBlack);

			if (eval == maxScore) {
				sameCount++;
				bestChoiceIndex[sameCount] = i;
			}
			else if (eval > maxScore) {
				maxScore = eval;
				sameCount = 0;
				bestChoiceIndex[0] = i;
			}
		}
#ifdef PRINT_MINIMAX
		std::cout << "maxScore: " << maxScore << std::endl;
#endif // PRINT_MINIMAX
	}
	else {
		firstBoard.nextCheck();
		int maxScore = -9999;
		int eval;

		for (int i = 0; i < firstBoard.nextCount; i++) {
			PredictionBoard nextPred(firstBoard);
			nextPred.put(firstBoard.nextArray[i][0], firstBoard.nextArray[i][1]);

#ifdef PRINT_MINIMAX
			for (int j = 1; j < depth; j++) {
				std::cout << ":   ";
			}
			std::cout << "Depth: " << depth;
			std::cout << "   X: " << firstBoard.nextArray[i][0] + 1;
			std::cout << " Y: " << firstBoard.nextArray[i][1] + 1 << std::endl;
#endif // PRINT_MINIMAX
			eval = minimize(nextPred, depth - 1, isBlack);

			if (eval == maxScore) {
				sameCount++;
				bestChoiceIndex[sameCount] = i;
			}
			else if (eval > maxScore) {
				maxScore = eval;
				sameCount = 0;
				bestChoiceIndex[0] = i;
			}
		}
#ifdef PRINT_MINIMAX
		for (int j = 1; j < depth; j++) {
			std::cout << ":   ";
		}
		std::cout << "maxScore: " << maxScore << std::endl;
#endif // PRINT_MINIMAX
	}
}
//경우의 수 중 최소 값을 리턴.
int AI::minimize(PredictionBoard pred, int depth, bool isBlack)
{
	if (depth == 1) { // 깊이가 1이면 이번 예측에서 끝냄.
		pred.nextCheck();
		int minScore = 9999; //비교를 위한 값. 큰 값으로 시작.
		int eval;        //점수 매긴 값을 임시 저장.

		if (pred.nextCount == 0) //이번에 둘 수 있는 곳이 없으면, 이번 상태의 점수 반환.
		{
			pred.changeTurn();
			minScore = Evaluator::evaluate(pred, isBlack);
			return minScore;
		}

		for (int i = 0; i < pred.nextCount; i++) {
			//다음 예측 상태를 만들고 점수를 매김.
			PredictionBoard nextPred(pred);
			nextPred.put(pred.nextArray[i][0], pred.nextArray[i][1]);
#ifdef PRINT_MINIMAX
			std::cout << "Depth: 1   X: " << pred.nextArray[i][0] + 1;
			std::cout << "   Y: " << pred.nextArray[i][1] + 1;
			std::cout << "   Eval: " << Evaluator::evaluate(nextPred, isBlack) << std::endl;
#endif // PRINT_MINIMAX

			eval = Evaluator::evaluate(nextPred, isBlack);

			//작은 값을 저장
			if (eval < minScore) {
				minScore = eval;
			}
		}
#ifdef PRINT_MINIMAX
		std::cout << "minScore: " << minScore << std::endl;
#endif // PRINT_MINIMAX
		return minScore;
	}
	else { //깊이가 2 이상이면 다음번까지 예측을 만듦
		pred.nextCheck();
		int minScore = 9999;
		int eval;

		if (pred.nextCount == 0) //이번에 둘 수 있는 곳이 없으면, 다음으로 바로 넘김.
		{
			PredictionBoard nextPred(pred);
			nextPred.changeTurn();
			minScore = maximize(nextPred, depth - 1, isBlack);
			return minScore;
		}

		for (int i = 0; i < pred.nextCount; i++) {
			PredictionBoard nextPred(pred);
			nextPred.put(pred.nextArray[i][0], pred.nextArray[i][1]);
#ifdef PRINT_MINIMAX
			for (int j = 1; j < depth; j++) {
				std::cout << ":   ";
			}
			std::cout << "Depth: " << depth;
			std::cout << "   X: " << pred.nextArray[i][0] + 1;
			std::cout << " Y: " << pred.nextArray[i][1] + 1 << std::endl;
#endif // PRINT_MINIMAX

			eval = maximize(nextPred, depth - 1, isBlack);

			if (eval < minScore) {
				minScore = eval;
			}
		}
#ifdef PRINT_MINIMAX
		for (int j = 1; j < depth; j++) {
			std::cout << ":   ";
		}
		std::cout << "minScore: " << minScore << std::endl;
#endif // PRINT_MINIMAX
		return minScore;
	}
}
//경우의 수 중 최대 값을 리턴.
int AI::maximize(PredictionBoard pred, int depth, bool isBlack)
{
	if (depth == 1) {
		pred.nextCheck();
		int maxScore = -9999;
		int eval;

		if (pred.nextCount == 0) //이번에 둘 수 있는 곳이 없으면, 다음으로 바로 넘김.
		{
			maxScore = Evaluator::evaluate(pred, isBlack);
			return maxScore;
		}

		for (int i = 0; i < pred.nextCount; i++) {
			PredictionBoard nextPred(pred);
			nextPred.put(pred.nextArray[i][0], pred.nextArray[i][1]);
#ifdef PRINT_MINIMAX
			std::cout << "Depth: 1   X: " << pred.nextArray[i][0] + 1;
			std::cout << "   Y: " << pred.nextArray[i][1] + 1;
			std::cout << "   Eval: " << Evaluator::evaluate(nextPred, isBlack) << std::endl;
#endif // PRINT_MINIMAX
			eval = Evaluator::evaluate(nextPred, isBlack);

			//큰 값을 저장
			if (eval > maxScore) {
				maxScore = eval;
			}
		}
#ifdef PRINT_MINIMAX
		std::cout << "maxScore: " << maxScore << std::endl;
#endif // PRINT_MINIMAX
		return maxScore;
	}
	else {
		pred.nextCheck();
		int maxScore = -9999;
		int eval;

		if (pred.nextCount == 0) //이번에 둘 수 있는 곳이 없으면, 다음으로 바로 넘김.
		{
			PredictionBoard nextPred(pred);
			nextPred.changeTurn();
			maxScore = minimize(nextPred, depth - 1, isBlack);
			return maxScore;
		}

		for (int i = 0; i < pred.nextCount; i++) {
			PredictionBoard nextPred(pred);
			nextPred.put(pred.nextArray[i][0], pred.nextArray[i][1]);
#ifdef PRINT_MINIMAX
			for (int j = 1; j < depth; j++) {
				std::cout << ":   ";
			}
			std::cout << "Depth: " << depth;
			std::cout << "   X: " << pred.nextArray[i][0] + 1;
			std::cout << " Y: " << pred.nextArray[i][1] + 1 << std::endl;
#endif // PRINT_MINIMAX
			eval = minimize(nextPred, depth - 1, isBlack);

			if (eval > maxScore) {
				maxScore = eval;
			}
		}
#ifdef PRINT_MINIMAX
		for (int j = 1; j < depth; j++) {
			std::cout << ":   ";
		}
		std::cout << "maxScore: " << maxScore << std::endl;
#endif // PRINT_MINIMAX
		return maxScore;
	}
}