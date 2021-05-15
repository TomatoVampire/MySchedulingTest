#include<iostream>
#include<string>
#include"FCFS.h"
#include"SJF.h"
#include"TimeSlice.h"
#include"MyQueue.h"
#include"HRF.h"
#include"MRLA.h"

using namespace std;
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

PCB pcb3[4] = {
	{1000,"A",0,	7,	7,	0,	'R'},
	{1001,"B",5,	4,	4,	0,	'R'},
	{1002,"C",7,	13,	13,	0,	'R'},
	{1003,"D",12,	9,	9,	0,	'R'}
};


//调度函数


void queueTest() {
	MyQueue<int> m;
	m.push(1);
	m.push(2);
	m.push(3);
	cout << m.front() << endl;
	m.pop();
	cout << m.front() << endl;
	cout << m[1] << endl;
	m.clear();
	cout << m.getsize() << endl;
	m.push(4);
	cout << m[0];
}

void main() {
	cout << "code by TomatoVampire 2021.5" << endl;

	//queueTest();
	//FCFS f(5,pcbdata); f.print();
	//SJF s(4, pcb2); s.print();
	//HRF h(4, pcb2); h.print();
	MRLA m(4, 2, 4, 8, pcb3); m.print();
	//TimeSlice t(5, time_unit, pcbdata); t.print();

	getchar();
	
}