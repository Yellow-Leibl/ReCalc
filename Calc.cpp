#include "tort.h"

void CleanMas(char mas[], int len)
{
    for (int i = 0; i < len; i++)
        mas[i] = 0;
}

class NumBuf
{
    public:
    
    char buffer[LNGb];
    int len = 0;

    void PushChar(char c) {
        buffer[len++] = c;
    }

    double getNum()
    {
        double num = atof(buffer);
        CleanMas(buffer, len);
        len = 0;
        return num;
    }

    NumBuf() { }
};

class OperBuf
{
    public:

    double lev[LNGb];
    double kof[LNGb];
    char  oper[LNGb];
    int sizeB = 0;

    void PushNum(double num) {
        lev[sizeB-1] += num;
    }

    void AddLvl(char op, double k = 1)
    {
        lev[sizeB] = 0;
        oper[sizeB] = op;
        kof[sizeB++] = k;
    }

    /*void DelLvl()// динам масив
    {
        lev[--sizeB] = 0;
        kof[sizeB]  = 0;
    }*/

    double getNum()
    {
        if (sizeB-- == 0)
            return 0;

        //cout << lev[sizeB] << "-lev" << endl;
        if (oper[sizeB] == '+')
            return lev[sizeB];
        else if (oper[sizeB] == '-')
            return -lev[sizeB];
        else if (oper[sizeB] == '/')
            return kof[sizeB] / lev[sizeB];
        else
            return kof[sizeB] * lev[sizeB];
    }
    
    OperBuf() { }
};

double Calc(const char exp[], NumBuf buf = NumBuf(), 
            double prevNum = 1, char op = '\0', OperBuf opB = OperBuf())
{
    double t;
    if (isdigit(*exp) || '.' == *exp || ',' == *exp)
    {
        if (',' == *exp)
            buf.PushChar('.');
        else
            buf.PushChar(*exp);
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if ('+' == *exp || '-' == *exp)
    {
        if (op == '*')
            t = prevNum * buf.getNum();
        else if (op == '/')
            t = prevNum / buf.getNum();
        else if (op == ')')
            t = prevNum;
        else
            t = buf.getNum();
        
        buf.PushChar(*exp);
        
        if (opB.sizeB != 0)
        {
            opB.PushNum(t);
            return Calc(exp+1, buf, 1, 0, opB);
        }

        return t + Calc(exp+1, buf);
    }
    else if ('*' == *exp || '/' == *exp)
    {
        if (op == '/')
            prevNum /= buf.getNum();
        else if (op == ')') ;
        else
            prevNum *= buf.getNum();
        
        op = *exp;
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if ('(' == *exp)
    {
        if (*buf.buffer == '-')
            opB.AddLvl('*', -1);
        else
            opB.AddLvl(op, prevNum);
        buf.getNum();
        return Calc(exp+1, buf, 1, 0, opB);
    }
    else if (')' == *exp)
    {
        if (op == '/')
            prevNum /= buf.getNum();
        else if (op == ')') ;
        else
            prevNum *= buf.getNum();
        
        op = ')';
        opB.PushNum(prevNum);
        prevNum = opB.getNum();
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if (isspace(*exp))
        return Calc(exp+1, buf, prevNum, op, opB);

    if (op == '*')
        return prevNum * buf.getNum();
    else if (op == '/')
        return prevNum / buf.getNum();
    else if (op == ')')
        return prevNum;
    return buf.getNum();
}

double Calc(const char * exp)
{
    return Calc(exp, NumBuf(), 1, 0, OperBuf());
}