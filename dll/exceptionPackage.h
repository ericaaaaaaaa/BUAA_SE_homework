#pragma once
//
// Created by lenovo on 2022/3/29.
//

#ifndef CLIONWORDLIST_EXCEPTIONPACKAGE_H
#define CLIONWORDLIST_EXCEPTIONPACKAGE_H
#define RESULT_CONTAIN 20000
#include <iostream>
#include <exception>
using namespace std;

struct MyException : public exception
{
    const char* what() const throw ()
    {
        return "C++ Exception";
    }
};

struct LoopException : public exception
{
    const char* what() const throw ()
    {
        return "ERROR: contains loop.";
    }
};

struct ResultContainException : public exception
{
    ResultContainException(int i) {
        length = i;
    }

    int length;
    const char* what() const throw ()
    {
        return "ERROR: the result list length is constrained in 20000.";
    }
};

struct FileException : public exception
{
    const char* what() const throw ()
    {
        return "ERROR: cannot open file.";
    }
};

struct DuplicatedInvalidParamException : public exception
{
    const char* what() const noexcept override
    {
        return "ERROR: duplicated parameter or invalid parameter";
    }
};

struct HTParamEmptyException : public exception
{
    const char* what() const noexcept override
    {
        return "ERROR: a parameter is needed after -h or -t.";
    }
};

struct HTParamIllegalException : public exception
{
    const char* what() const noexcept override
    {
        return "ERROR: illegal parameter after -h or -t.";
    }
};
#endif //CLIONWORDLIST_EXCEPTIONPACKAGE_H