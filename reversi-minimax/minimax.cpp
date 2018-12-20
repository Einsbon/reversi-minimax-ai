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
//����� �� �� �ּ� ���� ����.
int AI::minimize(PredictionBoard pred, int depth, bool isBlack)
{
	if (depth == 1) { // ���̰� 1�̸� �̹� �������� ����.
		pred.nextCheck();
		int minScore = 9999; //�񱳸� ���� ��. ū ������ ����.
		int eval;        //���� �ű� ���� �ӽ� ����.

		if (pred.nextCount == 0) //�̹��� �� �� �ִ� ���� ������, �̹� ������ ���� ��ȯ.
		{
			pred.changeTurn();
			minScore = Evaluator::evaluate(pred, isBlack);
			return minScore;
		}

		for (int i = 0; i < pred.nextCount; i++) {
			//���� ���� ���¸� ����� ������ �ű�.
			PredictionBoard nextPred(pred);
			nextPred.put(pred.nextArray[i][0], pred.nextArray[i][1]);
#ifdef PRINT_MINIMAX
			std::cout << "Depth: 1   X: " << pred.nextArray[i][0] + 1;
			std::cout << "   Y: " << pred.nextArray[i][1] + 1;
			std::cout << "   Eval: " << Evaluator::evaluate(nextPred, isBlack) << std::endl;
#endif // PRINT_MINIMAX

			eval = Evaluator::evaluate(nextPred, isBlack);

			//���� ���� ����
			if (eval < minScore) {
				minScore = eval;
			}
		}
#ifdef PRINT_MINIMAX
		std::cout << "minScore: " << minScore << std::endl;
#endif // PRINT_MINIMAX
		return minScore;
	}
	else { //���̰� 2 �̻��̸� ���������� ������ ����
		pred.nextCheck();
		int minScore = 9999;
		int eval;

		if (pred.nextCount == 0) //�̹��� �� �� �ִ� ���� ������, �������� �ٷ� �ѱ�.
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
//����� �� �� �ִ� ���� ����.
int AI::maximize(PredictionBoard pred, int depth, bool isBlack)
{
	if (depth == 1) {
		pred.nextCheck();
		int maxScore = -9999;
		int eval;

		if (pred.nextCount == 0) //�̹��� �� �� �ִ� ���� ������, �������� �ٷ� �ѱ�.
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

			//ū ���� ����
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

		if (pred.nextCount == 0) //�̹��� �� �� �ִ� ���� ������, �������� �ٷ� �ѱ�.
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