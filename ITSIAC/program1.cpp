#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Itsiac.h"

using namespace std;

void printHeader(ofstream &);
void printFooter(ofstream &);

int main() {

    Simulation mySimulation;

        //intialize input and output files
    ifstream inputFile("data1.txt");
    ofstream outputFile("output.txt");

    mySimulation.readData(inputFile);
   
        //execute first instruction (fetch and increment)
    mySimulation.fetchAndIncrement(outputFile);

        //execute instructions from main memory
    for(int x = 0; x < primaryStorageSize; x++) {
        mySimulation.programExecution(primaryStorageSize, outputFile)
    }

    printHeader(outputFile);

    mySimulation.outputData(outputFile);

    outputFile << endl;

        //output the final counts to the output file
    outputFile << machineLanguageCounter << endl;
    outputFile << microCodeCounter << endl;

    printFooter(outputFile);

    return 0;

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
    microCodeCounter = 0;
    machineLanguageCounter = 0;
    x = 1;
    m = 0;

        //initialize primary storage
    for (int i = 0; i < 101; i++) {
        storage[i][0] = 1000;
        storage[i][1] = 1000;
    }
}

//*****************************************************************************************************
void Simulation::readData(ifstream &inputFile)
{
		//Recieves - input file
		//Task - reads in data file, places values into "primary storage"
		//Returns - nothing

        //reads each bit as a character
	char bitRead;
	int binaryNumber[16] = {0};

        //reads in first number
	for(int i=0; i<16;i++) {

            //get next character
		inputFile >> ws;					
		inputFile.get(bitRead);

            //check value of bit
		if(bitRead == '0') {
            binaryNumber[i] = 0;
        }
			
		else if(bitRead == '1') {
            binaryNumber[i] = 1;
        }
			
		else {
            binaryNumber[i] = 9;
        }
	}

        //keep reading until sentinel is reached
	while(binaryNumber[0] != 'X')
	{
		storage[MLC][0] = convertToDecimal(0, binaryNumber);	//converts first part
		storage[MLC][1] = convertToDecimal(1, binaryNumber);	//converts second part
		MLC++;

		for(int i = 0; i < 16; i++) 
        {
			inputFile >> ws;
			inputFile.get(bitRead);

                //check value of bit
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

		for(int i = 0; i < 16; i++) {

			inputFile >> ws;
			inputFile.get(bitRead);

			if(bitRead == '0') {
                binaryNumber[i] = 0;
            }

			else if (bitRead == '1') {
                binaryNumber[i] = 1;
            }

			else {
                binaryNumber[i] = 9;
            }	
		}

            //converts the value to decimal and places in primary storage
		storage[m + 50][1] = convertToDecimal(binaryNumber);
		m++;

	}

	return;
}

//**********************************************************************************

void Simulation::doHalt()
{
        //Recieves - output file
        //Task - perform halt execution
        //Returns - nothing

   machineLanguageCounter++;
}

//**********************************************************************************

void functionsClass::executeRead()
{
        //Recieves - nothing
        //Task - execute read from storage
        //Returns - nothing

	mir = csiar;
	csiar++;
	sdr1 = storage[sar][0];
	sdr2 = storage[sar][1];

        //increment micro code count
	microCodeCounter++;

}


//**********************************************************************************

void functionsClass::executeWrite()
{
        //Recieves - nothing
        //Task - executes from control storage
        //Returns - nothing

	mir = csiar;
	csiar++;
	storage[sar][0] = sdr1;
	storage[sar][1] = sdr2;

        //increment micr code count
	micro++;
}


//**********************************************************************************

void Simulation::fetchAndIncrement(ofstream &outputFile)
{
        //Recieves - output file
        //Task - executes from stroage for fetch and increment
        //Returns - nothing

    for(int x = 0; x < executeValue.size(); x++) {
        programExecution(executeValue[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

void Simulation::executeAdd(ofstream &outputFile)
{
        //Recieves - output file
        //Task - execute add
        //Returns - nothing

    for(int x = 0; x < executeValueAdd.size(); x++) {
        programExecution(executeValueAdd[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

void Simulation::executeSubtract(ofstream &outputFile)
{
        //Recieves - output file
        //Task - execute subtraction
        //Returns - nothing

    for(int x = 0; x < executeValueSubtract.size(); x++) {
        programExecution(executeValueSubtract[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

void Simulation::executeLoad(ofstream &outputFile)
{
        //Recieves - output file
        //Task - execute load
        //Returns - nothing

    for(int x = 0; x < executeValueLoad.size(); x++) {
        programExecution(executeValueLoad[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

void Simulation::executeStore(ofstream &outputFile)
{
        //Recieves - output file
        //Task - execute store
        //Returns - nothing

    for(int x = 0; x < executeValueStore.size(); x++) {
        programExecution(executeValueStore[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

void Simulation::executeBranch(ofstream &outputFile)
{
        //Recieves - output file
        //Task - execute store
        //Returns - nothing

    for(int x = 0; x < executeValueBranch.size(); x++) {
        programExecution(executeValueBranch[x], outputFile)
    }

        //increment machine language instruction
	machineLanguageCounter++;
}

//**********************************************************************************

int Simulation::convertToDecimal(int binary[16]) {

        //Receives - binary number to be converted
        //Task - convert binary to decimal
        //Returns - decimal number that was converted

    int decimalValue = 0;

        //converts the binary to decimal
    if(first == 0) {
        for(int x = 0; x < 16; x++) {
            decimalValue += (binary1[x] - '0') * pow(2, x);
        }	
    }

        //return decimal value that was converted
    return decimalValue;
}

//**********************************************************************************

void Simulation::convertToHex(int num)
{
        //Recieves - decimal value to be converted
        //Task - converts a decimal number to hexadecimal and places in vector
        //Returns - nothing

	int remainder;

        //go through decimal values to convert
	if (num < 50)
	{
            //get number from primary storage
		int number = storage[num][0];

            //get next number
		number = storage[num][1];

            //check to make sure number isn't "NULL"
		if (number == 255) {
            hexValue.push_back('F');
            hexValue.push_back('F');
		}

		else {
            for (int i = 3; i > 1; i--) {
                int multiplyValue = number / 16;	

                    //get remainder
                remainder = number - (multiplyValue * 16);

                    //go through and check remainder and add to hex vector
                if (remainder == 1) {
                    hexValue.push_back('1');
                }
                    
                else if(remainder == 2) {
                    hexValue.push_back('2');
                }
                    
                else if(remainder == 3) {
                    hexValue.push_back('3');
                }
                    
                else if(remainder == 4) {
                    hexValue.push_back('4');
                }
                    
                else if(remainder == 5) {
                    hexValue.push_back('5');
                }
                    
                else if(remainder == 6) {
                    hexValue.push_back('6');
                }
                    
                else if(remainder == 7) {
                    hexValue.push_back('7');
                }
                    
                else if(remainder == 8) {
                    hexValue.push_back('8');
                }
                    
                else if(remainder == 9) {
                    hexValue.push_back('9');
                }
                    
                else if(remainder == 10) {
                    hexValue.push_back('A');
                }
                    
                else if(remainder == 11) {
                    hexValue.push_back('B');
                }
                    
                else if(remainder == 12) {
                    hexValue.push_back('C');
                }
                    
                else if(remainder == 13) {
                    hexValue.push_back('D');
                }
                    
                else if(remainder == 14) {
                    hexValue.push_back('E');
                }
                    
                else if(remainder == 15) {
                    hexValue.push_back('F');
                }
                    
                else if (remainder == 0) {
                    hexValue.push_back('0');
                }
                    
                number = multiplyValue;
            }
	}
}

//**********************************************************************************

void Simulation::outputData(ofstream &outputFile) {

        //Recieves - output file
        //Task - primts final output
        //Returns - nothing

	for(int i = 0; i < 101; i++)
	{
            //convert the value in primary storage to hex
		convertToHex(i);

		for(int i = 0; i < 4; i++) {
                //prints the converted number
            out << hex[i];		
        }
			
		outputFile << " ";

            //once 8 is reached, drop down to next line
		if(x % 8 == 0) {
            outputFile << endl;
		    x++;
        }			
			
	}
}

//**********************************************************************************

void Simulation::programExecution(int OpCode, ofstream &out)
{
    
	//Recieves - operation code ,output file
	//Task - executes the given operation
	//Returns - nothing

        //execute based on operation
	switch(OpCode)
	{
        case 0:
            doHalt();
            microCodeCounter++;
            break;

        case 1:
            mir = csiar;
            csiar++;
            sdr1 = acc1;
            sdr2 = acc2;
            microCodeCounter++;
            break;

        case 2:
            mir = csiar;
            csiar++;
            sdr1 = psiar;
            microCodeCounter++;
            break;

        case 3:
            mir = csiar;
            csiar++;
            sdr1 = tmpr1;
            sdr2 = tmpr2;
            microCodeCounter++;
            break;

        case 4:
            mir = csiar;
            csiar++;
            acc1 = sdr1;
            acc2 = sdr2;
            microCodeCounter++;
            break;

        case 5:
            mir = csiar;
            csiar++;
            psiar = sdr2;
            microCodeCounter++;
            break;

        case 6:
            mir = csiar;
            csiar++;
            tmpr1 = sdr1;
            tmpr2 = sdr2;
            microCodeCounter++;
            break;

        case 7:
            mir = csiar;
            csiar++;
            sar = acc1;
            microCodeCounter++;
            break;

        case 8:
            mir = csiar;
            csiar++;
            sar = psiar;
            microCodeCounter++;
            break;

        case 9:
            mir = csiar;
            csiar++;
            sar = tmpr2;
            microCodeCounter++;
            break;

        case 10:
            mir = csiar;
            csiar++;
            acc1 += acc1;
            acc2 += acc2;
            microCodeCounter++;
            break;

        case 11:
            mir = csiar;
            csiar++;
            acc2 += psiar;
            microCodeCounter++;
            break;

        case 12:
            mir = csiar;
            csiar++;
            acc2 += tmpr2;
            microCodeCounter++;
            break;

        case 13:
            mir = csiar;
            csiar++;
            acc1 -= acc1;
            acc2 -= acc2;
            microCodeCounter++;
            break;

        case 14:
            mir=csiar;
            csiar++;
            acc2 -= psiar;
            microCodeCounter++;
            break;

        case 15:
            mir = csiar;
            csiar++;
            acc1 -= tmpr1;
            acc2 -= tmpr2;
            microCodeCounter++;
            break;
        
        case 16:
            mir = csiar;
            csiar++;
            microCodeCounter++;
            break;

        case 17:
            mir = csiar;
            csiar++;
            acc2 = psiar;
            microCodeCounter++;
            break;

        case 18:
            mir = csiar;
            acc1 = tmpr1;
            acc2 = tmpr2;
            microCodeCounter++;
            break;

        case 19:
            mir = csiar;
            csiar++;
            microCodeCounter++;
            break;
        
        case 20:
            mir = csiar;
            csiar++;
            psiar = acc2;
            microCodeCounter++;
            break;

        case 21:
            mir = csiar;
            csiar++;
            tmpr1 = acc1;
            tmpr2 = acc2;
            microCodeCounter++;
            break;

        case 22:
            mir = csiar;
            csiar++;
            acc2++;
            microCodeCounter++;
            break;

        case 23:
            mir = csiar;
            csiar++;
            acc2 = psiar + 1;
            microCodeCounter++;
            break;
        case 24:
            acc1 = tmpr1 + 1;
            acc2 = tmpr2 + 1;
            microCodeCounter++;
            break;

        case 25:
            executeRead();
            microCodeCounter++;
            break;

        case 26:
            executeWrite();
            microCodeCounter++;
            break;

        case 27:
            mir = csiar;
            csiar++;
            microCodeCounter++;
            break;

        case 28:
            mir = csiar;

                //converts for given operation		
            if(sdr1 == 1) {
                csiar = 10;
            }

            else if(sdr1==2) {
                csiar = 20;
            }

            else if(sdr1==3) {
                csiar = 30;
            }

            else if(sdr1 == 4) {
                csiar = 40;
            }
                
            else if(sdr1 == 5) {
                csiar = 50;
            }
                
            else if(sdr1 == 6) {
                csiar = 60;
            }
                
            else if(sdr1 == 7) {
                csiar = 70;
            }
                
            else if(sdr1==8) {
                csiar = 80;
            }
                
            microCodeCounter++;
            break;

        case 29:
            mir = csiar;
            csiar = 0;
            microCodeCounter++;
            break;

        case 30:
            mir = csiar;
            if(acc1 == 0) {
                csiar++;
            }
            microCodeCounter++;
            break;

        case 31:
            dump(out);
            microCodeCounter++;
            break;

        case 32:
            mir = csiar;
            microCodeCounter++;
            break;
	}
	return;
}

//**********************************************************************************

void printHeader(ofstream &outputFile) 
{
		// Receive the output file
		// Task - print header
		// Return - Nothing

   outputFile << setw(30) << "Alex Knipfer";
   outputFile << setw(17) << "CSC 406";
   outputFile << setw(15) << "Section 11" << endl;
   outputFile << setw(30) << "Spring 2017";
   outputFile << setw(20) << "Assignment #1" << endl;
   outputFile << setw(35) << "-----------------------------------";
   outputFile << setw(35) << "-----------------------------------\n\n";

}

//**********************************************************************************


//**********************************************************************************

void printFooter(ofstream &outputFile) 
{
		// Receives - the output file
		// Task - print footer
		// Return - Nothing

   outputFile << endl;
   outputFile << setw(35) << " --------------------------------- " << endl;
   outputFile << setw(35) << "|      END OF PROGRAM OUTPUT      |" << endl;
   outputFile << setw(35) << " --------------------------------- " << endl;

  }

//**********************************************************************************