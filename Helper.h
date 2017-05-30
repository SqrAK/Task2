#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include "Date.h"



class Order{
public:

	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	Order(std::string aname, std::string atype, std::string aunit, int apriceForOne, Date atime, int avolume)
	{
		name = aname;
		type = atype;
		unit = aunit;
		priceForOne = apriceForOne;
		time = atime;
		volume = avolume;
	}

	Order()
	{
		name = "";
		type = "";
		unit = "";
		priceForOne = 0;
		time = Date();
		volume = 0;
	}

	~Order()
	{
	}

	bool operator==(const Order& right) const
	{
	return	this->name == right.name;
	}

	bool operator < (const Order &ord)
	{
	return this->name == ord.name;
	}
};


std::ostream& operator <<(std::ostream &os, const Order &ord) {
	os <<	ord.name + "\t" +
			ord.type + "\t" +
			ord.unit + "\t" +
			std::to_string(ord.priceForOne) + "\t";
	os <<	ord.time;
	os <<	"\t" +	std::to_string(ord.volume) + "\n";
	return os;
}

std::istream& operator>> (std::istream& is, Order &ord)
{
	is >> ord.name;
	is >> ord.type;
	is >> ord.unit;
	is >> ord.priceForOne;
	std::string str;
	is >> str;
	Date::StrToDate(str, ord.time);
	is >> ord.volume;

	return is;
}

Order inputOrder();

//Predicats and Comparators

class NamePred
{
protected:
	std::string name;

public:
	NamePred(std::string n)
	{
		name = n;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.name == name;
	}
};


class TypePred
{
protected:
	std::string type;

public:
	TypePred(std::string s)
	{
		type = s;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.type == type;
	}
};



class DatePred
{
protected:
	Date date;

public:
	DatePred(Date s)
	{
		date = s;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.time == date;
	}
};

class NameComp
{
public:
	bool operator () (Order ord1, Order ord2)
	{
		return ord1.name < ord2.name;
	}
};


class TypeComp
{
public:
	bool virtual operator () (Order ord1, Order ord2)
	{
		return ord1.type < ord2.type;
	}
};


class DateComp
{
public:
	bool virtual operator () (Order ord1, Order ord2)
	{
		return ord1.time < ord2.time;
	}
};


class NameAcc
{
protected:
	std::string str;
	std::vector<Order>* v;

public:
	NameAcc(std::string s)
	{
		str = s;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.name == str)
			(*v).push_back(ord);
	}
};


class TypeAcc
{
protected:
	std::string str;
	std::vector<Order>* v;

public:
	TypeAcc(std::string s)
	{
		str = s;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.type == str)
			(*v).push_back(ord);
	}
};



class DateAcc
{
protected:
	Date date;
	std::vector<Order>* v;

public:
	DateAcc(Date d)
	{
		date = d;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.time == date)
			(*v).push_back(ord);
	}
};



template <class O>
class AbsСontainer
{
public:

	AbsСontainer(int size)
	{
		vect = std::vector<O>(size);
	}

	AbsСontainer()
	{
		vect = std::vector<O>();
	}

	~AbsСontainer() {}

	bool add(O ord) {
		if (!find(ord))
		{
			vect.push_back(ord);
			return true;
		}
		else
			return false;
	}


	bool find(O ord, std::random_access_iterator_tag &it)
	{
		it = std::find(vect.begin(), vect.end(), ord);
		return it != vect.end()
	}

	bool find(O ord)
	{
		std::vector<O>::iterator it =
		std::find(vect.begin(), vect.end(), ord);
		return it != vect.end();
	}

	template<class Predicate>
	bool findBy(Predicate &pred, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> &it)
	{
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}
	
	template<class Comparator>
	bool findByBinary(Comparator &comp, O &bibb, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> &it)
	{
		std::sort(vect.begin(), vect.end(), comp);
		it = std::lower_bound(vect.begin(), vect.end(), bibb, comp);
		if (it == vect.end())
			return false;
		return true;
	}
	
