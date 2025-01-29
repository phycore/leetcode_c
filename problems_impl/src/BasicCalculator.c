#include "BasicCalculator.h"

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include "log.h"

#ifdef _DEBUG_VERSION
#define DEBUG_STR_LEN 64
#endif

#define STACK_CAPACITY 255
#define DIGITS_STR_LEN 255
#define STACK_INIT_INDEX ((int32_t)-1)

typedef struct stack_expressions {
    char stack[STACK_CAPACITY];
    int32_t top_index;
} stack_expressions_t;

static int32_t ten_power(int32_t n);

static void init_stack(stack_expressions_t* p_stack);
static void deinit_stack(stack_expressions_t* p_stack);

static int32_t push_stack(stack_expressions_t* p_stack, char push_value);
static int32_t pop_stack(stack_expressions_t* p_stack, char* p_pop_value);

static int32_t is_empty(stack_expressions_t* p_stack);
static int32_t is_full(stack_expressions_t* p_stack);

static char get_out_parenthese_sign(stack_expressions_t* p_stack);
static int32_t combine_sign(stack_expressions_t* p_stack, char outer_sign, char inter_sign);
static int32_t push_parenthese_result_to_stack(stack_expressions_t* p_stack, char* digits_string);
static int32_t calculate_parentheses(stack_expressions_t* p_stack);
static int32_t calculate_no_parentheses(stack_expressions_t* p_stack);

static int32_t ten_power(int32_t n) {
    int32_t ans = 1;
    for (size_t numbers = 0; numbers < n; numbers++) {
        ans *= 10;
    }

    return ans;
}

static void init_stack(stack_expressions_t* p_stack) {
    if (NULL != p_stack) {
        p_stack->top_index = STACK_INIT_INDEX;
        memset(&(p_stack->stack[0]), 0, (sizeof(char) * STACK_CAPACITY));
    }
}

static void deinit_stack(stack_expressions_t* p_stack) {
    if (NULL != p_stack) {
        init_stack(p_stack);
    }
}

static int32_t is_empty(stack_expressions_t* p_stack) {
    int32_t retval = -1;
    if (NULL != p_stack) {
        retval = (p_stack->top_index == STACK_INIT_INDEX) ? (1) : (0);
    }

    return retval;
}

static int32_t is_full(stack_expressions_t* p_stack) {
    int32_t retval = -1;
    if (NULL != p_stack) {
        retval = (p_stack->top_index == (STACK_CAPACITY - 1)) ? (1) : (0);
    }

    return retval;
}

static int32_t push_stack(stack_expressions_t* p_stack, char push_value) {
    int32_t retval = -1;
    if (NULL != p_stack) {
        if (!is_full(p_stack)) {
            p_stack->top_index++;
            p_stack->stack[(p_stack->top_index)] = push_value;
            retval = 0;  // return OK!
        } else {
            log_error("%s, stack is full!", __func__);
        }
    }

    return retval;
}

static int32_t pop_stack(stack_expressions_t* p_stack, char* p_pop_value) {
    int32_t retval = -1;
    if (NULL != p_stack) {
        if (!is_empty(p_stack)) {
            *p_pop_value = p_stack->stack[(p_stack->top_index)];
            p_stack->stack[(p_stack->top_index)] = 0;  // clear data!
            p_stack->top_index--;
            retval = 0;  // return OK!
        }
    }

    return retval;
}

static char get_out_parenthese_sign(stack_expressions_t* p_stack) {
    char sign = '0';
    if (!is_empty(p_stack)) {
        sign = p_stack->stack[p_stack->top_index];
    } else {
        // stack is empty!
        sign = '0';
    }
#ifdef _DEBUG_VERSION
    if (sign == '+' || sign == '-') {
        log_debug("%s, sign: %c", __func__, sign);
    } else if (sign == '(' || sign == '0') {
        log_debug("%s, there is boundary, no sign, get value: %c", __func__, sign);
    } else {
        log_warn("%s, there is not sign!!!, get value: %c", __func__, sign);
    }
#endif

    return sign;
}

static int32_t combine_sign(stack_expressions_t* p_stack, char outer_sign, char inter_sign) {
    char out_sign = get_out_parenthese_sign(p_stack);
    int32_t top_index = p_stack->top_index;
    if (out_sign == '+' || out_sign == '-') {
        // there is out sign.
        if (outer_sign == '+') {
            if (inter_sign == '+') {
                // +(+)
                // Rewrite out sign to '+'.
                if (top_index > STACK_INIT_INDEX) {
                    p_stack->stack[top_index] = '+';
                }
            } else if (inter_sign == '-') {
                // +(-)
                // Rewrite out sign to '-'.
                if (top_index > STACK_INIT_INDEX) {
                    p_stack->stack[top_index] = '-';
                }
            }
        } else if (outer_sign == '-') {
            if (inter_sign == '+') {
                // -(+)
                // Rewrite out sign to '-'.
                if (top_index > STACK_INIT_INDEX) {
                    p_stack->stack[top_index] = '-';
                }
            } else if (inter_sign == '-') {
                // -(-)
                // Rewrite out sign to '+'.
                if (top_index > STACK_INIT_INDEX) {
                    p_stack->stack[top_index] = '+';
                }
            }
        }
    } else if (out_sign == '(' || out_sign == '0') {
        // there is boundary.
        if (inter_sign == '+') {
            // (+)
        } else if (inter_sign == '-') {
            // (-)
            // Push a '-' for inter sign.
            push_stack(p_stack, '-');
        }
    }
    return 0;
}

