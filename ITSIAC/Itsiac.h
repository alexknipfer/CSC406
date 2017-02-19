#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Simulation {
    public:
        Simulation();
        void readMachineLanguageCode(ifstream &);
        void printMachineLanguageCode(ofstream &);
        void processNumericData(ifstream &);
        void printNumericData(ofstream &);
        void convertToDecimal(string);

    private:
        struct DecimalValues {
            int opCode;
            int operand;
        } myDecimalValues;

        int NUMERIC_DATA;

        vector<DecimalValues> decimalNumbers;
        vector<string> originalBinaryNumbers;

        vector<int> decimalNumericData;
        vector<string> binaryNumericData;
};