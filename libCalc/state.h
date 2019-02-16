#pragma once

#include <string>
#include <list>
#include <memory>
#include <map>

namespace calc
{

struct callee;

using value_t = long double;

struct state
{
	// function
	std::map<std::wstring, std::shared_ptr<callee>> functions;
	bool add(callee* callee);
	void remove(const std::wstring& name);
	bool call(value_t& self, const std::wstring& name, const std::list<value_t>& parameters);
};

}
