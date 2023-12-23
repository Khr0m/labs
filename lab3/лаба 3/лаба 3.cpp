// лаба 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <windows.h>
#include <vector>
#include <fstream>

#pragma pack(push, 1)

struct RARHeader
{
    uint16_t crc;
    uint8_t version;
    uint8_t flags;
    uint16_t size;
	//char signature[7];
	//WORD header_crc;
	//char header_type;
	//WORD header_flags;
	//WORD header_size;
};

struct RARBlock
{
    RARHeader header;
    std::vector<uint8_t> data;
};

struct RAREndArchive
{
    uint16_t crc;
    uint16_t type;
};

#pragma pack(pop)

int main()
{
    setlocale(LC_ALL, "RUS");

    string filename = "Example.rar"; // Имя файла архива

    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    std::vector<RARBlock> blocks;

    // Чтение заголовков блоков архива
    while (!file.eof())
    {
        RARBlock block;
        file.read(reinterpret_cast<char*>(&block.header), sizeof(RARHeader));
        block.data.resize(block.header.size);
        file.read(reinterpret_cast<char*>(block.data.data()), block.header.size);
        blocks.push_back(block);
    }

    cout << "Оглавление архива " << filename << ":" << endl;

    // Вывод информации о блоках архива
    for (const auto& block : blocks)
    {
        switch (block.header.version)
        {
        case 0x10:
            cout << "Тип: ARCHIVE_HEADER" << endl;
            break;
        case 0x20:
            cout << "Тип: FILE_HEADER" << endl;
            break;
        case 0x30:
            cout << "Тип: COMMENT_HEADER" << endl;
            break;
        case 0x40:
            cout << "Тип: AV_HEADER" << endl;
            break;
        case 0x45:
            cout << "Тип: END_ARCHIVE" << endl;
            break;
        default:
            cout << "Неизвестный тип блока" << endl;
            break;
        }
    }

    file.close();

    return 0;
   
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
