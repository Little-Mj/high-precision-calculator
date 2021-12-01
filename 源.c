#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int MAX_NUMBER = 10000;

//�жϵ�ǰ���ӷ�ĸ�Ƿ�Ϊѭ��С��������ѭ����ĸ���
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

//�Ѵ���10��������ӵ��ַ�����,�����ص�ǰstr�е�һ��û��������ݵ��±�
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



//ͨ����ĸ�ж��Ƿ�Ϊѭ��С��
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
        շת�����
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

//���ӷ�ĸ���
void simplify(long* de, long* num)
{
    long simple = maximunFactor(*de, *num);
    *de /= simple;
    *num /= simple;
}


char* fractionToDecimal(int numerator, int denominator)
{
    /*
    ��С�����������ֺ�С�����ֵ����������㡣
        �������֣������Ƿ�ĸ��9�����ϣ�����addInt��Ӵ���9���������ֵ�str�ַ����С�����ֱ����ӡ�
        С�����֣�num=num%de�������С�������ˣ�*10��ȥ / de �����ж��ж�ѭ����
    
    */

    int index=0;
    int length = 100;//str����
    char* str;

    //����Ϊ0
    if (!numerator)
    {
        str = (char*)malloc(2 * sizeof(char));
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    str = (char*)malloc(length * sizeof(char));

    //��ֹĳЩ�������������int���½�
    long num = numerator;
    long de = denominator;

    //������ӻ��ĸΪ���������
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

    //������������
    if (num >= 10 * de) //����������ָ�����������,num>de*10
        index = addInt(str, index, num / de);
    else
    {
        str[index] = '0' + num / de;
        index++;
    }

    num %= de;
    if (num == 0) //�����Ƿ�ĸ��������
    {
        str[index] = '\0';
        return str;
    }

    str[index] = '.';
    index++;

    while (num < 0) //����С��0����ǰ����
    {
        num *= 10;
        str[index] = '0';
        index++;
    }

    //simplify(&de, &num);
    bool isCle = isLoopByDenominator(de);

    //ѭ��С��
    if (isCle == true)
    {
        int ciecleLength;
        while (1)
        {
            //simplify(&num, &de);
            ciecleLength = isLoopByDeAndNum(num, de);//�����Ƿ񵽴�ѭ����
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
        //��ѭ��С��
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
