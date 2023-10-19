#include "Controllers.h"

Player* Controllers::checkPlayer(string name)
{
    return models.getPlayerByName(name).second;
}
void Controllers::creatMatch(Board _board, Player& _player1, Player& _player2, int _firstTurn)
{
    models.getMatch().set(_board, _player1, _player2, _firstTurn);
}
std::pair<int, std::pair<int, int>> Controllers::catchEvent(int& loop)// can using reference with "key" variale?
{

    INPUT_RECORD ir[128];
    HANDLE       hStdInput = NULL;
    HANDLE       hStdOutput = NULL;
    HANDLE       hEvent = NULL;
    DWORD        nRead;
    //COORD        xy;

    hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    FlushConsoleInputBuffer(hStdInput);
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE handles[2] = { hEvent, hStdInput };
    while (WaitForMultipleObjects(2, handles, FALSE, INFINITE))
    {
        ReadConsoleInput(hStdInput, ir, 128, &nRead);
        for (size_t i = 0; i < nRead; i++)
        {
            switch (ir[i].EventType)
            {
            case KEY_EVENT:
            {
                if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                {
                    loop = 0;
                    SetEvent(hEvent);
                    
                }
                else if ((char)(ir[i].Event.KeyEvent.uChar.AsciiChar) == 'u')
                {
                    loop = 2;
                    SetEvent(hEvent);
                    
                }
                else if ((char)(ir[i].Event.KeyEvent.uChar.AsciiChar) == 'r')
                {
                    loop = 3;
                    SetEvent(hEvent);
                    
                }
                
                break;
            }
            case MOUSE_EVENT:
                return { (int)ir[i].Event.MouseEvent.dwButtonState & 0x07, {ir[i].Event.MouseEvent.dwMousePosition.X,ir[i].Event.MouseEvent.dwMousePosition.Y } };
                break;
            default:
                loop = 1;
                break;
            }
        }
    };
}

void Controllers::playGame()
{
    views.board = models.getMatch().getBoard();
   // system("cls");
    Point origin = models.getMatch().getBoard().getOrigin();
    Point point;
    int loop = 1;
    int x, y, _x, _y;
    //models.getMatch().getBoard().plotBoard();
    views.setCursorPosition(50, 5); cout << models.getMatch().getID();
    //if (models.getMatch().isCompleted())
    //{
        //models.getMatch().getBoard().plotBoard();
    //}
   // else
    //{
        replay(models.getMatch());
    //}
    
    while (loop)
    {
        pair<int, pair<int, int>> key = catchEvent(loop);
        
        if (key.first == 1)
        {
            //PlaySoundA("click.wav", NULL, SND_FILENAME);
            x = key.second.first;
            y = key.second.second;
            if ((x - models.getMatch().getBoard().getOrigin().getX()) % 4 != 0 && (y - models.getMatch().getBoard().getOrigin().getY()) % 2 != 0)
            {
                _y = (x - models.getMatch().getBoard().getOrigin().getX()) / 4;
                _x = (y - models.getMatch().getBoard().getOrigin().getY()) / 2;
                if (checkAvail(models.getMatch().getBoard(), _x, _y))
                {
                    if ((models.getMatch().getMapCaro()[_x][_y] == '\0'))
                    {
                        if (models.getMatch().getTurn() == 1)
                        {
                            models.getMatch().getBoard().plotCaro(_x, _y, 'X');
                            point.set(_x, _y, 'X');
                            models.getMatch().setCountX(1);
                            models.getMatch().getMapCaro()[_x][_y] = models.getMatch().getTurn();
                        }
                        else
                        {
                            models.getMatch().getBoard().plotCaro(_x, _y, 'O');
                            point.set(_x, _y, 'O');
                            models.getMatch().setCountY(1);
                            models.getMatch().getMapCaro()[_x][_y] = models.getMatch().getTurn();
                        }

                        models.getMatch().getVctMove().push_back(point);
                        models.getMatch().getVctMoveExtra().clear();
                        pair<char, pair<int, int>> checkW = Controllers::checkWin(models.getMatch(), _x, _y);
                        if (checkW.first != -1)
                        {
                            if (checkW.first == 0)
                            {
                                views.dispDraw(models.getMatch());
                                models.getMatch().getPlayer1().raiseDraw();
                                models.getMatch().getPlayer2().raiseDraw();
                            }
                            else
                            {
                                views.dispWin(models.getMatch(), checkW.first, point, checkW.second.first, checkW.second.second);

                                if (models.getMatch().getTurn() == 1)
                                {
                                    models.getMatch().getPlayer1().raiseWin();
                                    models.getMatch().getPlayer2().raiseLose();
                                    models.getPlayerByName(models.getMatch().getPlayer1().getName()).second->raiseWin();
                                    models.getPlayerByName(models.getMatch().getPlayer2().getName()).second->raiseLose();

                                }
                                   
                                else
                                {
                                    models.getMatch().getPlayer2().raiseWin();
                                    models.getMatch().getPlayer1().raiseLose();
                                    models.getPlayerByName(models.getMatch().getPlayer2().getName()).second->raiseWin();
                                    models.getPlayerByName(models.getMatch().getPlayer1().getName()).second->raiseLose();
                                }
                            }
                            models.getMatch().setCompleted();
                            models.insertMatch(models.getMatch());
                        }
                        else models.getMatch().changeTurn();
                        
                        
                    }
                }
            }
        }
        if (loop == 2)
        {
            undo();
            loop = 1;
        }
        else if (loop == 3)
        {
            redo();
            loop = 1;
        }
    }
    
    system("cls");
}

