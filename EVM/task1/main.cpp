/*
    Хамитов Абулкаир 9308
    Вариант 24(4)
    Задача:
    int/long double
	Преобразование:
	Поменять местами заданные пользователем группы рядом стоящих бит, номера старших разрядов этих групп и количество бит в группе, вводится с клавиатуры.
*/
#include <iostream>

using namespace std;

#ifdef __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

// ----- Константы ------
const int s_int = 32;
const int s_ldb = 80;

// ----- Прототипы функций -----

// Функции конвертирования
void to_binary(long double, bool*);
void to_binary(int, bool*);
int to_dex(int, bool*);
long double to_dex(long double, bool*);

// Функции реализации 
void task_realize(bool*, bool*, short, short, short, short);

// Декоративные функции
void print_binary(bool*, short);


int main()
{
	long double ldb_val;	// Переменная для хранения long double
	int 		int_val;	// Переменная для хранения int

	short 	menu,		// Номер меню
			index1,		// Номер первого старшего разряда
			index2,		// Номер второго старшего разряда
			s_group;	// Размер группы

	bool bl_int_array[s_int];	// Бинарный код int
	bool bl_ldb_array[s_ldb];	// Бинарный код long double

	bool res_bl_int_array[s_int];	// Бинарный код int после преобразования
	bool res_bl_ldb_array[s_ldb];	// Бинарный код long double после преобразования

	do
    {
		// Меню
        cout << "\nMenu";
        cout << "\n1) Int input \n2) Long double input \n0) Exit" << endl;
        cin >> menu;

		system(CLEAR);
		switch(menu)
		{
			case 1:
				// int
				cout << "\nEnter your int value: ";
				cin >> int_val;
				// Конвертирование и вывод
				to_binary(int_val, bl_int_array);
				print_binary(bl_int_array, s_int);

				// Ввод размера группы
				do {
					cout << "\n\nEnter group size: ";
					cin >> s_group;
					if(s_group > s_int) cout << "\nIncorrect input. Try again";
				} while (s_group > s_int);

				// Ввод старших разрядов группы
				do {
					cout << "Enter the first senior position: ";
					cin >> index1;
					cout << "Enter the second senior position: ";
					cin >> index2;
					if(index1+1 > s_int || index2+1 > s_int) cout << "\nIncorrect input. Try again";
				} while (index1+1 > s_int || index2+1 > s_int);

				// Реализация и вывод	
				task_realize(bl_int_array, res_bl_int_array, s_group, index1, index2, s_int);
				print_binary(res_bl_int_array, s_int);
				cout << "\nDex    code: " << to_dex(int_val, res_bl_int_array);
			break;
			case 2:
				// long double
				cout << "\nEnter your long double value: ";
				cin >> ldb_val;

				// Конвертирование и вывод
				to_binary(ldb_val, bl_ldb_array);
				print_binary(bl_ldb_array, s_ldb);

				// Ввод размера группы
				do {
					cout << "\n\nEnter group size: ";
					cin >> s_group;
					if(s_group > s_ldb) cout << "\nIncorrect input. Try again";
				} while (s_group > s_ldb);

				// Ввод старших разрядов группы
				do {
					cout << "Enter the first senior position: ";
					cin >> index1;
					cout << "Enter the second senior position: ";
					cin >> index2;
					if(index1+1 > s_ldb || index2+1 > s_ldb) cout << "\nIncorrect input. Try again";
				} while (index1+1 > s_ldb || index2+1 > s_ldb);

				// Реализация и вывод
				task_realize(bl_ldb_array, res_bl_ldb_array, s_group, index1, index2, s_ldb);
				print_binary(res_bl_ldb_array, s_ldb);
				cout << "\nDex    code: " << to_dex(ldb_val, res_bl_ldb_array);
			break;
			case 0:
				cout << "\nGood bye!";
			break;
			default:
				cout << "Incorrect input. Try again";
			break;
		}
	} while (menu != 0);

	return 0;
}

void to_binary(long double val, bool *bl_array)
{
	int i, j, k;
	union {
        long double ss;
        unsigned char c[s_ldb];
	} code;
 	code.ss = val; //переменная объединения получила вещественное значение

	k = 0;
	for (j = s_ldb/8 - 1; j >= 0; j--)
		for (i = 128; i; i >>= 1) //Разбираем каждый бит из байта
			bl_array[k++] = i & code.c[j];
}

void to_binary(int val, bool *bl_array)
{
	short k = 0;
	for(int i = s_int-1; i >= 0; --i)
		bl_array[k++] = ((val >> i) & 1);
}

long double to_dex(long double val, bool *new_bl_array)
{
	int i, j, k;
	union {
        long double ss;
        unsigned char c[s_ldb];
	} code;
	code.ss = val;

	k = 0;
	for (j = s_ldb/8 - 1; j >= 0; j--)
		for (i = 7; i >= 0; --i)
		// Меняем старый код long double на новый
			if(new_bl_array[k++])	code.c[j] |= (1<<i);
			else					code.c[j] &=~(1<<i);

	return code.ss;
}

int to_dex(int val, bool *new_bl_array)
{
	int res;
	short k = 0;
	for(int i = s_int-1; i >= 0; --i)
		if(new_bl_array[k++]) 	val |= (1<<i);
		else 					val &=~(1<<i);

	return val;	
}

void task_realize(bool *bl_array, bool *res_array, short s_group, short index1, short index2, short amount)
{
/*
    Реализация задания через последовательный перебор
    Сложность алгоритма O(n), где n - длина кодового слова
*/
	int i;
	index1 = amount - index1 - 1;
	index2 = amount - index2 - 1;
	// Смотрим, чтобы выполнялось неравенство

	if(index1 > index2)
	{
		i = index2; index2 = index1; index1 = i;
	}
	i = 0;

	// Доходим до index1
	while(i != index1)
	{
		res_array[i] = bl_array[i];
		i++;
	}

	// Свап с index2
	while(i < index1+s_group)
	{
		res_array[i] = bl_array[(index2) + (i) - index1];
		i++;
	}

	// Доходим до index2
	while(i != index2)
	{
		res_array[i] = bl_array[i];
		i++;
	}

	// Свап с index1
	while(i < index2+s_group)
	{
		res_array[i] = bl_array[(index1) + (i) - index2];
		i++;
	}

	// Пробегаем по оставшимся
	while(i < amount)
	{
		res_array[i] = bl_array[i];
		i++;
	}
}

void print_binary(bool *bl_array, short amount)
{
	int i;
	cout << "-----------------------\n";
	cout << "Binary code: ";
	for(i = 0; i <= amount-1; i++) cout << bl_array[i];

	// if(amount != s_int)
	// {
	// 	cout << "\nsign: " << bl_array[0];
	// 	cout << "\nexponent: ";
	// 	for (i = 1; i <= 15; i++) cout << bl_array[i];
	// 	cout << "\nmantissa: ";
	// 	for (i = 16; i <= 79; i++) cout << bl_array[i];
	// }
}