#include "4ryad.h"
#include <iostream>
using namespace std;

const int Field::di[] = { 1, 0, 1, 1 };
const int Field::dj[] = { 0, 1, -1, 1 };

Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;
    gameOver = false;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column) {
    if (gameOver || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;  // ИСПРАВЛЕНО: i - это индекс колонки
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)  // ИСПРАВЛЕНО: j - это индекс строки
    {
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            if (!gameOver)
                isRedTurn = !isRedTurn;
            return true;
        }
    }
    return false;
}

void Field::checkWinner()
{
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;

            for (int k = 0; k < DIR_NUMBER; k++) {
                int length = 0;
                for (int step = 0; step < WIN_LENGTH; step++) {
                    int iline = i + step * di[k];
                    int jline = j + step * dj[k];

                    if (iline < 0 || iline >= FIELD_WIDTH ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;

                    if (cells[iline][jline] != start)
                        break;

                    length++;
                }
                if (length == WIN_LENGTH) {
                    gameOver = true;
                    winner = start;
                    return;
                }
            }
        }
    }
}

bool Field::isWon(bool red) const {
    Cell target = red ? RED : YELLOW;
    return gameOver && winner == target;  // ИСПРАВЛЕНО: проверяем что победитель - нужный игрок
}

bool Field::isOver() const {
    if (gameOver)
        return true;

    // Проверяем, заполнено ли поле
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;

    return true;  // Поле заполнено - ничья
}

void Field::print() const {
    for (int j = 0; j < FIELD_HEIGHT; j++) {  // ИСПРАВЛЕНО: сначала строки
        for (int i = 0; i < FIELD_WIDTH; i++) {  // ИСПРАВЛЕНО: потом колонки
            if (cells[i][j] == RED)
                cout << "R ";
            else if (cells[i][j] == YELLOW)
                cout << "Y ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
}

void Field::printResult() const {
    if (gameOver) {
        if (winner == RED) {
            cout << "Победил КРАСНЫЙ игрок!" << endl;
        }
        else if (winner == YELLOW) {
            cout << "Победил ЖЕЛТЫЙ игрок!" << endl;
        }
    }
    else if (isOver()) {
        cout << "Ничья!" << endl;
    }
}

bool Field::isRedTurnNow() const {
    return isRedTurn;
}

Cell Field::getCell(int i, int j) const {
    if (i >= 0 && i < FIELD_WIDTH && j >= 0 && j < FIELD_HEIGHT) {
        return cells[i][j];
    }
    return EMPTY;
}