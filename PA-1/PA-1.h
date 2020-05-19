#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/**********************************************************************************************
	* Programmer: Wenzhi Zhuang 
	* Class: CptS 122. Spring, 2020: Lab Section:12
	* Data: January 23, 2020
	* Description: This program print out the result of total calories, total distance, total 
	* floor, total steps, avg heartrate, max steps and sleep in result.csvfile, which is analys
	* from the FitbitData.csv file 
**********************************************************************************************/
typedef enum sleep {
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
}sleep;
typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floor;
	unsigned int heartRate;
	unsigned int steps;
	sleep SleepLevel;
}FitbitData;
