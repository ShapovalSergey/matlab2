// matlab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <locale.h>
using namespace std;



vector<vector<double>> get_matrix(char* str)
{
    char str1[100]; strcpy(str1, str);
    vector<vector<double>> result; vector<double> help;
    int n;
    char* ptr = strtok(str1, " ");
    n = atoi(ptr);
    for (size_t i = 0; i < n; i++)
    {
        help.push_back(0);
    }
    for (int i = 0; i < n; i++)
    {
        result.push_back(help);
        for (int j = 0; j < n; j++)
        {
            ptr = strtok(NULL, " ");
            result[i][j] = atof(ptr);
        }
    }
    return result;
}
vector<double> get_stolb(char* str)
{
    char str1[100]; strcpy(str1, str);
    vector<double> result; int n;
    char* ptr = strtok(str1, " ");
    n = atoi(ptr);
    for (int i = 0; i < n * n; i++)
    {
        ptr = strtok(NULL, " ");
    }
    for (int i = 0; i < n; i++)
    {
        ptr = strtok(NULL, " ");
        result.push_back(atof(ptr));
    }
    ptr = strtok(NULL, " ");
    result.push_back(atof(ptr));
    return result;
}

char* read_from_file(int n)
{
    char* result; char str[100];
    FILE* p1;
    p1 = fopen("data.txt", "r");
    if (p1 == NULL)
    {
        p1 = fopen("data.txt", "w");
    }
    _fcloseall();
    p1 = fopen("data.txt", "r");
    fseek(p1, n * 100, SEEK_SET);
    fgets(str, 100, p1);
    result = str;
    return result;
}


int main()
{
    int mode = 1, type, n;
    setlocale(LC_ALL, "Russian");
    while (mode == 1)
    {
        mode = 0;
        printf("Введите число от 1 до 5\n");
        scanf("%d", &type);
        if (type == 1)
        {
          //  func(0);
        }
        else if (type == 2)
        {
          //  func(1);
        }
        else if (type == 3)
        {
          //  func(2);
        }
        else if (type == 4)
        {
           // func(3);
        }
        else if (type == 5)
        {
           // func(4);
        }
        printf("Вы хотите продолжить? (1 - да, 0 - нет)\n");
        scanf("%d", &mode);
    }
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
