
#include <iostream>
#include <vector>

class Token {
public:
	const char* ptr;
	int len;
	long type; // todo, long -> enum or enum class
public:
	Token(const char* ptr, int len) :
		ptr(ptr), len(len), type(0)
	{
		//
	}
};


std::vector<Token> GetTokens(const char* text, int len) {
	std::vector<Token> token_vec;

	int token_start_idx = 0;
	int token_end_idx = 0;
	long state = 0;

	for (int i = 0; i < len; ++i) {
		if (0 == state && isspace(text[i])) {
			if (token_end_idx - token_start_idx > 0) {
				// push
				token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));
			}
			token_start_idx = i + 1;
			token_end_idx = token_start_idx;
		}
		else if (0 == state && '\"' == text[i]) {
			if (token_end_idx - token_start_idx > 0) {
				// push
				token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));
			}
			token_start_idx = i;
			token_end_idx = i + 1;
			state = 1;
		}
		else if (1 == state && '\"' == text[i]) {
			state = 0;

			token_end_idx = i + 1;

			// push
			token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));

			token_start_idx = i + 1;
		}
		else if (0 == state && '=' == text[i]) {
			if (token_end_idx - token_start_idx > 0) {
				// push
				token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));
			}

			token_start_idx = i;
			token_end_idx = i + 1;

			token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));
		
			token_start_idx = i + 1;
			token_end_idx = i + 1;
		}
		else {
			token_end_idx = i + 1;
		}
	}

	if (token_end_idx - token_start_idx > 0) {
		// push
		token_vec.push_back(Token(text + token_start_idx, token_end_idx - token_start_idx));
	}
	
	return token_vec;
}

void test(const char* text) {
	std::vector<Token> vec;

	vec = GetTokens(text, strlen(text));

	for (auto& x : vec) {
		for (int i = 0; i < x.len; ++i) {
			std::cout << x.ptr[i];
		}
		std::cout << "\n";
	}
}

int main(void)
{
	const char* text = " x = 1 y = 2 z = \"Hello World!\" ";
	const char* text2 = "x=12 y=33 z=44";
	const char* text3 = "x=y=z";

	test(text);
	std::cout << "\n";
	test(text2);
	std::cout << "\n";
	test(text3);

	return 0;
}

