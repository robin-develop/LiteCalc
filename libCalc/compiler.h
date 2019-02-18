#pragma once
#include "exp.h"


#include <string>
#include <list>

namespace calc
{

struct token
{
	int code;
	size_t line;
	int pos, len;

	value_t num;
	std::wstring str;
};

struct result
{
	exp* node;
	std::list<std::wstring> errors;
	std::list<std::pair<token, std::list<int>>> suggestions;
};

class compiler final
{
public:
	compiler();
	~compiler();
	result compile(const std::wstring& str) const;
private:
	void * _parser;
};

}
