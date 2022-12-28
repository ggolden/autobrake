#ifndef AUTOBRAKE_HARNESS_H
#define AUTOBRAKE_HARNESS_H

#include <cstdio>
#include <exception>

class Harness {
public:
    static void run_test(void(*unit_test)(), const char *name) {
        try {
            unit_test();
            printf("\033[32m[+] Test %s successful.\033[0m\n", name);
        } catch (const std::exception &e) {
            printf("\033[31m[-] Test failure in %s. %s.\033[0m\n", name, e.what());
        }
    }
};

#endif //AUTOBRAKE_HARNESS_H
