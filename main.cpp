//LR Parser
//Jenny Chau and Sorasit Wanichpan
//November-11-2013

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

                              // LHS  RHS
const string ruleTable[9][2] = { " ", " ",    //Null
								 "E", "3",    //Rule 1
                                 "E", "3",    //Rule 2
								 "E", "1",    //Rule 3
								 "T", "3",    //Rule 4
								 "T", "3",    //Rule 5
								 "T", "1",    //Rule 6
								 "F", "3",    //Rule 7
								 "F", "1"  }; //Rule 8
         

//Need hash table or something to replace this stuff!!!!!
//Need to be able to interpret from s,r, and acc

                                   //                     Terminals                  //    Nonterms
								   //   i     +     -     *     /     (     )      $     E     T     F
const string grammarTable[16][11] = { "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ",  "1",  "2",  "3",    //0
									  " " , "s6", "s7",  " ",  " ",  " ",  " ", "acc",  " ",  " ",  " ",    //1
									  " " , "r3", "r3", "s8", "s9",  " ", "r3",  "r3",  " ",  " ",  " ",    //2
									  " " , "r6", "r6", "r6", "r6",  " ", "r6",  "r6",  " ",  " ",  " ",    //3
									  "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ", "10",  "2",  "3",    //4
									  " " , "r8", "r8", "r8", "r8",  " ", "r8",  "r8",  " ",  " ",  " ",    //5
									  "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ",  " ", "11",  "3",    //6
									  "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ",  " ", "12",  "3",    //7
									  "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ",  " ",  " ", "13",    //8
									  "s5",  " ",  " ",  " ",  " ", "s4",  " ",   " ",  " ",  " ", "14",    //9
									  " " , "s6", "s7",  " ",  " ", " " ,"s15",   " ",  " ",  " ",  " ",    //10 
									  " " , "r1", "r1", "s8", "s9", " " , "r1",  "r1",  " ",  " ",  " ",    //11
									  " " , "r2", "r2", "s8", "s9", " " , "r2",  "r2",  " ",  " ",  " ",    //12
									  " " , "r4", "r4", "r4", "r4", " " , "r4",  "r4",  " ",  " ",  " ",    //13
									  " " , "r5", "r5", "r5", "r5", " " , "r5",  "r5",  " ",  " ",  " ",    //14
									  " " , "r7", "r7", "r7", "r7", " " , "r7",  "r7",  " ",  " ",  " " };  //15

int identifierTerm(string);
//Handles the terminals, converts them to their number representation

bool isTerm(string symbol);
//Check if the symbol is a terminal

//ToDo
void shift();
//Push the incoming token onto the stack and enter the current state

//ToDo
void reduce();
//Reduce by means of Production #n. When the left hand side has been pushed, we must also place a new state on the stack using the go-to part of the table

//ToDo
void accept();
//The parse is completed

int main()
{
	string userInput;
	string topOfStack;
	string incomingToken;
	stack<string> grammarStack;

	int iterate = 0; 

	//Test input 
	userInput = "i*(i-i"; //Invalid input i*(i-i
	                      //Valid input  (i+i)/i

	/* To be implemented
	cout << "Please enter an expression: "; 
	cin >> userInput;
	*/

	//Append the end marker to the end of the string input
	userInput += "$";

	//Push the starting state to the stack
	grammarStack.push("0");
	
	while (!grammarStack.empty())
	{
		//This part is for seperating the "action part" from the "value"
		//Either shift or reduction
		string actionPart; //Actionpart from the table, i.e: s6
		string action; //The action to be under taken: s6, so s == shift
		string actionValue; //The state or rule to go to, so s6, actionValue = 6, go to state 6

	    //Use for reduction
		string RHSVal; //Right hand side value of the rule table
		string LHSVal; //Left hand side value of the rule table
	
		topOfStack = grammarStack.top(); //The current state
		incomingToken = userInput[iterate]; //Incoming token

		//                         State           Incoming Token    
		//Example: grammarTable[topOfStack][identifierTerm(incomingToken)];

		//Access the table and pull out the action part
		actionPart = grammarTable[identifierTerm(topOfStack)][identifierTerm(incomingToken)];
		
		/*This is why we need a hash table, or some sort of data structure to organize everything. Using 2D arrays and strings will only get us so far*/
		//Takes the first part of the string (the front) and determine if we need to shift/reduce/accept
		action = actionPart.front();

		//Error checking, if input is invalid then break out of loop
		if (actionPart == " ")
		{
			cout << "Error: no table entry" << endl;
			break;
		}

		/*This is where we run into the limitations of the string. As our array gets bigger we have to make cases in which the program
		have to be able to accept bigger values from the string. 

		         string
		Example: actionPart = s1
		                     /  \
		                shift  go to state 1 (Array index == 1)
			    actionPart[0]  actionPart[1] 

				 string
		Example: actionPart = s15
                              / \
						shift    go to state 15 (Array index == 15)
			    actionPart[0]    actionPart[1] + actionPart[2]
		*/

		//If state value >= 10
		if (actionPart.length() >= 3)
		{
			//Example: s15
			actionValue = actionPart.substr(1,2);
			//Creates a substring 15 from s15
		}

		//If state value < 10 
		else
		{
			actionValue = actionPart[1];
		}
		

		//Case handling
		//Shift
		if (action == "s")
		{
			cout << "Shift" << endl;
			grammarStack.push(incomingToken);
			grammarStack.push(actionValue);
			if (userInput[iterate] != '$')
			{
				iterate++;
			}
		}
		//Reduction
		else if (action == "r")
		{
			cout << "Reduction" << endl;
			RHSVal = ruleTable[identifierTerm(actionValue)][1];
			LHSVal = ruleTable[identifierTerm(actionValue)][0];

			for (int i = 0; i < 2 * identifierTerm(RHSVal); i++)
			{
				grammarStack.pop();
			}

			topOfStack = grammarStack.top();
			grammarStack.push(LHSVal);

			grammarStack.push(grammarTable[identifierTerm(topOfStack)][identifierTerm(LHSVal)]);

		}
		//Accept
		else if (action == "a")
		{
			cout << "Completed" << endl;
			break;
		}
	}

	return 0;
}

int identifierTerm(string symbol)
{
	int result;

	if (symbol == "i") {
		return 0;
	}
	else if (symbol == "+") {
		return 1;
	}
	else if (symbol == "-") {
		return 2;
	}
	else if (symbol == "*") {
		return 3;
	}
	else if (symbol == "/") {
		return 4;
	}
	else if (symbol == "(") {
		return 5;
	}
	else if (symbol == ")") {
		return 6;
	}
	else if (symbol == "$") {
		return 7;
	}
	else if (symbol == "E") {
		return 8;
	}
	else if (symbol == "T") {
		return 9;
	}
	else if (symbol == "F") {
		return 10;
	}
	else
	{
		istringstream convert(symbol);
		convert >> result;
		return result;
	}
}

