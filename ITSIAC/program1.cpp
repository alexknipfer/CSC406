#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include "Itsiac.h"

using namespace std;

int main() {
    Simulation mySimulation;

        //intialize input and output files
    ifstream inputFile("data1.txt");
    ofstream outputFile("output.txt");

    mySimulation.readData(inputFile);
   // mySimulation.printMachineLanguageCode(outputFile);

    ////mySimulation.processNumericData(inputFile);
    //mySimulation.printNumericData(outputFile);

    return 0;
}

//**********************************************************************************

//*****************************************************************************************************
void Simulation::readData(ifstream &inputFile)
{
		// Recieves: input file
		// Task:	reads in data and places into storage
		// Returns:	nothing

        //reads each bit as a character
	char bitRead;
	int binaryNumber[16]={0};

        //reads first
	for(int i=0; i<16;i++) {

            //ignore whitespace and get next character
		inputFile >> ws;					
		inputFile.get(bitRead);

		if(bitRead=='0') {
            binaryNumber[i] = 0;
        }
			
		else if(bitRead == '1') {
            binaryNumber[i] = 1;
        }
			
		else
			binaryNumber[i] = 9;
	}

        //makes sure sentinel isn't reached
	while (binaryNumber[0] != 9)
	{
		primaryMemory[MLC][0] = convertToDecimal(0, binaryNumber);	//converts first part
		primaryMemory[MLC][1] = convertToDecimal(1, binaryNumber);	//converts second part
		MLC++;
		for(int i = 0; i < 16; i++)
		{
			inputFile >> ws;
			inputFile.get(bitRead);

			if (bitRead == '0') {
                binaryNumber[i]=0;
            }
				
			else if (bitRead == '1') {
                binaryNumber[i] = 1;
            }

			else {
                binaryNumber[i]=9;
            }
		}
	}

        //gets the next part of data file
	while(m != 50) {
		for(int i=0; i<16;i++) {
			inputFile >> ws;
			inputFile.get(bitRead);

			if(bitRead=='0') {
                binaryNumber[i]=0;
            }

			else if (bitRead=='1') {
                binaryNumber[i]=1;
            }

			else {
                binaryNumber[i]=9;
            }		
		}

            //converts the value to decimal and places in primary storage
		primaryMemory[m + 50][1] = convertToDecimal(3, binaryNumber);
		m++;
	}

	for(int x = 0; x < 101; x++) {
		for(int y = 0; y < 2; y++) {
			cout << primaryMemory[x][y];
		}
		cout << endl;

	}
	return;
}

//**********************************************************************************

int Simulation::convertToDecimal(int first, int binary[16]) {
    int numberValue = 0;

    if(first == 0) {
        numberValue = 128 * binary[0] + 64 * binary[1] + 32 * binary[2] + 
                      16 * binary[3] + 8 * binary[4] + 4 * binary[5] + 2 * 
                      binary[6] + 1 * binary[7];
		return numberValue;	
    }

    else if(first == 1) {
        numberValue = 128 * binary[8] + 64 * binary[9] + 32 * binary[10] + 16
                          * binary[11] + 8 * binary[12] + 4 * binary[13] + 2 * 
                          binary[14] + 1 * binary[15];
    }

    else if(first == 3) {

            //value is postiive
        if(binary[0] == 0) {
            numberValue = 8192 * binary[2] + 4096 * binary[3] + 2048 * binary[4] + 1024 * binary[5] + 512 * binary[6] + 256 * binary[7] +
						128 * binary[8] + 64 * binary[9] + 32 * binary[10] + 16 * binary[11] + 8 * binary[12] + 4 * binary[13] + 2 *
						binary[14] + 1 * binary[15];
        }

            //value is negative
        else {
            numberValue = 8192 * (binary[2] - 1) + 4096 * (binary[3] - 1) + 2048 * (binary[4]-1) + 1024 * (binary[5] - 1) + 512 *
						(binary[6] - 1) + 256 * (binary[7] - 1) + 128 * (binary[8] - 1) + 64 * (binary[9] - 1) + 32 * (binary[10] - 1) +
						16 * (binary[11] - 1) + 8 * (binary[12] - 1) + 4 * (binary[13] - 1) + 2 * (binary[14] - 1) + 1 * (binary[15] - 1) - 1;
        }
    }

    return numberValue;
}

//**********************************************************************************

Simulation::Simulation() {
    acc1 = 0;
    acc2 = 0;
    psiar = 0;
    sar = 0;
    sdr1 = 0;
    sdr2 = 0;
    tmpr1 = 0;
    tmpr2 = 0;
    csiar = 0;
    mir = 0;
    mli = 0;
    micro = 0;
    MLC = 0;
    x = 1;
    m = 0;
    for (int i = 0; i < 101; i++) {
        primaryMemory[i][0] = 1000;
        primaryMemory[i][1] = 1000;
    }
}

//**********************************************************************************

/*void Simulation::convertToDecimal(string binary) {

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
}*/

//**********************************************************************************