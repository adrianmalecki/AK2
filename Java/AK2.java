package com.company;

import org.ejml.simple.SimpleMatrix;
import java.util.*;


public class Main {

    public static int leaf = 64;

    static int[][] multiply(int[][] A,
                                int[][] B) {
        int n = A.length;

        int[][] C = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    static void printMatrix(int[][] matrix) {
        for (int[] line : matrix) {
            int i = 0;
            StringBuilder sb = new StringBuilder(matrix.length);
            for (int number : line) {
                if (i != 0) {
                    sb.append("\t");
                } else {
                    i++;
                }
                sb.append(number);
            }
            System.out.println(sb.toString());
        }
    }

    private static int[][] add(int[][] A, int[][] B) {
        int n = A.length;
        int[][] C = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        return C;
    }

    private static int[][] subtract(int[][] A, int[][] B) {
        int n = A.length;
        int[][] C = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        return C;
    }

    private static int nextPowerOfTwo(int n) {
        int log2 = (int) Math.ceil(Math.log(n) / Math.log(2));
        return (int) Math.pow(2, log2);
    }

    public static int[][] strassen(int[][] A, int[][] B) {
        int n = A.length;
        int m = nextPowerOfTwo(n);
        int[][] extendedA = new int[m][m];
        int[][] extendedB = new int[m][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                extendedA[i][j] = A[i][j];
                extendedB[i][j] = B[i][j];
            }
        }

        int[][] CPrep = strassenR(extendedA, extendedB);
        int[][] C = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = CPrep[i][j];
            }
        }
        return C;
    }

    private static int[][] strassenR(int[][] A, int[][] B) {
        int n = A.length;

        if (n <= leaf) {
            return multiply(A, B);
        } else {
            int newSize = n / 2;
            int[][] a11 = new int[newSize][newSize];
            int[][] a12 = new int[newSize][newSize];
            int[][] a21 = new int[newSize][newSize];
            int[][] a22 = new int[newSize][newSize];

            int[][] b11 = new int[newSize][newSize];
            int[][] b12 = new int[newSize][newSize];
            int[][] b21 = new int[newSize][newSize];
            int[][] b22 = new int[newSize][newSize];

            int[][] aTemp;
            int[][] BTemp;

            for (int i = 0; i < newSize; i++) {
                for (int j = 0; j < newSize; j++) {
                    a11[i][j] = A[i][j];
                    a12[i][j] = A[i][j + newSize];
                    a21[i][j] = A[i + newSize][j];
                    a22[i][j] = A[i + newSize][j + newSize];

                    b11[i][j] = B[i][j];
                    b12[i][j] = B[i][j + newSize];
                    b21[i][j] = B[i + newSize][j];
                    b22[i][j] = B[i + newSize][j + newSize];
                }
            }


            int[][] m1 = strassenR(add(a11, a22), add(b11, b22));
            int[][] m2 = strassenR(add(a21, a22), b11);
            int[][] m3 = strassenR(a11, subtract(b12, b22));
            int[][] m4 = strassenR(a22, subtract(b21, b11));
            int[][] m5 = strassenR(add(a11, a12), b22);
            int[][] m6 = strassenR(subtract(a21, a11), add(b11, b12));
            int[][] m7 = strassenR(subtract(a12, a22), add(b21, b22));


            int[][] c11 = subtract(add(add(m1, m4), m7), m5);
            int[][] c12 = add(m3, m5);
            int[][] c21 = add(m2, m4);
            int[][] c22 = subtract(add(add(m1, m3), m6), m2);

            int[][] C = new int[n][n];
            for (int i = 0; i < newSize; i++) {
                for (int j = 0; j < newSize; j++) {
                    C[i][j] = c11[i][j];
                    C[i][j + newSize] = c12[i][j];
                    C[i + newSize][j] = c21[i][j];
                    C[i + newSize][j + newSize] = c22[i][j];
                }
            }
            return C;
        }
    }

    private static double[][] arrayToMatrix(int[][] arr){
        int n = arr.length;
        double[][] dataArr= new double[n][n];

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dataArr[i][j] = arr[i][j];
            }
        }
        return dataArr;
    }

    private static int[][] drawMatrix(int n){
        int[][] arr= new int[n][n];
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                arr[i][j] = (int) (Math.random()*10);
            }
        }
        return arr;
    }


    public static void main(String[] args) {

        SimpleMatrix SimpleA;
        SimpleMatrix SimpleB;
        SimpleMatrix SimpleC;
        Scanner scanner = new Scanner(System.in);
        int choice = 99;
        int n = 0;
        int[][] A = {{0}};
        int[][] B = {{0}};
        long start, stop, timeElapsed;

        while (choice != 7){
            System.out.println("_________MENU_________");
            System.out.println("1. Dane losowe");
            System.out.println("2. Algorytm naiwny");
            System.out.println("3. Algorytm Strassena");
            System.out.println("4. Biblioteka EJML");
            System.out.println("5. Testy");
            System.out.println("6. Wyjście");

            System.out.println("Wybór: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    scanner = new Scanner(System.in);
                    System.out.println("Podaj rozmiar:");
                    n = scanner.nextInt();

                    A = drawMatrix(n);
                    B = drawMatrix(n);

                    //printMatrix(A);
                    //printMatrix(B);

                    break;
                case 2:
                    System.out.println("Algorytm naiwny");
                    start = System.currentTimeMillis();
                    int[][] C = multiply(A, B);
                    stop = System.currentTimeMillis();
                    timeElapsed = stop - start;
                    //printMatrix(C);
                    System.out.println("Czas: ");
                    System.out.println(timeElapsed);
                    break;
                case 3:
                    System.out.println("Algorytm Strassena");
                    start = System.currentTimeMillis();
                    C = strassen(A, B);
                    stop = System.currentTimeMillis();
                    timeElapsed = stop - start;
                    //printMatrix(C);
                    System.out.println("Czas: ");
                    System.out.println(timeElapsed);
                    break;
                case 4:
                    SimpleA = new SimpleMatrix(arrayToMatrix(A));
                    SimpleB = new SimpleMatrix(arrayToMatrix(B));

                    System.out.println("Biblioteka EJML");
                    start = System.currentTimeMillis();
                    SimpleC = SimpleA.mult(SimpleB);
                    stop = System.currentTimeMillis();
                    timeElapsed = stop - start;
                    //SimpleC.getMatrix().print();
                    System.out.println("Czas: ");
                    System.out.println(timeElapsed);
                    break;
                case 5:
                    int numberOfTest = 0;
                    int[] sizes = {200, 500, 1000, 2000, 4000, 8000};
                    System.out.println("Liczba testów: ");
                    numberOfTest = scanner.nextInt();
                    int[][] result;
                    long totalTimeNaive;
                    long totalTimeStrassen;
                    long totalTimeEJML;

                    for(int size : sizes){
                        totalTimeNaive = 0;
                        totalTimeStrassen = 0;
                        totalTimeEJML = 0;

                        System.out.println("Rozmiar macierzy: " + size);

                        for(int a = 0; a < numberOfTest; a++){
                            A = drawMatrix(size);
                            B = drawMatrix(size);

                            start = System.currentTimeMillis();
                            result = multiply(A, B);
                            stop = System.currentTimeMillis();
                            timeElapsed = stop - start;
                            totalTimeNaive += timeElapsed;

                            start = System.currentTimeMillis();
                            result = strassen(A, B);
                            stop = System.currentTimeMillis();
                            timeElapsed = stop - start;
                            totalTimeStrassen += timeElapsed;

                            SimpleA = new SimpleMatrix(arrayToMatrix(A));
                            SimpleB = new SimpleMatrix(arrayToMatrix(B));

                            start = System.currentTimeMillis();
                            SimpleC = SimpleA.mult(SimpleB);
                            stop = System.currentTimeMillis();
                            timeElapsed = stop - start;
                            totalTimeEJML += timeElapsed;
                        }
                        System.out.println("Czas algorytmu naiwnego: " + totalTimeNaive/numberOfTest);
                        System.out.println("Czas algorytmu Strassena: " + totalTimeStrassen/numberOfTest);
                        System.out.println("Czas biblioteki EJML: " + totalTimeEJML/numberOfTest);
                    }

                    break;
                case 6:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Wprowadz poprawną liczbę");
                    break;

        }
    }




    }
}