	template<class Accomulator>
	void findSubSetBy(Accomulator acc)
	{
		std::for_each(vect.begin(), vect.end(), acc);
		subv = acc.getSet();
	}
	

	int subSize()
	{
		return subv.size();
	}

protected:
	std::vector<O> vect;
	std::vector<O> subv;
};



template <class O = Order>
class Сontainer : public AbsСontainer<Order>
{
public:

	void remove(std::vector<Order>::iterator it) {
		vect.erase(it);
	}

	void change(std::vector<Order>::iterator &it) {
		inputOrderChange(it);									
	}


	bool findByName(std::string name, std::vector<Order>::iterator &it)
	{
		NamePred &pred = NamePred(name);

		return findBy(pred, it);
	}

	bool findByType(std::string type, std::vector<Order>::iterator &it)
	{
		TypePred pred = TypePred(type);

		return findBy(pred, it);
	}

	bool findByDate(Date date, std::vector<Order>::iterator &it)
	{
		DatePred pred = DatePred(date);

		return findBy(pred, it);
	}

	bool findByNameBinary(std::string name, std::vector<Order>::iterator &it)
	{
		NameComp comp = NameComp();
		O bibb = Order( name, "", "", 0, Date(), 0);

		return findByBinary(comp, bibb, it) && it->name == name;
	}


	bool findByTypeBinary(std::string type, std::vector<Order>::iterator &it)
	{
		TypeComp comp = TypeComp();
		O bibb = Order("", type, "", 0, Date(), 0);

		return findByBinary(comp, bibb, it) && it->type == type;
	}

	bool findByDateBinary(Date date, std::vector<Order>::iterator &it)
	{
		DateComp comp = DateComp();
		O bibb = Order("", "", "", 0, date, 0);

		return findByBinary(comp, bibb, it) && it->time == date;
	}


	void findSubSetByName(std::string s)
	{
		NameAcc acc = NameAcc(s);

		findSubSetBy(acc);
	}

	void findSubSetByType(std::string s)
	{
		TypeAcc acc = TypeAcc(s);

		findSubSetBy(acc);
	}

	void findSubSetByDate(Date d)
	{
		DateAcc acc = DateAcc(d);

		findSubSetBy(acc);
	}



	void consoleInput() {
		vect.clear();
		O ord;
		while (true) {
			try {
				ord = inputOrder();
			}
			catch (const char* str) {
				return;
			}

			add(ord);
		}
	}

	void consoleOutput()
	{
		if (vect.size() != 0)
		{
			printHead();
			copy(vect.begin(), vect.end(), std::ostream_iterator<O>(std::cout, "\n"));
		}
		else
		{
			std::cout << "Пусто\n";
		}
	}

	void consoleOutputSub()
	{
		printHead();
		copy(subv.begin(), subv.end(), std::ostream_iterator<O>(std::cout, "\n"));
	}

	void fileInput(std::string fn) {
		std::fstream fin(fn, std::ios::in);
		if (fin.is_open()) {
			std::istream_iterator<O> is(fin);
			vect.clear();
			O ord = *is++;
			while (!fin.fail() && !fin.eof()) {
				add(ord);
				ord = *is++;
			}
			//if (!fin.fail() && !fin.eof())
				add(ord);
			fin.close();
		}
		else
			std::cout << "Файл не существует!" << std::endl;		
	}

	void fileOutput(std::string fn) {
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open()) {
			copy(vect.begin(), vect.end(), std::ostream_iterator<O>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "Ошибка открытия файла!" << std::endl;		
	}


	void fileOutputSub(std::string fn)
	{
		std::fstream fout(fn, std::ios::out);
		if (fout.is_open())
		{
			copy(subv.begin(), subv.end(), std::ostream_iterator<O>(fout, "\n"));
			fout.close();
		}
		else
		{
			std::cout << "Ошибка открытия файла!";
		}
	}
};


//-----------------helpers------------------
int inputInt(std::string message = "", int min = 0, int max = 10000) {
	std::string str;
	int res;

	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "skip") return 0;
			if (str == "exit") throw "exit";
			res = std::stoi(str);
			while (res < min || res > max) {
				std::cout << "Ошибка (значение < " << min << " или значение > " << max << "). Повтор: "; 
				std::cin >> res;
			}
			return res;
		}
		catch (std::exception &e) {
			std::cout << "Ошибка! Направильно введено число" << std::endl;			
		}
	}
}

