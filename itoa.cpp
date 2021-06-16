#include <iostream>
#include <assert.h>
#include <string>
#include <string.h>

void reverse(char str[], int length){
    int start = 0;
    int end = length - 1;
    
    while (start < end){
        std::swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* custom_itoa(int num, char* buffer, int base){
    int i = 0;
    bool isNegative = false;

    static const char symbols[] = {'0','1','2','3','4','5','6','7','8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
    'q','r','s','t','u','v','w','x','y','z'};
    
    if (base < 2 || base > 36){
        throw std::invalid_argument("Invalid base, has to be [2,36]");
    }
    // num 0 is handled as a special case
    if (num == 0){
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // add a minus sign if we are in base 10 and have a 
    // negative value
    if (num < 0 && base == 10){
        isNegative = true;
        num = -num;
    }

    while (num != 0){
        int rem = num % base; // get the digit
        buffer[i++] = symbols[rem];
        num = num/base; // move onto the next digit
    }

    if (isNegative){
        buffer[i++] = '-';
    }
    // terminate string
    buffer[i] = '\0';
    // since our most significant value is at the end, we need
    // to reverse the string for the output to make sense
    reverse(buffer, i);

    return buffer;
}

int main(){
    char str[100];

    // test 1
    custom_itoa(1567, str, 10);
    std::cout << str << std::endl;
    assert(strcmp(str, "1567") == 0);
    // test 2
    custom_itoa(-1567, str, 10);
    std::cout << str << std::endl;
    assert(strcmp(str, "-1567") == 0);
    // test 3
    custom_itoa(1567, str, 2);
    std::cout << str << std::endl;
    assert(strcmp(str, "11000011111") == 0);
    // test 4
    custom_itoa(1567, str, 16);
    std::cout << str << std::endl;
    assert(strcmp(str, "61f") == 0);

    std::cout << "ALL TESTS PASSED!" << std::endl;

    std::cout.flush();

    return 0;
}