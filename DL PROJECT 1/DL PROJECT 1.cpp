// Quine McCluskey Implementation to Minimize the given MinTerm Expression
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

std::string toBinary(int n)
{
	if (n == 0)
		return n + "";

	if (n % 2 == 0)
		return toBinary(n / 2) + "0";
	else
		return toBinary(n / 2) + "1";
}
//ensure that all bitstrings are of even length
std::string pad(std::string bin, int numLiterals)
{
	int max = numLiterals - bin.length();
	for (int i = 0; i < max; i++)
		bin = "0" + bin;
	return bin;
}


std::vector<std::string> getVars(int x)
{
	std::vector<std::string> v;
	std::string letters[] = { "a","b","c","d","e","f","g","h","i","j" };
	for (int i = 0; i < x ; i++)
		v.push_back(letters[i]);

	return v;
}
int countNumOnes(int binary)
{
	unsigned int count = 0;
	while (binary) {
		count += binary  & 1;
		binary >>= 1;
	}
	return count;
}

//differ in one bit
bool isGreyCode(std::string a, std::string b)
{
	int flag = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] != b[i])
			flag++;
	}
	return (flag == 1);
}

//function to replace graycode terms with dashes
// Eg: 0110 and 0111 becomes 011-
std::string replace_complements(std::string a, std::string b)
{
	std::string temp = "";
	for (int i = 0; i < a.length(); i++)
		if (a[i] != b[i])
			temp = temp + "-";
		else
			temp = temp + a[i];

	return temp;
}

std::vector<std::string>reduceMin(std::vector<std::string> mt)
{
	std::vector<std::string> newminterms;

	int max = mt.size();
	int* checked = new int[max];
	for (int i = 0; i < max; i++)
	{
		for (int j = i; j < max; j++)
		{
			//If a grey code pair is found, replace the differing bits with don't cares.
			if (isGreyCode(mt[i], mt[j]))
			{
				checked[i] = 1;
				checked[j] = 1;
				if (!in_vector(newminterms, replace_complements(mt[i], mt[j])))
					newminterms.push_back(replace_complements(mt[i], mt[j]));
			}
		}
	}

	//appending all reduced terms to a new vector
	for (int i = 0; i < max; i++)
	{
		//cout<<checked[i]<<endl;
		if (checked[i] != 1 && !in_vector(newminterms, mt[i]))
			newminterms.push_back(mt[i]);
	}

	delete[] checked;

	return newminterms;
}


int main()
{
	//read in input
	std::string numLiterals;
	std::string input,onString, dcString;
	//change to test for DC's
	char delimiter('d');
	char delim(' ');
	std::getline(std::cin, numLiterals, delim);
	int numLit = std::stoi(numLiterals);
	std::getline(std::cin, onString, delimiter);
	std::getline(std::cin, dcString);
	std::vector <std::string> minTerms;
	std::stringstream iss1(onString);
	
	int number;
	while (iss1 >> number)
		minTerms.push_back(pad(toBinary(number), numLit));
	
	std::stringstream iss(dcString);
	int number2;
	while (iss >> number2)
		minTerms.push_back(pad(toBinary(number),numLit));

	std::sort (minTerms.begin(), minTerms.end());
	
	
	return 0;
}