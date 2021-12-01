#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int MAX_NUMBER = 10000;

//判断当前分子分母是否为循环小数，返回循环体的个数
int isLoopByDeAndNum(long n, long d)
{
    long k = n;
    int i = 1;
    for (; i < 5000; i++)
    {
        n *= 10;
        n %= d;
        if (n % d == k)
            return i;
        if (!n)
            return 0;
    }
    return 0;
}

//把大于10的整数添加到字符串中,并返回当前str中第一个没有填充数据的下标
int addInt(char* str, int start, long numerator)
{
    long k = 10;
    while (1)
    {
        if (numerator / k < 10)
            break;
        k *= 10;
    }

    while (k)
    {
        str[start] = '0' + numerator / k;
        start++;
        numerator %= k;
        k /= 10;
    }
    return start;
}



//通过分母判断是否为循环小数
bool isLoopByDenominator(long denominator)
{
    if (denominator == 1)
        return false;
    while (denominator % 2 == 0)
        denominator /= 2;
    while (denominator % 5 == 0)
        denominator /= 5;

    if (denominator == 1)
        return false;
    else
        return true;
}

int maximunFactor(long max, long min)
{
    /*
        辗转相除法
    */
    long k;
    if (max < min)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }
    while (min)
    {
        k = max % min;
        max = min;
        min = k;
    }
    return max;
}

//分子分母最简化
void simplify(long* de, long* num)
{
    long simple = maximunFactor(*de, *num);
    *de /= simple;
    *num /= simple;
}


char* fractionToDecimal(int numerator, int denominator)
{
    /*
    把小数的整数部分和小数部分单独拿来计算。
        整数部分：分子是分母的9倍以上，调用addInt添加大于9的整数部分到str字符串中。否则直接添加。
        小数部分：num=num%de，这就是小数部分了，*10再去 / de 咯。判断判断循环。
    
    */

    int index=0;
    int length = 100;//str长度
    char* str;

    //分子为0
    if (!numerator)
    {
        str = (char*)malloc(2 * sizeof(char));
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    str = (char*)malloc(length * sizeof(char));

    //防止某些特殊情况，比如int上下界
    long num = numerator;
    long de = denominator;

    //处理分子或分母为负数的情况
    if (num < 0)
    {
        num *= -1;
        if (de < 0)
            de *= -1;
        else
        {
            str[index] = '-';
            index++;
        }
    }
    else if (de < 0)
    {
        str[index] = '-';
        de = -de;
        index++;
    }

    //处理整数部分
    if (num >= 10 * de) //如果整数部分个数两个以上,num>de*10
        index = addInt(str, index, num / de);
    else
    {
        str[index] = '0' + num / de;
        index++;
    }

    num %= de;
    if (num == 0) //分子是分母的整数倍
    {
        str[index] = '\0';
        return str;
    }

    str[index] = '.';
    index++;

    while (num < 0) //分子小于0就提前调整
    {
        num *= 10;
        str[index] = '0';
        index++;
    }

    //simplify(&de, &num);
    bool isCle = isLoopByDenominator(de);

    //循环小数
    if (isCle == true)
    {
        int ciecleLength;
        while (1)
        {
            //simplify(&num, &de);
            ciecleLength = isLoopByDeAndNum(num, de);//计算是否到达循环体
            if (ciecleLength)
            {
                if(length-1<=ciecleLength+index)
                    str = realloc(str, length+ciecleLength-index+10);
                str[index] = '(';
                index++;
                for (; ciecleLength > 0; ciecleLength--, index++)
                {
                    num *= 10;
                    str[index] = '0' + num / de;
                    num %= de;
                }
                str[index] = ')';
                str[index + 1] = '\0';
                return str;
            }
            num *= 10;
            str[index] = '0' + num / de;
            index++;
            num %= de;
            if (index == length - 1)
            {
                length += MAX_NUMBER;
                str = realloc(str, length);
                if (length == MAX_NUMBER)
                {
                    str[index] = '\0';
                    return str;
                }
            }
        }
    }

    else
    {
        //不循环小数
        while (1)
        {
            num *= 10;
            str[index] = '0' + num / de;
            num %= de;
            if (num == 0)
            {
                str[index + 1] = '\0';
                return str;
            }
            index++;
            if (index == length - 1)
            {
                length += MAX_NUMBER;
                str = realloc(str, length);
                if (length == MAX_NUMBER)
                {
                    str[index] = '\0';
                    return str;
                }
            }
        }
    }
}

int main()
{
    fractionToDecimal(1,214748364);
    return 0;
}
// @lc code=end
