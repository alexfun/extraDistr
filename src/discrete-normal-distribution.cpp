#include <Rcpp.h>
#include "shared.h"
using namespace Rcpp;

/*
* Discrete normal distribution
* 
* Values:
* x
* 
* Parameters
* mu
* sigma > 0
*  
*/


double pmf_dnorm(double x, double mu, double sigma) {
  if (sigma <= 0)
    return NAN;
  if (std::floor(x) != x)
    return 0;
  return R::pnorm(x+1, mu, sigma, true, false) -
         R::pnorm(x, mu, sigma, true, false);
}


// [[Rcpp::export]]
NumericVector cpp_ddnorm(NumericVector x,
                         NumericVector mu, NumericVector sigma,
                         bool log_prob = false) {
  
  int n  = x.length();
  int nm = mu.length();
  int ns = sigma.length();
  int Nmax = Rcpp::max(IntegerVector::create(n, nm, ns));
  NumericVector p(Nmax);
  
  for (int i = 0; i < Nmax; i++)
    p[i] = pmf_dnorm(x[i % n], mu[i % nm], sigma[i % ns]);
  
  if (log_prob)
    for (int i = 0; i < Nmax; i++)
      p[i] = std::log(p[i]);
  
  return p;
}
