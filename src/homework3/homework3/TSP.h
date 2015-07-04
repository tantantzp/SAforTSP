#ifndef TSP_H
#define TSP_H

#include "iostream"
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

static ifstream fin;
static ofstream fout;

class Node         //���нڵ��� 
{
public:
	double x,y;
	char name;
	void set(double a, double b, char c){ x = a, y = b, name = c;}
};

class Node_map         //���нڵ��ͼ�� 
{
public:
	int N;
	Node* node;
    double** length_table;        //���о������ 

	Node_map(int n);
	~Node_map();
	void init();
	void cacu_distance();          //���������� 
};

class Path             //·���� 
{
public:
	double length;        //·������ 
	int N;                //������ 
	int* route;           //·��������� 
	Node_map* node_map;

	Path(int n, Node_map* nm);
	~Path(){ delete []route; }
	void randon_route();
	void cacu_length();        //����·������ 
	void change();             //�����½� 
	void output();
    bool operator < ( Path& p );
	void operator =( Path& p);
};

class TSP            //�������࣬ ģ���˻��㷨
{
public:
	int N;
	int initial_temp;           //��ʼ�¶�
	int L;                      //ÿ���¶��µ�ѭ������
	double speed;               //�¶��½��ٶ� 
    Node_map* node_map;
	Path* best_path;
	Path* temp_path;

	TSP(int n)
	{
	    N = n;
		initial_temp = 3000;
		speed = 0.98;
		L = 1000 * N;
		node_map = new Node_map(N);
		node_map->init();
		best_path = new Path(N, node_map);
		temp_path = new Path(N, node_map);
		temp_path->randon_route();
	}
	~TSP() 
	{
	    delete node_map;
		delete best_path;
		delete temp_path;
	}

	void tsp();
};


#include "TSP_implementation.h"

#endif