#include <iostream>
#include "Counter.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

Counter::Counter(int num,int start)
{
	n=num;
	counter=new int[n];
	for(int i=0;i<n;i++)
		counter[i]=0;
	int m=start;
	int c=0;
	while(m>0)
	{
		counter[c]=m%10;
		m/=10;
		c++;	
	}
}

string Counter::plus()
{
	counter[0]++;
	for(int i=0;i<n-1;i++)
	{
		if(counter[i]>=10)
		{
			counter[i]=0;
			counter[i+1]++;
		}
	}
	if(counter[n-1]>=10)
	{
		counter[n-1]=0;
		counter[0]++;
	}
	string res;
	for(int i=n-1;i>=0;i--)
	{
		res+=SSTR(counter[i]);
	}
	return res;
}

string Counter::now()
{
	string res;
	for(int i=n-1;i>=0;i--)
	{
		res+=SSTR(counter[i]);
	}
	return res;
}
