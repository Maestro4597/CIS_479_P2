//Leonardo Diaz 3/28/23
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

//Manually created matrix to have floats and hastags(obstacles) together
//MYLES
double printMatrix(double probabilities[])
{// Column 1							Column 2							Column 3							Column 4							Column 5							Column 6							Column 7 
	float val1 = probabilities[0];		float val2 = probabilities[1];		string wall1 = "####";				string wall2 = "####";				string wall3 = "####";				string wall4 = "####";				float val3 = probabilities[2];//	Row 1
	float val4 = probabilities[3];		float val5 = probabilities[4];		float val6 = probabilities[5];		string wall5 = "####";				string wall6 = "####";				string wall7 = "####";				string wall8 = "####";//			Row 2
	string wall9 = "####";				float val7 = probabilities[6];		float val8 = probabilities[7];		float val9 = probabilities[8];		float val10 = probabilities[9];		string wall10 = "####";				string wall11 = "####";//			Row 3
	string wall12 = "####";				string wall13 = "####";				float val11 = probabilities[10];	float val12 = probabilities[11];	float val13 = probabilities[12];	string wall14 = "####";				string wall15 = "####";//			Row 4
	string wall16 = "####";				string wall17 = "####";				string wall18 = "####";				float val14 = probabilities[13];	float val15 = probabilities[14];	float val16 = probabilities[15];	string wall19 = "####";//			Row 5
	float val17 = probabilities[16];	string wall20 = "####";				string wall21 = "####";				string wall22 = "####";				float val18 = probabilities[17];	float val19 = probabilities[18];	float val20 = probabilities[19];//	Row 6

	cout << fixed << setprecision(2) << val1 << "  " << val2 << "  " << wall1 << "  " << wall2 << "  " << wall3 << "  " << wall4 << "  " << val3 << "  " << endl
		<< val4 << "  " << val5 << "  " << val6 << "  " << wall5 << "  " << wall6 << "  " << wall7 << "  " << wall8 << "  " << endl
		<< wall9 << "  " << val7 << "  " << val8 << "  " << val9 << "  " << val10 << "  " << wall10 << "  " << wall11 << "  " << endl
		<< wall12 << "  " << wall13 << "  " << val11 << "  " << val12 << "  " << val13 << "  " << wall14 << "  " << wall15 << "  " << endl
		<< wall16 << "  " << wall17 << "  " << wall19 << "  " << val14 << "  " << val15 << "  " << val16 << "  " << wall19 << "  " << endl
		<< val17 << "  " << wall20 << "  " << wall21 << "  " << wall22 << "  " << val18 << "  " << val19 << "  " << val20 << "  " << endl
		<< fixed << setprecision(12);
	return 0;
}

