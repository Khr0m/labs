#include <iostream>

using namespace std;

int main()
{
    int num;
    setlocale(LC_ALL, "Russian");
    wcout << L"¬ведите число"<< endl;
    cin>>num;
    for(int i =0, i<=num, i++)
        cout<< i<< endl;

    i = 0;
    while(i < num)
    {
        if i%2 ==0
            cout << i << endl;
        else wcout <<L"нет" <<;
        i++
    }
    num = 45454
    while(num!=1000)
    {
        if num%1000 ==0
            cout<< num <<endl;
        num = num - num/15
    }

}