pair<char,pair<int, int>>  Controllers::checkWin(Match match, int row, int col)
{
    if (match.getCountX() < 5 && match.getCountO() < 5) return { -1, {0, 0} };
    if (match.getCountX() + match.getCountO() == views.board.getRows() * views.board.getColumns()) return { 0, {0, 0} };
    vector<vector<char>> arr = match.getMapCaro();
    char turn = match.getTurn();
    int count, i, j;
    bool check2Head = 0;
    //check by row -> |
    for (i = 1, count = 1, check2Head = 0; (row - i >= 0) && (arr[row - i][col] == match.getTurn()); i++, count++);
    for (j = 1; (row + j < views.board.getRows()) && (arr[row + j][col] == match.getTurn()); j++, count++);
    if (row - i >= 0 && row + j < views.board.getRows())
    {
        if (arr[row - i][col] == -turn && arr[row + j][col] == -turn) check2Head = 1;
    }
    if (count >= 5 && check2Head != 1) return { 1, {row - i + 1, row + j - 1} };
    //check by column -> ---
    for (i = 1, count = 1, check2Head = 0; (col - i >= 0) && (arr[row][col - i] == match.getTurn()); i++, count++);
    for (j = 1; (col + j < views.board.getColumns()) && (arr[row][col+j] == match.getTurn()); j++, count++);
    if (col - i >= 0 && col + j < views.board.getColumns())
    {
        if (arr[row][col - i] == -turn && arr[row][col + j] == -turn) check2Head = 1;
    }
    if (count >= 5 && check2Head != 1) return { 2, {col - i + 1, col + j - 1} };
    //check by the first cross -> '\'
    for (i = 1, count = 1, check2Head = 0; (row - i >= 0) && (col - i >= 0) && (arr[row - i][col - i] == match.getTurn()); i++, count++);
    for (j = 1; (row + j < views.board.getRows()) && (col + j < views.board.getColumns()) && (arr[row + j][col + j] == match.getTurn()); j++, count++);
    if ((row - i >= 0) && (col - i >= 0) && (row + j < views.board.getRows()) && (col + j < views.board.getColumns()))
    {
        if (arr[row - i][col - i] == -turn && arr[row + j][col + j] == -turn) check2Head = 1;
    }
    if (count >= 5 && check2Head != 1) return { 3, {row - i + 1, row + j - 1} };
    //check by the second cross -> '/'
    for (i = 1, count = 1, check2Head = 0; (row - i >= 0) && (col + i < views.board.getColumns()) && (arr[row - i][col + i] == match.getTurn()); i++, count++);
    for (j = 1; (row + j < views.board.getRows()) && (col - j >= 0) && (arr[row + j][col - j] == match.getTurn()); j++, count++);
    if ((row - i >= 0) && (col + i < views.board.getColumns()) && (row + j < views.board.getRows()) && (col - j >= 0))
    {
        if (arr[row - i][col + i] == -turn && arr[row + j][col - j] == -turn) check2Head = 1;
    }
    if (count >= 5 && check2Head != 1) return { 4, {row - i + 1, row + j - 1} };

    return { -1, {0, 0} };
}

