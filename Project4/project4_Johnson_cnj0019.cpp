/* 
* File Name: project4_Johnson_cnj0019.cpp
* Author: Caleb Johnson
* AU ID: cnj0019
*
* Description: This generates a trivia quiz game based on the data structure
* 	of a singly linked list. It can also run in play mode and unit testing
* 	mode with the use of the directives #define, #ifdef, and #endif. To run
* 	the UNIT_TESTING version, uncomment line 53 and comment line 54. To run
* 	the trivia_quiz version, uncomment line 54 and comment line 53.
*
* Sources: Project 4 hints were used extensively, and Parker T helped me better
* 	understand #define and other directives, as well as a greater grasp
*	on pointer to node relationships. I also emailed Tian about an issue
*	with the cin buffer in my add question loop, which he sent a stack
*	overflow page to help me understand cin.clear() and cin.ignore().
*
* Complilation: g++ project4_Johnson_cnj0019.cpp -o JohnsonTriviaQuiz
* Execution: ./JohnsonTriviaQuiz
*
* Formatting Tabs: :set tabstop=4
*/ 
//Libary imports. 
#include <climits>
#include <iostream>
#include <assert.h>
#include <string>

using namespace std; 

// Global Variables
int num_of_questions = 0;
int total_points = 0;

//Structure for creating a linked list that holds a trivia question,answer and point amount. 
struct trivia_node { 
	string question;
	string answer;
	int point;
	trivia_node *next;
};

//creates a pointer to triva_node. 
typedef trivia_node* ptr_node;

//Prototypes 
void Unit_Test(void);
void init_question_list(ptr_node& q_list);
void add_question(ptr_node& q_list);
int ask_question(ptr_node q_list, int num_ask);
 
//creates two versions.
//#define UNIT_TESTING
#define triva_quiz 
 
int main() {
	ptr_node node_list = new trivia_node; 
	//Creates a new trivia game / 
	//Sets up three original questions/ 
 	//Sets up loop for user to input his or her own questions. 
 	//Quiz questions are stored in linked list. 
#ifdef triva_quiz 
	init_question_list(node_list); 
	
	cout << "*** Welcome to Johnson's trivia quiz game ***\n";
	
	do {
		// Adds a new question and increases the question list size by 1
		add_question(node_list);
		num_of_questions++;
		
		// Asks if user would like to add another question
		cout << "Continue? (Yes/No): ";
		string cont = "";
		cin >> cont;
		
		// Clearing the buffer
		cin.clear();
		cin.ignore(10000, '\n');	
		
		// Exits the loop if "No" is entered
		if (cont == "No") break;
	} while (true);
	

	//This is start of Trivia quiz game. 
	ask_question(node_list, num_of_questions); 
 	cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***"; 
 	return 0; 
#endif 

	//Method for testing 
#ifdef UNIT_TESTING 
	Unit_Test(); 
 	return 0;  
#endif 
}
//initializes the quiz to have these three questions inputted into the linked list. 
void init_question_list(ptr_node& q_list) { 

	ptr_node cur_ptr = new trivia_node;
 
	// Q1
 	cur_ptr->question = "How long was the shortest war on record?"
		" (Hint: how many minutes)"; 
 	cur_ptr->answer = "38"; 
 	cur_ptr->point = 100;
	cur_ptr->next = new trivia_node;
	q_list = cur_ptr;

	// Q2
	cur_ptr = cur_ptr->next;
	cur_ptr->question = "What was Bank of America's original name?"
		" (Hint: Bank of Italy or Bank of Germany)";
        cur_ptr->answer = "Bank of Italy";
        cur_ptr->point = 50;
	cur_ptr->next = new trivia_node;
	
	// Q3
        cur_ptr = cur_ptr->next;
	cur_ptr->question = "What is the best-selling video game of all time?"
        	" (Hint: Call of Duty or Wii Sports)";
        cur_ptr->answer = "Wii Sports";
        cur_ptr->point = 20;
	cur_ptr->next = NULL;
	
	// Ititializes num_of_questions to 3
	num_of_questions = 3;
}

//gives user the option to add a question to the linked list. 
//question is added to the front of the linked list. 
void add_question(ptr_node& q_list) {
	
	// Adds a new node to front
	ptr_node new_q = new trivia_node;
	new_q->next = q_list;
	q_list = new_q;
	
	// Fills in node elements with user input
 	cout << "Enter a new question: ";
 	getline(cin, new_q->question);

	cout << "Enter an answer: ";
	getline(cin, new_q->answer);
	
	cout << "Enter award points: ";
	cin >> new_q->point;
}
 
//Checks for null value 
//Ask the user trivia questions and starts the game 
int ask_question(ptr_node q_list, int num_ask) {
		
	ptr_node cur_ptr = new trivia_node;
	cur_ptr = q_list;
	
	if (q_list == NULL) 
  		return -1;
 	if(num_ask < 1) { 
  		cout << "\nWarning - the number of trivia to be asked must equal to or be "
			<< "larger than 1."; 
		return 1;
	} 
	else if(num_of_questions < num_ask) { 
 		cout << "\nWarning - There is only " << num_of_questions << " trivia in the "
			<< "list."; 
		return 2;
	} 
 	else { 
 		for(int x = 0; x < num_ask; x++) { 
  			cout << "\nQuestion: " << cur_ptr->question << endl; 
  			cout << "Answer: ";
			string user_answer;
  			getline(cin, user_answer);
  			if (user_answer.compare(cur_ptr->answer) == 0) {//correct_answer) {
				total_points += cur_ptr->point;
				cout << "Your answer is correct. You have "
					<< "received " << cur_ptr->point
					<< " points." << endl;
 			}				 
  			else {
				cout << "Your answer is wrong. The correct "
					<< "answer is: " << cur_ptr->answer
					<< endl;
 			}
			cout << "Your total points: " << total_points << endl;
			cur_ptr = cur_ptr->next; 
		} 
	}	 
 	return 0; 
 } 

//Test cases to check whether the methods work. 
void Unit_Test() { 
	ptr_node node_list = new trivia_node; 
	init_question_list(node_list);
	
	// Case 1
	cout << "Unit Test Case 1: Ask no question. The program should give a "
		<< "warning message." << endl; 
	assert(ask_question(node_list, 0) == 1); 
 	cout << "\nCase 1 Passed\n\n"; 
 	
	// Case 2
 	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. "
		<< "The tester enters an incorrect answer." << endl; 
	assert(ask_question(node_list, 1) == 0);
	assert(total_points == 0);
	cout << "\nCase 2.1 Passed\n\n";

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. "
		<< "The tester enters a correct answer." << endl;
	assert(ask_question(node_list, 1) == 0);
	assert(total_points == 100);
	cout << "\nCase 2.2 Passed\n\n";

	total_points = 0;
	
	// Case 3
	cout << "Unit Test Case 3: Ask all the questions of the last trivia in the "
		<< "linked list." << endl;
	// Correct Answers
	assert(ask_question(node_list, 3) == 0);
	assert(total_points == 170);

	total_points = 0;
	// Incorrect Answers
        assert(ask_question(node_list, 3) == 0);
	assert(total_points == 0);
	cout << "\nCase 3 Passed\n\n";

	// Case 4
	cout << "Unit Test Case 4: Ask 5 questions in the linked list.";
	assert(ask_question(node_list, 5) == 2);
	cout << "\nCase 4 Passed\n\n";

	cout << "\n*** End of the Debugging Version ***" << endl; 
}
