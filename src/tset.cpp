// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h" 

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования 
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа 
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить максимальное к-во эл-тов 
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const //проверка на элемент множества 
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества 
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества 
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции 

TSet& TSet::operator=(const TSet &s) // присваивание 
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение множеств 
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение множеств 
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение множеств 
{
	TSet tmp(BitField | s.BitField);
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом 
{
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) //вычитание элемента 
{
	TSet tmp(*this);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение множеств 
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // дополнение 
{
	TSet tmp(~BitField);
	return tmp;
}


// перегрузка ввода/вывода 

istream &operator»(istream &istr, TSet &s) // ввод 
{
	int tmp;
	char ch;
	do { istr » ch; } while (ch != '{');
	do {
		istr » tmp;
		s.InsElem(tmp);
		do { istr » ch; } while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return istr;

}

ostream& operator«(ostream &ostr, const TSet &s) // вывод 
{
	char ch = ' ';
	ostr « '{';
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i))
		{
			ostr « ch « i;
			ch = ',';
		}
	}
	ostr « '}';
	return ostr;
}