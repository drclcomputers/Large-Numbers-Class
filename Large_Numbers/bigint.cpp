#include "bigint.h"

using namespace big;


//constructors

BIGINT::BIGINT() { //default constructor
	set_zero();
}

BIGINT::BIGINT(int num) { //constructor 1
	set_zero();
	if (num > 0) {
		len = 0;
		while (num > 0) {
			bigint[++len] = num % 10;
			num /= 10;
		}
	}
}

BIGINT::BIGINT(long long num) { //constructor 2
	set_zero();
	if (num > 0) {
		len = 0;
		while (num > 0) {
			bigint[++len] = num % 10;
			num /= 10;
		}
	}
}

BIGINT::BIGINT(char* p) { //constructor 3
	//set number to 0
	set_zero();
	if (p != NULL)
		set(p);
}


//set values

void BIGINT::set(char* p) {
	set_zero();

	if (p == nullptr) return;

	short int l = strlen(p);

	//set to element 0 the length of the number
	len = l;

	//set the number to the one in the char array
	for (int i = l; i > 0; i--)
		if (p[l - i] < 48 || p[l - i]>57) {
			throw std::exception("Undecimal symbol!");
			break;
		}
		else
			bigint[i] = (int)p[l - i] - 48;
}

void BIGINT::set_zero() {
	len = 1;
	for (int i = 1; i <= 10029; i++) bigint[i] = 0;
}


//mathematical operations

BIGINT BIGINT::operator+(BIGINT const& obj) {
	BIGINT res; // Result of addition
	int mx = std::max(len, obj.len); // Maximum length
	res.len = mx; // Set initial length of result

	bool add = false; // Carry flag for addition

	for (int i = 1; i <= mx; i++) {
		int sum = 0;

		if (i <= len) sum += bigint[i];
		if (i <= obj.len) sum += obj.bigint[i];
		if (add) sum += 1;

		res.bigint[i] = sum % 10;
		add = (sum >= 10);
	}

	if (add) {
		res.len++;
		res.bigint[res.len] = 1;
	}

	return res;
}
BIGINT BIGINT::operator+(int n) {
	return *this + BIGINT(n);
}
BIGINT BIGINT::operator+(long long n) {
	return *this + BIGINT(n);
}
void BIGINT::operator+=(BIGINT const& obj) {
	*this = *this + obj;
}
void BIGINT::operator+=(long long obj) {
	*this = *this + BIGINT(obj);
}
void BIGINT::operator+=(int obj) {
	*this = *this + BIGINT(obj);
}

BIGINT BIGINT::operator-(BIGINT const& obj) { //substraction
	//if (BIGINT(0) == obj) return *this;

	BIGINT res; //result

	int mn = std::max(len, obj.len);
	bool min = 0;

	res.len = mn;

	//substraction
	if (*this > obj) {
		for (int i = 1; i <= mn; i++) {
			if (min) {
				if (bigint[i] - obj.bigint[i] - 1 >= 0) {
					res.bigint[i] = bigint[i] - obj.bigint[i] - 1, min = 0;
				}
				else {
					res.bigint[i] = bigint[i] - obj.bigint[i] + 9, min = 1;
				}
			}
			else {
				if (bigint[i] - obj.bigint[i] >= 0) {
					res.bigint[i] = bigint[i] - obj.bigint[i], min = 0;
				}
				else {
					res.bigint[i] = bigint[i] - obj.bigint[i] + 10, min = 1;
				}
			}
		}
	}
	else {
		for (int i = 1; i <= mn; i++) {
			if (min) {
				if (obj.bigint[i] - bigint[i] - 1 >= 0) {
					res.bigint[i] = obj.bigint[i] - bigint[i] - 1, min = 0;
				}
				else {
					res.bigint[i] = obj.bigint[i] - bigint[i] + 9, min = 1;
				}
			}
			else {
				if (obj.bigint[i] - bigint[i] >= 0) {
					res.bigint[i] = obj.bigint[i] - bigint[i], min = 0;
				}
				else {
					res.bigint[i] = obj.bigint[i] - bigint[i] + 10, min = 1;
				}
			}
		}
	}
	for (int i = res.len; i > 1; i--)
		if (res.bigint[i] == 0) res.len--;
		else break;

	return res;
}
BIGINT BIGINT::operator-(int n) {
	return *this - BIGINT(n);
}
BIGINT BIGINT::operator-(long long n) {
	return *this - BIGINT(n);
}
void BIGINT::operator-=(BIGINT const& obj) {
	*this = *this - obj;
}
void BIGINT::operator-=(long long obj) {
	*this = *this - BIGINT(obj);
}
void BIGINT::operator-=(int obj) {
	*this = *this - BIGINT(obj);
}

