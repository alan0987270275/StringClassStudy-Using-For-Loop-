#include<iostream>
#include<iomanip>
#include"String.h"
using namespace std;

String::String(const char *s ) // conversion/default constructor
	:length( (s!=0) ? strlen(s) : 0)
{
	setString(s);
}

String::String(const String &copys) // copy constructor
	: length(copys.length)
{
	setString(copys.sPtr);
}

String::~String() // destructor
{
	delete[]sPtr;
}

void String::setString(const char *s)
{
	sPtr = new char[length + 1];

	if (s != 0)
	{
		for (int i = 0; i < length + 1; i++)
			sPtr[i] = s[i];
	}
	else
		sPtr[0] = '\0';
}


const String &String:: operator=(const String &right) // assignment operator
{
	if (*this != right)
	{
		delete[]sPtr;
		length = right.length;
		setString(right.sPtr);
	}
	else
		cout << "Error!" << endl;
	return *this;
}

const String &String:: operator+=(const String &right) // concatenation operator
{
	int newlength = length + right.length;
	char *tempstring = new char[newlength + 1];
	for (int i = 0; i < length; i++)
		tempstring[i] = sPtr[i];
	int j = 0;
	for (int i = length; i < newlength; i++)
	{
		tempstring[i] = right.sPtr[j];
		j++;
	}
	tempstring[newlength] = '\0';
	delete[]sPtr;
	length = newlength;
	sPtr = tempstring;
	return *this;
}

bool String:: operator!() const // is String empty?
{
	if (length == 0)
		return true;
	else
		return false;
}

bool String:: operator==(const String &right) const // test s1 == s2
{
	if (length != right.length)
		return false;

	for (int i = 0; i < length; i++)
	{
		if (sPtr[i] != right.sPtr[i])
			return false;
	}
	return true;
}

bool String:: operator<(const String &right) const // test s1 < s2
{
	for (int i = 0; i<length; i++)
	{
		if (sPtr[i]>right.sPtr[i])
			return false;
	}
	return true;
}

bool String::operator>(const String &right) const
{
	for (int i = 0; i<length; i++)
	{
		if (sPtr[i]<right.sPtr[i])
			return false;
	}
	return true;
}

char &String:: operator[](int subscript) // subscript operator (modifiable lvalue)
{
	if (subscript < 0 || subscript >= length)
		cout << "Error!" << endl;
	return sPtr[subscript];
}

char String::operator[](int subscript) const // subscript operator (rvalue)
{
	if (subscript < 0 || subscript >= length)
		cout << "Error!" << endl;
	return sPtr[subscript];
}

String String::operator()(int index, int subscript) const // return a substring
{
	if (index >= length || subscript < 0 || index < 0)
		return "";
	int newlength = 0;

	if (index + subscript >= length || subscript == 0)
		newlength = length - index;
	else
		newlength = subscript;
	char *tempString = new char[newlength + 1];

	for (int i = 0; i < newlength; i++)
	{
		tempString[i] = sPtr[index];
		index++;
	}
	tempString[newlength] = '\0';
	String temp(tempString);
	delete[]tempString;
	return temp;
}

int String::getLength() const // return string length
{
	return length;
}

ostream &operator<<(ostream &output, const String &s)
{
	output << s.sPtr;
	return output;

}

istream &operator>>(istream &input, String &s)
{
	char inputword[100];
	input >> setw(100) >> inputword;
	return input;
}