#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
using namespace std;

#ifdef LOCAL
    #define DEBUG_COLOR "\033[36m"
    #define RESET_COLOR "\033[0m"
    
    template<typename... Args>
    void de(Args&&... args) {
        cout << DEBUG_COLOR;
        ((cout << args << " "), ...);
        cout << RESET_COLOR << endl;
    }

    template<typename... Args>
    void dl(Args&&... args) {
        cout << DEBUG_COLOR;
        ((cout << args << " "), ...);
        cout << RESET_COLOR << ' ';
    }
#else
    template<typename... Args>
    void de(Args&&...) {}

    template<typename... Args>
    void dl(Args&&...) {}
#endif

#endif // DEBUG_HPP
