/* FILE NAME: project2_Johnson_cnj0019.cpp
 * AUTHOR: Caleb Johnson
 * AUBURN ID: cnj0019
 * 
 * Description: This program simulates a duel between three people: Aaron, Bob, and Charlie.
 * They each have differing accuracies which factor into who they target (the highest of
 * the two opposing them). There are two strategies for Aaron, the weakest duelist, which
 * are compared at the end to determine which is best.
 * 
 * Sources: Debugging help through - https://stackoverflow.com/questions/10056093/was-not-declared-in-this-scope-error?rq=1
 * 	and conversing about C++ function interaction with Parker T and Samarth K
 * 
 * Compilation: g++ project2_Johnson_cnj0019.cpp -o JohnsonDuelSimulator
 * Execution: ./JohnsonDuelSimulator
 * Tab Formatting in VIM: :set tabstop=4
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

using namespace std;

//-------------------------//
//        Constants        //
//-------------------------//

const int TRIALS = 10000;
const double A_acc = 33.3333;
const double B_acc = 50.0000;
const double C_acc = 100.0000;

//-------------------------//
//        Variables        //
//-------------------------//

bool A_alive = true;
bool B_alive = true;
bool C_alive = true;
int A_win1 = 0;
int A_win2 = 0;
int B_win = 0;
int C_win = 0;

//-------------------------//
//      Support Methods    //
//-------------------------//

// Checks to make sure at least 2 people are alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
        if (A_alive) {
                if (B_alive || C_alive) {
                        return true;
                }
        }
        else if (B_alive && C_alive) {
                return true;
        }

        return false;
}

// Aaron shooting with strategy 1
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
        assert(true == at_least_two_alive(true, true, true) || at_least_two_alive(true, true, false)
			|| at_least_two_alive(true, false, true));

        int shootResult = rand() % 100;

        bool hit = (shootResult <= A_acc);
        if(hit) {
                if(C_alive) {
                        C_alive = false;
                }
                else {
                        B_alive = false;
                }
        }
}

// Bob shooting
void Bob_shoots(bool& A_alive, bool& C_alive) {
	assert(true == at_least_two_alive(true, true, true) || at_least_two_alive(true, true, false)
            || at_least_two_alive(false, true, true));

        int shootResult = rand() % 100;

        bool hit = (shootResult <= B_acc);
        if(hit) {
                if(C_alive) {
                        C_alive = false;
                }
                else {
                        A_alive = false;
                }
        }
}

// Charlie shooting
void Charlie_shoots(bool& B_alive, bool& A_alive) {
	assert(true == at_least_two_alive(true, true, true) || at_least_two_alive(false, true, true)
            || at_least_two_alive(true, false, true));

        int shootResult = rand() % 100;

        bool hit = (shootResult <= C_acc);
        if(hit) {
                if(B_alive) {
                        B_alive = false;
                }
                else {
                        A_alive = false;
                }
        }
}

// Aaron shooting with strategy 2
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
        assert(true == at_least_two_alive(true, true, true) || at_least_two_alive(true, true, false)
                        || at_least_two_alive(true, false, true));

        int shootResult = rand() % 100;

        bool hit = (shootResult <= A_acc);
        
	if(!B_alive || !C_alive) {
        	if(hit) {
                	if(C_alive) {
                        	C_alive = false;
                	}
                	else {
                        	B_alive = false;
                	}
        	}
	}
}

// Press Enter to continue
void Press_any_key(void) {
	cout << "Press any key to continue...";

	cin.ignore(255, '\n');
	cout << '\n';
}

// Ressurects all dead duelists after each trial
void resurrect(bool& A_alive, bool& B_alive, bool& C_alive) {
    A_alive = true;
    B_alive = true;
    C_alive = true;
}

// Resets Bob and Charlie's win counts 
void reset(int& B_win, int& C_win) {
	B_win = 0;
	C_win = 0;
}

//-------------------------//
//		  Test Cases	   //
//-------------------------//

// Tests the at_least_two_alive method
void test_at_least_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";
	
	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 3:Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed ...\n";

 	cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed ...\n";
}

// Tests the Aaron_shoots1 method
void test_Aaron_shoots1(void) {
	cout << "Unit Testing 2: Function - Aaron_shoots1(B_alive, C_alive)\n";

	bool bob_a = true;
	bool charlie_a = true;

	cout << "\tCase1: Bob alive, Charlie alive\n"
		<< "\t\tAaron is shooting at Charlie\n";
	Aaron_shoots1(bob_a, charlie_a);

	bob_a = false;
	charlie_a = true;
	
	cout << "\tCase 2: Bob dead, Charlie alive\n"
		<< "\t\tAaron is shooting at Charlie\n";
	Aaron_shoots1(bob_a, charlie_a);

	bob_a = true;
	charlie_a = false;
	
	cout << "\tCase 3: Bob alive, Charlie dead\n"
		<< "\t\tAaron is shooting at Bob\n";
	Aaron_shoots1(bob_a, charlie_a);
}

// Tests the Bob_shoots method
void test_Bob_shoots(void) {
	cout << "Unit Testing 3: Function - Bob_shoots(A_alive, C_alive)\n";

	bool aaron_a = true;
	bool charlie_a = true;
	
	cout << "\tCase1: Aaron alive, Charlie alive\n"
        << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = false;
    charlie_a = true;
    
	cout << "\tCase 2: Aaron dead, Charlie alive\n"
        << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = true;
    charlie_a = false;
    
	cout << "\tCase 3: Aaron alive, Charlie dead\n"
        << "\t\tBob is shooting at Aaron\n";
	Bob_shoots(aaron_a, charlie_a);
}

// Tests the Charlie_shoots method
void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function - Charlie_shoots(A_alive, B_alive)\n";

    bool aaron_a = true;
    bool bob_a = true;

    cout << "\tCase1: Aaron alive, Bob alive\n"
        << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);

    aaron_a = false;
    bob_a = true;

    cout << "\tCase 2: Aaron dead, Bob alive\n"
        << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);

    aaron_a = true;
    bob_a = false;

    cout << "\tCase 3: Aaron alive, Bob dead\n"
        << "\t\tCharlie is shooting at Aaron\n";
    Charlie_shoots(aaron_a, bob_a);
}

// Tests the Aaron_shoots2 method
void test_Aaron_shoots2(void) {
	cout << "Unit Testing 5: Function - Aaron_shoots2(B_alive, C_alive)\n";

	bool bob_a = true;
	bool charlie_a = true;

	cout << "\tCase 1: Bob alive, Charlie alive\n"
		<< "\t\tAaron intentionally misses his first shot\n"
		<< "\t\tBoth Bob and Charlie are alive\n";
	Aaron_shoots2(bob_a, charlie_a);

	bob_a = false;
    charlie_a = true;

    cout << "\tCase 2: Bob dead, Charlie alive\n"
        << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = true;
    charlie_a = false;

    cout << "\tCase 3: Bob alive, Charlie dead\n"
        << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots2(bob_a, charlie_a);
}

//-------------------------//
//         Strategy        //
//-------------------------//

// Strategy 1
void strategy1(bool& A_alive, bool& B_alive, bool& C_alive) {
	if(A_alive) {
		Aaron_shoots1(B_alive, C_alive);
	}
	
	if(B_alive) {
		Bob_shoots(A_alive, C_alive);
	}

	if(C_alive) {
		Charlie_shoots(B_alive, A_alive);
	}
}	

// Strategy 2
void strategy2(bool& A_alive, bool& B_alive, bool& C_alive) {   
	if(A_alive) {
        Aaron_shoots2(B_alive, C_alive);
    }

    if(B_alive) {
        Bob_shoots(A_alive, C_alive);
    }   

    if(C_alive) {
        Charlie_shoots(B_alive, A_alive);
    }   
}

//-------------------------//
//			 Main		   //
//-------------------------//

int main() {
	
	cout << "\n*** Welcome to Johnson's Duel Simulator ***\n";
	
	// Initialize random seed
	srand(time(0));
	
	// Run Test cases
	
	test_at_least_two_alive();
	Press_any_key();
	
	
	test_Aaron_shoots1();
	Press_any_key();
	
	test_Bob_shoots();
	Press_any_key();

	test_Charlie_shoots();
	Press_any_key();

	test_Aaron_shoots2();
	Press_any_key();
	
	// Strategy 1
	
	cout << "Ready to test strategy 1 (run 10,000 times):\n";
	Press_any_key();

	for(int i = 0; i < TRIALS; i++) {
		resurrect(A_alive, B_alive, C_alive);

		while(at_least_two_alive(A_alive, B_alive, C_alive)) {
			strategy1(A_alive, B_alive, C_alive);
		}

		if(A_alive) {
			A_win1++;
		}

		if(B_alive) {
			B_win++;
		}

		if(C_alive) {
			C_win++;
		}
	}

	// Output for Strategy 1 Results
	cout << "Aaron won " << A_win1 << "/10000 duels or " << static_cast<double>(A_win1) /
 TRIALS * 100 << "%\n"
		<< "Bob won " << B_win << "/10000 duels or " << static_cast<double>(B_win) /
 TRIALS * 100 << "%\n"
		<< "Charlie won " << C_win << "/10000 duels or " << static_cast<double>(C_win) /
 TRIALS * 100 << "%\n"
		<< endl;
	
	//Reinitializes win counts
	reset(B_win, C_win);

	// Strategy 2
	
	cout << "Ready to test strategy 2 (run 10000 times):\n";
	Press_any_key();
	
	for(int i = 0; i < TRIALS; i++) {
		resurrect(A_alive, B_alive, C_alive);

		while(at_least_two_alive(A_alive, B_alive, C_alive)) {
            	strategy2(A_alive, B_alive, C_alive);
        }       

        if(A_alive) {
            A_win2++;   
        }       

        if(B_alive) {
            B_win++;
        }

        if(C_alive) {
            C_win++;
        }
	}

	// Output for Strategy 2 Results
	cout << "Aaron won " << A_win1 << "/10000 duels or " << static_cast<double>(A_win2) /
 TRIALS * 100 << "%\n"
        << "Bob won " << B_win << "/10000 duels or " << static_cast<double>(B_win) /
 TRIALS * 100 << "%\n"
        << "Charlie won " << C_win << "/10000 duels or " << static_cast<double>(C_win) /
 TRIALS * 100 << "%\n"
        << endl;

	// Prints statement on which strategy is more effective
	if(A_win1 > A_win2) cout << "Strategy 1 is better than Strategy 2.\n";
	
	if(A_win2 > A_win1) cout << "Strategy 2 is better than Strategy 1.\n";

	if(A_win1 == A_win2) cout << "Both Strategies are equal.\n";
	
	return 0;
}

