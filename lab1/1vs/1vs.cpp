﻿// 1vs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");


    int num;
    wcout << L"Введите число" << endl;
    cin >> num;
    
    for (int i = 0; i <= num; i++)
        wcout << i << endl;
    
    cout << endl;


    int i = 0;
    while (i < num)
    {
        if ((i*7) % 2 == 0)
            cout << i << endl;
        else
            wcout << L"нет" << endl;
        i++;
    }

    cout << endl;
    num = 4435;

    int n = 0;
    while (num >= 1000)
    {
        n++;
        if (num % 1000 == 0)
        {
            cout << " Прошло " << num << " циклов" << endl;
            n = 0;
        }
        num--;

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