void Controllers::replay(int id)
{

    if (models.getMatchByID(id).first)
    {
        system("cls");
        views.dispGame(models.getMatch(), { 5, 0 }, 155, 42);
        models.getMatchByID(id).second->getBoard().plotBoard();

        for (auto i : (*(models.getMatchByID(id).second)).getVctMove())
        {
            views.board.plotCaro(i.getX(), i.getY(), i.getType());
            Sleep(500);
        }
        
    }
}

void Controllers::replay(Match match)
{
        views.dispGame(models.getMatch(), { 5, 0 }, 155, 42);
        match.getBoard().plotBoard();
        for (auto i :match.getVctMove())
        {
            views.board.plotCaro(i.getX(), i.getY(), i.getType());
            Sleep(500);
        }
}

void Controllers::undo()
{
    if (!models.getMatch().getVctMove().empty())
    {
        models.getMatch().getVctMoveExtra().push_back(models.getMatch().getVctMove().back());
        if (models.getMatch().getVctMoveExtra().back().getType() == 1) models.getMatch().setCountX(1);
        else if (models.getMatch().getVctMoveExtra().back().getType() == -1) models.getMatch().setCountX(1);
        models.getMatch().getMapCaro()[models.getMatch().getVctMove().back().getX()][models.getMatch().getVctMove().back().getY()] = '\0';
        views.board.plotCaro(models.getMatch().getVctMove().back().getX(), models.getMatch().getVctMove().back().getY(), ' ');
        models.getMatch().getVctMove().pop_back();
        models.getMatch().changeTurn();
        Sleep(512);
    }
}

void Controllers::redo()
{
    if (!models.getMatch().getVctMoveExtra().empty())
    {
        char value;
        models.getMatch().getVctMove().push_back(models.getMatch().getVctMoveExtra().back());
        if (models.getMatch().getVctMoveExtra().back().getType() == 1)
        {
            value = 'X';
            models.getMatch().setCountX(-1);
        }
        else if (models.getMatch().getVctMoveExtra().back().getType() == -1)
        {
            value = 'O';
            models.getMatch().setCountY(-1);
        }
        models.getMatch().getMapCaro()[models.getMatch().getVctMove().back().getX()][models.getMatch().getVctMove().back().getY()] = value;
        views.board.plotCaro(models.getMatch().getVctMove().back().getX(), models.getMatch().getVctMove().back().getY(), models.getMatch().getVctMoveExtra().back().getType());
        models.getMatch().getVctMoveExtra().pop_back();

        models.getMatch().changeTurn();
        Sleep(512);
    }
}

void Controllers::dispListPlayer()
{
    views.setCursorPosition(32, 6);
    cout << "Rank";
    views.setCursorPosition(40, 6);
    cout << "Name";
    views.setCursorPosition(60, 6);
    cout << "W/D/L";
    views.setCursorPosition(72, 6);
    cout << "Win Covarage";
    int count = 1;
    for (auto i : models.getListPlayer())
    {
        views.setCursorPosition(32, 9 + count);
        cout << count;
        views.setCursorPosition(40, 9 + count);
        cout << i.second.getName();
        views.setCursorPosition(60, 9 + count);
        cout << i.second.getWin() << "/" << i.second.getDraw() << "/" << i.second.getLose();
        views.setCursorPosition(72, 9 + count);
        cout << i.second.getWinRate();
        count++;
    }
    Sleep(5000);
}

