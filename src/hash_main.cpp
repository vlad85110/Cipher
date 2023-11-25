//
// Created by vlad on 25.11.23.
//

#include "JenkinsHash.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    String input;

    cout << "Enter your string: ";
    std::cin >> input;

    auto hash = JenkinsHash::calculate(input);
    std::cout << "Result: " << hash << std::endl;

    return 0;
}
