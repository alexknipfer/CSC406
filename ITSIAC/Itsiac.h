#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Simulation {
    public:
		Simulation();
		int convertToDecimal(int [16]);
		void convertValueHexadecimal(int);
		void fetchAndIncrement(ofstream &);
		void executeAdd(ofstream &);
		void executeSubtract(ofstream &);
		void executeLoad(ofstream &);
		void executeStore(ofstream &);
		void executeBranch(ofstream &);
		void outputData(ofstream &);
		void doHalt();
		void programExecution(int, ofstream &);
		void executeRead();
		void executeWrite();
		void MLO(int, ofstream &);
		void readData(ifstream &);

	private:
		int storage[101][2];
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
		int machineLanguageCounter;
		int microCodeCounter;
		int x;
		int m;
		int primaryStorageSize;
		vector<char> hexValue;
		vector<int> executeValue;
		vector<int> executeValueAdd;
		vector<int> executeValueSubtract;
		vector<int> executeValueLoad;
		vector<int> executeValueStore;
		vector<int> executeValueBranch;
};