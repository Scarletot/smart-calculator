
#include <iostream>
#include <cstring>

bool isOper(char oper) {
    return (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '(' || oper == ')' || oper == '!');
}

short priority(char oper) {
    if (oper == '+' || oper == '-') {
        return 1;
    } else if (oper == '*' || oper == '/') {
        return 2;
    }else if(oper == '!' ){
        return 3;
    }else {
        return 0;
    }
}
long fib(double num){
    if (num == 1)
      return 1;
    return num * fib(num-1);

}

void toRPN(const char* exp, char* output) {
    char stack_oper[100];
    short top_oper = -1;
    short out_index = 0;
    char num_buffer[10];
    short num_index = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == ' ') {
            continue;
        }

        if (exp[i] >= '0' && exp[i] <= '9') {
            num_buffer[num_index++] = exp[i];
        } else {
            if (num_index > 0) {
                for (int j = 0; j < num_index; j++) {
                    output[out_index++] = num_buffer[j];
                }
                output[out_index++] = ' ';
                num_index = 0;
            }
            if (exp[i] == '(') {
                stack_oper[++top_oper] = exp[i];
            } else if (exp[i] == ')') {
                while (top_oper >= 0 && stack_oper[top_oper] != '(') {
                    output[out_index++] = stack_oper[top_oper--];
                    output[out_index++] = ' ';
                }
                top_oper--;
            } else if (isOper(exp[i])) {
                while (top_oper >= 0 && priority(stack_oper[top_oper]) >= priority(exp[i])) {
                    output[out_index++] = stack_oper[top_oper--];
                    output[out_index++] = ' ';
                }
                stack_oper[++top_oper] = exp[i];
            }
        }
    }

    if (num_index > 0) {
        for (int j = 0; j < num_index; j++) {
            output[out_index++] = num_buffer[j];
        }
        output[out_index++] = ' ';
    }

    while (top_oper >= 0) {
        output[out_index++] = stack_oper[top_oper--];
        output[out_index++] = ' ';
    }

    output[out_index] = '\0';
}

double eva(const char* rpn) {
    double stack[100];
    short top = -1;

    for (int i = 0; rpn[i] != '\0'; i++) {
        if (rpn[i] >= '0' && rpn[i] <= '9') {
            double num = 0;
            while (rpn[i] >= '0' && rpn[i] <= '9') {
                num = num * 10 + (rpn[i] - '0');
                i++;
            }
            stack[++top] = num;
        } else if (isOper(rpn[i])) {
            if (rpn[i] == '!'){
              stack[top] = fib(stack[top]);
              continue;
            }
            double b = stack[top--];
            double a = stack[top--];
            double result;
            switch (rpn[i]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            stack[++top] = result;
        }
    }

    return stack[top];
}

int main() {
    char math[100];
    char rpn[100];

    std::cout << "Введіть математичний вираз: ";
    std::cin.getline(math, 100);

    toRPN(math, rpn);

    std::cout << "Зворотна польська нотація: ";
    for (int i = 0; rpn[i] != '\0'; i++) {
        std::cout << rpn[i];
    }
    std::cout << std::endl;

    double res = eva(rpn);
    std::cout << "Результат: " << res << std::endl;

    return 0;
}
