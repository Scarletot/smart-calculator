#include <iostream>
short pos = 0;


double parseNumber(const char* input){
  double num = 0;
  while (input[pos] >= '0' && input[pos] <= '9'){
    num = num *10 + (input[pos] - '0');
    pos++;
  }
  if (input[pos] == '.'){
    double fl = 0.1;
    pos++;
    while (input[pos] >= '0' && input[pos] <= '9'){
      num = num + fl * (input[pos] - '0');
      pos++;
      fl /= 10;
       }
  }
  return num;
}


double parseExpression(const char* input); 


double mult_and_div(const char* input, double second_num){
  
    while (input[pos] == '*' || input[pos] == '/'){
      char oper = input[pos];
      pos++;
      double next_num = parseNumber(input);
      if (input[pos] == '('){
        pos++;
        next_num = parseExpression(input);
      }
      if (input[pos] == '!'){
        break;
      }
      if (oper == '*') {
          second_num *= next_num;

        } else if (oper == '/'){
          if (next_num == 0){
            return 0;
          }
          second_num /= next_num;
        }
    }
    return second_num;
}

double parseExpression(const char* input){
  double first_num = parseNumber(input);
  double second_num;
  char oper = input[pos];
  if (oper == '+' || oper == '-'){
    pos++;
    if (input[pos] == '('){
      pos++;
      second_num = parseExpression(input);
    } else{
    second_num = parseNumber(input);}
    }
    if (input[pos]=='*' || input[pos]=='/'){
      second_num = mult_and_div(input, second_num);
    }

  return first_num + second_num;
}

int main(){
  char* math = new char[100];
  
  std::cout << "Введіть математичний віраз: ";
  std::cin >> math;
  double res =parseExpression(math);
  std::cout << "Результат: " << res << std::endl;
  return 0;
  
}

