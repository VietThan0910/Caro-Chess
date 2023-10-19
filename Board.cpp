#include "Board.h"

void Board::set(Point _origin, int _rows, int _columns)
{
	origin = _origin;
	rows = _rows;
	columns = _columns;
}
int Board::getRows() { return rows; }
int Board::getColumns() { return columns; }
Point Board::getOrigin() { return origin; }
void Board::setCursorPosition(const int& posX, const int& posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}
void Board::plotBoard()
{
	int x0 = origin.getX();
	int y0 = origin.getY();

	setCursorPosition(x0, y0);
	for (int i = 1; i <= columns; i++)
	{
		setCursorPosition(x0 + i * 4 - 3, y0);
		cout << char(205) << char(205) << char(205) << char(209);
		setCursorPosition(x0 + columns * 4 - i * 4, y0 + 2 * rows);
		cout << char(207) << char(205) << char(205) << char(205);
		if (i == columns)
		{
			setCursorPosition(x0 + i * 4 - 3, y0);
			cout << char(205) << char(205) << char(205) << char(187);
			setCursorPosition(x0 + columns * 4 - i * 4, y0 + 2 * rows);
			cout << char(200) << char(205) << char(205) << char(205);
		}
		Sleep(30);
	}
	for (int i = 1; i <= rows; i++)
	{
		setCursorPosition(x0 + columns * 4, y0 + 2 * i - 1);
		cout << char(186);
		setCursorPosition(x0 + columns * 4, y0 + 2 * i);
		cout << char(182);

		setCursorPosition(x0, y0 + 2 * rows - 2 * i + 1);
		cout << char(186);
		setCursorPosition(x0, y0 + 2 * rows - 2 * i);
		cout << char(199);
		if (i == rows)
		{
			setCursorPosition(x0 + columns * 4, y0 + 2 * i - 1);
			cout << char(186);
			setCursorPosition(x0 + columns * 4, y0 + 2 * i);
			cout << char(188);

			setCursorPosition(x0, y0 + 2 * rows - 2 * i + 1);
			cout << char(186);
			setCursorPosition(x0, y0 + 2 * rows - 2 * i);
			cout << char(201);
		}
		Sleep(30);
	}

	for (int i = 1; i <= columns; i++)
	{
		for (int j = 1; j <= rows; j++)
		{
			if (j != rows)
			{
				setCursorPosition(x0 + 4 * i - 3, y0 + 2 * j);
				if (i != columns)
				{
					cout << char(196) << char(196) << char(196) << char(197);
					setCursorPosition(x0 + 4 * i, y0 + 2 * j - 1);
					cout << char(179);
				}
				else
				{
					cout << char(196) << char(196) << char(196);
				}
			}
			else
			{
				if (i != columns)
				{
					setCursorPosition(x0 + 4 * i, y0 + 2 * j - 1);
					cout << char(179);
				}
			}
		}
		Sleep(20);
	}
}
void Board::plotCaro(int x, int y, char type)
{
	int x0 = origin.getX();
	int y0 = origin.getY();
	setCursorPosition(x0 + y * 4 + 2, y0 + x * 2 + 1);
	cout << type;
}