/* FILE NAME: project3_Johnson_cnj0019.cpp
 * AUTHOR: Caleb Johnson
 * AUBURN ID: cnj0019
 *
 * Description: This program read two input files that are assumed to be in ascending order already.
 * It then uses arrays to merge the two files into one array, which is written as an output file of the users naming.
 *
 * Sources: Extensive use of https://www.cplusplus.com for funtions. Used StackOverflow.com to help with merge function.
 * Spoke with Samarth K and Parker S on fstream concepts.
 *
 * Compilation: g++ project3_Johnson_cnj0019.cpp -o JohnsonSorting
 * Execution: ./JohnsonSorting
 * Tab Formatting in VIM: :set tabstop=4
*/


#include <fstream>
#include <iostream>
#include <cstdlib> // For exit() if file not found
#include <string>

using namespace std;

////////////////////////////////////////
//				 Fields				  //
////////////////////////////////////////
const int MAX_SIZE = 100;

////////////////////////////////////////
//			  Support Methods		  //
////////////////////////////////////////

// Checks if file opens properly, then reads file into an empty array and 
// returns the array's size.
int readFile(int arrIn[], ifstream &fsIn) {
	
	int i = 0;
	// Checks if file opens properly
	if (fsIn.fail()) {
		cout << "Input file failed to open properly.\n\t\tTerminating Program";
		exit(1);
	}
	else {
		fsIn >> arrIn[i];
		while (!fsIn.eof()) {
			// Checks to confirm that file is withing bounds
			if (i >= MAX_SIZE - 1) {
				cout << "File is greater than the maximum size."
						<< "\n\t\tTerminating Program.";
				exit(1);
				}
			i++;
			fsIn >> arrIn[i];
		}
		return i; // Array size
	}
}
// Writes given values into a file
void writeFile(int arrOut[], int outSize, ofstream &fsOut) {
	// Test that file opens correctly
	if (fsOut.fail()) {
		cout << "File could not be written.\n\t\tTerminating Program";
		exit(1);
	}
	for (int i = 0; i < outSize; i++) {
		fsOut << arrOut[i] << endl;
	}
}

// Merges two values from input files and adds them to the output in sorted order.
// Also returns the output array size.
int merge(int arrIn1[], int arrSize1, int arrIn2[], int arrSize2, int arrOut[]) {
	int i = 0;
	int j = 0;
	int outSize = 0;
	bool fullyMerged = false;

	while (!fullyMerged) {
		if (i < arrSize1 && j < arrSize2) {
			// Array 1 smaller
			if (arrIn1[i] < arrIn2[j]) {
				if (outSize > 0) {
					if (arrIn1[i] != arrOut[outSize - 1]) {
						arrOut[outSize] = arrIn1[i];
					}
				}
				else {
					arrOut[outSize] = arrIn1[i];
				}	
				i++;	
			}
			// Array 2 smaller
			else if (arrIn2[j] < arrIn1[i]) {
				if (outSize > 0) {
					if (arrIn2[j] != arrOut[outSize - 1]) {
						arrOut[outSize] = arrIn2[j];
					}
				}
				else {
					arrOut[outSize] = arrIn2[j];
				}         
				j++;                 
			}
			// Equal Values
			else {
				arrOut[outSize] = arrIn1[i];
				outSize++;
				arrOut[outSize] = arrIn2[j];
				i++;
				j++;
			}
		}
		// Only Array 1 has values left
		else if (i < arrSize1) {
			if (outSize > 0) {
            	if (arrIn1[i] != arrOut[outSize - 1]) {
					arrOut[outSize] = arrIn1[i];
				}
			}
			else {
				arrOut[outSize] = arrIn1[i];
			}         
			i++;
		}
		else if (j < arrSize2) {
			if (outSize > 0) {
				if (arrIn2[j] != arrOut[outSize - 1]) {
					arrOut[outSize] = arrIn2[j];
				}
			}
			else {
				arrOut[outSize] = arrIn2[j];
			}
			j++;	
		}
		// Fully merged
		else {
			fullyMerged = true;
			return outSize;
		}
		outSize++;
	}
	// Fail case
	return -1;	
}

////////////////////////////////////////
//			   Main Method			  //
////////////////////////////////////////
int main() {
	// Locals
	string filename;
	ifstream fsIn;
	ofstream fsOut;
	int arrIn1[MAX_SIZE];
	int arrSize1;
	int arrIn2[MAX_SIZE];
	int arrSize2;
	int arrOut[MAX_SIZE];	
	int arrOutSize;

	// Begin UI
	cout << "*** Welcome to Johnson's sorting program ***"
		<< "\nEnter the first input file name: ";
	
	// Opens and reads file into an array
	cin >> filename;
	fsIn.open((char*)filename.c_str());
	arrSize1 = readFile(arrIn1, fsIn);
	fsIn.close();
	
	// Prints the array
	cout << "The lise of " << arrSize1 << " numbers in "	
		<< filename << " is:\n";
	for (int i = 0; i < arrSize1; i++) {
		cout << arrIn1[i] << endl;
	}
	cout << endl;
	
	// Opens and reads the second file into an array
	cout << "Enter the second input file name: ";
	cin >> filename;
	fsIn.open((char*)filename.c_str());
    arrSize2 = readFile(arrIn2, fsIn);
    fsIn.close();

	// Prints the array
	cout << "The lise of " << arrSize2 << " numbers in "            
		<< filename << " is:\n";
    for (int i = 0; i < arrSize2; i++) {
		cout << arrIn2[i] << endl;
	}
	cout << endl;
	
	// Merges the two arrays into a sorted output array and assigns the array size
	arrOutSize = merge(arrIn1, arrSize1, arrIn2, arrSize2, arrOut);
	
	// Prints the output array
	cout << "The sorted list of " << arrOutSize << " numbers is: ";
	for (int i = 0; i < arrOutSize; i++) {
		cout << arrOut[i] << " ";
	}
	cout << endl;
	
	// Error if merge was incorrect
	if (arrOutSize == -1) {
		cout << "Error occured in merge.\n\t\tTerminating Program";
		exit(1);
	}	
	
	// Writes the output file
	cout << "Enter the output file name: ";
	cin >> filename;
	
	fsOut.open((char*)filename.c_str());
	writeFile(arrOut, arrOutSize, fsOut);
	fsOut.close();
	
	// Final print statement
	cout << "*** Please check the new file - " << filename << " ***\n";
	cout << "*** Goodbye. ***\n";

	return 0;
}