static int32_t push_parenthese_result_to_stack(stack_expressions_t* p_stack, char* digits_string) {
    int32_t retval = -1;
    char out_parenthese_sign = get_out_parenthese_sign(p_stack);
    char* p_digit = digits_string;
    if (!is_full(p_stack)) {
        while (*p_digit != '\0') {
            switch (*p_digit) {
                case '+': {
                    combine_sign(p_stack, out_parenthese_sign, '+');
                    break;
                }
                case '-': {
                    combine_sign(p_stack, out_parenthese_sign, '-');
                    break;
                }
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9': {
                    push_stack(p_stack, *p_digit);
                    break;
                }
                default: {
                    log_error("%s, not expected digit char: %c", __func__, *p_digit);
                    retval = -1;
                    goto EXIT;
                }
            }
            p_digit++;
        }
        retval = 0;  // return OK!
    }

EXIT:
    return retval;
}

static int32_t calculate_parentheses(stack_expressions_t* p_stack) {
    int32_t parentheses_ans = 0;
    char pop_value = 0;
    int32_t temp_value = 0;
    int32_t number_of_digits = -1;
#ifdef _DEBUG_VERSION
    char debug_string[DEBUG_STR_LEN] = {0};
    memset(debug_string, 'd', DEBUG_STR_LEN);
    char* p_dbg_ch = &debug_string[DEBUG_STR_LEN - 1];
    *p_dbg_ch = '\0';
#endif
    do {
        pop_stack(p_stack, &pop_value);
#ifdef _DEBUG_VERSION
        *(--p_dbg_ch) = pop_value;
#endif
        if (pop_value == '+') {
            parentheses_ans += temp_value;
            // clear temp_value and reset number_of_digits.
            temp_value = 0;
            number_of_digits = -1;
        } else if (pop_value == '-') {
            parentheses_ans -= temp_value;
            // clear temp_value and reset number_of_digits.
            temp_value = 0;
            number_of_digits = -1;
        } else if ((pop_value == '(') || (pop_value == ')')) {
            // the latest pop digits.
            if (pop_value == '(') {
                parentheses_ans += temp_value;
            }
        } else {
            number_of_digits++;
            temp_value += (pop_value - '0') * ten_power(number_of_digits);
        }
    } while (pop_value != '(');

#ifdef _DEBUG_VERSION
    log_debug("%s, debug_string: %s", __func__, debug_string);
#endif

    return parentheses_ans;
}

static int32_t calculate_no_parentheses(stack_expressions_t* p_stack) {
    int32_t no_parentheses_ans = 0;
    char pop_value = 0;
    int32_t temp_value = 0;
    int32_t number_of_digits = -1;
    while ((p_stack->top_index) > STACK_INIT_INDEX) {
        pop_stack(p_stack, &pop_value);
        if (pop_value == '+') {
            no_parentheses_ans += temp_value;
            // clear temp_value and reset number_of_digits.
            temp_value = 0;
            number_of_digits = -1;
        } else if (pop_value == '-') {
            no_parentheses_ans -= temp_value;
            // clear temp_value and reset number_of_digits.
            temp_value = 0;
            number_of_digits = -1;
        } else {
            number_of_digits++;
            temp_value += (pop_value - '0') * ten_power(number_of_digits);

            // the latest pop digits.
            if (is_empty(p_stack)) {
                no_parentheses_ans += temp_value;
            }
        }
    }
    return no_parentheses_ans;
}

int calculate(char* s) {
    int32_t answer = 0;
    stack_expressions_t calc_stack;
    init_stack(&calc_stack);

#ifdef _DEBUG_VERSION
    size_t counter_parenthese = 0;
#endif
    size_t len = strlen(s);
    log_debug("%s, length of s:%zu", __func__, len);

    char* p_ch = s;
    while (p_ch < (s + len)) {
        if (isspace(*p_ch)) {
            p_ch++;
            continue;
        }

        switch (*p_ch) {
            case '(': {
                push_stack(&calc_stack, '(');
                break;
            }

            case ')': {
                push_stack(&calc_stack, ')');
                // work out (...) answer, and push this answer back to stack.
                int32_t temp_answer = calculate_parentheses(&calc_stack);

                // Rollback (...) answer as expression.
                char temp_answer_str[DIGITS_STR_LEN] = {0};
                snprintf(temp_answer_str, DIGITS_STR_LEN, "%d", temp_answer);
                push_parenthese_result_to_stack(&calc_stack, temp_answer_str);
#ifdef _DEBUG_VERSION
                counter_parenthese++;
                log_debug("%s, work out (#%zu) answer_string = %s", __func__, counter_parenthese,
                          temp_answer_str);
#endif
                break;
            }

            case '+':
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                push_stack(&calc_stack, *p_ch);
                break;
            }

            default:
                break;
        }
        p_ch++;
    }

    answer += calculate_no_parentheses(&calc_stack);
    log_debug("%s, no () answer = %d", __func__, answer);

    deinit_stack(&calc_stack);

    return answer;
}