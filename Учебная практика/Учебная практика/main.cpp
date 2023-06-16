#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;
ofstream f1out;
ofstream f2out;
ifstream fin;

void FOO1();
void FOO2();
int ASM(int a, int b);

int main(void)
{
	setlocale(0, "ru");

	while (true)
	{
		cout << "\t1. Создание массива и нахождение его локальных минимумов\n"
			<< "\t2. Считать данные из файла\n"
			<< "\t3. Выход\n" << endl;
		char BUTTON;

		switch (BUTTON = _getch())
		{
		case '1':
			FOO1();
			break;

		case '2':
			FOO2();
			break;

		case '3':
			return 0;
		}
	}
}

void FOO1()
{
	int N, M;
	int Kol = 0;

	cout << "Введите размеры массива" << endl;
	cin >> N;
	cin >> M;

	// Создаю двумерный массив заданной длины
	int** arr = new int* [N];
	for (int i = 0; i < N; i++) arr[i] = new int[M];

	// Заполняю полученный массив
	cout << "Введите элементы массива\n";
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> arr[i][j];
	cout << endl;

	// Открываю файл F1 для записи матрицы
	f1out.open("F1.txt", ofstream::app);
	if (!f1out.is_open()) cout << "\n\n\nОшибка открытия файла!!!\n\n\n" << endl;

	// Открываю файл F2 для записи матрицы результатов
	f2out.open("F2.txt", ofstream::app);
	if (!f2out.is_open()) cout << "\n\n\nОшибка открытия файла!!!\n\n\n" << endl;

	// Вывожу матрицу на экран
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cout << arr[i][j] << " ";
		for (int j = 0; j < M; j++) f1out << arr[i][j] << " ";
		for (int j = 0; j < M; j++) f2out << arr[i][j] << " ";
		cout << endl;
		f1out << endl;
		f2out << endl;
	}
	cout << endl;
	f1out << "-------------------------------------------\n" << endl;
	f2out << endl;

	// Нахожу локальные минимумы матрицы
	cout << "Локальные минимумы: ";
	f2out << "Локальные минимумы: ";

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			//-----------	jl  <
			//-----------	jle  <=
			// 
			//-----------	jg  >
			//-----------	jge  >=

			int a = arr[i][j];
			int b;

			if (j > 0)
			{
				b = arr[i][j - 1];
				if (ASM(a, b)) continue;
			}

			if (j < M - 1)
			{
				b = arr[i][j + 1];
				if (ASM(a, b)) continue;
			}

			if (i > 0)
			{
				b = arr[i - 1][j];
				if (ASM(a, b)) continue;
			}

			if (i < N - 1)
			{
				b = arr[i + 1][j];
				if (ASM(a, b)) continue;
			}

			Kol++;
			cout << arr[i][j] << " ";
			f2out << arr[i][j] << " ";
		}
	cout << "\nКоличество найдинных локальных минимумов = " << Kol << endl << endl;
	f2out << "\nКоличество найдинных локальных минимумов = " << Kol << endl
		<< "------------------------------------------------" << endl << endl;

	// Освобождаю выделенную память
	delete[] arr;

	// Закрываю файл
	f1out.close();
	f2out.close();
}
void FOO2()
{
	string str;
	fin.open("F2.txt");

	if (!fin.is_open()) cout << "\n\n\nОшибка открытия файла!!!\n\n\n" << endl;

	while (!fin.eof())
	{
		str = "";
		getline(fin, str);
		cout << str << endl;
	}
	cout << endl;
	fin.close();
}
int ASM(int a, int b)
{
	bool flag = false;

	__asm
	{
		mov eax, a;
		mov ebx, b;

		cmp eax, ebx
			jl TP;

		mov flag, 1;
	TP:
	}

	return flag;
}