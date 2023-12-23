// открытие архива.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <windows.h>
#include <vector>


#pragma pack(push, 1)// устанавливает новое выравнивание в 1 байт, старое сохраняется в стек

const BYTE RarSignature[] = { 0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00 };

typedef struct
{
	WORD header_crc;
	BYTE header_type;
	WORD header_flags;
	WORD header_size;

} RarVolumeHeaderFormat, * PRarVolumeHeaderFormat;

typedef struct
{
	DWORD PackSize;
	DWORD UnpSize;
	BYTE HostOS;
	DWORD FileCRC;
	DWORD FileTime;
	BYTE UnpVer;
	BYTE Method;
	WORD NameSize;
	DWORD FileAttr;

} FILE_HEAD, * PFILE_HEAD;

#pragma pack(pop)// восстановление старого выравнивания

int Achiverarhandle(const BYTE* dataBuffer, unsigned int bufferSize)
{

	setlocale(LC_ALL, "Russian");

	int numberOfFiles = 0;

	if (memcmp(dataBuffer, RarSignature, sizeof(RarSignature)) != 0)
	{
		cout << L"Ошибка, неверный файл" << endl;
		return -1;
	}

	// Отступить от начала файла на длину сигнатуры (7 байт)
	unsigned int fileOffset = sizeof(RarSignature);

	while (fileOffset < bufferSize)
	{
		RarVolumeHeaderFormat* currentvolumeheader = (RarVolumeHeaderFormat*)&dataBuffer[fileOffset];

		wcout << L"Тип записи: " << hex << uppercase << currentvolumeheader->header_type << endl;

		if (currentvolumeheader->header_type == 0x73) //115
		{
			fileOffset += currentvolumeheader->header_size; // пропуск main_head
		}
		else if(currentvolumeheader->header_type == 0x74)//116
		{
			const FILE_HEAD* fileheader = (FILE_HEAD*)&dataBuffer[fileOffset + sizeof(RarVolumeHeaderFormat)];

			string filename((char*)&dataBuffer[fileOffset + sizeof(RarVolumeHeaderFormat)]);

			cout << filename << endl;
			numberOfFiles++;

			fileOffset += currentvolumeheader->header_size;
			fileOffset += fileheader->PackSize;
		}
		else if (currentvolumeheader->header_type == 0x7a)//123
		{
			break;
		}
		else if (currentvolumeheader->header_type == 0x7b)//124
		{
			break;
		}
		else
		{
			break;
		}
	}
	return numberOfFiles;
	
}


int main() 
{ 

	setlocale(LC_ALL, "Russian");


	wstring filename = L"C:\\Users\\khrom\\Downloads\\Example.rar";

	//открытие файла
	HANDLE fileHandle = CreateFileW(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//wcout << fileHandle << endl;
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		wcout << L"Неверный заголовок" << endl;
		CloseHandle(fileHandle);
		return 1;

	}


	// размер файла
	DWORD filesize = GetFileSize(fileHandle, NULL);
	if (filesize == INVALID_FILE_SIZE)
	{
		wcout << L"Неверный размер файла" << endl;
		CloseHandle(fileHandle);
		return 1;
	}

	vector<BYTE> dataBuffer(filesize);
	DWORD bytesread;
	bool readok = ReadFile(fileHandle, dataBuffer.data(), filesize, &bytesread, NULL);

	//wcout << dataBuffer.data() << endl;
	//проверка, что файл читается и затем вывод заголовков
	if (readok && bytesread == filesize)
	{
		int numberoffiles = Achiverarhandle(dataBuffer.data(), filesize);
		wcout << L"Всего файлов в архиве: " << numberoffiles << endl;
	}
	
	//delete[] dataBuffer;
	//закрытие файла
	CloseHandle(fileHandle);
	cin.get();
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
