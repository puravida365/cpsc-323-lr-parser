#include <iostream>
#include <string>
#include <stack>

using namespace std;

class LR{
	private:
		string table[15][11] = { {} };
		stack <string> T;
		string expression;
		string input;
		int counter;
		int n;
		string temp;
		string token;
	
	public:
		LR(){
			expression = "(i+i)/i$";
			counter = 0;
		}
		void parse(){
			T.push("0");
			
			while(!T.empty()){
				if(temp == "1"){
					cout << "Accept" << endl;
					break;
				}
				else{
					input = expression[counter];
					pop();
					tokenize();
					g();
				}
			}
		}
		void pop(){
			temp = T.top();
			T.pop();
			cout << temp << endl;
		}
		void tokenize(){
			n = temp.length();
			token = temp;
			if(n == 1){
				token = token.insert(1,input);
				
			}
			else{
				token = token.insert(2,input);

			}	
			cout << token << endl;
		}
		void g(){
			// s4 state
			if (token == "0("){
				T.push("0");
				T.push("(");
				T.push("4");
				counter++;
			}
			// s5 state
			else if (token == "4i"){
				T.push("4");
				T.push("i");
				T.push("5");
				counter++;
			}
			// r8 state - F -> i |i| = 1, pop 2*1 items
			else if (token == "5+"){
				T.push("5");
				pop();
				pop();
				input = "F";
				pop();
				tokenize();
				g();
			}
			else if (token == "4F"){
				T.push("4");
				T.push("F");
				T.push("3");
			}
			// r6 state T -> F |F| = 1, pop 2*1 items
			else if (token == "3+"){
				T.push("3");
				pop();
				pop();
				input = "T";
				pop();
				tokenize();
				g();				
			}
			else if (token == "4T"){
				T.push("4");
				T.push("T");
				T.push("2");
			}
			// r3 state E -> T |T| = 1, pop 2*1 items
			else if (token == "2+"){
				T.push("2");
				pop();
				pop();
				input = "E";
				pop();
				tokenize();
				g();
			}
			else if (token == "4E"){
				T.push("4");
				T.push("E");
				T.push("10");	
			}
			// s6
			else if (token == "10+"){
				T.push("10");
				T.push("6");
				counter++;
			}
			// s5
			else if (token == "6i"){
				T.push("6");
				T.push("i");
				T.push("5");
				counter++;
			}
			// r8 state F -> i |i| = 1, pop 2*1 items
			else if (token == "5)"){
				T.push("5");
				pop();
				pop();
				input = "F";
				pop();
				tokenize();
				g();
			}
			else if (token == "6F"){
				T.push("6");
				T.push("F");
				T.push("3");
			}
			// r6 state T -> F |F| = 1, pop 2*1 items
			else if (token == "3)"){
				T.push("3");
				pop();
				pop();
				input = "T";
				pop();
				tokenize();
				g();
			}
			else if (token == "6T"){
				T.push("6");
				T.push("T");
				T.push("11");	
			}
			// r1 state E -> E + T |E+T|=3, pop 2*3 items
			else if (token == "11J"){
				T.push("11");
				pop();
				pop();
				pop();
				pop();
				pop();
				pop();
				input = "E";
				pop();
				tokenize();
				g();
			}
			else if (token == "4E"){
				T.push("4");
				T.push("E");
				T.push("10");
			}
			// s15 state
			else if (token == "10)"){
				T.push("10");
				T.push(")");
				T.push("15");
				counter++;
			}
			// c7 F -> (E) |(E)|= 3, pop 2*3 items
			else if (token == "15/"){
				T.push("15");
				pop();
				pop();
				pop();
				pop();
				pop();
				pop();
				input = "F";
				pop();
				tokenize();
				g();
				
			}
			else if (token == "0F"){
				T.push("0");
				T.push("F");
				T.push("3");
			}
			// r6 state T -> F |F| = 1, pop 2*1 items
			else if (token == "3/"){
				T.push("3");
				pop();
				pop();
				input = "T";
				pop();
				tokenize();
				g();
			}
			else if (token == "0T"){
				T.push("0");
				T.push("T");
				T.push("2");
			}
			else if (token == "2/"){
				T.push("2");
				T.push("/");
				T.push("9");
				counter++;
			}
			// s5 state
			else if (token == "9i"){
				T.push("9");
				T.push("i");
				T.push("5");
				counter++;
			}
			// r8 state F -> i |i|=1, pop 2*1 items
			else if (token == "5$"){
				T.push("5");
				pop();
				pop();
				input = "F";
				pop();
				tokenize();
				g();
			}
			else if (token == "9F"){
				T.push("9");
				T.push("F");
				T.push("14");
			}
			// r5 state T -> T/F |T/F|=3, pop 2*3 items
			else if (token == "14$"){
				T.push("14");
				pop();
				pop();
				pop();
				pop();
				pop();
				pop();
				input = "T";
				pop();
				tokenize();
				g();
			}
			// r3 state E -> T |T| = 1, pop 2*1 items
			else if (token == "2$"){
				T.push("2");
				pop();
				pop();
				input = "E";
				pop();
				tokenize();
				g();
			}
			else if (token == "0E"){
				T.push("0");
				T.push("E");
				T.push("1");
			}
		}
		
};

int main(){
	LR A;
	A.parse();
	return(0);
}