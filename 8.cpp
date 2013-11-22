#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;

char *SYMBOLS = "i+-*/()$ETF";

int assignValue(char state);
void printStack(stack<int> state_stack);
char reassignChar(int value);

int main()
{
	// Initialize table from book
	int table[16][11] = {205, 0,0,0,0,204,0,0,401,402,403,
						0,206,207,0,0,0,0,500,0,0,0,
						0,303,303,208,209,0,303,303,0,0,0,
						0,306,306,306,306,0,306,306,0,0,0,
						205,0,0,0,0,204,0,0,410,402,403,
						0,308,308,308,308,0,308,308,0,0,0,
						205,0,0,0,0,204,0,0,0,411,403,
						205,0,0,0,0,204,0,0,0,412,403,
						205,0,0,0,0,204,0,0,0,0,413,
						205,0,0,0,0,204,0,0,0,0,414,
						0,206,207,0,0,0,215,0,0,0,0,
						0,301,301,208,209,0,301,301,0,0,0,
						0,302,302,208,209,0,302,302,0,0,0,
						0,304,304,304,304,0,304,304,0,0,0,
						0,305,305,305,305,0,305,305,0,0,0,
						0,307,307,307,307,0,307,307,0,0,0};
	// Lengths of grammar rules
	int grammar[8] = {3,3,1,3,3,1,3,1};

	stack<int> state_stack;
	int action = 4, state, term, tvalue, adjust = 16;
	int index = 0;
	string teststring;
	
	// Initialize stack and string
	state_stack.push(0);
	cout << "Enter a string: ";
	cin >> teststring;
	teststring = teststring + "$";
	
	//While not accepted or rejected
	while(action != 3 && action != 0)
	{
		//Determine table value based on top of stack and input
		//States are 0-15, terminals are 16-26. The variable "adjust" is used
		// to fix terminal values to be able to access table.
		// i.e. "i" is 16, but in the table it is index 0. we adjust by 16
		state = state_stack.top();
		term = assignValue(teststring[index]) - adjust; 
		tvalue = table[state][term];

		//Determine what action to take based on table value
		// Shift = 200s. Reduce = 300s. 500 accept
		if(tvalue > 200 && tvalue <300)
			action = 1;
		else if(tvalue > 300 && tvalue < 400)
			action = 2;
		else if(tvalue == 500)
			action = 3;
		else
			action = 0;

		int value;
		switch(action)
		{
		case 0:
			cout << "Input NOT accepted" << endl;
			cout << "No table entry for [" << state << ", " << teststring[index] << "]" << endl;
			break;
		//Shift case - push input token and next state
		case 1:
			value = assignValue(teststring[index]);
			state_stack.push(value);
			state_stack.push(tvalue%100); // Modulo used to determine last digit, 204 -> 4
			index++;
			break;
		// Reduce case - reduce by 2* rule size, push left side of rule and state
		case 2:
			int temp;
			int stat;
			// Pop for 2 times the grammar size.
			for(int x = 0; x < 2*grammar[(tvalue%100)-1]; x++)
				state_stack.pop();
			// Depending on what grammar rule, push the left side of the rule and state
			if(tvalue%100 <=3)
			{
				temp = assignValue('E');
				stat = (table[state_stack.top()][temp-adjust])%100;
				state_stack.push(temp);
				state_stack.push(stat);
			}
			else if(tvalue%100 >= 7)
			{
				temp = assignValue('F');
				stat = (table[state_stack.top()][temp-adjust])%100;
				state_stack.push(temp);
				state_stack.push(stat);
			}
			else
			{
				temp = assignValue('T');
				stat = (table[state_stack.top()][temp-adjust])%100;
				state_stack.push(temp);
				state_stack.push(stat);
			}
			break;
		case 3:
			cout << "Input is accepted! " << endl;
		}
		
		// Print stack and input unless finished
		if(action != 3 && action != 0)
		{
			printStack(state_stack);
			cout << setw(5);
			for(int print = index; print < teststring.size(); print++)
			{
				cout << teststring[print];
			}
			cout << endl;
		}
	}
	return 0;
}

// Assigns value to terminals starting at 16 to not mix up with states 0-15
int assignValue(char terminal)
{
	const char *find = strchr(SYMBOLS, terminal);
	
	// Error number
	if(find == NULL)
		return 9001;
		
	return (find - SYMBOLS) + 16;
}

// Opposite of previous function, we must convert terminals back to char
// when printing the stack
char reassignChar(int value)
{
	return SYMBOLS[value - 16];
}

// Prints stack, converts terminal values to char
void printStack(stack<int> state_stack)
{
	stack<int> print_stack;
	while(!state_stack.empty())
	{
		print_stack.push(state_stack.top());
		state_stack.pop();
	}
	while(!print_stack.empty())
	{
		if(print_stack.top() > 15)
			cout<< reassignChar(print_stack.top());
		else
			cout << print_stack.top();
		state_stack.push(print_stack.top());
		print_stack.pop();
	}
}