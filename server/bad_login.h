#ifndef BAD_LOGIN_H
#define BAD_LOGIN_H

#pragma once
#include <exception>

class BadLogin :public std::exception
{
public:
    virtual const char* what() const noexcept override;
};

#endif // BAD_LOGIN_H
