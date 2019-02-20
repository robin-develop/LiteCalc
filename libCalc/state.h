#pragma once

#include <string>
#include <list>
#include <memory>
#include <map>
#include <optional>

namespace calc
{

struct callee;

using value_t = long double;

inline std::wstring to_string(const value_t& v)
{
	auto str = std::to_wstring(v);
	auto it = str.crbegin();
	size_t size = 0;
	while(it!= str.crend() && *it == L'0') ++it;
	if( *it==L'.') ++it;
	str.erase(str.size() - (it - str.crbegin()));
	if (str.empty()) return L"0";
	return str;
}

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
	// units
	std::map<std::wstring, value_t> units;
	value_t unit(value_t value, const std::wstring& name);

	// variables
	std::map<std::wstring, value_t> variables;
	const value_t& operator[](const std::wstring& name) const;
	void put(const std::wstring& name, value_t v);
	void erase(const std::wstring& name);
	void clear();
	
	// extern functions
	std::map<std::wstring, std::shared_ptr<callee>> functions;
	bool add(callee* function);
	void remove(const std::wstring& name);
	value_t call(const value_t& self, const std::wstring& name, const std::list<value_t>& parameters);
};

}
