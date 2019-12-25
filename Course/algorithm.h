#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>

/**
Module for FFT
**/
const int mod = 7340033;

/**
Root of 1 in GF(mod)
**/
const int root = 5;

/**
Inverse root of 1 in GF(mod)
**/
const int root_rev = 4404020;

/**
Maximum number degree for FFT
**/
const int root_pw = 1 << 20;

/**
Number of digits for benchmark
**/
const int digits = 10000;

/**
Shift digits for benchmark
**/
const int shift = 6;


/**
Formats the time in millis into a string
@param millis time in milliseconds
@return result of formatting
**/
const std::string time_print(long long millis);

/**
Ñompares two strings
@param first
@param second
@return true if the strings match otherwise false
**/
bool my_strcmp(const char* first, const char* second);

/**
Return maximum of two elements
@param first
@param second
@return Maximum of a and b
**/
inline int max(int first, int second);

/**
Swap two values
@param first
@param second
**/
inline void swap(int& first, int& second);

/**
Calculating the extended Euclidean algorithm for a*x + b*y = 1
@param a
@param b
@param x output parameter
@param y outpur parameter
@return Result of extended Euclidean algorithm and solution of equation
**/
int gcd(int a, int b, int& x, int& y);

/**
Calculating the inverse element modulo m
@param a element for reversing
@param m module
@return Inverse element
**/
int gf_reverse(int a, int m);

/**
Calculating Fast Fourier Transformation
@param data vector for transformation
@param invert direct or invert Fourier transform
**/
void fft(std::vector<int>& data, bool invert);

/**
Calculating multiplication using FFT
@param first
@param second
@param out result of multiplication
**/
void fast_multiply(std::vector<int> first, std::vector<int> second, std::vector<int>& out);

/**
Calculating multiplication using the multiplication in a column
@param first
@param second
@param out result of multiplication
**/
void multiply(std::vector<int> first, std::vector<int> second, std::vector<int>& out);

/**
Print usage and exit
@param path path to running program
**/
void usage(std::string path);

/**
Running benchmark for test speed of multiplication algorithms
**/
void run_benchmark();

/**
Running interactive mode for multiplication using FFT
**/
void run_interactive();