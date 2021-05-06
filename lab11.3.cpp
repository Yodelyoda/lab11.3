#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string>
#include <errno.h>
#include <algorithm>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;
enum Spec { KOMPNAUK, INFORMAT, TRUDOVIK, FIZIK, MATEM };
const char* specStr[] = { "���������� �����", "������������", "����������� �� ��������","�Գ���� �� �����������","�������� ���������" };
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
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	char fname[100];
	int N;
	int menuItem;
	int found;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ������������ �� ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� ������ �� ��������� ���������� ����,�� ������� �� ����� �������,�� �������� �� ���������" << endl;
		cout << " [4] - ������� ����� �������� �� ������� ����� �� ������� �� ����� �������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cin.get(); // ������� ����� ��������� � ��� �� ���� �������
			cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
			cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get(); // ������� ����� ��������� � ��� �� ���� �������
			cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
			cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get(); // ������� ����� ��������� � ��� �� ���� �������
			cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
			cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			break;
		case 4:
			cin.get(); // ������� ����� ��������� � ��� �� ���� �������
			cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
			cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
			IndexSort(fname);
			break;
		case 5:
			cin.get(); // ������� ����� ��������� � ��� �� ���� �������
			cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
			cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			if ((found = BinSearch(fname)) != -1)
			{
				cout << "�������� �������� � �������/" << found + 1 <<"/"<<endl;
			}

			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;

}
void Create(char* fname)
{
	ofstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "������� �������� ����� '" << fname << "'!" << endl;
		return;
	}
	Student student;
	int spec;
	char ch;
	int i = 0;
	do {
		cout << "������� No " << i + 1 << ":" << endl; i++;
		cout << " �������: "; cin >> student.prizv;
		cout << " ����: "; cin >> student.kurs;
		cout << " ���������� ����� �������� � ����: "; cin >> student.nomer;
		cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 -������� �������� ): ";
		cin >> spec;
		student.spec = (Spec)spec;
		switch (student.spec)
		{
		case KOMPNAUK:
			cout << " ������ � ������ : "; cin >> student.FIZrate;
			cout << " ������ � ���������� : "; cin >> student.MATrate;
			cout << " ������ � ������������� : "; cin >> student.PROGrate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PROGrate) / 3.0);
			cout << " ������� ������ = " << student.SERrate;
			break;
		case INFORMAT:
			cout << " ������ � ������ : "; cin >> student.FIZrate;
			cout << " ������ � ���������� : "; cin >> student.MATrate;
			cout << " ������ � ��������� ������ : "; cin >> student.CHISLrate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.CHISLrate) / 3.0);
			cout << " ������� ������ = " << student.SERrate;
			break;
		case TRUDOVIK:
			cout << " ������ � ������ : "; cin >> student.FIZrate;
			cout << " ������ � ���������� : "; cin >> student.MATrate;
			cout << " ������ � ��������� : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " ������� ������ = " << student.SERrate;
			break;
		case FIZIK:
			cout << " ������ � ������ : "; cin >> student.FIZrate;
			cout << " ������ � ���������� : "; cin >> student.MATrate;
			cout << " ������ � ��������� : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " ������� ������ = " << student.SERrate;
			break;
		case MATEM:
			cout << " ������ � ������ : "; cin >> student.FIZrate;
			cout << " ������ � ���������� : "; cin >> student.MATrate;
			cout << " ������ � ��������� : "; cin >> student.PEDArate;
			student.SERrate = ((student.FIZrate + student.MATrate + student.PEDArate) / 3.0);
			cout << " ������� ������ = " << student.SERrate;
			break;
		}
		if (!f.write((char*)& student, sizeof(Student))) {
			cerr << "������� ������ � ����" << endl;
			f.close();
		}
		cout << "����������?(Y/N)";
		cin >> ch;
		cout << endl;
	} while (ch == 'Y' || ch == 'y');
}
void Print(char* fname)
{
	ifstream f(fname, ios::binary);
	if (f.fail())
	{
		cout << "������� �������� ����� '" << fname << "'!" << endl;
		return;
	}
	Student student;
	cout << "====================================================================================================================================================================================================="
		<< endl;
	cout << "| No | ������� | ���� | ���������� ����� �������� � ���� | ������������ | ������ � ������ | ������ � ���������� | ������ � ��������� ������ | ������ � ������������� | ������ � ���������|"
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
		cout << "������� �������� ����� '" << fname << "'!" << endl;
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
		cout << "������� �������� ����� '" << fname << "'!" << endl;
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
		cout << "������� �������� ����� '" << fname << "'!" << endl;
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
		cout << "������� �������� ����� '" << fname << "'!" << endl;
		return -1;
	}
	Spec spec;
	int ispec, avar,trate;
	char prizv[100];
	cout << "������ ����� ������:" << endl;
	cout << "������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 -������� �������� ): ";
	cin >> ispec;
	spec = (Spec)ispec;
	cout << " �������: "; cin >> prizv;
	cout << " ������� ������: "; cin >> avar;
	cout << " ������ �� ����� �������: "; cin >> trate;
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