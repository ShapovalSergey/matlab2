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
void write_to_file(vector<vector<double>> a, vector<double> b, vector<double> answ, vector<double> nev)
//Функция записи информации в файл
{
    FILE* p1; string str;
    p1 = fopen("results.txt", "r");
    if (p1 == NULL)
    {
        p1 = fopen("results.txt", "w");
    }
    _fcloseall();

    ofstream out("results.txt", ios::app);

    out << "Исходная матрица" << endl;

    for (int i = 0; i < a[0].size(); i++)
    {
        string str = "";
        for (int j = 0; j < a[0].size(); j++)
        {
            str += to_string(a[i][j]); str += " ";
        }
        out << str << endl;
    }
    out << "Столбец свободных членов" << endl;
    str = "";
    for (int i = 0; i < a[0].size(); i++)
    {
        out << b[i] << endl;
    }
    out << str << endl;
    out << "Решения системы" << endl;
    str = "";
    for (int i = 0; i < a[0].size(); i++)
    {
        str = "x"; str += to_string(i); str += " = ";
        str += to_string(answ[i]); str += " ";
        out << str << endl;
    }
    out << "Невязки системы" << endl;
    str = "";
    for (int i = 0; i < a[0].size(); i++)
    {
        str = "r"; str += to_string(i); str += " = ";
        str += to_string(nev[i]); str += " ";
        out << str << endl;
    }
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
//Функция остановки, невязки должны быть меньше точности
{
    bool result = false;
    vector<double> nev_vector=nev(a,b1,reshenie);
    for (int i = 0; i < a.size(); i++)
    {
        if (fabs(nev_vector[i])>e)
        {
            result = true;
        }
    }
    return result;
}
bool norm(vector<double> a, vector<double> b,double e)
//Функция остановки, разница нового и старого решения меньше точности
{
    bool result=false;
    for (int i = 0; i < a.size(); i++)
    {
        //printf("%.4f e=%.4f\n", fabs(a[i] - b[i]),e);
        if (fabs(a[i]-b[i])>e)
        {
            result = true;
        }
    }
    return result;
}
void vivod(vector<double> arr, char c)
//Функция вывода на экран одномерного вектора
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (c=='b')
        {
            printf("\n%c%d=%.2f ", c, i + 1, arr[i]);
        }
        else
        {
            printf("\n%c%d=%.4f ", c, i + 1, arr[i]);
        }
        
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
//Функция выполнения итерации для метода Якоби
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

vector<double> change1(vector<vector<double>> arr, vector<double> a)
//Функция выполнения итерации для метода Зейделя
{
    vector<double> result=a;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                result[i] += arr[i][i];
            }
            else
            {
                result[i] -= arr[i][j] * a[j];
            }
        }
        a[i] = result[i];
    }
    return result;
};
vector<double> yacob(vector<vector<double>> a, vector<double> b1,double e1)
//Функция, находящая решение по методу Якоби
{
    printf("Исходная матрица\n");
    vivod(a);
    printf("Столбец свободных членов");
    vivod(b1,'b'); //printf("\n");
    vector<vector<double>> arr = a;
    vector<double> b = b1;
    double e = e1;
    vector<double> result=b1;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            
            if (i != j)
            {
                arr[i][j] /= a[i][i] ;
            }
            else
            {
                arr[i][i] = b1[i] / a[i][i];
            }
        }
    }
    int iter = 0;
    //arr = check(arr); 
    for (int i = 0; i < n; i++)
    {
        result[i] = arr[i][i];
    }
    while (norm(result,b,e)) 
    {
        b = result;
        result = change(arr,result);
        iter++;
    }
    printf("\nКоличество итераций = %d\nРешение",iter);
    vivod(result,'x');
    printf("\nНевязки");
    vivod(nev(a, b1, result),'r');
    printf("\nЗаданная точность = %.4f", e);
    write_to_file(a,b1,result, nev(a, b1, result));
    return result;
}
vector<double> zeyd(vector<vector<double>> a, vector<double> b1, double e1)
//Функция, находящая решение по методу Зейделя
{
    printf("Исходная матрица\n");
    vivod(a);
    printf("Столбец свободных членов");
    vivod(b1, 'b');
    vector<vector<double>> arr = a;
    vector<double> b = b1;
    double e = e1;
    vector<double> result;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (i != j)
            {
                arr[i][j] /= a[i][i];
            }
            else
            {
                arr[i][i] = b[i] / a[i][i];
            }
        }
        result.push_back(0);
    }
    result[0] = arr[0][0];
    int iter = 0;
    while (norm1(a,b1,result,e))
    {
        result = change1(arr,result);
        iter++;
    }
    printf("\nКоличество итераций = %d\nРешение", iter);
    vivod(result,'x');
    printf("\nНевязки");
    vivod(nev(a, b1, result),'r');
    printf("\nЗаданная точность = %.4f",e);
    write_to_file(a, b1, result, nev(a, b1, result));
    return result;
}

void func(int q,bool metod) 
{
    char str[100];
    strcpy(str, read_from_file(q));
    double e = get_e(str);
    vector<vector<double>> a = get_matrix(str);
    vector<double> b1 = get_stolb(str);
    vector<vector<double>> arr = a;
    vector<double> b = b1;
    //int n = arr.size();
    if (metod==true)
    {
        yacob(arr, b, e);
    }
    else
    {
        zeyd(arr,b,e);
    }
}

void choose(int q) 
{
    int r;
    printf("Выберите метод\n1)Метод Якоби\n2)Метод Зейделя\n");
    scanf("%d",&r);
    if (r==1)
    {
        func(q,true);
    }
    else
    {
         func(q,false);
    }
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
            choose(0);
        }
        else if (type == 2)
        {
            choose(1);
        }
        else if (type == 3)
        {
            choose(2);
        }
        else if (type == 4)
        {
            choose(3);
        }
        else if (type == 5)
        {
            choose(4);
        }
        printf("\nВы хотите продолжить? (1 - да, 0 - нет)\n");
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
