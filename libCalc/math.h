#pragma once

#include "callee.h"

#include <cmath>

namespace math
{
	struct pow : calc::callee
	{
		pow():callee(L"pow"){}
		calc::value_t run(calc::state& state, const calc::value_t& self,
			const std::list<calc::value_t>& parameters) const override
		{
			if (parameters.size() != 1) throw calc::eval_exception(L"parameter count of pow is 1");
			return std::pow(self, *parameters.begin());
		}
	};

	struct sqrt : calc::callee
	{
		sqrt() :callee(L"sqrt") {}
		calc::value_t run(calc::state& state, const calc::value_t& self,
			const std::list<calc::value_t>& parameters) const override
		{
			if (!parameters.empty()) throw calc::eval_exception(L"parameter count of pow is 0");
			return std::sqrt(self);
		}
	};


	inline void import(calc::state& state)
	{
		state.add(new pow());
		state.add(new sqrt());
	}
}