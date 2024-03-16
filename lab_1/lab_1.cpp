#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

unsigned long binet(int n) {
	double phidia = (1 + sqrt(5)) / 2;
	return round((pow(phidia, n) - pow(1 - phidia, n)) / sqrt(5));
}

unsigned long iteration(int n) {
	int a = 0;
	int b = 1;

	for (int i = 2; i <= n; ++i) {
		int c = a + b;
		a = b;
		b = c;
	}
	return b;
}

unsigned long div_conq(int n) {
	if (n <= 1) {
		return n;
	}
	else {
		return div_conq(n - 1) + div_conq(n - 2);
	}

}

int fibs_m[35];
unsigned long down_pr(int n) {
	if (n <= 1)
		return n;

	if (fibs_m[n] != 0)
		return fibs_m[n];

	fibs_m[n] = down_pr(n - 1) + down_pr(n - 2);
	return fibs_m[n];
}

unsigned long up_pr(int n) {

	int fibs[35];
	fibs[0] = 0;
	fibs[1] = 1;

	for (int i = 2; i <= n + 1; ++i) {
		fibs[i] = (fibs[i - 1] + fibs[i - 2]);
	}

	return fibs[n];
}

chrono::microseconds::rep sec(unsigned long (*func)(int), int n) {
	auto start = chrono::steady_clock::now();
	func(n);
	auto end = chrono::steady_clock::now();
	return std::chrono::nanoseconds(end - start).count();
}

int main() {
	int n = 35;
	cout << sec(binet, n) << "\n";
	cout << sec(iteration, n) << "\n";
	cout << sec(div_conq, n) << "\n";
	cout << sec(down_pr, n) << "\n";
	cout << sec(up_pr, n) << "\n";
}