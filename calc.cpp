#include <iostream>
#include <fstream>
#include <string>
#include <stack>




class operand{
public:
  enum techs_t {OP, VAR, SCA, PAR};
  techs_t type;
  int value;  //if operator: 0=add, 1=sub, 2=mult, 3=divide, 4=assignment
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

void operate(operand a, operand b, operand c){

}

std::stack<operand> perform(std::stack<operand> s, int al[]){
  operand t = s.top();
  s.pop();
  operand m = s.top();
  s.pop();
  operand b = s.top();
  s.pop();
  int r = 0;
  if(m.value == 0){
    //add
    if(b.type == operand::SCA && t.type == operand::SCA)
      r = b.value + t.value;
    if(b.type == operand::VAR && t.type == operand::SCA)
      r = al[b.value] + t.value;
    if(b.type == operand::SCA && t.type == operand::VAR)
      r = b.value + al[t.value];
    if(b.type == operand::VAR && t.type == operand::VAR)
      r = al[b.value] + al[t.value];
    //if b or t's type is VAR, instead of using itself use alphabet[b.value]
  }
  if(m.value == 1){
    //add
    if(b.type == operand::SCA && t.type == operand::SCA)
      r = b.value - t.value;
    if(b.type == operand::VAR && t.type == operand::SCA)
      r = al[b.value] - t.value;
    if(b.type == operand::SCA && t.type == operand::VAR)
      r = b.value - al[t.value];
    if(b.type == operand::VAR && t.type == operand::VAR)
      r = al[b.value] - al[t.value];
    //if b or t's type is VAR, instead of using itself use alphabet[b.value]
  }if(m.value == 2){
    //add
    if(b.type == operand::SCA && t.type == operand::SCA)
      r = b.value * t.value;
    if(b.type == operand::VAR && t.type == operand::SCA)
      r = al[b.value] * t.value;
    if(b.type == operand::SCA && t.type == operand::VAR)
      r = b.value * al[t.value];
    if(b.type == operand::VAR && t.type == operand::VAR)
      r = al[b.value] * al[t.value];
    //if b or t's type is VAR, instead of using itself use alphabet[b.value]
  }if(m.value == 3){
    //add
    if(b.type == operand::SCA && t.type == operand::SCA)
      r = b.value / t.value;
    if(b.type == operand::VAR && t.type == operand::SCA)
      r = al[b.value] / t.value;
    if(b.type == operand::SCA && t.type == operand::VAR)
      r = b.value / al[t.value];
    if(b.type == operand::VAR && t.type == operand::VAR)
      r = al[b.value] / al[t.value];
    //if b or t's type is VAR, instead of using itself use alphabet[b.value]
  }
  if(m.value == 4){
    //assignment
    if(t.type == operand::SCA)
      al[b.value] = t.value;
    if(t.type == operand::VAR)
      al[b.value] = al[t.value];
  }
  operand o;
  o.type = operand::SCA;
  o.value = r;
//  std::cout << r << '\n';
  s.push(o);
  return s;
}


int main () {

  std::string input;
  std::ifstream myfile("191.in");
  std::stack<operand> stack;
  int alphabet[0x5B]; //current variable values
                    //when operand is between values 0x41 and 0x5A
                    //subtract 65 (0x41) from it to find its current-ness
                    //in the array

  alphabet[0x41] = 4;
  operand o;
  o.type = operand::SCA;
  o.value = 15;
  stack.push(o);

  o.type = operand::OP;
  o.value = 0;
  stack.push(o);

  o.type = operand::VAR;
  o.value = 0x41;
  stack.push(o);

  o.type = operand::OP;
  o.value = 1;
  stack.push(o);

  o.type = operand::SCA;
  o.value = 3;
  stack.push(o);

  stack = perform(stack, alphabet);
  stack = perform(stack, alphabet);
//  stack = s;
  std::cout << stack.top().value << '\n';


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
