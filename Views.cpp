#include "Views.h"

void Views::setCursorPosition(const int& posX, const int& posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}

void Views::setBoad(Board _board)
{
	board = _board;
}

void Views::setColor(int color)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
}

void Views::dispBorder(Point origin, int width, int height)
{
	int x0 = origin.getX();
	int y0 = origin.getY();

	for (int i = 0; i < width; i++)
	{
		setCursorPosition(x0 + i, y0);
		cout << char(220);
		setCursorPosition(x0 + width - i, y0 + height);
		cout << char(220);
		Sleep(1);
	}
	for (int i = 0; i < height; i++)
	{
		setCursorPosition(x0, y0 + height - i);
		cout << char(219);
		setCursorPosition(x0 + width, y0 + i + 1);
		cout << char(219);
		Sleep(1);
	}
	setCursorPosition(x0 + width, y0);
	cout << char(220);
}

void Views::dispSpaceSquare(Point origin, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			setCursorPosition(origin.getX() + i, origin.getY() + j);
			cout << ' ';
		}
		Sleep(10);
	}
}


void Views::dispMenu()
{
	int i = 0;
	dispBorder({ 30, 5 }, 60, 20);
	setCursorPosition(58, 7);
	cout << "MENU";



	setCursorPosition(55, 10);
	cout << ++i << ". Resume";
	setCursorPosition(55, 12);
	cout << ++i << ". New Game";
	setCursorPosition(55, 14);
	cout << ++i << ". List Match";
	setCursorPosition(55, 16);
	cout << ++i << ". Replay";
	setCursorPosition(55, 18);
	cout << ++i << ". List Player";
	setCursorPosition(55, 20);
	cout << ++i << ". About us";
	setCursorPosition(55, 23);
}


void Views::dispGame(Match match, Point origin, int width, int height)
{
	system("cls");
	int x0 = origin.getX();
	int y0 = origin.getY();
	dispBorder(origin, width, height);
	for (int i = 1; i <= height; i++)
	{
		setCursorPosition(x0 + 85, y0 + i);
		cout << char(219);
		Sleep(1);
	}

	for (int i = 85 + 1; i <= width - 1; i++)
	{
		setCursorPosition(x0 + i, y0 + 5);
		cout << char(22);
		setCursorPosition(x0 + i, y0 + 20);
		cout << char(22);
		setCursorPosition(x0 + i, y0 + height - 7);
		cout << char(22);
		Sleep(1);

	}

	setCursorPosition(x0 + 115, y0 + 3);
	cout << "Infomation";
	setCursorPosition(x0 + 90, y0 + 7);
	cout << "Player 1";
	setCursorPosition(x0 + 90, y0 + 9);
	cout << "Name: " << match.getPlayer1().getName();
	setCursorPosition(x0 + 90, y0 + 11);
	cout << "Win/Draw/Lose: " << match.getPlayer1().getWin() << "/" << match.getPlayer1().getDraw() << "/" << match.getPlayer1().getLose();
	setCursorPosition(x0 + 90, y0 + 13);
	cout << "Rank: " << match.getPlayer1().getWinRate() << "%";

	setCursorPosition(x0 + 130, y0 + 7);
	cout << "Player 2";
	setCursorPosition(x0 + 130, y0 + 9);
	cout << "Name: " << match.getPlayer2().getName();
	setCursorPosition(x0 + 130, y0 + 11);
	cout << "Win/Draw/Lose: " << match.getPlayer2().getWin() << "/" << match.getPlayer2().getDraw() << "/" << match.getPlayer2().getLose();
	setCursorPosition(x0 + 130, y0 + 13);
	cout << "Rank: " << match.getPlayer2().getWinRate() << "%";



	setCursorPosition(x0 + 90, y0 + height - 5);
	cout << "Click to play";
	setCursorPosition(x0 + 90, y0 + height - 3);
	cout << "Enter \"ESC\" key to return MENU ";
	setCursorPosition(x0 + 130, y0 + height - 5);
	cout << "Enter \"u\" to UNDO";
	setCursorPosition(x0 + 130, y0 + height - 3);
	cout << "Enter \"r\" to REDO";

}

