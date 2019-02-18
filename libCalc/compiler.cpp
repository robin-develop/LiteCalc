#include "compiler.h"

#include <string>
#include <sstream>


namespace calc
{
struct scanner final
{
	const wchar_t *start{}, *cur{}, *marker{}, *end{}, *begin{};
	size_t line{};
};

#define TOK_ERROR (-1)
#define TOK_END 0
#include "parser.h"

#include "parser.c"
#include "lex.cpp"

compiler::compiler()
	:_parser(ParseAlloc(malloc))
{
}

compiler::~compiler()
{
	ParseFree(_parser, free);
}

token* create_token(const int code, const scanner& scanner)
{
	auto token = new calc::token{ code, scanner.line, scanner.start - scanner.begin + 1, scanner.cur - scanner.start, {}, {} };
	switch (code)
	{
	case TOK_NUMBER:
		token->num = std::stold(std::wstring(scanner.start, scanner.cur));
		break;
	case TOK_IDENTITY:
		token->str = std::wstring(scanner.start, scanner.cur);
		break;
	default:
		break;
	}
	return token;
}

void process_suggestions(result& state, unsigned int code, scanner& scanner)
{
	if (!state.suggestions.empty())
	{
		for (auto &n : state.suggestions)
		{
			std::wostringstream oss;
			oss << L"(" << n.first.line << L"," << n.first.pos << L"):" << n.first.len;
			oss << L" " << yyTokenName[n.first.code];

			oss << L" Should be ";

			for (auto& nn : n.second)
				oss << yyTokenName[nn] << L" ";
			state.errors.push_back(oss.str());
		}
	}
}

result compiler::compile(const std::wstring& str) const
{
	scanner scanner;
	scanner.start = str.c_str();
	scanner.cur = scanner.start;
	scanner.end = scanner.start + str.size();
	scanner.marker = nullptr;

	scanner.begin = scanner.start;
	scanner.line = 1;


	result state{nullptr, {}, {}};
	for (;;)
	{
		const auto code = scan(scanner);
		const auto token = create_token(code, scanner);

		if (code == TOK_ERROR)
		{
			Parse(_parser, TOK_END, token, &state);
			std::wostringstream oss;
			oss << L"Error character";
			oss << L"(" << scanner.line << L"," << scanner.start - scanner.begin + 1 << L"):" << scanner.cur - scanner.start << L"";
			oss << L" " << L"'" << std::wstring(scanner.start, scanner.cur) << L"'";
			state.errors.push_back(oss.str());

			break;
		}

		Parse(_parser, code, token, &state);
		if (!state.errors.empty() || code == TOK_END)
		{
			process_suggestions(state, code, scanner);
			if (code != TOK_END)
				Parse(_parser, TOK_END, token, &state);
			break;
		}
	}

	return state;
}

}
