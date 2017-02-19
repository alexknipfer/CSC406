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

    mySimulation.processNumericData(inputFile);
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
    NUMERIC_DATA = 50;
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

void Simulation::processNumericData(ifstream &inputFile) {
    string binary;
    string binaryInverted;
    int decimalValue = 0;

        //go through series of 50 numbers
    for(int x = 0; x < NUMERIC_DATA; x++ ) {
        
        inputFile >> binary;

            //check to see if the binary value is negative
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

                //add decimal and original binary values to vectors
                //for printing
            decimalNumericData.push_back(decimalValue);
            binaryNumericData.push_back(binary);

                //reset binary and decimal values for next read
            binaryInverted = "";
            decimalValue = 0;
        }

            //binary value read in is NOT negative
        else {

                //temp for binary reversal
            string binaryReverse = binary;

                //reverse order to calculate decimal
            reverse(binaryReverse.begin(), binaryReverse.end());

                //convert to decimal
            for(int x = 0; x < binaryReverse.length(); x++) {
                decimalValue += (binaryReverse[x] - '0') * pow(2, x);
            }

                //add decimal and original binary values to vectors
                //for printing
            decimalNumericData.push_back(decimalValue);
            binaryNumericData.push_back(binary);

                //reset decimal value
            decimalValue = 0;
        }
    }
}

//**********************************************************************************

void Simulation::printNumericData(ofstream &outputFile) {

        //Receives - output file
        //Task - prints out the numeric data
        //Returns - nothing

        //print header for rows
    outputFile << "Decimal";
    outputFile << setw(23);
    outputFile << "Binary Equivalent";
    outputFile << setw(10);
    outputFile << "Decimal";
    outputFile << setw(24);
    outputFile << "Binary Equivalent" << endl;

    outputFile << "--------      ";
    outputFile << "---------------    ";
    outputFile << "--------      ";
    outputFile << "---------------    " << endl;

        //go through numeric data vectors for printing
    for(int x = 0; x < decimalNumericData.size(); x++) {

            //print on a new line for every two pieces
            //of data (have two numeric values per line)
        if(x % 2 == 0 && x > 0) {
            outputFile << endl;
        }

            //print the decimal and binary values
        outputFile << setw(6) << right << decimalNumericData[x];
        outputFile << setw(24);
        outputFile << binaryNumericData[x];
        outputFile << "  ";
    }

}