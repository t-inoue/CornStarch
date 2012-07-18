#pragma once
#include <time.h>
#include "sstream"
#include "string"

class CMyTimer
{
private:
    clock_t start, end;

public:
    CMyTimer(void);
    ~CMyTimer(void);

    void push(void);

    std::string pop(void);
};

