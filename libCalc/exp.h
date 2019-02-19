#pragma once

#include "state.h"

#include <string>
#include <functional>
#include <cmath>


namespace calc
{

namespace exp
{
struct exp
{
	virtual ~exp() = default;
	virtual value_t run(state& state) const = 0;
};

struct number final : exp
{
	value_t value;

	explicit number(value_t v) : value(v)
	{
	}

	value_t run(state& state) const override
	{
		return value;
	}
};

struct parameters final
{
	explicit parameters(exp *e)
	{
		push_back(e);
	}

	parameters& push_back(exp* e)
	{
		params.push_back(std::shared_ptr<exp>(e));
		return *this;
	}

	std::list<std::shared_ptr<exp>> params;
};

struct caller final : exp
{
	std::shared_ptr<exp> self;
	std::wstring name;
	std::shared_ptr<parameters> params;
	caller(exp *self, std::wstring name, parameters* p) : self(self), name(std::move(name)), params(p)
	{
	}

	value_t run(state& state) const override
	{
		std::list<value_t> pv;
		if(params != nullptr)
		{
			for(const auto& n : params->params)
			{
				pv.push_back(n->run(state));
			}
		}
		return state.call(self->run(state), name, pv);
	}
};

struct unary : exp
{
	std::shared_ptr<exp> n;

	explicit unary(exp* n) : n(n)
	{
	}

	~unary() override = default;

	value_t run(state& state) const override
	{
		return run(state, n->run(state));
	}

	virtual value_t run(state&, value_t) const = 0;
};

struct negative final : unary
{
	explicit negative(exp* n) : unary(n)
	{
	}

	value_t run(state& state, value_t value) const override
	{
		return -value;
	}
};

struct binary : exp
{
	std::shared_ptr<exp> left, right;

	binary(exp* l, exp* r) : left(l), right(r)
	{
	}

	~binary() override = default;

	value_t run(state& state) const override
	{
		return run(state, left->run(state), right->run(state));
	}

	virtual value_t run(state& state, value_t l, value_t r) const = 0;
};

template <typename FunT>
struct basic_binary_operator : binary
{
	using fun_t = FunT;
	fun_t fun;

	basic_binary_operator(exp* l, exp* r) : binary(l, r)
	{
	}

	value_t run(state& state, value_t l, value_t r) const override
	{
		return fun(l, r);
	}
};

using add = basic_binary_operator<std::plus<>>;
using sub = basic_binary_operator<std::minus<>>;
using mul = basic_binary_operator<std::multiplies<>>;
using div = basic_binary_operator<std::divides<>>;

struct mod : binary
{
	mod(exp* l, exp* r) : binary(l, r) {}

	value_t run(state& state, value_t l, value_t r) const override
	{
		return std::fmod(l, r);
	}

};

struct variable : exp
{
	std::wstring name;

	variable(std::wstring name):name(std::move(name)){}

	value_t run(state& state) const override
	{
		return state[name];
	}

};

}
}
