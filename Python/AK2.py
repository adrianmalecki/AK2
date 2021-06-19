import numpy as np
import random
import math
from time import perf_counter_ns as timer


def multiply(A, B):
    N = len(A)
    C = [[0 for i in range(N)] for j in range(N)]
    for i in range(N):
        for j in range(N):
            for k in range(N):
                C[i][j] += A[i][k] * B[k][j]
    return C

def print_matrix(matrix):
    for row in matrix:
        print(row)


def add(A, B):
    N = len(A)

    C = []
    for i in range(N):
        rows = []
        for j in range(N):
            rows.append(A[i][j] + B[i][j])
        C.append(rows)
    return C


def subtract(A, B):
    N = len(A)
    C = []
    for i in range(N):
        rows = []
        for j in range(N):
            rows.append(A[i][j] - B[i][j])
        C.append(rows)
    return C


def next_power_of_2(x):
    return 1 if x == 0 else 2**(x - 1).bit_length()


def split_matrix(A, B, half):
    a11 = [[0 for j in range(0, half)] for i in range(0, half)]
    a12 = [[0 for j in range(0, half)] for i in range(0, half)]
    a21 = [[0 for j in range(0, half)] for i in range(0, half)]
    a22 = [[0 for j in range(0, half)] for i in range(0, half)]

    b11 = [[0 for j in range(0, half)] for i in range(0, half)]
    b12 = [[0 for j in range(0, half)] for i in range(0, half)]
    b21 = [[0 for j in range(0, half)] for i in range(0, half)]
    b22 = [[0 for j in range(0, half)] for i in range(0, half)]

    for i in range(half):
        for j in range(half):
            a11[i][j] = A[i][j]
            a12[i][j] = A[i][j + half]
            a21[i][j] = A[i + half][j]
            a22[i][j] = A[i + half][j + half]

            b11[i][j] = B[i][j]
            b12[i][j] = B[i][j + half]
            b21[i][j] = B[i + half][j]
            b22[i][j] = B[i + half][j + half]

    return a11, a12, a21, a22, b11, b12, b21, b22


def strassen_algorithm(A, B):
    N = len(A)

    if N <= 64:
        return multiply(A, B)
    else:
        half = N // 2
        a11, a12, a21, a22, b11, b12, b21, b22 = split_matrix(A, B, half)

        m1 = strassen_algorithm(add(a11, a22), add(b11, b22))
        m2 = strassen_algorithm(add(a21, a22), b11)
        m3 = strassen_algorithm(a11, subtract(b12, b22))
        m4 = strassen_algorithm(a22, subtract(b21, b11))
        m5 = strassen_algorithm(add(a11, a12), b22)
        m6 = strassen_algorithm(subtract(a21, a11), add(b11, b12))
        m7 = strassen_algorithm(subtract(a12, a22), add(b21, b22))

        c11 = subtract(add(add(m1, m4), m7), m5)
        c12 = add(m3, m5)
        c21 = add(m2, m4)
        c22 = subtract(add(add(m1, m3), m6), m2)

        C = []
        for i in range(len(c11)):
            C.append(c11[i] + c12[i])
        for i in range(len(c21)):
            C.append(c21[i] + c22[i])

        return C

def strassen(A, B):
    n = len(A)
    m = next_power_of_2(n)

    if n != m:
        extendedA = [[0 for i in range(m)] for j in range(m)]
        extendedB = [[0 for i in range(m)] for j in range(m)]
        for i in range(n):
            for j in range(n):
                extendedA[i][j] = A[i][j]
                extendedB[i][j] = B[i][j]

        extendedC = strassen_algorithm(extendedA, extendedB)
        C = [[0 for i in range(n)] for j in range(n)]
        for i in range(n):
            for j in range(n):
                C[i][j] = extendedC[i][j]
        return C
    else:
        C = strassen_algorithm(A, B)
        return C

if __name__ == '__main__':
    choice = 99
    A = np.array([[0]])
    B = np.array([[0]])


    while choice != 7:
        print('_________MENU_________')
        print('1. Dane losowe')
        print('2. Algorytm naiwny')
        print('3. Algorytm Strassena')
        print('4. Numpy')
        print('5. Testy')
        print('6. Wyjście')

        choice = input('Wybór: ')


        if choice == '1':
            N = int(input("Podaj rozmiar: "))
            A = np.random.randint(100, size=(N, N))
            B = np.random.randint(100, size=(N, N))
            #print_matrix(A)
            #print_matrix(B)

        elif choice == '2':
            print('Algorytm naiwny')
            start = timer()
            C = multiply(A, B)
            stop = timer()
            time = stop - start
            print("Czas: ")
            print(time)
            #print_matrix(C)

        elif choice == '3':
            print('Algorytm Strassena')
            start = timer()
            C = strassen(A, B)
            stop = timer()
            time = stop - start
            print("Czas: ")
            print(time)
            #print_matrix(C)


        elif choice == '4':
            print('Biblioteka numpy')
            start = timer()
            C = np.dot(A, B)
            stop = timer()
            time = stop - start
            print("Czas: ")
            print(time)
            #print_matrix(C)

        elif choice == '5':
            numberOfTest = int(input("Podaj ilosc testów: "))
            sizes = [200, 500, 1000, 2000, 4000, 8000]


            for size in sizes:
                strassen_time = 0
                naive_time = 0
                numpy_time = 0

                print('Rozmiar macierzy: ', size)

                for i in range(numberOfTest):
                    A = np.random.randint(100, size=(size, size))
                    B = np.random.randint(100, size=(size, size))

                    start = timer()
                    C = multiply(A, B)
                    stop = timer()
                    naive_time += (stop - start)

                    start = timer()
                    C = strassen(A, B)
                    stop = timer()
                    strassen_time += (stop - start)

                    start = timer()
                    C = np.dot(A, B)
                    stop = timer()
                    numpy_time += (stop - start)

                print('Czas algorytmu naiwnego: ', naive_time/numberOfTest)
                print('Czas algorytmu Strassena: ', strassen_time/numberOfTest)
                print('Czas biblioteki EJML: ', numpy_time/numberOfTest)

        elif choice == '6':
            exit()

        else:
            print("Wprowadz poprawną liczbę")