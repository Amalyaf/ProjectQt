#ifndef BAD_PASSWORD_H
#define BAD_PASSWORD_H

#pragma once
#include <exception>

class BadPassword :public std::exception
{
public:
    virtual const char* what() const noexcept override;
};

#endif // BAD_PASSWORD_H
