#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Itsiac.h"

using namespace std;

int main() {
    Simulation mySimulation;

        //intialize input and output files
    ifstream inputFile("data1.txt");
    ofstream outputFile("output.txt");

    mySimulation.readMachineLanguageCode(inputFile);
    mySimulation.printMachineLanguageCode(outputFile);

    mySimulation.readNumericData(inputFile);
    mySimulation.printNumericData(outputFile);

    return 0;
}

//**********************************************************************************

void Simulation::readMachineLanguageCode(ifstream &inputFile) {

        //Receives - input file
        //Task - read data from file
        //Returns - nothing

    string binaryNumber;

        //read the current binary number
    inputFile >> binaryNumber;

        //read until sentinel is reached
    while(binaryNumber != "XXXXXXXXXXXXXXXX") {

            //keep a vector of the original binary values
        originalBinaryNumbers.push_back(binaryNumber);

            //convert the binary to decimal form
        convertToDecimal(binaryNumber);

            //get the next value
        inputFile >> binaryNumber;
    }
}

Simulation::Simulation() {
    //constructor
}

//**********************************************************************************

void Simulation::convertToDecimal(string binary) {

        //Given - the binary value to be converted
        //Task - convert a binary number to decimalNumbers
        //Returns - nothing

        //splits the number in half
    string binary1 = binary.substr(0, 8);
    string binary2 = binary.substr(8);

        //reverse the values for easy conversion
    reverse(binary1.begin(), binary1.end());
    reverse(binary2.begin(), binary2.end());

        //initialize accumulator for converting
    int currentDecimalValue1 = 0;
    int currentDecimalValue2 = 0;

        //convert to decimal
    for(int x = 0; x < 8; x++) {
        currentDecimalValue1 += (binary1[x] - '0') * pow(2, x);
        currentDecimalValue2 += (binary2[x] - '0') * pow(2, x);
    }

        //store opcode and operand in struct
    myDecimalValues.opCode = currentDecimalValue1;
    myDecimalValues.operand = currentDecimalValue2;

        //keep a vector of structures
    decimalNumbers.push_back(myDecimalValues);
}

//**********************************************************************************

void Simulation::printMachineLanguageCode(ofstream &outputFile) {

        //Receives - output file
        //Task - prints out the intitial "Program" data
        //Returns - nothing

        //print header for rows
    outputFile << "Decimal numbers";
    outputFile << setw(35);
    outputFile << "Binary Equivalent" << endl;
    outputFile << "----------------";
    outputFile << setw(33);
    outputFile << "-----------------" << endl;

        //print the decimal numbers and binary equivalent
    for(int x = 0; x < decimalNumbers.size(); x++) {

            //output opcode and operand with binary equivalent
        if(decimalNumbers[x].opCode == 255 && decimalNumbers[x].operand ==  255) {
            outputFile << setw(8) << "------" << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }

            //output opcode and operand with binary equivalent
        else if(decimalNumbers[x].operand == 255) {
            outputFile << setw(3) << "0" << decimalNumbers[x].opCode << " ";
            outputFile << setw(3) <<  "--" << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }

            //output opcode and operand with binary equivalent
        else {
            outputFile << setw(3) <<  "0" << decimalNumbers[x].opCode << " ";
            outputFile << setw(3) << decimalNumbers[x].operand << right;
            outputFile << setw(40);
            outputFile << originalBinaryNumbers[x] << endl;
        }
    
    }
    outputFile << setw(7) << "XXXXX" << endl;
    outputFile << endl;
}

//**********************************************************************************

void Simulation::readNumericData(ifstream &inputFile) {
    string binary;
    string binaryInverted;
    int decimalValue = 0;

    inputFile >> binary;
    cout << binary << endl;

        //checkt o see if the binary value is negative
    if(binary[0] == '1') {

            //invert the binary for 2's complement conversion
        for(int x = 0; x < binary.length(); x++) {
            if(binary[x] == '1') {
                binaryInverted += '0';
            }
            else {
                binaryInverted += '1';
            }
        }

            //reverse order to calculate decimal
        reverse(binaryInverted.begin(), binaryInverted.end());

            //convert to decimal
        for(int x = 0; x < binaryInverted.length(); x++) {
            decimalValue += (binaryInverted[x] - '0') * pow(2, x);
        }

            //make decimal value negative and add 1 since we converted/
            //from 2's complement to decimal
        decimalValue += 1;
        decimalValue *= -1;

        cout << decimalValue << endl;
    }

    else {
        cout << "hello" << endl;
            //reverse order to calculate decimal
        reverse(binary.begin(), binary.end());

            //convert to decimal
        for(int x = 0; x < binary.length(); x++) {
            decimalValue += (binary[x] - '0') * pow(2, x);
        }

        cout << decimalValue << endl;
    }
}

//**********************************************************************************

void Simulation::printNumericData(ofstream &outputFile) {

        //Receives - output file
        //Task - prints out the numeric data
        //Returns - nothing

        //print header for rows
    outputFile << "Decimal";
    outputFile << setw(25);
    outputFile << "Binary Equivalent";
    outputFile << setw(15);
    outputFile << "Decimal";
    outputFile << setw(28);
    outputFile << "Binary Equivalent" << endl;

    outputFile << "-----------    ";
    outputFile << "---------------         ";
    outputFile << "-----------        ";
    outputFile << "---------------    ";

}