#ifndef EDCPP_SHARED_H
#define EDCPP_SHARED_H


// Basic functions

bool tol_equal(double x, double y);
bool isInteger(double x);

// Dealing with Inf

bool anyFinite(Rcpp::NumericVector x);
double finite_max(Rcpp::NumericVector x);

// Standard normal

double phi(double x);
double Phi(double x);
double InvPhi(double x);

// Factorial

double factorial(double x);
double lfactorial(double x);

// Random generation

double rng_unif(); // standard uniform
double rng_bern(double p);
double rng_sign(); // Rademacher distribution

#endif