BIGINT BIGINT::operator*(BIGINT const& obj) { //multiplication
	if (BIGINT(0) == obj || BIGINT(0) == *this) { set_zero(); return 0; }

	BIGINT res; //result

	int mx = len + obj.len - 1;
	int add = 0;

	res.len = mx;

	if (*this > obj) {

		for (int i = 1; i <= len; i++) {
			for (int j = 1; j <= obj.len; j++) {
				res.bigint[i + j - 1] += bigint[i] * obj.bigint[j];
			}
		}

		for (int i = 1; i <= res.len; i++) {
			add += res.bigint[i];
			res.bigint[i] = add % 10;
			add /= 10;
		}
	}
	else {
		for (int i = 1; i <= obj.len; i++) {
			for (int j = 1; j <= len; j++) {
				res.bigint[i + j - 1] += obj.bigint[i] * bigint[j];
			}
		}

		for (int i = 1; i <= res.len; i++) {
			add += res.bigint[i];
			res.bigint[i] = add % 10;
			add /= 10;
		}
	}

	if (add)
		res.bigint[++res.len] = add;

	return res;
}
BIGINT BIGINT::operator*(int n) {
	return *this * BIGINT(n);
}
BIGINT BIGINT::operator*(long long n) {
	return *this * BIGINT(n);
}
void BIGINT::operator*=(BIGINT const& obj) {
	*this = *this * obj;
}
void BIGINT::operator*=(long long obj) {
	*this = *this * BIGINT(obj);
}
void BIGINT::operator*=(int obj) {
	*this = *this * BIGINT(obj);
}

BIGINT BIGINT::operator/(BIGINT const& obj) { //division
	if (BIGINT(0) == obj) throw std::exception("Division by zero!");

	int o = 0;

	BIGINT aux, rez;

	if (*this > obj) {
		for (int i = len; i > len - obj.len; i--)
			aux = aux * 10 + bigint[i];

		//aux.len = len - obj.len - 1;

		while (len - obj.len - o > 0) {

			if (aux < obj) aux = aux * 10 + bigint[len - obj.len - o];
			//cout << bigint[len - obj.len - o] << ' ';
			if (BIGINT(0) == aux) {
				rez = rez * 10;
				o++;
				continue;
			}
			int i = 0;
			while (aux >= obj) {
				aux = aux - obj;
				i++;
			}

			rez = rez * 10 + i;

			o++;
		}
	}
	else {
		for (int i = len; i > obj.len-len; i--)
			aux = aux * 10 + obj.bigint[i];

		//aux.len = len - obj.len - 1;

		while (obj.len - len - o > 0) {

			if (aux < *this) aux = aux * 10 + obj.bigint[obj.len - len - o];
			//cout << bigint[len - obj.len - o] << ' ';
			if (BIGINT(0) == aux) {
				rez = rez * 10;
				o++;
				continue;
			}
			int i = 0;
			while (aux >= *this) {
				aux = aux - *this;
				i++;
			}

			rez = rez * 10 + i;

			o++;
		}
	}

	return rez;

}
BIGINT BIGINT::operator/(int n) {
	return *this / BIGINT(n);
}
BIGINT BIGINT::operator/(long long n) {
	return *this / BIGINT(n);
}
void BIGINT::operator/=(BIGINT const& obj) {
	*this = *this / obj;
}
void BIGINT::operator/=(long long obj) {
	*this = *this / BIGINT(obj);
}
void BIGINT::operator/=(int obj) {
	*this = *this / BIGINT(obj);
}