Date inputDate(std::string message = "Введите дату по формату: mm:hh/dd/mm/yyyy : ") {		
	Date date = Date();

	std::string buf;
	bool ok = false;
	while (!ok)
	{
		std::cout << message;
		std::cin >> buf;
		if (buf == "exit") throw "exit";
		if (buf == "skip") return Date();
		ok = Date::StrToDate(buf, date);
		if (!ok)
			std::cout << "Неправильно введена дата!!!!";
	}
	return date;
}

Order inputOrder()
{
	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	std::cout << "-------------Заказ-------------" << std::endl;
	std::cout << "Введите \"exit\" для выхода" << std::endl;

	std::cout << "Введите название фирмы: ";
	std::cin >> name;	
	if (name == "exit") throw "exit";

	std::cout << "Введите вид работ: ";
	std::cin >> type;
	if (type == "exit") throw "exit";

	std::cout << "Введите единицу измерения: ";
	std::cin >> unit;
	if (unit == "exit") throw "exit";
	
	priceForOne = inputInt("Введите стоимость единицы выполненной работы: ");
	
	time = inputDate();
	
	volume = inputInt("Введите объем работ: ");


	return Order(name, type, unit, priceForOne, time, volume);
}


Order inputOrderAdd(Сontainer<Order> &c)
{
	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	std::cout << "-------------Заказ-------------" << std::endl;
	std::cout << "Введите \"exit\" для выхода" << std::endl;

	std::cout << "Введите название фирмы: ";
	std::cin >> name;

	std::cout << "Введите вид работ: ";
	std::cin >> type;

	std::cout << "Введите единицу измерения: ";
	std::cin >> unit;

	priceForOne = inputInt("Введите стоимость единицы выполненной работы: ");

	time = inputDate();

	volume = inputInt("Введите объем работ: ");


	return  Order(name, type,unit, priceForOne, time, volume);
}


void inputOrderChange(std::vector<Order>::iterator &it)
{
	std::cout << "-------------Заказ-------------" << std::endl;
	std::cout << "Введите \"skip\" для пропуска" << std::endl;

	std::string StrName;
	std::cout << "Введите название фирмы(сейчас: " + it->name + "): ";
	std::cin >> StrName;
	if (StrName != "skip")  it->name = StrName;

	std::string strType;
	std::cout << "Введите вид работ(сейчас: " + it->type + "): ";
	std::cin >> strType;
	if (strType != "skip") it->type = strType;

	std::string strUnit;
	std::cout << "Введите единицу измерения(сейчас: " + it->unit + "): ";
	std::cin >> strUnit;
	if (strUnit != "skip") it->unit = strUnit;

	int tmp;
	tmp = inputInt("Введите стоимость единицы выполненной работы(сейчас: " + std::to_string(it->priceForOne) + "): ");
	if (tmp != 0) it->priceForOne = tmp;

	std::string curDate = it->time.to_string();
	Date dt = inputDate("Введите дату по формату(mm:hh/dd/mm/yyyy)( сейчас: " + curDate + ")");
	Date defDt = Date();
	if (dt == defDt);
	else it->time = dt;


	tmp = inputInt("Введите объем работ( сейчас: " + std::to_string(it->volume) + "): ");
	if (tmp != 0) it->volume = tmp;

}

static void printHead()
{
	std::cout << "Название\t" << "Вид\t"<< "Единица измерения\t" << " Стоимость единицы\t" << "Дата\t\t" << "Объем\n";
}



