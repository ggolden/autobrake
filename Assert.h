//
// Created by Glenn R. Golden on 12/27/22.
//

#ifndef AUTOBREAK_ASSERT_H
#define AUTOBREAK_ASSERT_H

#include <stdexcept>
constexpr void assert_that(bool statement, const char* message) {
    if (!statement) throw std::runtime_error{message};
}

#endif //AUTOBREAK_ASSERT_H
