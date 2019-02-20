#pragma once

#include "exp.h"
#include <memory>
#include <string>
#include <optional>

namespace calc
{
namespace stmt
{
struct stmt
{
	stmt() = default;
	virtual ~stmt() = default;
	virtual std::optional<value_t> run(state& state) const = 0;
};

struct exp final: stmt
{
	std::shared_ptr<calc::exp::exp> expr;

	explicit exp(calc::exp::exp* exp):expr(exp){}
	std::optional<value_t> run(state& state) const override
	{
		return expr->run(state);
	}
};

struct assign final : stmt
{
	std::wstring name;
	std::shared_ptr<calc::exp::exp> expr;
	assign(std::wstring name, calc::exp::exp* expr):name(std::move(name)), expr(expr){}
	std::optional<value_t> run(state& state) const override
	{
		state.put(name, expr->run(state));
		return {};
	}
};
}
}
