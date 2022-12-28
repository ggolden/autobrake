//
// Created by Glenn R. Golden on 12/27/22.
//

#ifndef AUTOBREAK_HARNESS_H
#define AUTOBREAK_HARNESS_H

#include <cstdio>
#include <exception>

class Harness {
public:

    static void run_test(void(*unit_test)(), const char *name) {
        try {
            unit_test();
            printf("[+] Test %s successful.\n", name);
        } catch (const std::exception &e) {
            printf("[-] Test failure in %s. %s.\n", name, e.what());
        }
    }
};

#endif //AUTOBREAK_HARNESS_H
