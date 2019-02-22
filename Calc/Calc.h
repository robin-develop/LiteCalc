#pragma once

#include "../libCalc/stmt.h"
#include "../libCalc/compiler.h"
#include <msclr/marshal_cppstd.h>
namespace Calc
{
public ref class Memory
{
public:
	property System::String^ Name;
	property calc::value_t^ Value;
};

public ref class EvalException : System::Exception
{
public:
	EvalException(){}
	explicit EvalException(const std::wstring& str)
	{
		Message = gcnew System::String(str.c_str());
	}
	System::String^ Message;
};

public ref class Calc
{
public:
	Calc();
	~Calc();
	!Calc();
	
	calc::value_t^ Calc::Eval(System::String^ code);

	property System::Collections::Generic::List<Memory^>^ Variables
	{
		System::Collections::Generic::List<Memory^>^ get()
		{
			auto list = gcnew System::Collections::Generic::List<Memory^>;
	
			for(auto &n : _state->variables)
			{
				auto memory = gcnew Memory;
				memory->Name = gcnew System::String(n.first.c_str());
				memory->Value = n.second;
				list->Add(memory);
			}
			return list;
		}
	}

private:
	calc::compiler* _compiler;
	calc::state* _state;
};

}
