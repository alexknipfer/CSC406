#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Simulation {
    public:
        Simulation();
        void readData(ifstream &);
        void printInitialData(ofstream &);
        void convertToDecimal(string);

    private:
        struct DecimalValues {
            int opCode;
            int operand;
        } myDecimalValues;
        vector<DecimalValues> decimalNumbers;
        vector<string> originalBinaryNumbers;
};