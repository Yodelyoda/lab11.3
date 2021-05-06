#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string>
#include <errno.h>
#include <algorithm>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Spec { KOMPNAUK, INFORMAT, TRUDOVIK, FIZIK, MATEM };
const char* specStr[] = { "«Комп’ютерні науки»", "«Інформатика»", "«Математика та економіка»","«Фізика та інформатика»","«Трудове навчання»" };
struct Student
{
	char prizv[100];
	unsigned kurs;
	unsigned nomer;
	Spec spec;
	int SERrate;
	int FIZrate;
	int MATrate;
	union
	{
		int PEDArate;
		int PROGrate;
		int CHISLrate;
	};
};
void Create(char* fname);
void Print(char* fname);
void Sort(char* fname);
void IndexSort(char* fname);
int BinSearch(char* fname);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[100];
	int N;
	int menuItem;
	int found;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - завантвження та вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування масиву за значенням середнього балу,за оцінкою за третій предмет,за прізвищем за спаданням" << endl;
		cout << " [4] - бінарний пошук студента за середнім балом та оцінкою за третій предмет" << endl;
		cout << " [5] - індексне впорядкування та вивід даних" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			break;
		case 4:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			IndexSort(fname);
			break;
		case 5:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			if ((found = BinSearch(fname)) != -1)
			{
				cout << "Знайдено студента в позиції/" << found + 1 <<"/"<<endl;
			}

			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;

}
void Create(char* fname)
{
	ofstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	Student student;
	int spec;
	char ch;
	int i = 0;
	do {
		cout << "Студент No " << i + 1 << ":" << endl; i++;
		cout << " прізвище: "; cin >> student.prizv;
		cout << " курс: "; cin >> student.kurs;
		cout << " порядковий номер студента у групі: "; cin >> student.nomer;
		cout << " Спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 -Трудове навчання ): ";
		cin >> spec;
		student.spec = (Spec)spec;
		switch (student.spec)
		{
		case KOMPNAUK:
			cout << " Оцінка з фізики : "; cin >> student.FIZrate;
			cout << " Оцінка з математики : "; cin >> student.MATrate;
			cout << " Оцінка з програмування : "; cin >> student.PROGrate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PROGrate) / 3.0);
			cout << " Середня оцінка = " << student.SERrate;
			break;
		case INFORMAT:
			cout << " Оцінка з фізики : "; cin >> student.FIZrate;
			cout << " Оцінка з математики : "; cin >> student.MATrate;
			cout << " Оцінка з чисельних методів : "; cin >> student.CHISLrate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.CHISLrate) / 3.0);
			cout << " Середня оцінка = " << student.SERrate;
			break;
		case TRUDOVIK:
			cout << " Оцінка з фізики : "; cin >> student.FIZrate;
			cout << " Оцінка з математики : "; cin >> student.MATrate;
			cout << " Оцінка з педагогіки : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " Середня оцінка = " << student.SERrate;
			break;
		case FIZIK:
			cout << " Оцінка з фізики : "; cin >> student.FIZrate;
			cout << " Оцінка з математики : "; cin >> student.MATrate;
			cout << " Оцінка з педагогіки : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " Середня оцінка = " << student.SERrate;
			break;
		case MATEM:
			cout << " Оцінка з фізики : "; cin >> student.FIZrate;
			cout << " Оцінка з математики : "; cin >> student.MATrate;
			cout << " Оцінка з педагогіки : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " Середня оцінка = " << student.SERrate;
			break;
		}
		if (!f.write((char*)& student, sizeof(Student))) {
			cerr << "Помилка запису в файл" << endl;
			f.close();
		}
		cout << "Продовжити?(Y/N)";
		cin >> ch;
		cout << endl;
	} while (ch == 'Y' || ch == 'y');
}
void Print(char* fname)
{
	ifstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	Student student;
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << "| No | Прізвище | Курс | Порядковий номер студента у групі | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з чисельних методів | Оцінка з програмування | Оцінка з педагогіки|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (f.read((char*)& student, sizeof(Student)))
	{
		cout << "| " << setw(4) << right << i + 1 << " "; i++;
		cout << "| " << setw(13) << left << student.prizv
			<< "| " << setw(6) << left << student.kurs
			<< "| " << setw(36) << right << student.nomer
			<< "| " << setw(20) << left << specStr[student.spec]
			<< "| " << setw(11) << right << student.FIZrate
			<< "| " << setw(11) << right << student.MATrate;
		switch (student.spec)
		{
		case KOMPNAUK:
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right << student.PROGrate << " |" << setw(11) << right << "|" << endl;
			break;
		case INFORMAT:
			cout << "| " << " " << setw(8) << right << student.CHISLrate << "|" << setw(11) << right << "|" << setw(11) << right << "|" << endl;
		case TRUDOVIK:
		case FIZIK:
		case MATEM:
			cout << "| " << setw(11) << right << "|" << setw(11) << right << "|" << " " << setw(8) << right << student.PEDArate << " |" << endl;
			break;
		}
	}
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << endl;
}
void Sort(char* fname)
{
	ifstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return ;
	}
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Student);
	f.seekg(0, ios::beg);
	Student* student = new Student[size];
	Student temp;
	f.read((char*)& student,size * sizeof(Student));
	f.close();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j > i; j++)
		{
			
			if ((student[j].SERrate < student[j - 1].SERrate)
				||
				(student[j].SERrate == student[j - 1].SERrate &&
					student[j].PROGrate < student[j - 1].PROGrate)
				||
				(student[j].SERrate == student[j - 1].SERrate &&
					student[j].PROGrate == student[j - 1].PROGrate &&
					student[j].prizv < student[j - 1].prizv))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}

	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)& student,size * sizeof(Student));
}
void IndexSort(char* fname)
{
	ifstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Student);
	f.seekg(0, ios::beg);
	Student* student = new Student[size];
	Student temp;
	f.read((char*)& student, size * sizeof(Student));
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if ((student[j].SERrate < student[j - 1].SERrate)
				||
				(student[j].SERrate == student[j - 1].SERrate &&
					student[j].PROGrate < student[j - 1].PROGrate)
				||
				(student[j].SERrate == student[j - 1].SERrate &&
					student[j].PROGrate == student[j - 1].PROGrate &&
					student[j].prizv < student[j - 1].prizv))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}

	}
	f.close();
	ofstream file(fname, ios::binary);
	if (file.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return;
	}
	file.write((char*)& student, size * sizeof(Student));
	file.close();
}
int BinSearch(char* fname)
{
	ifstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "Помилка відкриття файлу '" << fname << "'!" << endl;
		return -1;
	}
	Spec spec;
	int ispec, avar,trate;
	char prizv[100];
	cout << "Введіть ключі пошуку:" << endl;
	cout << "Спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 -Трудове навчання ): ";
	cin >> ispec;
	spec = (Spec)ispec;
	cout << " прізвище: "; cin >> prizv;
	cout << " середня оцінка: "; cin >> avar;
	cout << " оцінка за третій предмет: "; cin >> trate;
	cout << endl;
	f.seekg(0, ios::end);
	int size = f.tellg();
	size = size / sizeof(Student);
	f.seekg(0, ios::beg);
	Student* student = new Student[size];
	Student temp;
	f.read((char*)& student, size * sizeof(Student));
	int L = 0, R = size, m;
	do {
		m = (L + R) / 2;
		if (student[m].spec == KOMPNAUK)
		{
			if (student[m].prizv == prizv && student[m].PROGrate == trate && student[m].SERrate == avar)
				return m;
			if ((student[m].PROGrate < trate)
				||
				(student[m].PROGrate == trate &&
					student[m].prizv < prizv)
				||
				(student[m].PROGrate == trate &&
					student[m].prizv == prizv &&
					student[m].SERrate < avar))
			{
				L = m + 1;
			}
			else
			{
				R = m - 1;
			}
		}
		if (student[m].spec == INFORMAT)
		{
			if (student[m].prizv == prizv && student[m].PROGrate == trate && student[m].SERrate == avar)
				return m;
			if ((student[m].CHISLrate < trate)
				||
				(student[m].CHISLrate == trate &&
					student[m].prizv < prizv)
				||
				(student[m].CHISLrate == trate &&
					student[m].prizv == prizv &&
					student[m].SERrate < avar))
			{
				L = m + 1;
			}
			else
			{
				R = m - 1;
			}
		}
		if (student[m].spec == TRUDOVIK || student[m].spec == FIZIK || student[m].spec == MATEM)
		{
			if (student[m].prizv == prizv && student[m].PROGrate == trate && student[m].SERrate == avar)
				return m;
			if ((student[m].PEDArate < avar)
				||
				(student[m].PEDArate == trate &&
					student[m].prizv < prizv)
				||
				(student[m].PEDArate == trate &&
				student[m].prizv == prizv &&
					student[m].SERrate < avar))
			{
				L = m + 1;
			}
			else
			{
				R = m - 1;
			}
		}
	} while (L <= R);
	return -1;
}