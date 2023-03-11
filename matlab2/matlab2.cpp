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
#include <time.h>
#include <locale.h>
using namespace std;

void vivod(vector<double> arr);
void vivod(vector<vector<double>> arr);
vector<vector<double>> check(vector<vector<double>> arr)
{
    vector<vector<double>> result=arr;
    //vivod(arr);
    double sum,sum1;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        sum = 0; sum1 = 0;
        for (int j = 0; j < n; j++)
        {
            if (i!=j)
            {
            sum += fabs(arr[i][j]);
            //sum1 += fabs(arr[j][i]);
            }
        }
        if (sum>=1)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] /= sum + 1;
            }
        }
    }
    return result;
};

vector<vector<double>> random_matrix(int n) 
{
    srand(time(NULL));
    vector<vector<double>> result;
    vector<double>h1;
    for (int i = 0; i < n; i++)
    {
        result.push_back(h1);
        for (int j = 0; j < n; j++)
        {
            if (i==j)
            {
                result[i].push_back(rand()%n+n);
            }
            else
            {
                result[i].push_back(rand() % n+1);
            }
        }
    }
    return result;
}

vector<double> random_stolb(vector<vector<double>> arr,int n)
{
    srand(time(NULL)); double sum;
    vector<double> result,result1;
    for (int i = 0; i < n; i++)
    {
        result1.push_back(rand() % n + 1);
    }
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += arr[i][j] * result1[j];
        }
        result.push_back(sum);
    }



    return result;
}

vector<double> nev(vector<vector<double>> a, vector<double> b1, vector<double> reshenie)
//Функция нахождения невязок
{
    vector<double>result;
    double sum;
    int n = b1.size();
    for (int i = 0; i < n; i++)
    {
        result.push_back(0);
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += a[i][j] * reshenie[j];
        }
        result[i] = b1[i] - sum;
    }
    return result;
}
bool norm1(vector<vector<double>> a, vector<double> b1, vector<double> reshenie, double e)
{
    bool result = false;
    vector<double> nev_vector=nev(a,b1,reshenie);
    //vivod(nev_vector);
    for (int i = 0; i < a.size(); i++)
    {
        printf("%.2f e=%.2f ", fabs(nev_vector[i]), e); vivod(reshenie); printf("\n");
        if (fabs(nev_vector[i])>e)
        {
            result = true;
        }
    }
    return result;
}
bool norm(vector<double> a, vector<double> b,double e)
{
    bool result=false;
    for (int i = 0; i < a.size(); i++)
    {
        printf("%.4f e=%.4f\n", fabs(a[i] - b[i]),e);
        if (fabs(a[i]-b[i])>e)
        {
            result = true;
        }
    }
    return result;
}
void vivod(vector<double> arr)
//Функция вывода на экран одномерного вектора
{
    for (int i = 0; i < arr.size(); i++)
    {
        printf("%.4f ", arr[i]);
    }
}

void vivod(vector<vector<double>> arr)
//Функция вывода на экран матрицы
{

    for (int i = 0; i < arr[0].size(); i++)
    {
        for (int j = 0; j < arr[0].size(); j++)
        {
            printf("%.2f ", arr[i][j]);
        }
        printf("\n");
    }
}
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
    return result;
}
double get_e(char* str)
{
    char str1[100]; strcpy(str1, str);
    double result; int n;
    char* ptr = strtok(str1, " ");
    n = atoi(ptr);
    for (int i = 0; i < n * n + n; i++)
    {
        ptr = strtok(NULL, " ");
    }
    ptr = strtok(NULL, " ");
    result = atof(ptr);
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
vector<double> change(vector<vector<double>> arr, vector<double> a)
{
    vector<double> result=a;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i==j)
            {
                result[i] += arr[i][i];
            }
            else
            {
                result[i] -= arr[i][j] * a[j];
            }
        }
    }
    return result;
};
vector<double> yacob(vector<vector<double>> a, vector<double> b1,double e1)
{
    
}
vector<double> zeyd(vector<vector<double>> a, vector<double> b1, double e1)
{
    
}


void func(int q) 
{
    char str[100];
    strcpy(str, read_from_file(q));
    double e = get_e(str);
    vector<vector<double>> a = get_matrix(str);
    vector<double> b1 = get_stolb(str);
    vector<vector<double>> arr = a;
    vector<double> b = b1;
    int n = arr.size();
    yacob(arr,b,e);
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
            func(0);
        }
        else if (type == 2)
        {
          
            vector<vector<double>> a=random_matrix(10);
            vector<double> b1 = random_stolb(a,10);
            //yacob(a, b1, 0.00000000001);
            vivod(nev(a,b1, yacob(a, b1, 0.0001)));
            //  func(1);
        }
        else if (type == 3)
        {
            func(1);
        }
        else if (type == 4)
        {
            func(3);
        }
        else if (type == 5)
        {
            func(2);
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
