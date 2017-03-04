#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Simulation {
    public:
		Simulation();
		int convertToDecimal(int, int [16]);
		void convertToHex(int);
		void convertR(int, int);
		void FetchAInc(ofstream &);
		void add(ofstream &);
		void sub(ofstream &);
		void load(ofstream &);
		void store(ofstream &);
		void branch(ofstream &);
		void branchOnO(ofstream &);
		void dump(ofstream &);
		void halt();
		void branchHL(ofstream &);
		void ControlStor(int, ofstream &);
		void read();
		void write();
		void MLO(int, ofstream &);
		void readData(ifstream &);
		int GetMLC() {return MLC;}
		int GetPrimaryMemory(int );
		int Getmli();
		int Getmicro();
		int GetX();

	private:
		int acc1;
		int acc2;
		int psiar;
		int sar;
		int sdr1;
		int sdr2;
		int tmpr1;
		int tmpr2;
		int csiar;
		int mir;
		int mli;
		int micro;
		char hex[4];
		int primaryMemory[101][2];
		int MLC;
		int x;
		int m;
};