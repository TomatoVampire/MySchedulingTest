#pragma once
#include"Scheduling.h"
#include<vector>

class HRF : Scheduling {
private:
	//响应比
	double* Rp;

	virtual void init() {

	}

	virtual void schedule() {
		int doneCount = 0;
		int* doneProcess = new int[num];//[i]:第i个进程是否已经完成 0:未完 1：完成
		for (int i = 0; i < num; i++) { doneProcess[i] = 0; }
		int nowTime = 500, temp = 0;
		//找出最先开始的进程
		for (int i = 0; i < num; i++) {
			if (pcbs[i].time_start < nowTime) { nowTime = pcbs[i].time_start; temp = i; }
		}
		//将其加入完成队列
		doneProcess[temp] = 1;
		ready[doneCount] = temp;
		doneCount++;
		vector<int> inready;
		while (doneCount < num) {
			cout << "Now time: " << nowTime;
			cout << "	process: " << pcbs[temp].name << "	service: " << pcbs[temp].time_left;
			cout << "	Rp: " << Rp[temp] << endl;
			nowTime += pcbs[temp].time_need;
			inready.clear();

			//将此刻到达等待队列的进程加入集合
			for (int i = 0; i < num; i++) {
				if (doneProcess[i] == 0 && pcbs[i].time_start <= nowTime)
					inready.push_back(i);
			}
			//找出等待队列的最大相应比的进程序号
			double nowMax = -1;
			for (int i = 0; i < inready.size(); i++) {
				//优先权=等待时间/服务时间+1
				Rp[inready[i]] = 1.0 + (double)(nowTime - pcbs[inready[i]].time_start) / pcbs[inready[i]].time_need;
				if (nowMax == -1 || (nowMax < Rp[inready[i]]))
				{
					nowMax = Rp[inready[i]];
					temp = inready[i];
				}
			}
			//加入排序好的队列
			doneProcess[temp] = 1;
			ready[doneCount] = temp;
			doneCount++;
		}
		cout << "Now time: " << nowTime;
		cout << "	process: " << pcbs[temp].name << "	service: " << pcbs[temp].time_left;
		cout << "	Rp: " << Rp[temp] << endl;
	}

	int findMax() {
		int max = -1, maxi=0;
		for (int i = 0; i < num; i++) {

		}
	}

public:
	HRF() :Scheduling() {}
	HRF(int num, PCB* r) :Scheduling(num, r) {
		Rp = new double[num];
		for (int i = 0; i < num; i++) Rp[i] = 0.0;
	}
	void print() {
		init();
		cout << "------------HRF---------------" << endl;
		schedule();
		cout << "------------Done--------------\n";
	}
};