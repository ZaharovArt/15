// 15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h> 
#include <cstdio> 

int Field[4][4];
int EmptyX, EmptyY;

enum Direction { LEFT, UP, RIGHT, DOWN };

void CreateField();
void DrawField();
void Move(Direction dir);
bool FieldIsCorrect();

int main()
{
    CreateField();
    DrawField(); 
    char c; 
    int a;
    while (!FieldIsCorrect())
    {
        // c = getchar();
        std::cin >> a;
        switch (a)
        {
        case 4 /*75*/: Move(LEFT); break; 
        case 8/*72*/: Move(UP); break;
        case 6/*77*/: Move(RIGHT); break;
        case 2/*80*/: Move(DOWN); break;
        case 0/*27*/: return 0;
        }
        DrawField(); 
    }
    std::cout << "\n\nCongratulations! Press Enter to exit!";
    std::cin.get();
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
        Field[i % 4][i / 4] = Nums[i];
    Field[3][3] = 0;
    EmptyX = 3; EmptyY = 3;

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

void Move(Direction dir)
{
    switch (dir)
    {
    case LEFT:
    {
        if (EmptyX < 3)
        {
            Field[EmptyX][EmptyY] = Field[EmptyX + 1][EmptyY];
            Field[EmptyX + 1][EmptyY] = 0;
            EmptyX++;
        }
    } break;
    case UP:
    {
        if (EmptyY < 3)
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


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
