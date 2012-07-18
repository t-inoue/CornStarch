#include "MyTimer.hpp"

using namespace std;

CMyTimer::CMyTimer(void)
{
}


CMyTimer::~CMyTimer(void)
{
}


void CMyTimer::push(void)
{
    start = clock();
}

string CMyTimer::pop(void)
{
    end = clock();

    double result = (double)(end - start) / CLOCKS_PER_SEC;
    stringstream ss;
    ss << result;
    string s;
    ss >> s;
    return s;
}