BIGINT BIGINT::operator%(BIGINT const& obj) { //division
	if (BIGINT(0) == obj) throw std::exception("Division by zero!");

	int o = 0;

	BIGINT aux, rez;

	for (int i = len; i > len - obj.len; i--)
		aux = aux * 10 + bigint[i];

	//aux.len = len - obj.len - 1;

	while (len - obj.len - o > 0) {

		if (aux < obj) aux = aux * 10 + bigint[len - obj.len - o];
		//cout << bigint[len - obj.len - o] << ' ';
		if (BIGINT(0) == aux) {
			rez = rez * 10;
			o++;
			continue;
		}
		int i = 0;
		while (aux >= obj) {
			aux = aux - obj;
			i++;
		}

		rez = rez * 10 + i;

		o++;
	}

	return aux;
}
BIGINT BIGINT::operator%(int n) {
	return *this % BIGINT(n);
}
BIGINT BIGINT::operator%(long long n) {
	return *this % BIGINT(n);
}


//logic operations

bool BIGINT::operator<(BIGINT const& obj) {
	if (len == obj.len) {
		for (int i = len; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else if (bigint[i] < obj.bigint[i]) return 1;
			else return 0;
		}
	}
	else
		return len < obj.len;
	return 0;
}
bool BIGINT::operator<(int n) {
	return *this < BIGINT(n);
}
bool BIGINT::operator<(long long n) {
	return *this < BIGINT(n);
}

bool BIGINT::operator>(BIGINT const& obj) {
	if (len == obj.len) {
		for (int i = len; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else if (bigint[i] < obj.bigint[i]) return 0;
			else return 1;
		}
	}
	else
		return len > obj.len;
	return 0;
}
bool BIGINT::operator>(int n) {
	return *this > BIGINT(n);
}
bool BIGINT::operator>(long long n) {
	return *this > BIGINT(n);
}

bool BIGINT::operator==(BIGINT const& obj) {
	int mx = std::max(len, obj.len);
	if (len == obj.len) {
		for (int i = mx; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else return 0;
		}
	}
	else
		return 0;
	return 1;
}
bool BIGINT::operator==(int num) {
	return BIGINT(num) == *this;
}
bool BIGINT::operator==(long long num) {
	return BIGINT(num) == *this;
}

bool BIGINT::operator<=(BIGINT const& obj) {
	if (len < obj.len) return 1;
	if (len > obj.len) return 0;

	for (int i = len; i > 0; i--) {
		if (bigint[i] < obj.bigint[i]) return 1;
		if (bigint[i] > obj.bigint[i]) return 0;
	}

	return 1;
}
bool BIGINT::operator<=(int n) {
	return *this <= BIGINT(n);
}
bool BIGINT::operator<=(long long n) {
	return *this <= BIGINT(n);
}

bool BIGINT::operator>=(BIGINT const& obj) {
	if (len < obj.len) return 0;
	if (len > obj.len) return 1;

	for (int i = len; i > 0; i--) {
		if (bigint[i] < obj.bigint[i]) return 0;
		if (bigint[i] > obj.bigint[i]) return 1;
	}

	return 1;
}
bool BIGINT::operator>=(int n) {
	return *this >= BIGINT(n);
}
bool BIGINT::operator>=(long long n) {
	return *this >= BIGINT(n);
}

void BIGINT::operator=(BIGINT const& obj) {
	len = obj.len;
	for (int i = 1; i <= obj.len; i++) {
		bigint[i] = obj.bigint[i];
	}
}
void BIGINT::operator=(int num) {
	*this = BIGINT(num);
}
void BIGINT::operator=(long long n) {
	*this = BIGINT(n);
}

