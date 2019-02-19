#pragma once

#include "exp.h"
#include <memory>
#include <string>


namespace calc
{
namespace stmt
{
struct stmt
{
	stmt() = default;
	virtual ~stmt() = default;
	virtual std::wstring run(state& state) const = 0;
};

struct exp final: stmt
{
	std::shared_ptr<calc::exp::exp> expr;

	explicit exp(calc::exp::exp* exp):expr(exp){}
	std::wstring run(state& state) const override
	{
		return std::to_wstring(expr->run(state));
	}
};

struct assign final : stmt
{
	std::wstring name;
	std::shared_ptr<calc::exp::exp> expr;
	assign(std::wstring name, calc::exp::exp* expr):name(std::move(name)), expr(expr){}
	std::wstring run(state& state) const override
	{
		state.variables[name] = expr->run(state);
		return {};
	}
};
}
}
