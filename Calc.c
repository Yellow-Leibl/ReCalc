#include "tort.h"

typedef struct NumBuf
{
    char *buffer;
    int len;
} NumBuf;
NumBuf *InitNumBuf()
{
    NumBuf*temp = (NumBuf*)malloc(sizeof(NumBuf));
    temp->len = 0;
    temp->buffer = (char*)malloc(sizeof(char) * LNGb);
    return temp;
}
void PushChar(NumBuf *buf, char c)
{
    buf->buffer[buf->len++] = c;
}
double getBufNum(NumBuf *buf)
{
    double num = atof(buf->buffer);
    for (int i = 0; i < buf->len; i++)
        buf->buffer[i] = 0;
    buf->len = 0;
    return num;
}
void FreeNumBuf(NumBuf *buf)
{
    free(buf->buffer);
    free(buf);
}


typedef struct OperBuf
{
    double *lev;
    double *kof;
    char  *oper;
    int sizeB;
} OperBuf;
OperBuf *InitOperBuf()
{
    OperBuf *temp = (OperBuf*)malloc(sizeof(OperBuf));
    temp->sizeB = 0;
    temp->kof = (double*)malloc(sizeof(double) * LNGb);
    temp->lev = (double*)malloc(sizeof(double) * LNGb);
    temp->oper = (char*)malloc(sizeof(char) * LNGb);
    return temp;
}
void PushNum(OperBuf *buf, double num)
{
    buf->lev[buf->sizeB-1] += num;
}
void AddLvl(OperBuf *buf, char op, double k) // k = 1
{
    buf->lev[buf->sizeB] = 0;
    buf->oper[buf->sizeB] = op;
    buf->kof[buf->sizeB++] = k;
}
double getOperBufNum(OperBuf *buf)
{
    if (buf->sizeB-- == 0)
        return 0;

    if (buf->oper[buf->sizeB] == '+')
        return buf->lev[buf->sizeB];
    else if (buf->oper[buf->sizeB] == '-')
        return -buf->lev[buf->sizeB];
    else if (buf->oper[buf->sizeB] == '/')
        return buf->kof[buf->sizeB] / buf->lev[buf->sizeB];
    else
        return buf->kof[buf->sizeB] * buf->lev[buf->sizeB];
}
void FreeOperBuf(OperBuf *buf)
{
    free(buf->kof);
    free(buf->lev);
    free(buf->oper);
    free(buf);
}

//double Calc(const char exp[], NumBuf buf = NumBuf(), 
//            double prevNum = 1, char op = '\0', OperBuf opB = OperBuf())

double Calc(const char exp[], NumBuf *buf, 
            double prevNum, char op, OperBuf *opB)
{
    double t;
    if (isdigit(*exp) || '.' == *exp || ',' == *exp)
    {
        if (',' == *exp)
            PushChar(buf, '.');
        else
            PushChar(buf, *exp);
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if ('+' == *exp || '-' == *exp)
    {
        if (op == '*')
            t = prevNum * getBufNum(buf);
        else if (op == '/')
            t = prevNum / getBufNum(buf);
        else if (op == ')')
            t = prevNum;
        else
            t = getBufNum(buf);
        
        PushChar(buf, *exp);
        
        if (opB->sizeB != 0)
        {
            PushNum(opB, t);
            return Calc(exp+1, buf, 1, 0, opB);
        }

        FreeOperBuf(opB);
        return t + Calc(exp+1, buf, 1, '\0', InitOperBuf());
    }
    else if ('*' == *exp || '/' == *exp)
    {
        if (op == '/')
            prevNum /= getBufNum(buf);
        else if (op == ')') ;
        else
            prevNum *= getBufNum(buf);
        
        op = *exp;
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if ('(' == *exp)
    {
        if (*buf->buffer == '-')
            AddLvl(opB, '*', -1);
        else
            AddLvl(opB, op, prevNum);
        getBufNum(buf);
        return Calc(exp+1, buf, 1, 0, opB);
    }
    else if (')' == *exp)
    {
        if (op == '/')
            prevNum /= getBufNum(buf);
        else if (op == ')') ;
        else
            prevNum *= getBufNum(buf);
        
        op = ')';
        PushNum(opB, prevNum);
        prevNum = getOperBufNum(opB);
        return Calc(exp+1, buf, prevNum, op, opB);
    }
    else if (isspace(*exp))
        return Calc(exp+1, buf, prevNum, op, opB);

    FreeOperBuf(opB);
    double Num = getBufNum(buf);
    FreeNumBuf(buf);

    if (op == '*')
        return prevNum * Num;
    else if (op == '/')
        return prevNum / Num;
    else if (op == ')')
        return prevNum;

    return Num;
}

double Calculate(const char * exp)
{
    return Calc(exp, InitNumBuf(), 1, 0, InitOperBuf());
}