#include <iostream>
#include <cstdlib>
#include "food.cpp"
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
void readFromFile(LinkedList * list)
{
	string buffer = "";
	char command;
	double serving;
	double protein;
	double fat;
	double carb;
	ifstream infile;
	infile.open("output.txt", ios::in);

	while(infile)
	{
		command = 'c';
		infile >> command;
		//cout << command << endl;
		switch(command)
		{
			case 'a': {
					  infile.ignore();
					  getline(infile, buffer);
					  infile >> serving;
					  infile >> protein;
					  infile >> carb;
					  infile >> fat;
					  list -> add(buffer, serving, protein, carb, fat);
					  break;
				  }
			case 'r': { 
					  infile.ignore();
					  getline(infile, buffer);
					  list -> remove(buffer);
					  break;
				  }
		}
	}
	infile.close();

}
void CopyFile(string input, string output)
{
	string buffer = "";
	char command;
	double serving;
	double protein;
	double fat;
	double carb;
	ifstream infile;
	ofstream outfile;
	infile.open(input, ios::in);
	outfile.open(output, ios_base::app);


	while(infile)
	{
		command = '\0';
		infile >> command;
		if(command)
		{
		outfile << command << endl;
		}
		switch(command)
		{
		case 'a': { 
				  infile.ignore();
				  getline(infile, buffer);
				  infile >> serving;
				  infile >> protein;
				  infile >> carb;
				  infile >> fat;
				  outfile << buffer << endl;
				  outfile << serving << endl;
				  outfile << protein << endl;
				  outfile << carb << endl;
				  outfile << fat << endl;
				  break;
			  }
		case 'r' : { 
				 infile.ignore();
				 getline(infile , buffer);
				 outfile << buffer << endl;
				 break;
			   }
		}
	}

}


int main()
{
	string buffer = "";
	string filename = "";
	char command;
	double serving;
	double protein;
	double fat;
	double carb;
	LinkedList * list = new LinkedList();
	ofstream myfile;
	myfile.open("output.txt", ios_base::app);


	readFromFile(list);
	int label = 0;
	while (cin && label == 0)
	{
		command = 'z';      //resets the character
		cout << "Please enter a command ((a)dd, (r)emove, (p)rint, (d)elete the list, (c)opy the list, (m)ake a summary)";
		cin >> command;
		cout << endl;

		switch (command) 
		{
			case 'a': {
					  myfile << 'a' << endl;
					  cout << "Food name: ";
					  cin.ignore();
					  getline(cin, buffer); 
					  myfile << buffer << endl;

					  cout << "number of Servings :";
					  cin >> serving;
					  myfile << serving << endl;

					  cout << "grams of Protein :";
					  cin >> protein;
					  myfile << protein << endl;

					  cout << "grams of Carbs :";
					  cin >> carb;
					  myfile << carb << endl;

					  cout << "grams of Fat :";
					  cin >> fat;
					  myfile << fat << endl;

					  list -> add(buffer, serving, protein, carb, fat);
					  break;
				  }

			case 'r': {
					  myfile << 'r' << endl;
					  cout << "Enter the food to remove: ";
					  cin.ignore();
					  getline(cin, buffer);
					  myfile << buffer << endl;
					  if(list -> remove(buffer))
					  {
						  cout<< buffer << " REMOVED" << endl;
					  }
					  else
					  {
						  cout << "REMOVE FAILED"<< endl;
					  }
					  break;
				  }


			case 'p': {
					  list -> print();
					  break;
				  }


			case 'd': {
					  cout << "Are you sure you want to delete the list? (y)es / (n)o";
					  cin >> command;
					  if(command == 'y')
					  {
						  remove("output.txt");
						  list -> removeAllNodes(); 
					  }
					  label = 1;
					  break;
				  }
			case 'm': {
					  ofstream myfile;
					  cout << "please enter the filename of the summary you wish to create with extension" << endl;
					  cin.ignore();
					  getline(cin, filename);
					  int n = filename.length();
					  char *namearray = new char[n+1];
					  strcpy(namearray, filename.c_str());
					  remove(namearray);
					  freopen(namearray, "a+", stdout);
				          list -> print();
					  fclose(stdout);
					  label = 1;

					  break;
				  }

			case 'c': {
					cout << "Would you like to copy (t)o a file or (f)rom a file" << endl;
					cin >> command;
					if( command == 'f')
					{
						cout << "Please enter the filename you wish to copy from with extension: " << endl;
						cin.ignore();
						getline(cin, filename);
						cout << "Would you like to (a)ppend to the list or (r)eplace it?" << endl;
						cin >> command;
						if (command == 'R' || command == 'r')
						{
						list -> removeAllNodes();
						remove("output.txt");
						}
						CopyFile(filename, "output.txt");
						readFromFile(list);
					}
					
					else if(command == 't')
					{
					cout << "Please enter the filename with the extension to be copied to: " << endl;
					cin.ignore();
					getline(cin, filename);
					//remove(filename);
					int n = filename.length();
					char *namearray= new char[n+1];
					strcpy(namearray, filename.c_str());
					remove(namearray);
					CopyFile("output.txt" , filename);
					delete[] namearray;
					}
					else
					{
						cout << "no copy occurred" << endl;
					}
				  }
			
		}

	}
	delete list;
}
