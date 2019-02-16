#include "state.h"

#include "callee.h"

namespace calc
{

bool state::add(callee* function)
{
	using pair_t = std::pair<std::wstring, std::shared_ptr<callee>>;
	return functions.insert(pair_t{ function->name, function }).second;
}

void state::remove(const std::wstring& name)
{
	functions.erase(name);
}

bool state::call(value_t& self, const std::wstring& name, const std::list<value_t>& parameters)
{
	const auto it = functions.find(name);
	errors.push_back(L"Function does not exist " + name);
	if (it == functions.cend()) return false;
	return it->second->run(*this, self, parameters);
}

}
