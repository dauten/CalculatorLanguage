#include <iostream>
#include <fstream>
#include <string>
#include <stack>




class operand{
public:
  enum techs_t {OP, VAR, SCA, PAR};
  techs_t type;
  int value;  //if operator: 0=add, 1=sub, 2=mult, 3=divide
              //if variable, 0=A, 1=B, 2=C,...,25=Z
              //if scalar value is values
              //if paren, 0=open, 1=close

  operand(techs_t t, int val){
    type = t;
    value = val;
  }

  operand(){

  }

  operand operator=(const operand& other){
    operand o;
    o.type = other.type;
    o.value = other.value;
    return o;
  }
};



int main () {

  std::string input;
  std::ifstream myfile("191.in");
  std::stack<operand> stack;
  operand alphabet[26]; //current variable values
                    //when operand is between values 0x41 and 0x5A
                    //subtract 65 (0x41) from it to find its current-ness
                    //in the array
  operand o;
  o.type = operand::SCA;
  o.value = 15;
  stack.push(o);

  o.type = operand::OP;
  o.value = 1;
  stack.push(o);

  o.type = operand::SCA;
  o.value = 8;
  stack.push(o);

  o.type = operand::OP;
  o.value = 1;
  stack.push(o);

  o.type = operand::SCA;
  o.value = 3;
  stack.push(o);

  std::cout << stack.top().value << '\n';
  stack.pop();
  std::cout << stack.top().value << '\n';
  stack.pop();
  std::cout << stack.top().value << '\n';
  stack.pop();
  std::cout << stack.top().value << '\n';
  stack.pop();
  std::cout << stack.top().value << '\n';
  stack.pop();
  /*
  getline(myfile,input);
  //while ( getline(myfile,input) )
  {
    for(int i = 0; i < input.length(); i++){
      if(input[i] != ' ' && input[i] != '\n' && input[i] != '\r'){
        stack.push(input[i]);
        std::cout << stack.top() << '\n';
      }

    }
  }*/
  myfile.close();
  return 0;
}
