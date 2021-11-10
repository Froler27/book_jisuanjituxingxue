#include "Log.hpp"
#include <iostream>

using namespace std;


Log::Log()
{
}


Log::~Log()
{
}

Log& Log::operator<<(const char* info)
{
	cout << info;
	return *this;
}

Log& Log::operator<<(const std::string& info)
{
	cout << info;
	return *this;
}

Log& Log::operator<<(int info)
{
	cout << info;
	return *this;
}

Log& Log::operator<<(ESymbol eSymbol)
{
	switch (eSymbol)
	{
	case Log::ENDL:
	{
		cout << endl;
	}
		break;
	case Log::END:
	{
		cout << "\n";
	}
		break;
	default:
		break;
	}
	return *this;
}

Log& Log::show()
{
	switch (_type)
	{
	case Log::INFO:
	{
		cout << "Info: ";
	}
		break;
	case Log::ERROR:
	{
		cout << "Error: ";
	}
		break;
	default:
		break;
	}
	
	return *this;
}

Log& Log::show(EType eType)
{
	_type = eType;
	return show();
}