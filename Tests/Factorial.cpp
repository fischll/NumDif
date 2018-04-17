//#include<iostream>
//using namespace std;
//
//int fakultaet(int value)
//{
//	if (value == 0)
//	{
//		return 1;
//	}
//	else if (value >= 1)
//	{
//		int ergebnis = 1;     
//
//		for (int i = 1; i <= value; i++)
//		{
//			ergebnis *= i;
//		}
//
//		return ergebnis;
//	}
//}
//
//int main(){
//	int k = fakultaet(100);
//	cout << "n!= " << k << endl;
//	return 0;
//}
#include <iostream> 

int64_t compute_factorial(int n)
{
	int64_t factorial = 1;

	for (int i = 1; i <= n; i++)
	{
		factorial *= i;
	}
	return factorial;
}

int main()
{
	int counter;

	std::cout << "Gebe einen Wert N zum berechnen ein : ";
	do
	{
		std::cin >> counter;
		std::cin.get();
	} while (counter < 0);

	std::cout << std::endl << counter << "! = " << compute_factorial(counter) << std::endl << std::endl;

	std::cout << "Druecke \'Return\' zum beenden." << std::endl;
	std::cin.get();
}