#pragma once

#include <string>

class Log
{
public:
	enum EType {
		INFO,
		ERROR
	};

	enum ESymbol {
		ENDL,
		END
	};

public:
	Log();
	~Log();

	Log& operator<<(const char* info);
	Log& operator<<(const std::string& info);
	Log& operator<<(int info);
	Log& operator<<(ESymbol eSymbol);
	Log& show();
	Log& show(EType eType);

private:
	EType _type{ ERROR };
};

