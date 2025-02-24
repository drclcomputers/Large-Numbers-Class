//BIGUNSIGNEDINT is a class made to store numbers with up to 10000 digits.
//For addition, the result of the sum needs to have maximum 10000 digits.
//For multiplication, the numbers need to have a maximum of 5000 digits, so the max number is n=9999...9 (5000 of 9s) so n^2 will have 100001 digits. 


#include<iostream>
#include<cstring>

#include "bigunsignedint.h"

using namespace std;
using namespace big;


int main() {
	BIGUNSIGNEDINT A, B;
	char a[10000] = "123456789011", b[100]="5111";
	A.set(a);
	B.set(b);

	//A = 12;
	//B = 3;

	cout << b << '\n';

	cout<<to_chararray(A);

	//cout << b;

	return 0;
}