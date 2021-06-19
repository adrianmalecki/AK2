#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <chrono>
#include <armadillo>


using namespace std;


void strassen(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, unsigned int tam);
unsigned int nextPowerOfTwo(int n);
void strassenR(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C,
	int tam);
void sum(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int tam);
void subtract(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int tam);


void printMatrix(vector< vector<int> > matrix, int n);

void multiply(vector< vector<int> > A,
	vector< vector<int> > B,
	vector< vector<int> > &C, int n) {
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

vector< vector<int> > ijkalgorithm(vector< vector<int> > A,
	vector< vector<int> > B) {
	int n = A.size();

	vector<int> tmp(n, 0);
	vector< vector<int> > C(n, tmp);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}


void strassenR(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int tam) {
	if (tam <= 64) {
		multiply(A, B, C, tam);
		return;
	}

	else {
		int newTam = tam / 2;
		vector<int> inner(newTam);
		vector< vector<int> >
			a11(newTam, inner), a12(newTam, inner), a21(newTam, inner), a22(newTam, inner),
			b11(newTam, inner), b12(newTam, inner), b21(newTam, inner), b22(newTam, inner),
			c11(newTam, inner), c12(newTam, inner), c21(newTam, inner), c22(newTam, inner),
			m1(newTam, inner), m2(newTam, inner), m3(newTam, inner), m4(newTam, inner),
			m5(newTam, inner), m6(newTam, inner), m7(newTam, inner),
			aResult(newTam, inner), bResult(newTam, inner);

		int i, j;

		for (i = 0; i < newTam; i++) {
			for (j = 0; j < newTam; j++) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + newTam];
				a21[i][j] = A[i + newTam][j];
				a22[i][j] = A[i + newTam][j + newTam];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + newTam];
				b21[i][j] = B[i + newTam][j];
				b22[i][j] = B[i + newTam][j + newTam];
			}
		}


		sum(a11, a22, aResult, newTam);
		sum(b11, b22, bResult, newTam);
		strassenR(aResult, bResult, m1, newTam);

		sum(a21, a22, aResult, newTam);
		strassenR(aResult, b11, m2, newTam);

		subtract(b12, b22, bResult, newTam);
		strassenR(a11, bResult, m3, newTam);

		subtract(b21, b11, bResult, newTam);
		strassenR(a22, bResult, m4, newTam);

		sum(a11, a12, aResult, newTam);
		strassenR(aResult, b22, m5, newTam);

		subtract(a21, a11, aResult, newTam);
		sum(b11, b12, bResult, newTam);
		strassenR(aResult, bResult, m6, newTam);

		subtract(a12, a22, aResult, newTam);
		sum(b21, b22, bResult, newTam);
		strassenR(aResult, bResult, m7, newTam);


		sum(m3, m5, c12, newTam);
		sum(m2, m4, c21, newTam);

		sum(m1, m4, aResult, newTam);
		sum(aResult, m7, bResult, newTam);
		subtract(bResult, m5, c11, newTam);

		sum(m1, m3, aResult, newTam);
		sum(aResult, m6, bResult, newTam);
		subtract(bResult, m2, c22, newTam);

		for (i = 0; i < newTam; i++) {
			for (j = 0; j < newTam; j++) {
				C[i][j] = c11[i][j];
				C[i][j + newTam] = c12[i][j];
				C[i + newTam][j] = c21[i][j];
				C[i + newTam][j + newTam] = c22[i][j];
			}
		}
	}
}

unsigned int nextPowerOfTwo(int n) {
	return pow(2, int(ceil(log2(n))));
}

void strassen(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, unsigned int n) {

	unsigned int m = nextPowerOfTwo(n);
	vector<int> inner(m);
	vector< vector<int> > APrep(m, inner), BPrep(m, inner), CPrep(m, inner);

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			APrep[i][j] = A[i][j];
			BPrep[i][j] = B[i][j];
		}
	}

	strassenR(APrep, BPrep, CPrep, m);
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			C[i][j] = CPrep[i][j];
		}
	}
}

void sum(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int tam) {
	int i, j;

	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void subtract(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int tam) {
	int i, j;

	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}


void printMatrix(vector< vector<int> > matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != 0) {
				cout << "\t";
			}
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

void drawMatrix(vector< vector<int> > &A,
	vector< vector<int> > &B,
	vector< vector<int> > &C, int n) {
	srand((unsigned)time(0));
	int rangeStart = 1, rangeEnd = 10;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			A[i][j] = (rand() % rangeEnd) + rangeStart;
			B[i][j] = (rand() % rangeEnd) + rangeStart;
			C[i][j] = 0;
		}
}

int main(int argc, char* argv[]) {
	//int n = 0;
	//cout << "Podaj rozmiar: " << endl;
	//cin >> n;
	srand((unsigned)time(0));
	int rangeStart = 1, rangeEnd = 100;
	int numberOfTest;

	int sizes[6] = { 200, 500, 1000, 2000, 4000, 8000 };

	//vector<int> inner(n);
	//vector< vector<int> > A(n, inner), B(n, inner), C(n, inner);

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	cout << "Liczba testow: " << endl;
	cin >> numberOfTest;

	for (int i = 0; i < 6; i++) {
		long totalTimeNaive = 0;
		long totalTimeStrassen = 0;
		long totalTimeArmadillo = 0;
		int n = sizes[i];
		vector<int> inner(n);
		vector< vector<int> > A(n, inner), B(n, inner), C(n, inner);



		cout << "Rozmiar macierzy: " << sizes[i] << endl;
		for (int i = 0; i < numberOfTest; i++) {
			drawMatrix(A, B, C, n);
			
			begin = std::chrono::steady_clock::now();
			C = ijkalgorithm(A, B);
			end = std::chrono::steady_clock::now();
			totalTimeNaive += std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();
			
			begin = std::chrono::steady_clock::now();
			strassen(A, B, C, n);
			end = std::chrono::steady_clock::now();
			totalTimeStrassen += std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();


			arma::arma_rng::set_seed_random();
			// Utworzenie macierzy wype³nionych liczbami ca³kowitymi
			arma::mat MatrixA = arma::randi<arma::mat>(n, n, arma::distr_param(rangeStart, rangeEnd));
			arma::mat MatrixB = arma::randi<arma::mat>(n, n, arma::distr_param(rangeStart, rangeEnd));

			begin = std::chrono::steady_clock::now();
			arma::mat MatrixC = MatrixA * MatrixB;
			end = std::chrono::steady_clock::now();
			totalTimeArmadillo += std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();
		}
		cout << "Czas algorytmu naiwnego: " << totalTimeNaive/numberOfTest << "[ms]" << std::endl;
		cout << "Czas algorytmu Strassena: " << totalTimeStrassen/numberOfTest << "[ms]" << std::endl;
		cout << "Czas biblioteki Armadillo: " << totalTimeArmadillo/numberOfTest << "[ms]" << std::endl;
	}



	//int cos;
	//cout << "start: " << endl;
	//cin >> cos;

	//cout << "Strassen " << endl;
	//std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
	//strassen(A, B, C, n);
	//std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end1 - begin1).count() << "[s]" << std::endl;
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end1 - begin1).count() << "[ns]" << std::endl;
	//cout << "start: " << endl;
	//cin >> cos;











	return 0;
}