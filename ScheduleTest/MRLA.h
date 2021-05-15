#pragma once
#include"Scheduling.h"
#include"MyQueue.h"

struct ProcessSlice {
	int no;//进程的序号
	int remain;//剩余时间片
	ProcessSlice(int no = 0, int remain = 0) :no(no), remain(remain) {}
};
typedef ProcessSlice PS;

class MRLA : Scheduling{
private:
	MyQueue<ProcessSlice> Q1, Q2, Q3;//三级就绪队列
	int slice1,slice2,slice3;//三级时间片长度
	int* sort;//到达时间

	void init() {
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

	void schedule() {
		//接下来进入第n个进程（进程序号取sort[n]）
		int nextprocessin = 1;
		int nowtime = 0;
		int* doneprocess = new int[num];
		int* hasentered = new int[num];
		for (int i = 0; i < num; i++) { doneprocess[i] = 0; hasentered[i] = 0; }
		//初始化
		Q1.push(ProcessSlice(sort[0], slice1));
		nowtime = pcbs[sort[0]].time_start;
		hasentered[sort[0]] = 1;
		while (!alldone(doneprocess)) {
			// 首要：是否有进程进入（开始时间-时间片结束时间/提前结束时间内是否有进程加入）
			// 判断下一个进程是取
			int currentp, remain,queue;
			if (!Q1.isempty()) {
				currentp = Q1.front().no;
				remain = Q1.front().remain;
				queue = 1;
			}
			else if (!Q2.isempty()) {
				currentp = Q2.front().no;
				remain = Q2.front().remain;
				queue = 2;
			}
			else if (!Q3.isempty()) {
				currentp = Q3.front().no;
				remain = Q3.front().remain;
				queue = 3;
			}
			int sliceend = nowtime + remain;
			int endabove = nowtime + pcbs[currentp].time_left;
			//所取进程的最早完成时间
			int nextdone = sliceend < endabove ? sliceend : endabove;
			int nextin = pcbs[sort[nextprocessin]].time_start;
			//所取进程的执行时间
			int processtime;
			if (nextin <= nextdone && currentp != sort[nextprocessin] && !hasentered[sort[nextprocessin]]) {
				Q1.push(PS(sort[nextprocessin], slice1));
				hasentered[sort[nextprocessin]] = 1;
				nextprocessin = nextprocessin + 1 >= num ? num - 1 : nextprocessin + 1;
				//当前进程执行的时间
				if(queue > 1) processtime = nextin - nowtime;
				else {
					processtime = nextdone - nowtime;
				}
				//todo:同时结束和进入时，执行进入的进程，而不是应该取的下一个
				if (nextin == nowtime) continue;
			}
			else
			{
				processtime = nextdone - nowtime;
			}
			// 是否结束时间片
			// 是否提前完成
			// 执行当前进程（即使被抢占）
			cout << "Now time: " << nowtime << "	process: " << pcbs[currentp].name;;
			pcbs[currentp].time_used += processtime;
			cout << "	service: " << pcbs[currentp].time_left;
			pcbs[currentp].time_left = pcbs[currentp].time_need -pcbs[currentp].time_used;
			remain -= processtime;
			cout << "->" << pcbs[currentp].time_left;
			nowtime += processtime;
			cout << "	queue:" << queue;
			
			string donestr = "";
			// 被抢占，未完成
			if (remain > 0 && pcbs[currentp].time_left > 0) {
				//加入队尾
				switch (queue)
				{
					case 1:Q1.pop(); Q1.push(PS(currentp, remain)); break;
					case 2:Q2.pop(); Q2.push(PS(currentp, remain)); break;
					case 3:Q3.pop(); Q3.push(PS(currentp, remain)); break;
				}
			}
			//时间片完，未完成
			else if(remain <= 0 && pcbs[currentp].time_left > 0){
				//降级
				switch (queue)
				{
				case 1:Q1.pop(); Q2.push(PS(currentp, slice2)); break;
				case 2:Q2.pop(); Q3.push(PS(currentp, slice3)); break;
				case 3:Q3.pop(); Q3.push(PS(currentp, slice3)); break;
				}
			}
			//进程完成
			else if (pcbs[currentp].time_left <= 0) {
				//标记完成
				doneprocess[currentp] = 1;
				//退队
				switch (queue)
				{
				case 1:Q1.pop(); break;
				case 2:Q2.pop(); break;
				case 3:Q3.pop(); break;
				}
				donestr = "\n	" + pcbs[currentp].name + " done at time " + to_string(nowtime) + ".";
				//cout << "	done.";
			}
			cout << "	after: "<< allQueue2String() + donestr << endl;
		}
	}

	//所有进程完成
	bool alldone(int* n) {
		for (int i = 0; i < num; i++) {
			if (n[i] == 0) return false;
		}
		return true;
	}

	string allQueue2String() {
		string t = "";
		t += "Q1:";
		for (int i = 0; i < Q1.getsize(); i++) {
			t += pcbs[Q1[i].no].name;
			t += " ";
		}
		t += "		Q2:";
		for (int i = 0; i < Q2.getsize(); i++) {
			t += pcbs[Q2[i].no].name;
			t += " ";
		}
		t += "		Q3:";
		for (int i = 0; i < Q3.getsize(); i++) {
			t += pcbs[Q3[i].no].name;
			t += " ";
		}
		return t;
	}

public:
	MRLA() :Scheduling() {}
	MRLA(int n, int slice1,int slice2,int slice3, PCB* r) :slice1(slice1),slice2(slice2), slice3(slice3) {
		num = n;
		order = new int[num];
		sort = new int[num];
		pcbs = r;
	}//暂时不初始化ready

	void print() {
		init();
		cout << "------------MRLA--------------" << endl;
		schedule();
		cout << "------------Done--------------\n";
	}
};