// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <cstdio>
#include <vector>
using namespace rapidjson;
using namespace std;

int main(int argc, char* args[])
{
	ifstream ifs("D:/test.json");
	IStreamWrapper isw(ifs);
	Document d;
	d.ParseStream(isw);
	assert(d.IsObject());
	assert(d.HasMember("t"));
	assert(d["t"].IsBool());
	vector<int>* x = new vector<int>(0);
	const Value& a = d["a"].GetArray();
	for(SizeType i = 0; i < a.Size(); i++)
	{
		x->push_back(a[i].GetInt());
	}
	for (int i = 0; i < x->size(); i++)
		cout << x->at(i);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
