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

void CreateField_(int N);
void DrawField_(int N);
void Move(Direction dir, int N);
bool FieldIsCorrect();
bool FieldIsCorrect_(int N);
void showMenu();
void OutTime(float sec_time);

int main()
{
    setlocale(LC_ALL, "russian");
    int choice = 0;
    while (choice != 3)
    {
        unsigned int start_time, end_time, search_time;
        system("cls");
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1: {
            int start_time = clock();
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
            int end_time = clock();
            int search_time = end_time - start_time;
            float sec_time = ((float)search_time) / CLOCKS_PER_SEC;
            int min_time;
            
            OutTime(sec_time);

            cout << "\n\nПобеда! Нажмите Enter для выхода!";
            cout << endl;
            system("pause");
            cin.get(); }
            break;

        case 2: {
            int start_time = clock();
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
            int end_time = clock();
            int search_time = end_time - start_time;
            float sec_time = ((float)search_time) / CLOCKS_PER_SEC;
            int min_time;

            OutTime(sec_time);

            cout << "\n\nПобеда! Нажмите Enter для выхода!";
            cout << endl;
            system("pause");
            cin.get();
        }
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
    std::cout << "Выберите режим игры: ";
}


void CreateField_(int N) // N = 3 или 4
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

    int Chaos = 0; // Число беспорядков
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

void OutTime(float sec_time) {
    int min_time;
    if (sec_time < 60) cout << "\n\nВаше время:" << (int)sec_time << " сек.";
    if (sec_time > 60 && sec_time < 3600) {
        min_time = sec_time / 60;
        cout << "\n\nВаше время: " << min_time << " мин. " << (int)sec_time - min_time * 60 << " сек.";
    }
};
