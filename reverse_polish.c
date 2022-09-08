#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
size_t str_len(char *str) {
    size_t i = 0;
    for (i; str[i] != '\0'; ++i);
    
    return i;
}

void push_op(char *operators, char op, int *top) {
    operators[*top+1] = op;
    *top += 1;
}

void pop(char *operators, int *top) {
    operators[*top] = '\0';
    *top -= 1;
    
}

bool is_operand(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

size_t count_ops(char *expr) {          // Count the amount of operators in expr
    size_t count = 0;
    for (size_t i = 0; i < str_len(expr); ++i) {
        if (is_operand(expr[i])) {
            count++;
        }
    }
    return count;
}

void cp_arg(char *argv, char *dest) {
    for (size_t i = 0; i < str_len(argv); ++i) {
        dest[i] = argv[i];
    }
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Missing expression argument or exceding arguments needed!\n");
        return -1;
    }
    char *expr = (char*) malloc(str_len(argv[1]));
    int i_expr = 0;
    cp_arg(argv[1], expr);
    size_t len = str_len(expr);                                     //  Length of expression
    expr[len] = ')';                                                //  Automatic End Parenthesis
    expr[len+1] = '\0';
    len += 1;

    size_t amount_of_operators = count_ops(expr);

    if (amount_of_operators == 0) {
         printf("Insert an valid math expression!");
         return -1;
     }

    char *p_expr = (char*) malloc(len + amount_of_operators);       //  Allocates memory to the resulting RPN expression
    size_t i_p_expr = 0;
    char *operators = (char*) malloc(amount_of_operators + 1);      //  This will be the stack of operators 
    int top = -1;                                                   //  Top of stack
    
    bool err_happened = false;
    while (i_expr < len) {
        if (isdigit(expr[i_expr])) {
            p_expr[i_p_expr] = expr[i_expr];
            i_p_expr++;
        }
        else if (is_operand(expr[i_expr])) {
            push_op(operators, expr[i_expr], &top);
            p_expr[i_p_expr] = ' ';
            i_p_expr++;
        }
        else if (expr[i_expr] == ')') {
            if (top < 0) {
                printf("Invalid operation!\n");
                err_happened = true;
                break;
            }
            p_expr[i_p_expr] = ' ';
            p_expr[i_p_expr+1] = operators[top];
            i_p_expr += 2;
            pop(operators, &top);                
            
        }
        else if (expr[i_expr] == '.') {
            p_expr[i_p_expr] = '.';
            i_p_expr++;
        }

        i_expr++;
    }
    
    if (!err_happened) {
        size_t length = str_len(p_expr);
        
        printf("Equivalent RPN Expression: ");
        for (size_t i = 0; i < length; ++i) {
            printf("%c", p_expr[i]);
        }
        printf("\n");
        return 0;
    }


    return -1;
}
