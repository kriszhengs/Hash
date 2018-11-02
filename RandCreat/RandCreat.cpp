﻿// RandCreat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <set>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

const int Amount = 100000;
//const double rate =0.666;

void RandCreat(char *adress)
{
	srand((unsigned)time(NULL));
	set<string> names;
	FILE *fp;
	fopen_s(&fp, adress, "w");

	while (names.size() <= Amount)
	{
		int len = 5 + rand() % 5;
		string name = "";
		for (int i = 0; i<len; ++i)
		{
			name += rand() % 26 + 'a';
		}

		if (names.find(name) == names.end())
		{
			names.insert(name);
			fprintf(fp, "%s\n", name.c_str());
		}

	}

	fprintf(fp, "0");
	fclose(fp);
}


int main(int argc, char *argv[])
{
	//RandCreat("input.txt");

	for (int i = 1; i <= argc; ++i)
	{
		RandCreat(argv[i]);
	}

	return 0;

}

