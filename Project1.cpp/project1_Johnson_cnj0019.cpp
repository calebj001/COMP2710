/* project1_Johnson_cnj0019.cpp
 * Caleb Johnson: This program calculates and prints an
   amortization table of monthly payments on an interest
   payment.
 * Used Dr. Li's lecture slides and the project 1 hints
   file to create this program.
 * Compilation instruction: g++ project1_Johnson_cnj0019.cpp
 * Execution Instruction: ./a.out
 */

#include <iostream>
#include <limits>
using namespace std;
using std::ios;

int main() {
	// VARIABLE INITIALIZATION
	double loan;
	double interestRate;
	double monthlyPaid;
	double interestPaid;
	double interestRateC;
	double principal;
	double interestTotal;
	int currentMonth = 0;

	// CURRENCY FORMATTING
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// USER INPUT
	// For valid input, loan, interest, and monthly payment
	// must be positive. The monthly payment must also
	// be large enough to terminate the loan.
	
		cout << "\nLoan Amount: ";
		cin >> loan;
		while (1) {
			if(loan < 0 || cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid Value, must be a higher number" << endl;
				cin >> loan;
			}
			if (loan >= 0 || !cin.fail())
				break;
		}

		cout << "Interest Rate (% per year): ";
		cin >> interestRate;
		while (1) {
                        if(interestRate < 0 || cin.fail()) {
                                cin.clear();
                                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid Value, must be a higher number" << endl;
                                cin >> interestRate;
                        }
                        if (interestRate > 0 || !cin.fail())
                                break;
                }

		// Calculate proper interest rate
		interestRate /= 12;
		interestRateC = interestRate / 100;
	
		cout << "Monthly Payments: ";
		cin >> monthlyPaid;
		while (1) {
                        if(monthlyPaid <= (loan * interestRateC) || cin.fail()) {
                                cin.clear();
                                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid Value, must be a higher payment" << endl;
                                cin >> monthlyPaid;
                        }
                        if (monthlyPaid > (loan * interestRateC) || !cin.fail())
                                break;
                }

		cout << endl;
   
	// AMORTIZATION TABLE
	cout << "*****************************************************************\n"
	<< "\tAmortization Table\n"
   	<< "*****************************************************************\n"  
   	<< "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
  
	// LOOP TO FILL TABLE
	while (loan > 0) {
		// Formatting first line with no down payments
		if (currentMonth == 0) {
         		cout << currentMonth << "\t$" << loan;
	 		if (loan < 1000) { 
				cout << "\t"; // Formatting Magic
			}	 		
			cout << "\t" << "N/A\tN/A\tN/A\t\tNA\t\n";
      		} else { //Formatting if not first line 

			// If final payment
			if (loan * (1 + interestRateC) < monthlyPaid) {
				monthlyPaid = loan * (1 + interestRateC); 
			}
			interestPaid = loan * interestRateC;
			principal = monthlyPaid - interestPaid;
			loan = loan - principal;
			cout << currentMonth << "\t$" << loan << "\t";
			if (loan < 1000) {
                                cout << "\t"; // Formatting Magic
			}
			cout << "$" << monthlyPaid << "\t" << interestRate << "\t$"; 
			cout << interestPaid << "\t\t$" << principal << "\n";;
   		}
	currentMonth++;
	interestTotal += interestPaid;
	}
	
	// Formatting Final Summary
	cout << "****************************************************************\n";
	cout << "\nIt takes " << -- currentMonth <<  " months to pay off "
	<< "the loan.\n"
	<< "Total interest paid is: $" << interestTotal;
	cout << endl;
	return 0; 
}
