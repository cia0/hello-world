#include <cs50.h>
#include <stdio.h>
#include <math.h>

int bytwosum(long long n);
int otherintsum(long long n);
string cardtype(long long n);

int main(void) //for future reference this is how you comment 
/* this is how you do a
multi line comment*/
{
    printf("Number: ");
    long long creditnum = get_long_long();
    int luhnsum = bytwosum(creditnum) + otherintsum(creditnum);
    /*printf("LUHNSUM: %d\n", luhnsum);
    printf("BY TWO: %d\n", bytwosum(creditnum) );
    printf("OTHER DIGIT: %d\n", otherintsum(creditnum) );*/
    
    if (luhnsum % 10 == 0)
    {
        printf("%s", cardtype(creditnum) );
    }
    
    else
    {
        printf("INVALID\n");
    }
}

int bytwosum(long long n)
{
    int i = 2;
    int sum = 0;
    
    while (n/pow(10, i - 2) > 1)
    {
        int z = n % (long long)pow(10, i) / (long long)pow(10, i-1);
        //printf("%d  ", z);
        
        if (z > 4)
        {
            sum += z*2 % 10;
            //printf("%d 1\n", z*2 % 10);
            sum += 1;
        }
        else
        {
            sum += z*2;
            //printf("%d\n", z*2);
        }
        
        i = i + 2;
    }
    
    return sum;
}

int otherintsum(long long n)
{
    int sum = 0;
    int i = 1;
    
    while (n/pow(10, i-1) > 1)
    {
        sum += n % (long long)pow(10, i) / (long long)pow(10, i-1);
        //printf("%lld\n", n % (long long)pow(10, i) / (long long)pow(10, i-1));
        i = i + 2;
    }
    
    return sum;
}

string cardtype(long long n)
{
    
    if (n >= pow(10, 14) && n < pow(10, 15) )
    {
        if (n / (long long)pow(10, 13) == 34 || n / (long long)pow(10, 13) == 37)
        {
            return "AMEX\n";
        }
        return "INVALID\n";
    }
    
    else if (n >= pow(10, 15) && n < pow(10, 16) )
    {
        //printf("%lld\n", n / (long long)pow(10, 15) );
        
        
        if (n / (long long)pow(10, 14) == 51 || n / (long long)pow(10, 14) == 52 || n / (long long)pow(10, 14) == 53 || n / (long long)pow(10, 14) == 54 || n / (long long)pow(10, 14) == 55)
        {
            return "MASTERCARD\n";
        }
        
        
        else if (n / (long long)pow(10, 15) == 4)
        {
            return "VISA\n";
        }
        
        return "INVALID\n"; 
    }
    
    else if ( (n >= pow(10, 12) && n < pow(10, 13) ) )
    {
        if (n / (long long)pow(10, 12) == 4)
        {
            return "VISA\n";
        }
        return "INVALID\n";
    }
    
    else
    {
        return "INVALID\n";
    }
}