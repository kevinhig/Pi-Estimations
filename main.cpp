/*
    Kevin Higgins 2022
    This program uses different methods to estimate pi and records the times it takes.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <random>
#include <bits/stdc++.h>
#include <string>
using namespace std;

const int PRECISION = 50;

double leibinez(int degree) {
    clock_t start = clock();
    cout << "degree " << degree << " using Leibinez method" << endl;
    double pi = 0.0;
    for(int i = 0; i < degree; i++) {
        pi += pow(-1,i)/(2*i+1);
    }
    clock_t end = clock();
    cout << setprecision(PRECISION) << (double)(end - start) / CLOCKS_PER_SEC << 
         "\nseconds to compute degree " << degree << " using Leibinez method" << endl;
    return pi * 4;
}
double quickLeibinez(int degree) {
    clock_t start = clock();
    cout << "degree " << degree << " using Quick Leibinez method" << endl;
    double pi = 0.0;
    int flip = 1;
    for(int i = 0; i < degree; i++) {
        pi += flip/(2*i+1.0);
        flip = -flip;
    }
    clock_t end = clock();
    cout << setprecision(PRECISION) << (double)(end - start) / CLOCKS_PER_SEC << 
         "\nseconds to compute degree " << degree << " using Quick Leibinez method" << endl;
    return pi * 4;
}
double checkPi(double val) {
    return val - M_PI;
}
double monteCarlo(int degree) {
    clock_t start = clock();
    cout << "degree " << degree << " using Monte Carlo method" << endl;
    double pi  = 0;
    int hit    = 0;
    int miss   = 0;
    double rx, ry;
    uniform_real_distribution<double> gen(-1, 1);
    default_random_engine engine;
    for(int i = 0; i < degree * degree; i++) {
        rx = gen(engine);
        ry = gen(engine);
        if(rx*rx+ry*ry <= 1) {
            hit++;
        }
        miss++;
    }
    clock_t end = clock();
    pi = 4.0 * hit / miss;
    cout << setprecision(PRECISION) << (double)(end - start) / CLOCKS_PER_SEC << 
         "\nseconds to compute degree " << degree << " using Monte Carlo method" << endl;
    return pi;
}
void   rankMethods(int degree) {
    double pi = 0.0;
    double pi1, pi2, pi3;
    ofstream rank;
    rank.open("rankings.txt");
    if(rank.is_open()) {
        rank << setprecision(PRECISION) << "Degree: " << degree << endl;
        clock_t start = clock();
        pi = leibinez(degree);
        pi1 = pi;
        clock_t end = clock();
        rank << "Leibinez: " << pi << "\n";
        rank << "\t" << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
        rank << "\tOff by " << checkPi(pi) << endl;
        start = clock();
        pi = quickLeibinez(degree);
        pi2 = pi;
        end = clock();
        rank << "Quick Leibinez: " << pi << "\n";
        rank << "\t" << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
        rank << "\tOff by " << checkPi(pi) << endl;
        start = clock();
        pi = monteCarlo(degree);
        pi3 = pi;
        rank << "Monte Carlo: " << pi << endl;
        end = clock();
        rank << "\t" << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
        rank << "\tOff by " << checkPi(pi) << endl;
        vector<double> pies;
        pies.push_back(abs(checkPi(pi1)));
        pies.push_back(abs(checkPi(pi2)));
        pies.push_back(abs(checkPi(pi3)));
        sort(pies.begin(), pies.end());
        for(int i = 0; i < 3; i++) {
            rank << "#" << i << " " << pies.at(i) << "\n";
        }
        rank.close();
    }

}

int main(int argc, char* argv[]) {
    string input;
    cout << "Enter degree: ";
    cin >> input;
    rankMethods(stoi(input));
    return 0;
}