#pragma once

#include "state.h"

namespace calc
{

/*
struct syntax
{
	unsigned line, pos;
	std::wstring str;

	explicit operator std::wstring() const
	{
		return L"(" + std::to_wstring(line) + L"," + std::to_wstring(pos) + L")" + L"'" + str + L"'";
	}
};
*/
struct node
{
	/*
	syntax stx;

	explicit node(syntax stx)
		:stx(std::move(stx))
	{
		
	}

	void error(state& state, const std::wstring& str) const
	{
		state.errors.push_back(std::wstring(stx) + str);
	}

	void warning(state& state, const std::wstring& str) const
	{
		state.warnings.push_back(std::wstring(stx) + str);
	}
	*/
	virtual ~node() = default;
	virtual bool run(state&) const = 0;
};

}