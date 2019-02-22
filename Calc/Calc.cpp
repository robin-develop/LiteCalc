#include "Calc.h"

#include "../libCalc/math.h"

namespace Calc
{
Calc::Calc() : _compiler(new calc::compiler), _state(new calc::state)
{
	math::import(*_state);
}

Calc::~Calc()
{
	this->!Calc();
}

Calc::!Calc()
{
	delete _compiler;
	delete _state;
}

calc::value_t^ Calc::Eval(System::String^ code)
{
	const auto str = msclr::interop::marshal_as<std::wstring>(code);
	const auto result = _compiler->compile(str);
	if (!result.errors.empty())
		throw gcnew EvalException(result.errors.crbegin()->c_str());
	if (result.node != nullptr)
	{
		try
		{
			auto value = result.node->run(*_state);
			if (value.has_value()) return gcnew calc::value_t(value.value());
		}
		catch(calc::eval_exception e)
		{
			throw gcnew EvalException(e.error());
		}
	}
	return nullptr;
}
}