void Views::dispDraw(Match match)
{
	int i, j, k;
	for (i = 0; i <= 19 * 2; i++)
	{
		if (i <= 19)
		{
			j = 0;
			k = i;
		}
		else
		{
			j = i - 19;
			k = 19;
		}
		for (; j <= k; j++)
		{
			match.getBoard().plotCaro(j, i - j, 219);
		}
		Sleep(10);
	}


	dispSpaceSquare({ match.getBoard().getOrigin().getX() + 15, match.getBoard().getOrigin().getY() + 14 }, 55, 11);

	setCursorPosition(match.getBoard().getOrigin().getX() + 25, match.getBoard().getOrigin().getY() + 18);
	cout << "Draw";
}

void Views::dispWin(Match match, char type, Point para1, int para2, int para3)
{
	if (type == 1)
	{
		for (int i = para2; i <= para3; i++)
		{
			board.plotCaro(i, match.getVctMove().back().getY(), 219);
			Sleep(200);
		}
	}
	else if (type == 2)
	{
		for (int i = para2; i <= para3; i++)
		{
			board.plotCaro(match.getVctMove().back().getX(), i, 219);
			Sleep(200);
		}
	}
	else if (type == 3)
	{
		for (int i = 0; para2 + i <= para3; i++)
		{
			board.plotCaro(para2 + i, match.getVctMove().back().getY() - (match.getVctMove().back().getX() - para2) + i, 219);
			Sleep(200);
		}
	}
	else if (type == 4)
	{
		for (int i = 0; para2 + i <= para3; i++)
		{
			board.plotCaro(para2 + i, match.getVctMove().back().getY() + (match.getVctMove().back().getX() - para2) - i, 219);
			Sleep(200);
		}
	}
	Sleep(1000);
	int i, j, k;
	for (i = 0; i <= 19 * 2; i++)
	{
		if (i <= 19)
		{
			j = 0;
			k = i;
		}
		else
		{
			j = i - 19;
			k = 19;
		}
		for (; j <= k; j++)
		{
			match.getBoard().plotCaro(j, i - j, 219);
		}
		Sleep(20);
	}


	dispSpaceSquare({ match.getBoard().getOrigin().getX() + 15, match.getBoard().getOrigin().getY() + 14 }, 55, 11);

	setCursorPosition(match.getBoard().getOrigin().getX() + 27, match.getBoard().getOrigin().getY() + 18);
	if (match.getTurn() == 1)
	{
		cout << "   X WIN <=> " << match.getPlayer1().getName() << " IS WINNER   ";
		setCursorPosition(5 + 90, 0 + 11);
		cout << "Win/Draw/Lose: " << match.getPlayer1().getWin() + 1 << "/" << match.getPlayer1().getDraw() << "/" << match.getPlayer1().getLose();
		setCursorPosition(5 + 130, 0 + 11);
		cout << "Win/Draw/Lose: " << match.getPlayer2().getWin() << "/" << match.getPlayer2().getDraw() << "/" << match.getPlayer2().getLose() + 1;
	}
	else
	{
		cout << "   O WIN <=> " << match.getPlayer2().getName() << " IS WINNER   ";
		setCursorPosition(5 + 90, 0 + 11);
		cout << "Win/Draw/Lose: " << match.getPlayer1().getWin() << "/" << match.getPlayer1().getDraw() << "/" << match.getPlayer1().getLose() + 1;
		setCursorPosition(5 + 130, 0 + 11);
		cout << "Win/Draw/Lose: " << match.getPlayer2().getWin() + 1 << "/" << match.getPlayer2().getDraw() << "/" << match.getPlayer2().getLose();
	}
	setCursorPosition(match.getBoard().getOrigin().getX() + 27, match.getBoard().getOrigin().getY() + 20);
	cout << "Enter 'ESC' key to continute...";
}

void Views::dispMatch(Match match)
{
	cout << match.getPlayer1().getName() << match.getPlayer2().getName();
}

void Views::setConsoleWindow(int w, int h)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, w, h, TRUE);
}