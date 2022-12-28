#ifndef AUTOBRAKE_ASSERT_H
#define AUTOBRAKE_ASSERT_H

#include <stdexcept>

constexpr void assert_that(bool statement, const char *message) {
    if (!statement) throw std::runtime_error{message};
}

#endif //AUTOBRAKE_ASSERT_H
