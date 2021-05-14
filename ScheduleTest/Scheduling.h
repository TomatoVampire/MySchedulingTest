#pragma once
#include<iostream>
#include<string>
#include"PCB.h"
using namespace std;

//系统挂起n秒
void _sleep(int n) {
	clock_t goal;
	goal = (clock_t)n * CLOCKS_PER_SEC + clock();
	while (goal > clock());
}

//升序排序
void bubble_sort(int size, int* a) {
	int i, j, temp;
	for (i = 0; i < size; i++) {
		for (j = i; j < size; j++) {
			if (a[i] > a[j]) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}

		}
	}
}

//非抢占式进程
class Scheduling {
protected:
	PCB* pcbs;	//所有进程的数据
	int num;	//总进程数?
	int* ready;	//就绪队列
	int* order;	//排序依据？

	//子类实现：
	virtual void init() = 0;
	virtual void schedule() = 0;
public:
	Scheduling() {}
	Scheduling(int num, PCB* r) :num(num), pcbs(r) {
		ready = new int[num];
		order = new int[num];
	}

	void print() {
		int i, j, temp;
		double k;
		temp = pcbs[ready[0]].time_start;
		for (i = 0; i < num; i++) {
			cout << "the " << i + 1 << " process--" << pcbs[ready[i]].name << endl;
			printf("arrival -- %d,service -- %d\n", pcbs[ready[i]].time_start, pcbs[ready[i]].time_left);
			printf("processing.......");
			_sleep(1);
			printf("process done.\n");
			temp += pcbs[ready[i]].time_need;
			j = temp - pcbs[ready[i]].time_start;
			k = (float)j / pcbs[ready[i]].time_need;
			printf("done -- %d, turnaround -- %d, weighted turnaround -- %.1f\n",
				temp, j, k);
		}
		//cout << "------------done--------------\n";
	}
};