// 15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h> 
#include <cstdio> 
#include <ctime>
using namespace std;

int Field[4][4];
int EmptyX, EmptyY;

enum Direction { LEFT, UP, RIGHT, DOWN };

void CreateField();
void CreateField_(int N);
void DrawField();
void DrawField_(int N);
void Move(Direction dir, int N);
bool FieldIsCorrect();
bool FieldIsCorrect_(int N);
void showMenu();

int main()
{
    setlocale(LC_ALL, "russian");
 
    
    int choice = 0;
    unsigned int start_time, end_time, search_time;

    while (choice != 3)
    {
        unsigned int start_time, end_time, search_time;
        system("cls");
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            unsigned int start_time = clock();
            CreateField_(3);
            DrawField_(3);
            char c;
            while (!FieldIsCorrect_(3))
            {
                c = _getch();
                switch (c)
                {
                case 75: Move(LEFT, 3); break;
                case 72: Move(UP, 3); break;
                case 77: Move(RIGHT, 3); break;
                case 80: Move(DOWN, 3); break;
                case 27: return 0;
                }
                DrawField_(3);
            }
            end_time = clock();
            search_time = end_time - start_time; 

            std::cout << "\n\nВаше время:"<< search_time;
            std::cout << "\n\nПобеда! Нажмите Enter для выхода!";
            cout << endl;
            system("pause");
            std::cin.get();
            break;

        case 2:
            unsigned int start_time_4 = clock();
            CreateField_(4);
            DrawField_(4);
            char cc;
            while (!FieldIsCorrect_(4))
            {
                cc = _getch();
                switch (cc)
                {
                case  75: Move(LEFT, 4); break;
                case 72: Move(UP, 4); break;
                case 77: Move(RIGHT, 4); break;
                case 80: Move(DOWN, 4); break;
                case 27: return 0;
                }
                DrawField_(4);
            }
            unsigned int end_time_4 = clock();
            unsigned int search_time_4 = end_time_4 - start_time_4;

            std::cout << "\n\nВаше время:" << search_time_4;
            std::cout << "\n\nПобеда! Нажмите Enter для выхода!";
            cout << endl;
            system("pause");
            std::cin.get();
            break;
        case 27: return 0;

        }
    }
}

void showMenu() {

    std::cout << "Игра Пятнашки" << std::endl;
    std::cout << std:: endl;
    std::cout << "[1]  8 (3х3)" << std::endl;
    std::cout << "[2]  15 (4х4)" << std::endl;
    std::cout << "[3]  Выход." << std::endl;
    std::cout << std::endl;
    std::cout << "Выберите режим игры:" << std::endl;

}

void CreateField()
{
    bool NumIsFree[15]; 
    int Nums[15]; 
    for (int i = 0; i < 15; i++) 
        NumIsFree[i] = true;

    srand(time(NULL));

    bool Ok;
    int RandNum;
    for (int i = 0; i < 15; i++)
    {
        Ok = false;
        while (!Ok)
        {
            RandNum = rand()%15 + 1; 
            if (NumIsFree[RandNum - 1])
                Ok = true;
        }
        Nums[i] = RandNum; 
        NumIsFree[RandNum - 1] = false;
    }

    int Chaos = 0; 
    int CurrNum; 
    for (int i = 0; i < 14; i++) 
    {
        CurrNum = Nums[i];
        for (int j = i + 1; j < 15; j++)
            if (CurrNum > Nums[j])
                Chaos++;
    }
    if (Chaos % 2 == 1) 
    { 
        int temp = Nums[13];
        Nums[13] = Nums[14];
        Nums[14] = temp;
    }

    for (int i = 0; i < 15; i++)
        Field[i % 4/2][i / 4] = Nums[i];
    Field[3][3] = 0;
    EmptyX = 3; EmptyY = 3;

}

void CreateField_(int N) // N= 3 или 4
{
    int size = N * N - 1;
    bool* NumIsFree = new bool[size];
    int* Nums = new int[size];
    for (int i = 0; i < size; i++)
        NumIsFree[i] = true;

    srand(time(NULL));

    bool Ok;
    int RandNum;
    for (int i = 0; i < size; i++)
    {
        Ok = false;
        while (!Ok)
        {
            RandNum = rand() % size + 1;
            if (NumIsFree[RandNum - 1])
                Ok = true;
        }
        Nums[i] = RandNum;
        NumIsFree[RandNum - 1] = false;
    }

    int Chaos = 0;
    int CurrNum;
    for (int i = 0; i < size-1; i++)
    {
        CurrNum = Nums[i];
        for (int j = i + 1; j < size; j++)
            if (CurrNum > Nums[j])
                Chaos++;
    }
    if (Chaos % 2 == 1)
    {
        int temp = Nums[size-2];
        Nums[size-2] = Nums[size-1];
        Nums[size-1] = temp;
    }

    for (int i = 0; i < size; i++) {
    Field[i % N][i / N] = Nums[i];
    }
    Field[N-1][N-1] = 0;
    EmptyX = N-1; EmptyY = N-1;

}


void DrawField()
{
    system("cls");

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
                std::cout << "----";
            else
                std::cout << "    ";
        }
        std::cout << '\n';
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
            {
                std::cout << "|";
                std::cout.width(2);
                std::cout << Field[i][j] << "|";
            }
            else
                std::cout << "    ";
        }
        std::cout << '\n';
        for (int i = 0; i < 4; i++)
        {
            if (Field[i][j])
                std::cout << "----";
            else
                std::cout << "    ";
        }
        std::cout << '\n';
    }
}

void DrawField_(int N)
{
    system("cls");

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            if (Field[i][j])
                std::cout << "----";
            else
                std::cout << "    ";
        }
        std::cout << '\n';
        for (int i = 0; i < N; i++)
        {
            if (Field[i][j])
            {
                std::cout << "|";
                std::cout.width(2);
                std::cout << Field[i][j] << "|";
            }
            else
                std::cout << "    ";
        }
        std::cout << '\n';
        for (int i = 0; i < N; i++)
        {
            if (Field[i][j])
                std::cout << "----";
            else
                std::cout << "    ";
        }
        std::cout << '\n';
    }
}

void Move(Direction dir, int N)
{
    switch (dir)
    {
    case LEFT:
    {
        if (EmptyX < N-1)
        {
            Field[EmptyX][EmptyY] = Field[EmptyX + 1][EmptyY];
            Field[EmptyX + 1][EmptyY] = 0;
            EmptyX++;
        }
    } break;
    case UP:
    {
        if (EmptyY < N-1)
        {
            Field[EmptyX][EmptyY] = Field[EmptyX][EmptyY + 1];
            Field[EmptyX][EmptyY + 1] = 0;
            EmptyY++;
        }
    } break;
    case RIGHT:
    {
        if (EmptyX > 0)
        {
            Field[EmptyX][EmptyY] = Field[EmptyX - 1][EmptyY];
            Field[EmptyX - 1][EmptyY] = 0;
            EmptyX--;
        }
    } break;
    case DOWN:
    {
        if (EmptyY > 0)
        {
            Field[EmptyX][EmptyY] = Field[EmptyX][EmptyY - 1];
            Field[EmptyX][EmptyY - 1] = 0;
            EmptyY--;
        }
    } break;
    }
}

bool FieldIsCorrect()
{
    for (int i = 0; i < 15; i++)
        if (Field[i % 4][i / 4] != i + 1)
            return false; 
    return true;
}

bool FieldIsCorrect_(int N)
{
    int size = N * N - 1;
    for (int i = 0; i < size; i++)
        if (Field[i % N][i / N] != i + 1)
            return false;
    return true;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