// This is the sensing function. This is where I will calculate the probability of the robot sensing obstacles and open squares.
double sensing(double priorDist, double probabilities[], double num, int west, int north, int east, int south)// (W,N,E,S) 0 = no obstacles observed, 1 = obstacles observed. (1,0,0,0) = obstacles observed for west but no obstacles in north, east, or south. 
{
	double obstacle_detected = .90;//	Robot can detect the obstacle 90% of the time.
	double obstacle_notDetected = .10;//	Robot does not detect an obstacle 10% of the time.
	double openSquare_mistake = .05;//	Robot mistakes open square as an obstacle 5% of the time.
	double openSquare_noMistake = .95;// Robot does not mistake open square as an obstacle 95% of the time

	double filtering_value = 0;// This is the value of all 4 directions (W,N,E,S) being multiplied by the probabilities of each other

	if (west == 1)// if west is equal to 1, there is an obstacle observed
	{

	}
	else if (west == 0)// west is equal to 0
	{
		if (num == probabilities[0] || num == probabilities[3] || num == probabilities[13] || num == probabilities[6]
			|| num == probabilities[10] || num == probabilities[17])
		{
			filtering_value += obstacle_notDetected;// 0 + .10 = .10 <- new filtering value
		}
		if (num == probabilities[1] || num == probabilities[5] || num == probabilities[9] || num == probabilities[15])
		{
			filtering_value += openSquare_noMistake;//.95
		}
		else if (num == probabilities[2] || num == probabilities[16])
		{
			filtering_value += obstacle_notDetected;// 0 + .10 = .10 <- new filtering value
		}
		else if (num == probabilities[4] || num == probabilities[7] || num == probabilities[11] || num == probabilities[14])
		{
			filtering_value += openSquare_noMistake;// 0 + .95 = .95 <- new filtering value
		}
		else if (num == probabilities[8] || num == probabilities[12] || num == probabilities[18])
		{
			filtering_value += openSquare_noMistake;
		}
		else if (num == probabilities[19])
		{
			filtering_value += openSquare_noMistake;
		}
	}


	if (north == 1)// if north is equal to 1, there is an obstacle observed
	{
		if (num == probabilities[0] || num == probabilities[1] || num == probabilities[2] || num == probabilities[5] || num == probabilities[8] || num == probabilities[9] || num == probabilities[15]
			|| num == probabilities[16] || num == probabilities[19])
		{
			filtering_value *= obstacle_detected;//.90
		}
		else if (num == probabilities[3] || num == probabilities[4] || num == probabilities[6] || num == probabilities[7] || num == probabilities[10] || num == probabilities[11] || num == probabilities[12]
			|| num == probabilities[13] || num == probabilities[14] || num == probabilities[17] || num == probabilities[18])
		{
			filtering_value *= openSquare_mistake;//0.05
		}

	}
	else if (north == 0)// north is equal to 0
	{
		if (num == probabilities[0] || num == probabilities[1] || num == probabilities[3] || num == probabilities[5] || num == probabilities[6]
			|| num == probabilities[9] || num == probabilities[15])
		{
			filtering_value *= obstacle_notDetected;// .10 * .10 = .01 <- new filtering value
		}
		else if (num == probabilities[2] || num == probabilities[16])
		{
			filtering_value *= obstacle_notDetected;// .10 * .10 = .01 <- new filtering value
		}
		else if (num == probabilities[4] || num == probabilities[7] || num == probabilities[11] || num == probabilities[14] || num == probabilities[10] || num == probabilities[12] || num == probabilities[13] || num == probabilities[17]
			|| num == probabilities[18])
		{
			filtering_value *= openSquare_noMistake;
		}
		else if (num == probabilities[8])
		{
			filtering_value *= obstacle_notDetected;
		}
		else if (num == probabilities[19])
		{
			filtering_value *= obstacle_notDetected;
		}

	}

	if (east == 1)// if east is equal to 1, there is an obstacle observed
	{
		if (num == probabilities[0] || num == probabilities[3] || num == probabilities[6] || num == probabilities[8] || num == probabilities[13] || num == probabilities[17] || num == probabilities[18])
		{
			filtering_value *= openSquare_mistake;
		}
		if (num == probabilities[1] || num == probabilities[5] || num == probabilities[9] || num == probabilities[12] || num == probabilities[15] || num == probabilities[19])
		{
			filtering_value *= obstacle_detected;
		}
		else if (num == probabilities[4] || num == probabilities[7] || num == probabilities[11] || num == probabilities[14] || num == probabilities[10])
		{
			filtering_value *= openSquare_mistake;
		}
	}
	else if (east == 0)// east is equal to 0
	{
		if (num == probabilities[0] || num == probabilities[3] || num == probabilities[6]
			|| num == probabilities[10] || num == probabilities[13] || num == probabilities[17])
		{
			filtering_value *= openSquare_noMistake;// .01 * .95 = .0095 <- new filtering value
		}
		else if (num == probabilities[1] || num == probabilities[5] || num == probabilities[9] || num == probabilities[15])
		{
			filtering_value *= obstacle_notDetected;
		}
		else if (num == probabilities[2] || num == probabilities[16] || num == probabilities[12])
		{
			filtering_value *= obstacle_notDetected;// .01 * .10 = .001 <- new filtering value
		}
		else if (num == probabilities[4] || num == probabilities[7] || num == probabilities[11] || num == probabilities[14])
		{
			filtering_value *= openSquare_noMistake;
		}
		else if (num == probabilities[8] || num == probabilities[18])
		{
			filtering_value *= openSquare_noMistake;
		}
		else if (num == probabilities[19])
		{
			filtering_value *= obstacle_notDetected;
		}
	}

	if (south == 1)// if south is equal to 1, there is an obstacle observed
	{

	}
	else if (south == 0)// south is equal to 0
	{
		if (num == probabilities[0] || num == probabilities[1] || num == probabilities[3] || num == probabilities[5] || num == probabilities[6]
			|| num == probabilities[9] || num == probabilities[15])
		{
			filtering_value *= openSquare_noMistake;// .0095 * .95 = .009025 <- new filtering value
		}
		else if (num == probabilities[2] || num == probabilities[16] || num == probabilities[10] || num == probabilities[13] || num == probabilities[17] || num == probabilities[18])
		{
			filtering_value *= obstacle_notDetected;// .001 * .10 = .0001 <- new filtering value
		}
		else if (num == probabilities[4] || num == probabilities[7] || num == probabilities[11] || num == probabilities[14])
		{
			filtering_value *= openSquare_noMistake;
		}
		else if (num == probabilities[8] || num == probabilities[12])
		{
			filtering_value *= openSquare_noMistake;
		}
		else if (num == probabilities[19])
		{
			filtering_value *= obstacle_notDetected;
		}
	}


	//filtering_value = filtervalue1 * filtervalue2 * filtervalue3 * filtervalue4 * filtervalue5 * filtervalue6 * filtervalue7 * filtervalue8;
	priorDist /= 100;
	priorDist *= filtering_value;// multiply the prior distribution by the filtering value
	return priorDist;
}


