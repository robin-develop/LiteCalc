#pragma once

#include <string>
#include <list>
#include <memory>
#include <map>

namespace calc
{

struct callee;

using value_t = long double;

class eval_exception : std::exception
{
public:
	explicit eval_exception(std::wstring error)
		:_error(std::move(error))
	{

	}
	const char* what() const override
	{
		return "error";
	}

	const std::wstring& error() const
	{
		return _error;
	}
private:
	std::wstring _error;
};

struct state
{
	// extern functions
	std::map<std::wstring, std::shared_ptr<callee>> functions;
	bool add(callee* function);
	void remove(const std::wstring& name);
	value_t call(const value_t& self, const std::wstring& name, const std::list<value_t>& parameters);
};

}
