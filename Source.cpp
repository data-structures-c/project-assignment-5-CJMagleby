#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<chrono>
#include<math.h>

using namespace std;
static const int arraySize = 1000;
static const int numTrials = 50;


void print(vector<int>& ar)
{
	for (int i = 0; i < ar.size(); i++)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}
void findMeanandSTDDEV(vector<double>& times)
{
	double mean = 0;
	double standardDeviation = 0;
	for (size_t i = 0; i < times.size(); i++)
	{
		mean += times[i];
	}
	mean = mean / times.size();
	cout <<"mean: " << mean << endl;
	for (size_t i = 0; i < times.size(); i++)
	{
		standardDeviation += (times[i] - mean) * (times[i] - mean);
	}
	standardDeviation = standardDeviation / times.size();
	cout << "Standard Deviation: " << sqrt(standardDeviation) << endl;

}
void bubbleSort(vector<int>& ar)
{
	for (int i = (ar.size() - 1); i >= 0; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			if (ar[j - 1] > ar[j])
			{
				int temp = ar[j - 1];
				ar[j - 1] = ar[j];
				ar[j] = temp;
			}
		}
	}
}
void selectionSort(vector<int> &ar)
{
	for (int i = 0; i < ar.size() - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < ar.size(); j++)
		if (ar[j] < ar[min]) min = j;
		int temp = ar[i];
		ar[i] = ar[min];
		ar[min] = temp;
	}
}
void insertionSort(vector<int>& ar)
{
	for (int i = 1; i < ar.size(); i++)
	{
		int index = ar[i]; int j = i;
		while (j > 0 && ar[j - 1] > index)
		{
			ar[j] = ar[j - 1];
			j--;
		}
		ar[j] = index;
	}
}
void fillWithNumbers(vector<int>& ar, int size)
{
	for (int i = 0; i < size; i++)
	{
		ar.push_back(rand() % 10000);
	}
}
void merge(vector<int>& list, int p, int q, int r)
{

	int n1 = q - p + 1;
	int n2 = r - q;
	vector<int>L(n1 + 1);
	vector<int>R(n2 + 1);


	for (int i = 0; i<n1; i++)
	{
		L[i] = list[p + i];
	}
	for (int j = 0; j<n2; j++)
	{
		R[j] = list[q + 1 + j];
	}


	int largest;
	if (L[n1 - 1]<R[n2 - 1]) largest = R[n2 - 1]; else largest = L[n1 - 1];
	L[n1] = largest + 1;
	R[n2] = largest + 1;


	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			list[k] = L[i];
			i++;
		}
		else
		{
			list[k] = R[j];
			j++;
		}
	}
}

void merge_sort_aux(vector<int> &list, int p, int r)
{
	if (p<r)
	{
		int q = floor((p + r) / 2);
		merge_sort_aux(list, p, q);
		merge_sort_aux(list, q + 1, r);
		merge(list, p, q, r);
	}

}

void merge_sort(vector<int>& list)
{
	merge_sort_aux(list, 0, list.size() - 1);
}
void timeBubbleSort()
{
	cout << "Bubble Sort:" << endl;
	chrono::high_resolution_clock::time_point start, end;
	vector<double> sortTimes;
	for (size_t i = 0; i < numTrials; i++)
	{
		vector<int> numbers;
		fillWithNumbers(numbers, arraySize);
		start = chrono::high_resolution_clock::now();
		bubbleSort(numbers);
		end = chrono::high_resolution_clock::now();
		double bubbletime = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		sortTimes.push_back(bubbletime);
	}
	findMeanandSTDDEV(sortTimes);
}
void timeSelectionSort()
{
	cout << "Selection Sort:" << endl;
	chrono::high_resolution_clock::time_point start, end;
	vector<double> sortTimes;
	for (size_t i = 0; i < numTrials; i++)
	{
		vector<int> numbers;
		fillWithNumbers(numbers, arraySize);
		start = chrono::high_resolution_clock::now();
		selectionSort(numbers);
		end = chrono::high_resolution_clock::now();
		double selectiontime = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		sortTimes.push_back(selectiontime);
	}
	findMeanandSTDDEV(sortTimes);
}
void timeInsertionSort()
{
	cout << "Insertion Sort:" << endl;
	vector<double> sortTimes;
	for (size_t i = 0; i < numTrials; i++)
	{
		vector<int> numbers;
		fillWithNumbers(numbers, arraySize);
		chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
		insertionSort(numbers);
		chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
		double insertiontime = chrono::duration_cast<std::chrono::microseconds>(endTime - start).count();
		sortTimes.push_back(insertiontime);
	}
	findMeanandSTDDEV(sortTimes);
}
void timeMergeSort()
{
	cout << "Merge Sort:" << endl;
	chrono::high_resolution_clock::time_point start, end;
	vector<double> sortTimes;

	for (size_t i = 0; i < numTrials; i++)
	{
		vector<int> numbers;
		fillWithNumbers(numbers, arraySize);
		start = chrono::high_resolution_clock::now();
		merge_sort(numbers);
		end = chrono::high_resolution_clock::now();
		double mergetime = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		sortTimes.push_back(mergetime);
	}
	findMeanandSTDDEV(sortTimes);
}


int main()
{
	srand(time(0));


	timeBubbleSort();
	timeSelectionSort();	
	timeInsertionSort();
	timeMergeSort();

	system("pause");
	return 0;
}