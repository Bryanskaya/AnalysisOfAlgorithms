#ifndef CODINGS_H
#define CODINGS_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <mutex>
#include <thread>


using namespace std;


void vigenere_code(string& str, string key);
void dec_vigenere_code(string& str, string key);

void transposition(string& str);
void dec_transposition(string& str);

//void xor_modify(string& str, string key_letter);
void xor_simple(string& str, string key);
//void dec_xor_modify(string& str, string key);

#endif // CODINGS_H