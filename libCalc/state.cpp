#include "state.h"
#include "callee.h"

namespace calc
{

const value_t& state::operator[](const std::wstring& name) const
{
	const auto it = variables.find(name);
	if (it == variables.cend()) throw eval_exception(L"Variable doesn't exist " + name);
	return it->second;
}

void state::put(const std::wstring& name, value_t v)
{
	variables[name] = v;
}

void state::erase(const std::wstring& name)
{
	variables.erase(name);
}

void state::clear()
{
	variables.clear();
}


bool state::add(callee* function)
{
	using pair_t = std::pair<std::wstring, std::shared_ptr<callee>>;
	return functions.insert(pair_t{ function->name, function }).second;
}

void state::remove(const std::wstring& name)
{
	functions.erase(name);
}

value_t state::call(const value_t& self, const std::wstring& name, const std::list<value_t>& parameters)
{
	const auto it = functions.find(name);
	if (it == functions.cend()) throw eval_exception(L"Function does not exist " + name);
	return it->second->run(*this, self, parameters);
}

}