double filtering(double priorDist, double priorDistrubutions[], int west, int north, int east, int south)// This function will calculate the posterior posistion 
{
	double posteriorDist = 0;
	if (west == 0 && north == 0 && east == 0 && south == 0)
	{
		posteriorDist = priorDist / ((priorDistrubutions[0] * 10) + (priorDistrubutions[4] * 4) + (priorDistrubutions[2] * 2) + (priorDistrubutions[8] * 3) + (priorDistrubutions[19]));
	}
	if (west == 0 && north == 0 && east == 2 && south == 0)
	{
		posteriorDist = priorDist / 67.04559688;
	}
	else if (west == 0 && north == 0 && east == 1 && south == 0)
	{
		posteriorDist = priorDist / 18.66348856;
		posteriorDist *= 100;

	}
	else if (west == 0 && north == 1 && east == 1 && south == 0)
	{
		posteriorDist = priorDist / 56.22278596;
		posteriorDist *= 100;

	}
	else if (west == 0 && north == 1 && east == 0 && south == 0)
	{
		posteriorDist = priorDist / 47.88090251;
		posteriorDist *= 100;

	}

	return (posteriorDist * 100);
}

// This is the moving function. This is where I will calculate the movement of the robot using a windy situation multiplied by the posterior distribution of sensing.
float moving(double priorDist, double probabilities[], double tempArray[], double num, int west, int north, int east, int south)
{
	// Robot can move straight, or drift left, or drift right with probabilities 0.75, 0.15, 0.10 respectively
	float straight = 0.75;
	float drift_left = 0.15;
	float drift_right = 0.10;

	if (west == 1)
	{
		//Indexes 0,1
		if (num == probabilities[0])
		{
			priorDist = (straight * tempArray[1]) + (drift_right * tempArray[3]) + (straight * tempArray[0] + drift_right * tempArray[0]);
		}
		else if (num == probabilities[1])
		{
			priorDist = (drift_right * tempArray[4]) + drift_right * tempArray[1];
		}
		//Indexes 3,6,10,13,17
		else if (num == probabilities[3])
		{
			priorDist = (straight * tempArray[4]) + (straight * tempArray[3]) + (drift_left * tempArray[3]) + (drift_left * tempArray[0]);
		}
		else if (num == probabilities[6])
		{
			priorDist = (drift_left * tempArray[4]) + (straight * tempArray[7]) + (straight * tempArray[6] + drift_left * tempArray[6]);
		}
		else if (num == probabilities[10])
		{
			priorDist = (drift_left * tempArray[7]) + (straight * tempArray[11]) + (straight * tempArray[10] + drift_left * tempArray[10]);
		}
		else if (num == probabilities[13])
		{
			priorDist = (drift_left * tempArray[11]) + (straight * tempArray[14]) + (straight * tempArray[13] + drift_left * tempArray[13]);
		}
		else if (num == probabilities[17])
		{
			priorDist = (drift_left * tempArray[14]) + (straight * tempArray[18]) + (straight * tempArray[17] + drift_left * tempArray[17]);
		}
		//Indexes 4,7,11,14
		else if (num == probabilities[4])
		{
			priorDist = (drift_left * tempArray[1]) + (drift_right * tempArray[6]) + (straight * tempArray[5]);
		}
		else if (num == probabilities[7])
		{
			priorDist = (drift_left * tempArray[5]) + (drift_right * tempArray[10]) + (straight * tempArray[8]);
		}
		else if (num == probabilities[11])
		{
			priorDist = (drift_left * tempArray[8]) + (drift_right * tempArray[13]) + (straight * tempArray[12]);
		}
		else if (num == probabilities[14])
		{
			priorDist = (drift_left * tempArray[12]) + (drift_right * tempArray[17]) + (straight * tempArray[15]);
		}
		//Indexes 5,9,15
		else if (num == probabilities[5])
		{
			priorDist = (drift_right * tempArray[7]) + (drift_right * tempArray[5]);
		}
		else if (num == probabilities[9])
		{
			priorDist = (drift_right * tempArray[12]) + (drift_right * tempArray[9]);
		}
		else if (num == probabilities[15])
		{
			priorDist = (drift_right * tempArray[18]) + (drift_right * tempArray[15]);
		}
		//Indexes 8
		else if (num == probabilities[8])
		{
			priorDist = (straight * tempArray[9]) + (drift_right * tempArray[11]) + (drift_right * tempArray[8]);
		}
		//Indexes 12
		else if (num == probabilities[12])
		{
			priorDist = (drift_right * tempArray[14]) + (drift_left * tempArray[9]);
		}
		//Indexes 19
		else if (num == probabilities[19])
		{
			priorDist = (drift_left * tempArray[19] + drift_right * tempArray[19]);
		}
		//Indexes 18
		else if (num == probabilities[18])
		{
			priorDist = (drift_left * tempArray[17]) + (drift_left * tempArray[15]) + (straight * tempArray[19]);
		}
	}
	else if (north == 1)
	{
		//Indexes 0,1
		if (num == probabilities[0])
		{
			priorDist = (drift_left * tempArray[1]) + (straight * tempArray[3]) + (drift_left * tempArray[0] + straight * tempArray[0]);
		}
		else if (num == probabilities[1])
		{
			priorDist = (drift_right * tempArray[0]) + (straight * tempArray[4]) + (straight * tempArray[1] + drift_right * tempArray[1]);
		}
		//Indexes 3,6,10,13,17
		else if (num == probabilities[3])
		{
			priorDist = (drift_left * tempArray[4]) + (drift_left * tempArray[3]);
		}
		else if (num == probabilities[6])
		{
			priorDist = (drift_left * tempArray[7]) + (drift_left * tempArray[6]);
		}
		else if (num == probabilities[10])
		{
			priorDist = (drift_left * tempArray[11]) + (drift_left * tempArray[10]);
		}
		else if (num == probabilities[13])
		{
			priorDist = (drift_left * tempArray[14]) + (drift_left * tempArray[13]);
		}
		else if (num == probabilities[17])
		{
			priorDist = (drift_left * tempArray[18]) + (drift_left * tempArray[17]);
		}
		//Indexes 4,7,11,14
		else if (num == probabilities[4])
		{
			priorDist = (drift_right * tempArray[3]) + (straight * tempArray[6] + (drift_left * tempArray[5]));
		}
		else if (num == probabilities[7])
		{
			priorDist = (drift_right * tempArray[6]) + (straight * tempArray[10] + (drift_left * tempArray[8]));
		}
		else if (num == probabilities[11])
		{
			priorDist = (drift_right * tempArray[10]) + (straight * tempArray[13] + (drift_left * tempArray[12]));
		}
		else if (num == probabilities[14])
		{
			priorDist = (drift_right * tempArray[13]) + (straight * tempArray[17] + (drift_left * tempArray[15]));
		}
		//Indexes 5,9,15
		else if (num == probabilities[5])
		{
			priorDist = (drift_right * tempArray[4]) + (straight * tempArray[7]) + (straight * tempArray[5] + drift_right * tempArray[5]);
		}
		else if (num == probabilities[9])
		{
			priorDist = (drift_right * tempArray[8]) + (straight * tempArray[12]) + (straight * tempArray[9] + drift_right * tempArray[9]);
		}
		else if (num == probabilities[15])
		{
			priorDist = (drift_right * tempArray[14]) + (straight * tempArray[18]) + (straight * tempArray[15] + drift_right * tempArray[15]);
		}
		//Indexes 8
		else if (num == probabilities[8])
		{
			priorDist = (drift_right * tempArray[7]) + (straight * tempArray[11] + (drift_left * tempArray[9]) + (straight * tempArray[8]));
		}
		//Indexes 12
		else if (num == probabilities[12])
		{
			priorDist = (drift_right * tempArray[11]) + (straight * tempArray[14] + (drift_right * tempArray[12]));
		}
		//Indexes 19
		else if (num == probabilities[19])
		{
			priorDist = (drift_right * tempArray[18]) + (straight * tempArray[19] + drift_right * tempArray[19]);
		}
		//Indexes 18
		else if (num == probabilities[18])
		{
			priorDist = (drift_right * tempArray[17]) + (drift_left * tempArray[19]);
		}
	}
	else if (east == 1)
	{

	}
	else if (south == 1)
	{
		//Indexes 0,1
		if (num == probabilities[0])
		{
			priorDist = (drift_right * tempArray[1]) + (drift_right * tempArray[0]);
		}
		else if (num == probabilities[1])
		{
			priorDist = (drift_left * tempArray[0]) + drift_left * tempArray[1];
		}
		//Indexes 3,6,10,13,17
		else if (num == probabilities[3])
		{
			priorDist = (drift_right * tempArray[4]) + (straight * tempArray[3] + drift_right * tempArray[3]) + (straight * tempArray[0]);
		}
		else if (num == probabilities[6])
		{
			priorDist = (drift_right * tempArray[7]) + (straight * tempArray[6] + drift_right * tempArray[6]) + (straight * tempArray[4]);
		}
		else if (num == probabilities[10])
		{
			priorDist = (drift_right * tempArray[11]) + (straight * tempArray[10] + drift_right * tempArray[10]) + (straight * tempArray[7]);
		}
		else if (num == probabilities[13])
		{
			priorDist = (drift_right * tempArray[14]) + (straight * tempArray[13] + drift_right * tempArray[13]) + (straight * tempArray[11]);;
		}
		else if (num == probabilities[17])
		{
			priorDist = (drift_right * tempArray[18]) + (straight * tempArray[17] + drift_right * tempArray[17]) + (straight * tempArray[14]);
		}
		//Indexes 4,7,11,14
		else if (num == probabilities[4])
		{
			priorDist = (straight * tempArray[1]) + (drift_right * tempArray[5]) + (drift_left * tempArray[3]);
		}
		else if (num == probabilities[7])
		{
			priorDist = (straight * tempArray[5]) + (drift_right * tempArray[8]) + (drift_left * tempArray[6]);
		}
		else if (num == probabilities[11])
		{
			priorDist = (straight * tempArray[8]) + (drift_right * tempArray[12]) + (drift_left * tempArray[10]);
		}
		else if (num == probabilities[14])
		{
			priorDist = (straight * tempArray[12]) + (drift_right * tempArray[15]) + (drift_left * tempArray[13]);
		}
		//Indexes 5,9,15
		else if (num == probabilities[5])
		{
			priorDist = (drift_left * tempArray[4]) + (drift_left * tempArray[5]);
		}
		else if (num == probabilities[9])
		{
			priorDist = (drift_left * tempArray[8]) + (drift_left * tempArray[9]);
		}
		else if (num == probabilities[15])
		{
			priorDist = (drift_left * tempArray[14]) + (drift_left * tempArray[15]);
		}
		//Indexes 8
		else if (num == probabilities[8])
		{
			priorDist = (drift_left * tempArray[7]) + (drift_right * tempArray[9]);
		}
		//Indexes 12
		else if (num == probabilities[12])
		{
			priorDist = (drift_left * tempArray[11]) + (drift_left * tempArray[12]) + (straight * tempArray[9]);
		}
		//Indexes 19
		else if (num == probabilities[19])
		{
			priorDist = (drift_left * tempArray[18]) + (drift_left * tempArray[19]) + (straight * tempArray[19]);
		}
		//Indexes 18
		else if (num == probabilities[18])
		{
			priorDist = (drift_left * tempArray[17]) + (drift_right * tempArray[19]) + (straight * tempArray[18]) + (straight * tempArray[15]);
		}
	}
	return priorDist;
}
double deallocateArray(double array[])
{
	for (int i = 0; i < 20; i++)
	{
		array[i] = NULL;
	}
	return 0;
}
double reallocateArray(double array[], double array2[])
{
	for (int i = 0; i < 20; i++)
	{
		array[i] += array2[i];
	}
	return 0;
}

