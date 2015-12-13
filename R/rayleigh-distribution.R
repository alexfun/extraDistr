

#' Rayleigh distribution
#'
#' Density, distribution function, quantile function and random generation
#' for the Rayleigh distribution.
#'
#' @param x 	            vector of quantiles.
#' @param p	              vector of probabilities.
#' @param n	              number of observations. If \code{length(n) > 1},
#'                        the length is taken to be the number required.
#' @param sigma           parameter.
#' @param log,log.p	      logical; if TRUE, probabilities p are given as log(p).
#' @param lower.tail	    logical; if TRUE (default), probabilities are \eqn{P[X \le x]}
#'                        otherwise, \eqn{P[X > x]}.
#'
#' @details
#'
#' Probability density function
#' \deqn{
#' f(x) = \frac{x}{\sigma^2} \exp\left(-\frac{x^2}{2\sigma^2}\right)
#' }{
#' f(x) = x/\sigma^2 * exp(-(x^2 / 2*\sigma^2))
#' }
#'
#' Cumulative distribution function
#' \deqn{
#' F(x) = 1 - \exp\left(-\frac{x^2}{2\sigma^2}\right)
#' }{
#' F(x) = 1 - exp(-x^2 / 2*\sigma^2)
#' }
#'
#' Quantile function
#' \deqn{
#' F^{-1}(p) = \sqrt{-2\sigma^2 \log(1-p)}
#' }{
#' F^-1(p) = sqrt(-2*\sigma^2 * log(1-p))
#' }
#'
#' @references
#' Krishnamoorthy, K. (2006). Handbook of Statistical Distributions
#' with Applications. Chapman & Hall/CRC.
#'
#' @references
#' Forbes, C., Evans, M. Hastings, N., & Peacock, B. (2011).
#' Statistical Distributions. John Wiley & Sons.
#'
#' @name Rayleigh
#' @aliases Rayleigh
#' @aliases drayleigh
#' @keywords distribution
#'
#' @export

drayleigh <- function(x, sigma = 1, log = FALSE) {
  .Call('extraDistr_cpp_drayleigh', PACKAGE = 'extraDistr', x, sigma, log)
}


#' @rdname Rayleigh
#' @export

prayleigh <- function(x, sigma = 1, lower.tail = TRUE, log.p = FALSE) {
  .Call('extraDistr_cpp_prayleigh', PACKAGE = 'extraDistr', x, sigma, lower.tail, log.p)
}


#' @rdname Rayleigh
#' @export

qrayleigh <- function(p, sigma = 1, lower.tail = TRUE, log.p = FALSE) {
  .Call('extraDistr_cpp_qrayleigh', PACKAGE = 'extraDistr', p, sigma, lower.tail, log.p)
}


#' @rdname Rayleigh
#' @export

rrayleigh <- function(n, sigma = 1) {
  if (length(n) > 1) n <- length(n)
  .Call('extraDistr_cpp_rrayleigh', PACKAGE = 'extraDistr', n, sigma)
}