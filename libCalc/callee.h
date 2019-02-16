#pragma once


#include "state.h"

#include <string>

namespace calc
{

struct callee
{
	std::wstring name;
	callee(std::wstring name):name(std::move(name)){}

	virtual bool run(state& state, value_t& self, const std::list<value_t>& parameters) const = 0;
};

}
