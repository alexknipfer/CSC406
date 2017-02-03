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
    myDecimalValues.value1 = currentDecimalValue1;
    myDecimalValues.value2 = currentDecimalValue2;
    decimalNumbers.push_back(myDecimalValues);
}

void Simulation::printInitialData(ofstream &outputFile) {
    outputFile << "Decimal numbers";
    outputFile << setw(30);
    outputFile << "Binary Equivalent" << endl;
    outputFile << "----------------";
    outputFile << setw(29);
    outputFile << "-----------------" << endl;
    for(int x = 0; x < decimalNumbers.size(); x++) {

        if(decimalNumbers[x].value1 == 255 && decimalNumbers[x].value2 ==  255) {
            outputFile << "------" << "                     ";
            outputFile << originalBinaryNumbers[x] << endl;
        }

        else if(decimalNumbers[x].value2 == 255) {
            outputFile << "0" << decimalNumbers[x].value1 << " ";
            outputFile << "--" << "                     ";
            outputFile << originalBinaryNumbers[x] << endl;
        }

        else {
            outputFile << "0" << decimalNumbers[x].value1 << " ";
            outputFile << decimalNumbers[x].value2 << "                  ";
            outputFile << left << setw(30) << originalBinaryNumbers[x] << endl;
        }
    
    }
}