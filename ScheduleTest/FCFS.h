#pragma once
#include"Scheduling.h"

class FCFS : Scheduling{
private:

	virtual void init() {
		int i, j, temp;
		double k;
		for (int i = 0; i < num; i++) {
			order[i] = pcbs[i].time_start;
			ready[i] = i;
		}
	}

	virtual void schedule() {
		int i, j, temp;
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
	}

public:
	FCFS():Scheduling() {}
	FCFS(int num, PCB* r) : Scheduling(num, r) {}
	void print() {
		init();
		schedule();
		cout << "------------FCFS--------------"<<endl;
		Scheduling::print();
		cout << "------------Done--------------";
	}
};