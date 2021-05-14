#pragma once
#include<iostream>
#include<string>
using namespace std;

typedef struct pcb PCB;
struct pcb {
	int id;
	string name;
	int time_start;		//开始时间
	int time_need;		//服务时间
	int time_left;		//剩余时间
	int time_used;		//已服务时间
						//need = left + used
	char state;
};