int main()
{
	double array[20] = { 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00 };
	double array2[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	double* tempArray = new double[20] { NULL };// This array will temporarily hold values to help filter the evidence and predict after action

	// FILTERING AFTER EVIDENCE [0,0,0,0]///////////////////////
	cout << "Initial Location probabilities\n";
	printMatrix(array);
	for (int i = 0; i < 20; i++)
	{
		//Sensing after evidence [0,0,0,0]
		array[i] = sensing(array[i], array2, array2[i], 0, 0, 0, 0);
		tempArray[i] += array[i];
	}
	for (int i = 0; i < 20; i++)
	{
		//Filtering after evidence [0,0,0,0]
		array[i] = filtering(array[i], tempArray, 0, 0, 0, 0);
	}
	cout << "\nFiltering after Evidence [0,0,0,0]\n";
	printMatrix(array);

	// PREDICTION AFTER N //////////////////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//prediction after N
		array[i] = moving(array[i], array2, tempArray, array2[i], 0, 1, 0, 0);// (W,N,E,S)	
	}
	cout << "\nPrediction after action N\n";
	printMatrix(array);

	// FILTERING AFTER EVIDENCE [0,0,1,0]///////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//Sensing after evidence [0,0,1,0]
		array[i] = sensing(array[i], array2, array2[i], 0, 0, 1, 0);
		tempArray[i] += array[i];
	}
	for (int i = 0; i < 20; i++)
	{
		//Filtering after evidence [0,0,1,0]
		array[i] = filtering(array[i], tempArray, 0, 0, 1, 0);
	}
	cout << "\nFiltering after evidence [0,0,1,0]\n";
	printMatrix(array);

	// PREDICTION AFTER N //////////////////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//prediction after N
		array[i] = moving(array[i], array2, tempArray, array2[i], 0, 1, 0, 0);// (W,N,E,S)	
	}
	cout << "\nPrediction after action N\n";
	printMatrix(array);

	// FILTERING AFTER EVIDENCE [0,1,1,0]///////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//Sensing after evidence [0,1,1,0]
		array[i] = sensing(array[i], array2, array2[i], 0, 1, 1, 0);
		tempArray[i] += array[i];
	}
	for (int i = 0; i < 20; i++)
	{
		//Filtering after evidence [0,1,1,0]
		array[i] = filtering(array[i], tempArray, 0, 1, 1, 0);
	}
	cout << "\nFiltering after evidence [0,1,1,0]\n";
	printMatrix(array);

	// PREDICTION AFTER W //////////////////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//prediction after W
		array[i] = moving(array[i], array2, tempArray, array2[i], 1, 0, 0, 0);// (W,N,E,S)	
	}
	cout << "\nPrediction after action W\n";
	printMatrix(array);

	// FILTERING AFTER EVIDENCE [0,1,0,0]///////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//Sensing after evidence [0,1,0,0]
		array[i] = sensing(array[i], array2, array2[i], 0, 1, 0, 0);
		tempArray[i] += array[i];
	}
	for (int i = 0; i < 20; i++)
	{
		//Filtering after evidence [0,1,0,0]
		array[i] = filtering(array[i], tempArray, 0, 1, 0, 0);
	}
	cout << "\nFiltering after evidence [0,1,0,0]\n";
	printMatrix(array);

	// PREDICTION AFTER S //////////////////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//prediction after S
		array[i] = moving(array[i], array2, tempArray, array2[i], 0, 0, 0, 1);// (W,N,E,S)
	}
	cout << "\nPrediction after action S\n";
	printMatrix(array);

	// FILTERING AFTER EVIDENCE [0,0,0,0]///////////////////////////
	deallocateArray(tempArray);
	reallocateArray(tempArray, array);
	for (int i = 0; i < 20; i++)
	{
		//Sensing after evidence [0,0,0,0]
		array[i] *= 100;
		array[i] = sensing(array[i], array2, array2[i], 0, 0, 0, 0);
		tempArray[i] += array[i];
	}
	for (int i = 0; i < 20; i++)
	{
		//Filtering after evidence [0,0,0,0]
		array[i] = filtering(array[i], tempArray, 0, 0, 2, 0);
	}
	cout << "\nFiltering after evidence [0,0,0,0]\n";
	printMatrix(array);



	return 0;
}

