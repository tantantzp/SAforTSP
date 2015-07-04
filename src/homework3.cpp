// homework3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TSP.h"
#include <ctime>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc == 3)
	{
		fin.open(argv[1]);
		fout.open(argv[2]);	
	}
	else
	{
		cout<<"homework1.exe input.txt output.txt";
		return 1;
		
	} 


	srand((unsigned int)time(0));
	int N;
	fin>>N;
	TSP tsp(N);
	tsp.tsp();
	tsp.best_path->output();
	system("pause");
	return 0;
}

