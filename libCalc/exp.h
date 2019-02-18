#pragma once

#include "node.h"

namespace calc
{

struct exp
{
	virtual ~exp() = default;
	virtual bool run(state& state, value_t& value) const = 0;
};



struct unary : exp
{
	std::shared_ptr<exp> n;

	explicit unary(exp* n) : n(n) {}
	~unary() override = default;

	bool run(state& state, value_t& value) const override
	{
		if (!n->run(state, value)) return false;
		return run(state, value, value);
	}

	virtual bool run(state& state, value_t before, value_t& after) const = 0;
};

struct binary : exp
{
	std::shared_ptr<exp> left, right;

	binary(exp * l, exp * r) : left(l), right(r){}
	~binary() override = default;

	bool run(state& state, value_t& value) const override
	{
		value_t l{};
		if (!left->run(state, l)) return false;
		if (!right->run(state, value)) return false;
		return run(state, l, value, value);
	}

	virtual bool run(state& state, value_t l, value_t r, value_t& value) const = 0;
};


struct caller final : exp
{
	std::wstring name;
	caller(std::wstring name):name(std::move(name)){}
	bool run(state& state, value_t& value) const override
	{
		// TODO:
		return false;
	}
};

struct number final : exp
{
	value_t value;
	explicit number(value_t v) : value(v) {}

	bool run(state& state, value_t& value) const override
	{
		value = this->value;
		return true;
	}
};

struct negative final : unary
{
	explicit negative(exp* n) : unary(n) {}

	bool run(state& state, value_t before, value_t& after) const override
	{
		after = -before;
		return true;
	}
};

struct add final: binary
{
	add(exp* l, exp* r) : binary(l, r){}

	bool run(state& state, value_t l, value_t r, value_t& value) const override
	{
		value = l + r;
		return true;
	}
};

struct sub : binary
{
	sub(exp* l, exp* r) : binary(l, r) {}

	bool run(state& state, value_t l, value_t r, value_t& value) const override
	{
		value = l - r;
		return true;
	}
};

struct mul : binary
{
	mul(exp* l, exp* r) : binary(l, r) {}

	bool run(state& state, value_t l, value_t r, value_t& value) const override
	{
		value = l * r;
		return true;
	}
};

struct div : binary
{
	div(exp* l, exp* r) : binary(l, r) {}

	bool run(state& state, value_t l, value_t r, value_t& value) const override
	{
		// TODO: Need to check the r value that it does not equal to zero
		value = l / r;
		return true;
	}
};


}