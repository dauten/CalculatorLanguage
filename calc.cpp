#include <iostream>
#include <fstream>
#include <string>
#include <stack>


int main () {
  std::string input;
  std::ifstream myfile("191.in");
  std::stack<char> stack;


  while ( getline(myfile,input) )
  {
    for(int i = 0; i < input.length(); i++){
      if(input[i] != ' ' && input[i] != '\n' && input[i] != '\r'){
        stack.push(input[i]);
        std::cout << stack.top() << '\n';
      }
      else if(input[i] == '\r'){
        std::cout << "NEWLINE" << '\n';
      }
    }
  }
  myfile.close();
  return 0;
}
