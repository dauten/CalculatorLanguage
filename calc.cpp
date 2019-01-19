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
  if(m.type == operand::PAR && m.value == 0){
    s.push(t);
    return s;

  }
  operand b = s.top();
  s.pop();
  int r = 0;

  if(m.value == 0){
    //add

    if(b.type == operand::PAR){
      s = perform(s, al);//b=result of interior of parenthesis
      int to =  s.top().value ;
      b = s.top();
      b.type = operand::SCA;
      b.value = to;
      s.pop();

    }

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
    if(b.type == operand::PAR){
      s = perform(s, al);//b=result of interior of parenthesis
      int to =  s.top().value ;
      b = s.top();
      b.type = operand::SCA;
      b.value = to;
      s.pop();

    }

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

    if(b.type == operand::PAR){
      s = perform(s, al);//b=result of interior of parenthesis
      int to =  s.top().value ;
      b = s.top();
      b.type = operand::SCA;
      b.value = to;
      s.pop();

    }

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

    if(b.type == operand::PAR){
      s = perform(s, al);//b=result of interior of parenthesis
      int to =  s.top().value ;
      b = s.top();
      b.type = operand::SCA;
      b.value = to;
      s.pop();

    }

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
    if(t.type == operand::SCA){
      al[b.value] = t.value;
    }
    if(t.type == operand::VAR){
      al[b.value] = al[t.value];
    }
    r = al[b.value];
  }
  operand o;
  o.type = operand::SCA;
  o.value = r;
  if(s.empty()){
    s.push(o);
    return s;
  }

  s.push(o);
  return perform(s, al);

}


int main () {

  std::string input;
  std::stack<operand> stack;
  std::ifstream infile("191.in");
  int alphabet[0x5B]; //current variable values
                    //when operand is between values 0x41 and 0x5A
                    //subtract 65 (0x41) from it to find its current-ness
                    //in the array
  int old[0x5B];
  for(int y = 0 ; y < 0x5B; y++){
    old[y] = 0;
    alphabet[y] = 0;
  }

  operand o;

  std::stack<operand> s;

  std::string line;
  //read input
  if(infile.is_open()){
    while(getline(infile, line)){
        std::cout << "\n\n" << line << '\n';
        std::string built = "";
        for(int i = 0; i < line.length(); i++){
          char next = line[i];



          if(built != "" && (next < 48 || next > 57)){
            o.type = operand::SCA;
            o.value = atoi(built.c_str());
            built = "";
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }

          if(next > 64 && next < 91){
            //add to stack a VAR with value next
            o.type = operand::VAR;
            o.value = next;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 40){
            //add to stack a PAR with value 0
            o.type = operand::PAR;
            o.value = 0;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 41){
            //add to stack a PAR with value 1
            o.type = operand::PAR;
            o.value = 1;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 43){
            //add +
            o.type = operand::OP;
            o.value = 0;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 45){
            //add -
            o.type = operand::OP;
            o.value = 1;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 42){
            //add *
            o.type = operand::OP;
            o.value = 2;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 47){
            //add /
            o.type = operand::OP;
            o.value = 3;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next == 61){
            //add =
            o.type = operand::OP;
            o.value = 4;
            s.push(o);
            //std::cout << "Pushing type " << o.type << " with vaule " << o.value << '\n';
          }
          else if(next > 47 && next < 58){
            //start constructing an int, may be more than one chars and may be negated
            built += next;
            //std::cout << "build is now " << built << " because next was "<< (next-48) << '\n';

          }
          else if(next == 95){
            //proceed as if a number follows, but set flag to negate it
            built = "-";
          }
        }

        s = perform(s, alphabet);

        for(char i = 0; i < 0x5B; i++){
          if(old[i] != alphabet[i]){
            std::cout << i << " = " << alphabet[i] << ", ";
          }
          old[i] = alphabet[i];
        }



        s.pop();

    }
  }

  s = perform(s, alphabet);

  for(char i = 0; i < 0x5B; i++){
    if(old[i] != alphabet[i]){
      std::cout << i << " = " << alphabet[i] << ", ";
    }
  }
  return 0;
}
