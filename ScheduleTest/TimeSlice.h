#pragma once
#include"Scheduling.h"
#include<queue>
class TimeScale : Scheduling{
private:
	int slice;
	int* sort;
	int roundnum;
	virtual void init() {
		int i, j, temp;
		double k;
		for (int i = 0; i < num; i++) {
			order[i] = pcbs[i].time_start;
			sort[i] = i;
		}
		for (i = 0; i < num; i++) {
			for (j = i; j < num; j++) {
				if (order[i] > order[j]) {
					temp = order[i];
					order[i] = order[j];
					order[j] = temp;
					//sort为排序好开始时间的进程序号
					temp = sort[i];
					sort[i] = sort[j];
					sort[j] = temp;
				}

			}
		}
	}

	virtual void schedule() {
		queue<int> inready;//就绪队列？
		int doneCount = 0;
		int* doneProcess = new int[num];//[i]:第i个进程是否已经完成 0:未完 1：完成
		for (int i = 0; i < num; i++) { doneProcess[i] = 0; }
		int nowTime = 500, temp = 0;
		int* tempready = new int[500];
		//找出最先开始的进程
		for (int i = 0; i < num; i++) {
			if (pcbs[i].time_start < nowTime) { nowTime = pcbs[i].time_start; temp = i; }
		}
		inready.push(temp);
		while (!DoneAll(doneProcess)) {
			int top = inready.front();
			inready.pop();
			tempready[roundnum] = top;
			pcbs[top].time_used += slice;
			pcbs[top].time_left -= slice;
			if (pcbs[top].time_left <= 0) {
				doneProcess[top] = 1;
				nowTime += slice + pcbs[top].time_left;
			}
			else nowTime += slice;
			//入队列
			for (int i = 0; i < num; i++) {
				if (!doneProcess[sort[i]] || (pcbs[sort[i]].time_start <= nowTime))
				{
					inready.push(sort[i]);
				}
			}
			if (pcbs[top].time_left > 0)
				inready.push(top);
			roundnum++;
		}

		//todo:ready
		ready = new int[roundnum];
		for (int i = 0; i < roundnum; i++) {
			ready[i] = tempready[i];
		}
	}

	bool DoneAll(int* d) {
		for (int i = 0; i < num; i++) {
			if (d[i] == 0) return false;
		}
		return true;
	}

public:
	TimeScale() :Scheduling() {}
	TimeScale(int num,int slice, PCB* r) :slice(slice) {
		order = new int[num];
		sort = new int[num];
		roundnum = 0;
	}//暂时不初始化ready
	void print() {
		//todo
		num = 0;
	}
};