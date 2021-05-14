#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<queue>
#include"FCFS.h"
#include"SJF.h"

using namespace std;
//系统函数：sleep,keygo


//用户函数
//set
int time_unit = 2;
const int maxnum = 10;
int num = 5;
PCB pcbdata[maxnum] = {
	{1000,"A",0,4,4,0,'R'},
	{1001,"B",1,3,3,0,'R'},
	{1002,"C",2,5,5,0,'R'},
	{1003,"D",3,2,2,0,'R'},
	{1004,"E",4,4,4,0,'R'}
};

PCB pcb2[4] = {
	{1000,"P1",10,	8,	8,	0,	'R'},
	{1001,"P2",12,	12,	12,	0,	'R'},
	{1002,"P3",14,	4,	4,	0,	'R'},
	{1003,"P4",16,	6,	6,	0,	'R'}
};


//调度函数
/*
void FCFS() {
	//以到达顺序进行排序
	int i, j, temp;
	double k;
	for (int i = 0; i < 5; i++) {
		order[i] = ready[i] = pcbdata[i].time_start;
	}

	for (i = 0; i < num; i++) {
		for (j = i; j < num; j++) {
			if (order[i] > order[j]) {
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
				temp = ready[i];
				ready[i] = ready[j];
				ready[j] = temp;
			}

		}
	}

	printf("--FCFS--\n");
	temp = pcbdata[ready[0]].time_start;
	for (i = 0; i < num; i++) {
		cout << "the " << i + 1 << " process--" << pcbdata[ready[i]].name << endl;
		printf("arrival -- %d,service -- %d\n", pcbdata[ready[i]].time_start, pcbdata[ready[i]].time_need);
		printf("processing.......");
		_sleep(1);
		printf("process done.\n");
		temp += pcbdata[ready[i]].time_need;
		j = temp - pcbdata[ready[i]].time_start;
		k = (float)j / pcbdata[ready[i]].time_need;
		printf("done -- %d, turnaround -- %d, weighted turnaround -- %.1f\n",
			temp, j, k);
	}
	printf("--all process done--\n");

}
*/
/*
void SJF() {//短作业优先
	int i, j, temp;
	double k;
	for (i = 0; i < 4; i++) {
		order[i] = pcb2[i].time_need;
		ready[i] = i;
	}

	bubble_sort(4, order);
	bubble_sort(num, ready);

	printf("--SJF--\n");
	temp = pcb2[ready[0]].time_start;
	for (i = 0; i < 4; i++) {
		cout << "the " << i + 1 << " process--" << pcb2[ready[i]].name << endl;
		printf("arrival -- %d,service -- %d\n", pcb2[ready[i]].time_start, pcb2[ready[i]].time_need);
		printf("processing.......");
		_sleep(1);
		printf("process done.\n");
		temp += pcb2[ready[i]].time_need;
		j = temp - pcb2[ready[i]].time_start;
		k = (float)j / pcb2[ready[i]].time_need;
		printf("done -- %d, turnaround -- %d, weighted turnaround -- %.1f\n",
			temp, j, k);
	}
	printf("--all process done--\n");
}
*/
void HRF() {//高相应比算法

}

void Timeslice() {//按照先来先服务并且使用时间片轮转

}

void MRLA() {//多级反馈调度队列，抢占式调度

}

void main() {
	int i = 0, sch = 99;
	while (sch != 0) {
		FCFS f(5,pcbdata); f.print();
		//SJF s(4, pcb2); s.print();

		//FCFS();
		//SJF();

		getchar();
	}
}