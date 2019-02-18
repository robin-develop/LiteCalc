// CmdCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../libCalc/compiler.h"

#include <iostream>
#include <string>


int main()
{
	std::wstring line;

	calc::compiler comp;
	calc::state state;
	while(std::getline(std::wcin, line))
	{
		auto result = comp.compile(line);
		if(!result.errors.empty())
		{
			for(auto& e : result.errors) std::wcerr << e << std::endl;
			continue;
		}

		calc::value_t value;
		if(result.node->run(state, value))
		{
			std::wcout << value << std::endl;
		}
	}
}

