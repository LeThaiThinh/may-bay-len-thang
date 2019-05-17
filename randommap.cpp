// sinh map.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#define maplenght 1000
using namespace std;

void random(int &a)
{
	int i;
	if ( a==1 )
	{
		a++;
	} else
	{
		if ( a==7 )
		{
			a--;
		} else
		{
			i = rand()%2;
			if ( i == 1) a++;
			else a--;
			
		}
	}
}/*
int main()
{
	int a = 2 , b = 3;
	int mang[20][maplenght];
	srand(time(0));
	for ( int i=0; i<maplenght; i++)
	{
		for (int j=0; j<a; j++)         mang[j][i]=1;		
				
		for (int j=a; j< 20-b; j++)	    mang[j][i]=0;
		
		for (int j=20-b; j<20; j++)   	mang[j][i]=1;
	
		random(a);
		
		random(b);
	}	
	ofstream output("mapmahoa.txt");
	for ( int i=0; i<20; i++)
	{
		for ( int j=0; j<maplenght; j++)
		{
			output<<mang[i][j];
		}
		output<<endl;
	}
	system("pause");
	return 0;
}*/
