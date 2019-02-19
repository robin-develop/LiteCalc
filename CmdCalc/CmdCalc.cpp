// CmdCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../libCalc/compiler.h"
#include "../libCalc/math.h"

#include <iostream>
#include <string>


int main()
{
	std::wstring line;

	calc::compiler comp;
	calc::state state;
	math::import(state);

	while(std::getline(std::wcin, line))
	{
		if (line.empty()) continue;

		auto result = comp.compile(line);
		if(!result.errors.empty())
		{
			for(auto& e : result.errors) std::wcerr << e << std::endl;
			continue;
		}
		{
			try 
			{
				if (result.node == nullptr) continue;;
				std::wcout << result.node->run(state) << std::endl;
			}
			catch(calc::eval_exception& e)
			{
				std::wcout << e.error() << std::endl;
			}
		}
	}
}

