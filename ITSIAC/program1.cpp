#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Itsiac.h"

using namespace std;

int main() {
    Simulation mySimulation;

    ifstream inputFile("data1.txt");
    ofstream outputFile("output.txt");

    mySimulation.readData(inputFile);
    mySimulation.printInitialData(outputFile);

    return 0;
}

void Simulation::readData(ifstream &inputFile) {
    string binaryNumber;

    inputFile >> binaryNumber;

    while(binaryNumber != "XXXXXXXXXXXXXXXX") {
        originalBinaryNumbers.push_back(binaryNumber);
        convertToDecimal(binaryNumber);
        inputFile >> binaryNumber;
    }
}

Simulation::Simulation() {
    //constructor
}

void Simulation::convertToDecimal(string binary) {
    string binary1 = binary.substr(0, 8);
    string binary2 = binary.substr(8);
    reverse(binary1.begin(), binary1.end());
    reverse(binary2.begin(), binary2.end());
    int currentDecimalValue1 = 0;
    int currentDecimalValue2 = 0;

    for(int x = 0; x < 8; x++) {
        currentDecimalValue1 += (binary1[x] - '0') * pow(2, x);
        currentDecimalValue2 += (binary2[x] - '0') * pow(2, x);
    }
    myDecimalValues.opCode = currentDecimalValue1;
    myDecimalValues.operand = currentDecimalValue2;
    decimalNumbers.push_back(myDecimalValues);
}

void Simulation::printInitialData(ofstream &outputFile) {
    outputFile << "Decimal numbers";
    outputFile << setw(35);
    outputFile << "Binary Equivalent" << endl;
    outputFile << "----------------";
    outputFile << setw(33);
    outputFile << "-----------------" << endl;

    for(int x = 0; x < decimalNumbers.size(); x++) {

        if(decimalNumbers[x].opCode == 255 && decimalNumbers[x].operand ==  255) {
            outputFile << setw(8) << "------" << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }

        else if(decimalNumbers[x].operand == 255) {
            outputFile << setw(3) << "0" << decimalNumbers[x].opCode << " ";
            outputFile << setw(3) <<  "--" << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }

        else {
            outputFile << setw(3) <<  "0" << decimalNumbers[x].opCode << " ";
            outputFile << setw(3) << decimalNumbers[x].operand << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }
    
    }
}