/*
BIGINT custom_pow(BIGINT const& obj) {
	if (BIGINT(0) == obj) return 1;
	if (obj % 2 == 1) return (*this * custom_pow((obj-1)));
	BIGINT P = custom_pow((BIGINT(obj/2)));
	return P * P;
}
BIGINT custom_pow(int n) {
	return custom_pow(BIGINT(n));
}*/


//printing or input

std::ostream& big::operator<<(std::ostream& console, const BIGINT& obj) { //print BIGINT
	int l = obj.len; //length
	for (int i = l; i > 0; i--) //iterate through loop to get every digit
		console << obj.bigint[i];
	return console;
}

std::istream& big::operator>>(std::istream& console, BIGINT& obj) {
	char p[1025] = "";
	console >> p;

	obj.set_zero();

	int l;
	obj.len = l = strlen(p);
	for (int i = obj.len; i > 0; i--)
		if (p[l - i] < 48 || p[l - i]>57) {
			throw std::exception("Undecimal symbol!");
			break;
		}
		else
			obj.bigint[i] = (int)p[l - i] - 48;

	return console;
}


//converting

int BIGINT::to_int() {
	int rez = 0;
	if (len <= 10 && *this <= INT32_MAX) {
		for (int i = len; i > 0; i--) {
			rez = rez * 10 + bigint[i];
		}
	}
	else
		throw std::exception("Integer limit excedeed.");

	return rez;
}

long long BIGINT::to_longlong() {
	long long rez = 0;
	if (len<=19 && *this <= INT64_MAX) {
		for (int i = len; i > 0; i--) {
			rez = rez * 10 + bigint[i];
		}
	}
	else
		throw std::exception("Long long limit excedeed. Cannot convert to primitive C++ data types.");

	return rez;
}


//other functions

BIGINT operator+(int num, BIGINT const& obj) {
	return BIGINT(num) + obj;
}
BIGINT operator+(BIGINT const& obj, int num) {
	return BIGINT(num) + obj;
}

BIGINT operator-(int num, BIGINT const& obj) {
	return BIGINT(num) - obj;
}
BIGINT operator-(BIGINT const& obj, int num) {
	return BIGINT(num) - obj;
}

BIGINT operator*(int num, BIGINT const& obj) {
	return BIGINT(num) * obj;
}
BIGINT operator*(BIGINT const& obj, int num) {
	return BIGINT(num) * obj;
}

BIGINT operator/(int num, BIGINT const& obj) {
	return BIGINT(num) / obj;
}
BIGINT operator/(BIGINT const& obj, int num) {
	return BIGINT(num) / obj;
}

BIGINT operator%(int num, BIGINT const& obj) {
	return BIGINT(num) % obj;
}
BIGINT operator%(BIGINT const& obj, int num) {
	return BIGINT(num) % obj;
}

bool operator==(int num, BIGINT const& obj) {
	return BIGINT(num) == obj;
}
bool operator==(BIGINT const& obj, int num) {
	return BIGINT(num) == obj;
}

bool operator>(int num, BIGINT const& obj) {
	return BIGINT(num) > obj;
}
bool operator>(BIGINT const& obj, int num) {
	return BIGINT(num) > obj;
}

bool operator<(int num, BIGINT const& obj) {
	return BIGINT(num) < obj;
}
bool operator<(BIGINT const& obj, int num) {
	return BIGINT(num) < obj;
}

bool operator>=(int num, BIGINT const& obj) {
	return BIGINT(num) >= obj;
}
bool operator>=(BIGINT const& obj, int num) {
	return BIGINT(num) >= obj;
}

bool operator<=(int num, BIGINT const& obj) {
	return BIGINT(num) <= obj;
}
bool operator<=(BIGINT const& obj, int num) {
	return BIGINT(num) <= obj;
}
