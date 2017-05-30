// C++Task2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Helper.h"

/*
������������ ������ �������������

14. ������ ����� ������������ ���������� � ������: �������� �����, ��� �����, ������� ���������,
��������� ������� ����������� ������, ���� ����������, ����� �����. ����� �� �������� �����, ���� �����, ���� ����������.

*/


void printMainMenu()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " ��������:" << std::endl;
	std::cout << " 1)������� ����" << std::endl;
	std::cout << " 2)�������" << std::endl;
	std::cout << " 3)��������� � ����" << std::endl;
	std::cout << " 4)������� �� �����" << std::endl;
	std::cout << " 5)����� ������" << std::endl;
	std::cout << " 6)�������� ������" << std::endl;
	std::cout << " 7)������������" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printMenuFindParam()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " �����" << std::endl;
	std::cout << " 1)�� �������� �����" << std::endl;
	std::cout << " 2)�� ���� �����" << std::endl;
	std::cout << " 3)�� ���� ����������" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printMenuSearch()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "��� ������:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printAction()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "�������� � �������:" << std::endl;
	std::cout << " 1)������" << std::endl;
	std::cout << " 2)��������" << std::endl;
	std::cout << " 3)�������" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printSubSetMenu(int size)
{
	std::cout << " ������ ������������: " << size << "\n";
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)����� �� �����" << std::endl;
	std::cout << " 2)����� � ����" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

bool TryOpenFile(std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}
	file.close();
	return true;
}

std::string inputFileName()
{
	std::string filename;
	std::cout << "������� ��� �����:\n";
	std::cin >> filename;

	while (!TryOpenFile(filename))
	{
		std::cout << "������� ��� �����:\n";
		std::cin >> filename;
	}

	return filename;
}


int main()
{
	setlocale(LC_ALL, "rus");
	bool notEnd = true;
	�ontainer<> cont = �ontainer<>();
	std::string filename;
	std::vector<Order>::iterator it;
	bool fl;
	bool binarSearch;
	bool found;
	std::string str;

	int c;
	while (notEnd)
	{
		printMainMenu();
		std::cin >> c;
		switch (c)
		{
		case 1:
			filename = inputFileName();
			cont.fileInput(filename);
			break;
		case 2:
			cont.consoleInput();
			break;
		case 3:
			std::cout << "������� ��� �����:\n";
			std::cin >> filename;
			cont.fileOutput(filename);
			break;
		case 4:
			cont.consoleOutput();
			break;
		case 5:
			fl = true;
			while (fl)
			{
				printMenuSearch();
				std::cin >> c;
				
				switch (c)
				{
				case 1:
					binarSearch = false;
					fl = false;
					break;
				case 2:
					binarSearch = true;
					fl = false;
					break;
				case 0:
					fl = false;
					break;
				default:
					std::cout << "������� ������� �������!!" << std::endl;
					break;
				}
				
			}
			fl = true;
			while (fl)
			{
				printMenuFindParam();
				std::cin >> c;
				switch (c)
				{
				case 1:
					std::cout << "������� ��������: ";
					std::cin >> str;
					if (binarSearch)
						try
					{
						found = cont.findByName(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByNameBinary(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						while (fl)
						{
							printAction();
							std::cin >> c;

							switch (c)
							{
							case 1:
								std::cout << *it;
								break;
							case 2:
								cont.change(it);
								break;
							case 3:
								cont.remove(it);
								fl = false;
								break;
							case 0:
								fl = false;
								break;
							default:
								std::cout << "������� ������� �������!" << std::endl;
								break;
							}
						}
					}
					else
						std::cout << "������ �� �������\n";
					fl = false;
					break;
				case 3:
					if (binarSearch)
						try
					{
						found = cont.findByDateBinary(inputDate(), it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByDate(inputDate(), it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						while (fl)
						{
							printAction();
							std::cin >> c;

							switch (c)
							{
							case 1:
								std::cout << *it;
								break;
							case 2:
								cont.change(it);
								break;
							case 3:
								cont.remove(it);
								fl = false;
								break;
							case 0:
								fl = false;
								break;
							default:
								std::cout << "����������� ������� �������!" << std::endl;
								break;
							}

						}
					}
					else
						std::cout << "������ �� ������� \n";
					fl = false;
					break;
				case 2:
					std::cout << "������� ���: ";
					std::cin >> str;
					if (binarSearch)
						try
					{
						found = cont.findByTypeBinary(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByType(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						printAction();
						std::cin >> c;

						switch (c)
						{
						case 1:
							std::cout << *it;
							break;
						case 2:
							cont.change(it);
							break;
						case 3:
							cont.remove(it);
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}

					}
					else
						std::cout << "������ �� ������� \n";
					fl = false;
					break;
				case 0:
					fl = false;
					break;
				default:
					std::cout << "����������� ������� �������!" << std::endl;
					break;
				}
			}
			break;
		case 6:
			try
			{
				cont.add(inputOrderAdd(cont));
			}
			catch (const char* str) {
				fl = false;
			}
			break;
		case 7:
			fl = true;
			while (fl)
			{
				printMenuFindParam();
				std::cin >> c;
				switch (c)
				{
				case 1:
					std::cout << "������� �������� �����: ";
					std::cin >> str;
					cont.findSubSetByName(str);
					fl = true;
					while (fl)
					{
						printSubSetMenu(cont.subSize());
						std::cin >> c;
						switch (c)
						{
						case 1:
							cont.consoleOutputSub();
							fl = false;
							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;	
							cont.fileOutputSub(filename);
							fl = false;
							break;
						case 0:
						fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}
						
					}
					break;
				case 3:
					std::cout << "������� ����: ";
					cont.findSubSetByDate(inputDate());
					fl = true;
					while (fl)
					{
						printSubSetMenu(cont.subSize());
						std::cin >> c;
						
						switch (c)
						{
						case 1:
							cont.consoleOutputSub();
							fl = false;
							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;
							cont.fileOutputSub(filename);
							fl = false;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}
						
					}
					break;
				case 2:
					std::cout << "Enter place: ";
					std::cin >> str;
					cont.findSubSetByType(str);
					fl = true;
					while (fl)
					{
						
						printSubSetMenu(cont.subSize());
						std::cin >> c;
						
						switch (c)
						{
						case 1:
							cont.consoleOutputSub();
							fl = false;
							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;
							cont.fileOutputSub(filename);
							fl = false;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}
					}
					break;
				case 0: fl = false;
				}
			}
			break;

		case 0:
			notEnd = false;
			break;
		default:
			std::cout << "����� ������� ���! ��������� ����!" << std::endl;
			break;
			}

	}
    return 0;
}



