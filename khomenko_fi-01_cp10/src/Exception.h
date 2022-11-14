#ifndef AAF_LABS_2022_EXCEPTION_H
#define AAF_LABS_2022_EXCEPTION_H

#include <string>
#include <utility>
#include <stdexcept>

class Exception : public std::exception {
public:
    Exception(const char *msg) : msg_(msg) {    }

    Exception(const std::basic_string<char>& error_string):msg_(error_string.c_str()) {  }

    ~Exception() {  }

    const char *what() const noexcept override {
        return msg_.what();
    }
private:
    std::runtime_error msg_;
};

#endif //AAF_LABS_2022_EXCEPTION_H
