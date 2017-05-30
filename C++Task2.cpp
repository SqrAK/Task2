// C++Task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Helper.h"

/*
Капранчикова Алисия Александровна

14. Оплата счета представлена структурой с полями: название фирмы, вид работ, единица измерения,
стоимость единицы выполненной работы, дата исполнения, объем работ. Поиск по названию фирмы, виду работ, дате исполнения.

*/


void printMainMenu()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " Действия:" << std::endl;
	std::cout << " 1)Открыть файл" << std::endl;
	std::cout << " 2)Создать" << std::endl;
	std::cout << " 3)Сохранить в файл" << std::endl;
	std::cout << " 4)Вывести на экран" << std::endl;
	std::cout << " 5)Поиск записи" << std::endl;
	std::cout << " 6)Добавить запись" << std::endl;
	std::cout << " 7)Подмножество" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void printMenuFindParam()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " Поиск" << std::endl;
	std::cout << " 1)По названию фирмы" << std::endl;
	std::cout << " 2)По виду работ" << std::endl;
	std::cout << " 3)По дате исполнения" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void printMenuSearch()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Вид поиска:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void printAction()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Действия с записью:" << std::endl;
	std::cout << " 1)Печать" << std::endl;
	std::cout << " 2)Изменить" << std::endl;
	std::cout << " 3)Удалить" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void printSubSetMenu(int size)
{
	std::cout << " Размер подмножества: " << size << "\n";
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Вывод на экран" << std::endl;
	std::cout << " 2)Вывод в файл" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

bool TryOpenFile(std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Невозможно открыть файл" << std::endl;
		return false;
	}
	file.close();
	return true;
}

std::string inputFileName()
{
	std::string filename;
	std::cout << "Введите имя файла:\n";
	std::cin >> filename;

	while (!TryOpenFile(filename))
	{
		std::cout << "Введите имя файла:\n";
		std::cin >> filename;
	}

	return filename;
}


int main()
{
	setlocale(LC_ALL, "rus");
	bool notEnd = true;
	Сontainer cont = Сontainer();
	Сontainer sub;
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
			cont.fileInput(std::fstream(filename, std::ios::in));
			break;
		case 2:
			consoleInput(cont);
			break;
		case 3:
			std::cout << "Введите имя файла:\n";
			std::cin >> filename;
			cont.fileOutput(std::fstream(filename, std::ios::in));
			break;
		case 4:
			consoleOutput(cont);
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
					std::cout << "Неверно введена команда!!" << std::endl;
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
					std::cout << "Введите название: ";
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
						std::cout << "Запись найдена \n";
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
								std::cout << "Неверно введена команда!" << std::endl;
								break;
							}
						}
					}
					else
						std::cout << "Запись не найдена\n";
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
						std::cout << "Запись найдена \n";
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
								std::cout << "Неправильно введена команда!" << std::endl;
								break;
							}

						}
					}
					else
						std::cout << "Запись не найдена \n";
					fl = false;
					break;
				case 2:
					std::cout << "Введите вид: ";
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
						std::cout << "Запись найдена \n";
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
							std::cout << "Неправильно введена команда!" << std::endl;
							break;
						}

					}
					else
						std::cout << "Запись не найдена \n";
					fl = false;
					break;
				case 0:
					fl = false;
					break;
				default:
					std::cout << "Неправильно введена команда!" << std::endl;
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
					std::cout << "Введите название фирмы: ";
					std::cin >> str;
					//cont.findSubSetByName(str);
					sub = cont.findSubSetByName(str);
					fl = true;
					while (fl)
					{
						printSubSetMenu(sub.size());
						std::cin >> c;
						switch (c)
						{
						case 1:
							consoleOutput(sub);
							fl = false;
							break;
						case 2:
							std::cout << "Введите имя файла:\n";
							std::cin >> filename;	
							cont.fileOutput(std::fstream(filename, std::ios::out));
							fl = false;
							break;
						case 0:
						fl = false;
							break;
						default:
							std::cout << "Неправильно введена команда!" << std::endl;
							break;
						}
						
					}
					break;
				case 3:
					std::cout << "Введите дату: ";
					sub = cont.findSubSetByDate(inputDate());
					fl = true;
					while (fl)
					{
						printSubSetMenu(sub.size());
						std::cin >> c;
						
						switch (c)
						{
						case 1:
							consoleOutput(sub);
							fl = false;
							break;
						case 2:
							std::cout << "Введите имя файла:\n";
							std::cin >> filename;
							cont.fileOutput(std::fstream(filename, std::ios::out));
							fl = false;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "Неправильно введена команда!" << std::endl;
							break;
						}
						
					}
					break;
				case 2:
					std::cout << "Введите тип: ";
					std::cin >> str;
					sub = cont.findSubSetByType(str);
					fl = true;
					while (fl)
					{
						
						printSubSetMenu(sub.size());
						std::cin >> c;
						
						switch (c)
						{
						case 1:
							consoleOutput(sub);
							fl = false;
							break;
						case 2:
							std::cout << "Введите имя файла:\n";
							std::cin >> filename;
							cont.fileOutput(std::fstream(filename, std::ios::out));
							fl = false;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "Неправильно введена команда!" << std::endl;
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
			std::cout << "Такой команды нет! Повторите ввод!" << std::endl;
			break;
			}

	}
    return 0;
}



