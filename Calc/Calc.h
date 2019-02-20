#pragma once


using namespace System;


#include "../libCalc/stmt.h"
#include "../libCalc/compiler.h"

#include <msclr/marshal.h>

namespace Calc
{
public ref class Calc
{
public:
	Calc():_compiler(new calc::compiler), _state(new calc::state){}
	~Calc() { delete _compiler; delete _state; }

	String^ Eval(String^ code)
	{
		const auto str = msclr::interop::marshal_as<std::wstring>(code);
		const auto result = _compiler->compile(str);
		if(result.node != nullptr)
		{
			
		}
		return gcnew String("");
	}

private:
	calc::compiler* _compiler;
	calc::state* _state;
};

}
