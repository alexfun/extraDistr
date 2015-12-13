#include <Rcpp.h>
using namespace Rcpp;


/*
 *  Generalized extreme value distribution
 *
 *  Values:
 *  x
 *
 *  Parameters:
 *  mu
 *  sigma > 0
 *  xi
 *
 *  z = (x-mu)/sigma
 *  where 1+xi*z > 0
 *
 *  f(x)    = { 1/sigma * (1-xi*z)^{-1-1/xi} * exp(-(1-xi*z)^{-1/xi})     if xi != 0
 *            { 1/sigma * exp(-z) * exp(-exp(-z))                         otherwise
 *  F(x)    = { exp(-(1+xi*z)^{1/xi})                                     if xi != 0
 *            { exp(-exp(-z))                                             otherwise
 *  F^-1(p) = { mu - sigma/xi * (1 - (-log(1-p))^xi)                      if xi != 0
 *            { mu - sigma * log(-log(1-p))                               otherwise
 *
 */

double pdf_gev(double x, double mu, double sigma, double xi) {
  if (sigma <= 0)
    return NAN;
  double z = (x-mu)/sigma;
  if (1+xi*z > 0) {
    if (xi != 0)
      return 1/sigma * std::pow(1+xi*z, -1-(1/xi)) * std::exp(-std::pow(1+xi*z, -1/xi));
    else
      return 1/sigma * std::exp(-z) * std::exp(-std::exp(-z));
  } else {
    return 0;
  }
}

double cdf_gev(double x, double mu, double sigma, double xi) {
  if (sigma <= 0)
    return NAN;
  double z = (x-mu)/sigma;
  if (1+xi*z > 0) {
    if (xi != 0)
      return std::exp(-std::pow(1+xi*z, -1/xi));
    else
      return std::exp(-std::exp(-z));
  } else {
    return 0;
  }
}

double invcdf_gev(double p, double mu, double sigma, double xi) {
  if (sigma <= 0 || p < 0 || p > 1)
    return NAN;
  if (xi != 0)
    return mu - sigma/xi * (1 - std::pow(-std::log(1-p), -xi));
  else
    return mu - sigma * std::log(-std::log(1-p));
}


// [[Rcpp::export]]
NumericVector cpp_dgev(NumericVector x,
                       NumericVector mu, NumericVector sigma, NumericVector xi,
                       bool log_prob = false) {

  double z;
  int n  = x.length();
  int nm = mu.length();
  int ns = sigma.length();
  int nx = xi.length();
  int Nmax = Rcpp::max(IntegerVector::create(n, nm, ns, nx));
  NumericVector p(Nmax);

  for (int i = 0; i < Nmax; i++)
    p[i] = pdf_gev(x[i % n], mu[i % nm], sigma[i % ns], xi[i % nx]);

  if (log_prob)
    for (int i = 0; i < Nmax; i++)
      p[i] = std::log(p[i]);

  return p;
}


// [[Rcpp::export]]
NumericVector cpp_pgev(NumericVector x,
                       NumericVector mu, NumericVector sigma, NumericVector xi,
                       bool lower_tail = true, bool log_prob = false) {

  double z;
  int n  = x.length();
  int nm = mu.length();
  int ns = sigma.length();
  int nx = xi.length();
  int Nmax = Rcpp::max(IntegerVector::create(n, nm, ns, nx));
  NumericVector p(Nmax);

  for (int i = 0; i < Nmax; i++)
    p[i] = cdf_gev(x[i % n], mu[i % nm], sigma[i % ns], xi[i % nx]);

  if (!lower_tail)
    for (int i = 0; i < Nmax; i++)
      p[i] = 1-p[i];

  if (log_prob)
    for (int i = 0; i < Nmax; i++)
      p[i] = std::log(p[i]);

  return p;
}


// [[Rcpp::export]]
NumericVector cpp_qgev(NumericVector p,
                       NumericVector mu, NumericVector sigma, NumericVector xi,
                       bool lower_tail = true, bool log_prob = false) {

  int n  = p.length();
  int nm = mu.length();
  int ns = sigma.length();
  int nx = xi.length();
  int Nmax = Rcpp::max(IntegerVector::create(n, nm, ns, nx));
  NumericVector q(Nmax);

  if (log_prob)
    for (int i = 0; i < n; i++)
      p[i] = std::exp(p[i]);

  if (!lower_tail)
    for (int i = 0; i < n; i++)
      p[i] = 1-p[i];

  for (int i = 0; i < Nmax; i++)
    q[i] = invcdf_gev(p[i % n], mu[i % nm], sigma[i % ns], xi[i % nx]);

  return q;
}


// [[Rcpp::export]]
NumericVector cpp_rgev(int n,
                       NumericVector mu, NumericVector sigma, NumericVector xi) {

  double u;
  int nm = mu.length();
  int ns = sigma.length();
  int nx = xi.length();
  NumericVector x(n);

  for (int i = 0; i < n; i++) {
    u = R::runif(0, 1);
    x[i] = invcdf_gev(u, mu[i % nm], sigma[i % ns], xi[i % nx]);
  }

  return x;
}
