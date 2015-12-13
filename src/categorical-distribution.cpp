#include <Rcpp.h>
using namespace Rcpp;


/*
*  Categorical distribution
*
*  Values:
*  x
*
*  Parameters:
*  0 <= p <= 1
*  sum(p) = 1
*
*/


// [[Rcpp::export]]
NumericVector cpp_dcat(NumericVector x, NumericMatrix prob,
                       bool log_prob = false) {
  
  int n  = x.length();
  int np = prob.nrow();
  int Nmax = Rcpp::max(IntegerVector::create(n, np));
  int k = prob.ncol();
  NumericVector p(Nmax);
  
  for (int i = 0; i < Nmax; i++) {
    double p_tot = 0;
    bool wrong_p = false;
    for (int j = 0; j < k; j++) {
      if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
        wrong_p = true;
        break;
      }
      p_tot += prob(i % np, j);
    }
    
    if (p_tot != 1 || wrong_p) {
      p[i] = NAN;
    } else if (x[i] < 1 || x[i] > k || std::floor(x[i]) != x[i]) {
      p[i] = 0;
    } else {
      p[i] = prob(i % np, x[i]-1);
    }
  }

  if (log_prob)
    for (int i = 0; i < Nmax; i++)
      p[i] = std::log(p[i]);
    
    return p;
}


// [[Rcpp::export]]
NumericVector cpp_pcat(NumericVector x, NumericMatrix prob,
                       bool lower_tail = true, bool log_prob = false) {
  
  int n  = x.length();
  int np = prob.nrow();
  int Nmax = Rcpp::max(IntegerVector::create(n, np));
  int k = prob.ncol();
  NumericVector p(Nmax);
  
  for (int i = 0; i < Nmax; i++) {
    if (x[i] < 1) {
      p[i] = 0;
    } else if (x[i] > k) {
      p[i] = 1;
    } else {
      bool wrong_p = false;
      p[i] = 0;
      int j = 0;
      while (j < std::min((int)x[i], k)) {
        if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
          wrong_p = true;
          break;
        }
        p[i] += prob(i % np, j);
        j++;
      }
      double p_tot = p[i];
      while (j < k) {
        if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
          wrong_p = true;
          break;
        }
        p_tot += prob(i % np, j);
        j++;
      }
      if (p_tot != 1 || wrong_p)
        p[i] = NAN;
      
    }
  }

  if (!lower_tail)
    for (int i = 0; i < Nmax; i++)
      p[i] = 1-p[i];
    
  if (log_prob)
    for (int i = 0; i < Nmax; i++)
      p[i] = std::log(p[i]);
      
  return p;
}


// [[Rcpp::export]]
IntegerVector cpp_qcat(NumericVector p, NumericMatrix prob,
                       bool lower_tail = true, bool log_prob = false) {
  
  int n  = p.length();
  int np = prob.nrow();
  int Nmax = Rcpp::max(IntegerVector::create(n, np));
  int k = prob.ncol();
  IntegerVector q(Nmax);
  
  if (log_prob)
    for (int i = 0; i < n; i++)
      p[i] = std::exp(p[i]);
    
  if (!lower_tail)
    for (int i = 0; i < n; i++)
      p[i] = 1-p[i];
    
  for (int i = 0; i < Nmax; i++) {
    if (p[i] < 0 || p[i] > 1) {
      q[i] = NAN;
    } else {
      bool wrong_p = false;
      double cs_prob = 0;
      int j = 0;
      while (cs_prob < p[i] && j < k) {
        if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
          wrong_p = true;
          break;
        }
        cs_prob += prob(i % np, j);
        j++;
      }
      if (p[i] == 0)
        q[i] = 1;
      else
        q[i] = j;
      
      while (j < k) {
        if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
          wrong_p = true;
          break;
        }
        cs_prob += prob(i % np, j);
        j++;
      } 
      if (cs_prob != 1 || wrong_p)
        q[i] = NAN;
    }
  }
      
  return q;
}


// [[Rcpp::export]]
IntegerVector cpp_rcat(int n, NumericMatrix prob) {
  
  double u;
  int np = prob.nrow();
  int k = prob.ncol();
  IntegerVector x(n);

  for (int i = 0; i < n; i++) {
    bool wrong_p = false;
    u = R::runif(0, 1);

    double cs_prob = 0;
    int j = 0;
    while (cs_prob < u && j < k) {
      if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
        wrong_p = true;
        break;
      }
      cs_prob += prob(i % np, j);
      j++;
    }
    x[i] = j;
    
    while (j < k) {
      if (prob(i % np, j) < 0 || prob(i % np, j) > 1) {
        wrong_p = true;
        break;
      }
      cs_prob += prob(i % np, j);
      j++;
    } 
    if (cs_prob != 1 || wrong_p)
      x[i] = NAN;
  }
  
  return x;
}
