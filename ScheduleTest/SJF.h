#pragma once
#include"Scheduling.h"
#include<vector>
using namespace std;

class SJF : Scheduling {
private:

	virtual void init() {
		int i, j, temp;
		double k;
		for (int i = 0; i < num; i++) {
			//i：pcbs中的序号
			order[i] = pcbs[i].time_need;
			ready[i] = i;
		}
	}

	virtual void schedule() {
		int doneCount = 0;
		int* doneProcess = new int[num];//[i]:第i个进程是否已经完成 0:未完 1：完成
		for (int i = 0; i < num; i++) { doneProcess[i] = 0; }
		int nowTime=500, temp=0;
		//找出最先开始的进程
		for (int i = 0; i < num; i++) {
			if (pcbs[i].time_start < nowTime) { nowTime = pcbs[i].time_start; temp = i; }
		}
		//将其加入完成队列
		doneProcess[temp] = 1;
		ready[doneCount] = temp;
		doneCount++;
		vector<int> inready;
		while(doneCount < num) {
			nowTime += pcbs[temp].time_need;
			inready.clear();

			//将此刻到达等待队列的进程加入集合
			for (int i = 0; i < num; i++) {
				if (doneProcess[i] == 0 && pcbs[i].time_start <= nowTime)
					inready.push_back(i);
			}
			//找出等待队列的最小服务时间的进程序号
			int nowMin = -1;
			for (int i = 0; i < inready.size(); i++) {
				if (nowMin == -1 || (nowMin > pcbs[inready[i]].time_need))
				{
					nowMin = pcbs[inready[i]].time_need;
					temp = inready[i];
				}
			}
			//加入排序好的队列
			doneProcess[temp] = 1;
			ready[doneCount] = temp;
			doneCount++;
		}
	}

public:
	SJF() :Scheduling() {}
	SJF(int num, PCB* r) :Scheduling(num, r) {}

	void print() {
		init();
		schedule();
		cout << "------------SJF--------------" << endl;
		Scheduling::print();
		cout << "------------Done--------------";
	}
};