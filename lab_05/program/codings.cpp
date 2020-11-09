#include "codings.h"

using namespace std;


void vigenere_code(string& str, string key)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = (str[i] + key[i % key.length()]) % 256;
}

void dec_vigenere_code(string& str, string key)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = (str[i] - key[i % key.length()]) % 256;
}


/*void xor_modify(string& str, string key)
{
	if (str.length() >= key.length())
		for (size_t i = 0; i < str.length() - key.length() + 1; i++)
			for (size_t j = 0; j < key.length(); j++)
				str[i + j] = (str[i + j] ^ key[j]) % 256;
	else
		for (size_t i = 0; i < str.length(); i++)
			str[i] = (str[i] ^ key[i]) % 256;
}*/

void xor_simple(string& str, string key)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = (str[i] ^ key[0]) % 256;

	//if (key.length() > 1)
		for (size_t i = 0; i < str.length(); i += 3)
			str[i] = (str[i] ^ key[1]) % 256;
}

void dec_xor_modify(string& str, string key)
{
	if (str.length() >= key.length())
		for (size_t i = 0; i < str.length() - key.length() + 1; i++)
			for (size_t j = 0; j < key.length(); j++)
				str[i + j] = (str[i + j] ^ key[j]) % 256;
	else
		for (size_t i = 0; i < str.length(); i++)
			str[i] = (str[i] ^ key[i]) % 256;
}

void transposition(string& str)
{
	char temp;

	for (size_t i = 0; i < str.length() - 1; i += 2)
	{
		temp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = temp;
	}

	for (size_t i = 0; i < str.length() / 2; i += 2)
	{
		temp = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = temp;
	}
}

void dec_transposition(string& str)
{
	char temp;

	for (size_t i = 0; i < str.length() - 1; i += 2)
	{
		temp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = temp;
	}

	for (size_t i = 0; i < str.length() / 2; i += 2)
	{
		temp = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = temp;
	}
}