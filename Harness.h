#ifndef AUTOBRAKE_HARNESS_H
#define AUTOBRAKE_HARNESS_H

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

#endif //AUTOBRAKE_HARNESS_H