void Controllers::dispListMatch()
{
    views.setCursorPosition(32, 6);
    cout << "ID";
    views.setCursorPosition(40, 6);
    cout << "Player1";
    views.setCursorPosition(60, 6);
    cout << "Player2";
    views.setCursorPosition(80, 6);
    cout << "Winner";
    int count = 1;
    for (auto i : models.getListMatch())
    {
        views.setCursorPosition(32, 9 + count);
        cout << i.second.getID();
        views.setCursorPosition(40, 9 + count);
        cout << i.second.getPlayer1().getName();
        views.setCursorPosition(60, 9 + count);
        cout << i.second.getPlayer2().getName();
        views.setCursorPosition(80, 9 + count);
        cout << ((i.second.getTurn() == 1) ? i.second.getPlayer1().getName() : i.second.getPlayer2().getName());
        count++;
    }
    Sleep(5000);
}

Player* Controllers::insertPlayer(string _player)
{
    return models.insertPlayer(_player);
}

void Controllers::setBoardinViews(Board board)
{
    views.board = board;
}

void Controllers::setConsoleWindow(int width, int height)
{
    views.setConsoleWindow(width, height);
}

void Controllers::loopGame()
{
    int option;
    int id;
    views.setColor(14);
    while (true)
    {
        system("cls");
        views.dispMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            if (!models.getMatch().isCompleted())
                playGame();
            break;
        case 2:
        {
            system("cls");
            views.dispBorder({ 30, 5 }, 60, 20);
            views.setCursorPosition(58, 7);
            cout << "New Game";

            string name1, name2;
            Player* player1, * player2;
            views.setCursorPosition(50, 10);
            cout << "Enter Player 1: ";
            cin.ignore();
            getline(cin, name1);
            player1 = checkPlayer(name1);
            views.setCursorPosition(50, 11);
            if (player1)
            {
                cout << "Win/Draw/Lose: " << player1->getWin() << "/" << player1->getDraw() << "/" << player1->getLose();

            }
            else
            {
                cout << "You are new player" << endl;
                player1 = insertPlayer(name1);
            }
            views.setCursorPosition(50, 14);
            cout << "Enter Player 2: ";
            getline(cin, name2);
            player2 = checkPlayer(name2);
            views.setCursorPosition(50, 15);
            if (player2)
            {
                cout << "Win/Draw/Lose: " << player2->getWin() << "/" << player2->getDraw() << "/" << player2->getLose();

            }
            else
            {
                cout << "You are new player" << endl;
                player2 = insertPlayer(name2);
            }
            views.setCursorPosition(50, 18);
            cout << "Loading the match ";
            Sleep(900);
            cout << ".";
            Sleep(700);
            cout << ".";
            Sleep(500);
            cout << ".";
            Sleep(500);
            cout << ".";

            Board board;
            board.set(Point(7, 1), 20, 20);
            setBoardinViews(board);
            creatMatch(board, *player1, *player2, 1);
            playGame();
            break;
        }
        case 3:
            system("cls");
            views.dispBorder({ 30, 5 }, 60, 20);
            dispListMatch();
            break;
        case 4:
            views.setCursorPosition(55, 23);
            cout << "Enter ID Match:";
            cin >> id;
            replay(id);
            break;
        case 5:
            system("cls");
            views.dispBorder({ 30, 5 }, 60, 20);
            dispListPlayer();
            break;
        case 6:
            system("cls");
            views.dispBorder({ 30, 5 }, 60, 20);
            views.setCursorPosition(50, 15);
            cout << "ThanVV";
            Sleep(1500);
            break;
        case 0:
            return;
        default:
            break;
        }
    }
}

bool Controllers::checkAvail(Board board, int row, int col)
{
    return (row < board.getRows() && col < board.getColumns());
}

