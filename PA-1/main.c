#include "PA-1.h"
#include <string.h>
#include <stdlib.h>
/**********************************************************************************************
	* Programmer: Wenzhi Zhuang
	* Class: CptS 122. Spring, 2020: Lab Section:12
	* Data: January 23, 2020
	* Description: This program print out the result of total calories, total distance, total
	* floor, total steps, avg heartrate, max steps and sleep in result.csvfile, which is analys
	* from the FitbitData.csv file
**********************************************************************************************/
int main(void)
{
	FILE* infile = fopen("FitbitData.csv", "r");// open the FitbitData.csv file named infile for reading
	FILE* outfile = fopen("result.csv", "w");// open the result.csv file named outfile for writing 
	FitbitData Fitbit[1440];// struct of array, size is 1442 
	printf("Patient		minute	calories	distance	floors	heart	steps	sleep_level\n");// print these words on the top of screen 
	double total_calories = 0.0, total_distance = 0.0, average_hearate = 0.0;
	int max_steps[1440], Max_steps = 0, max_poor_sleep_range[1440], Max_poor_sleep_range = 0, total_steps = 0;
	int r = 0,total_floors = 0;
	int i = 0, g = 0;
	char time[1440][100];
	if (infile != NULL)// check whether infile is open or empty
	{
		char line[1500][100], word[20];// definite a array in char 
		int size;
		int total_poor = 0;
		int m = 0;
		while (!feof(infile))
		{
			fgets(line[i], 100, infile);// get the sentence from infile 	
			// level - 1 if line copy the first sentence from infile, then it will be igrone. Because first sentence is all char
			if (i == 0)
			{
				fgets(line[i], 100, infile);
			}
			// get the size of line[i] for further function 
			size = sizeof(line[i]);
			//level - 2 if there is completely same information and appear continonus, then one of sentence will be ignore(delete) 
			if (line[i] == line[i + 1])
			{
				i = i + 1;
				fgets(line[i], 100, infile);
			}
			
			for (int a = 0; a < size; ++a)
			{
				//12cx7
				//level - 3 if patient's name isn't 12cxy, then it will be ignored. 
				if (line[i][0] == '1' && line[i][1] == '2' && line[i][2] == 'c' && line[i][3] == 'x' && line[i][4] == '7')
				{
				}
				else
				{
					i = i + 1;
					fgets(line[i], 100, infile);
					size = sizeof(line[i]);
					a = 0;
				}
				// level - 3 - 1 check whethear there are same datas in minute before 10 min. If it does, than ignore one of them.
				if (line[i][8] == line[i - 1][8] && line[i][9] == line[i - 1][9] && line[i][7] == ':') 
				{
					i = i + 1;
					fgets(line[i], 100, infile);
					size = sizeof(line[i]);
					a = 0;
				}
				// level - 3 - 1 check whethear there are same datas in minute after 10 min. If it does, than ignore one of them.
				if (line[i][9] == line[i - 1][9] && line[i][10] == line[i - 1][10] && line[i][8] == ':')
				{
					i = i + 1;
					fgets(line[i], 100, infile);
					size = sizeof(line[i]);
					a = 0;
				}
				//level - 4 if there is a double-commas, then there will be a number fit in the middle of them 
				if ((line[i][a] == line[i][a + 1]) && line[i][a] == ',')
				{
					for (int b = 36; b >= a + 1; b--)
					{
						line[i][b] = line[i][b - 1];
					}
					line[i][a + 1] = '0';
					a = 0;
					
				}
			}
			//level - 5 
			size = sizeof(line[i]);
			int n = 0;
			// count the amount of comma in a sentence
			for (int a = 0; a < size; ++a)
			{
				if (line[i][a] == ',')
				{
					n = n + 1;
				}
			}
			for (int a = 0; a < size; ++a)
			{
				// if there is empty data right after a comma, then it will be judged under certain condition to move further 
				if (line[i][a] == ',' && line[i][a + 1] == '\n')
				{
					// if there are 8 commas, then cancel the last one of comma
					if (n == 8)
					{
						//printf("YES\n");
						line[i][a] = '\n';
						//fgets(line[i], 100, infile);
					}
					//if there are 7 commas, which means there is empty existed in the sentence, and there will be a number fit in the position 
					else if(n == 7)
					{
						if (line[i][a] == ',' && line[i][a + 1] == '\n')
						{
							line[i][a + 1] = '0'; 
							line[i][a + 2] = '\n';
							line[i][a + 3] = '\0';
						}
					}
				}
			}
			size = sizeof(line[i]);// get the new size again after judging 
			strcpy(Fitbit[r].patient, strtok(line[i], ","));//get the patient's name 
			printf("%s\t", Fitbit[r].patient);
			strcpy(Fitbit[r].minute, strtok(NULL, ","));// get the minute 
			printf("%s\t\t", Fitbit[r].minute);
			strcpy(word, strtok(NULL, ","));// get the calories 
			Fitbit[r].calories = atof(word);
			total_calories = total_calories + atof(word);// calculate the total calories in the loop 
			printf("%lf\t", Fitbit[r].calories);
			strcpy(word, strtok(NULL, ","));// get the distance 
			Fitbit[r].distance = atof(word);
			total_distance = total_distance + atof(word);// calculate the distance in the loop
			printf("%lf\t", Fitbit[r].distance);
			strcpy(word, strtok(NULL, ","));// get the floor 
			Fitbit[r].floor = atoi(word);
			total_floors = total_floors + atoi(word);// calculate the floors in the loop
			printf("%d\t", Fitbit[r].floor);
			strcpy(word, strtok(NULL, ","));// get the heartrate
			Fitbit[r].heartRate = atoi(word);
			average_hearate = average_hearate + atoi(word);// calculate the total heartrate in the loop 
			printf("%d\t", Fitbit[r].heartRate);
			strcpy(word, strtok(NULL, ","));// get the steps 
			Fitbit[r].steps = atoi(word);
			total_steps = total_steps + atoi(word);// calculate the total steps in the loop 
			max_steps[r] = atoi(word);
			printf("%d\t", Fitbit[r].steps);
			strcpy(word, strtok(NULL, "\n"));// get the sleep level 
			Fitbit[r].SleepLevel = atoi(word);
			//printf("%d", Fitbit[r].SleepLevel);
			//fprintf(outfile, "%s %s %lf %lf %d %d %d %d\n", Fitbit[r].patient, Fitbit[r].minute, Fitbit[r].calories, Fitbit[r].distance, Fitbit[r].floor, Fitbit[r].heartRate, Fitbit[r].steps, Fitbit[r].SleepLevel);
			if (Fitbit[r].SleepLevel <= 1 && Fitbit[r - 1].SleepLevel <= 1)//count the range of sleep in poor level 
			{
				total_poor = total_poor + 1;
				max_poor_sleep_range[m] = total_poor;
				strcpy(time[m], Fitbit[r].minute);
				
			}
			else
			{
				//strcpy(time[m], Fitbit[r].minute);
				++m;
				total_poor = 0;
			}
			printf("%d\t", Fitbit[r].SleepLevel);
			i++;
			r++;
			puts("");
		}
		Max_steps = max_steps[0];
		for (int a = 0; a <= 1440; ++a)// get the max steps 
		{
			if (Max_steps <= max_steps[a])
			{
				Max_steps = max_steps[a];
			}
		}
		Max_poor_sleep_range = max_poor_sleep_range[0];
		for (int a = 0; a <= 1440; ++a)// get the max sleep level range 
		{
			if (Max_poor_sleep_range < max_poor_sleep_range[a])
			{
				Max_poor_sleep_range = max_poor_sleep_range[a];
			}
		}
		for (int a = 0; a <= 1440; ++a)
		{
			if (Max_poor_sleep_range == max_poor_sleep_range[a])
			{
				g = a;
			}
		}
		
		for (int a = 0; a <= 1440; ++a)
		{
			if (time[g] == Fitbit[a].minute)
			{
				r = a;
			}
		}
		average_hearate = average_hearate / 1440;// total heartrate divide by 12*60 min, which is 1440 min
		printf("total calories:%lf\ntotal distance: %lf\n total_floors: %d\n total steps: %d\n average heartrate: %lf/min \n max_steps: %d\nmax poor sleep range: %d\n",total_calories,total_distance, total_floors, total_steps,average_hearate,Max_steps,Max_poor_sleep_range );
		printf("start time: %s, end time: %s", Fitbit[r - Max_poor_sleep_range].minute, time[g]);
		fprintf(outfile, "total calories	total distance	total_floors	total steps	\taverage heartrate	max_steps	max poor sleep range	start time	end time\n");
		fprintf(outfile, "%lf\t\t%lf\t\t\t%d\t\t\t%d\t\t\t%lf\t\t\t%d\t\t\t%dmin\t\t\t\t	%s\t\t%s", total_calories, total_distance, total_floors, total_steps, average_hearate, Max_steps, Max_poor_sleep_range, Fitbit[r - Max_poor_sleep_range].minute, time[g]);
	}
 	fclose(infile);// close infile 
	fclose(outfile);//close outfile 
	return 0;
}