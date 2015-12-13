

#' Dirichlet distribution
#'
#' Density function, cumulative distribution function and random generation
#' for the Dirichlet distribution.
#'
#' @param x               \eqn{k}-column matrix of quantiles.
#' @param n	              number of observations. If \code{length(n) > 1},
#'                        the length is taken to be the number required.
#' @param alpha           \eqn{k}-values vector or \eqn{k}-column matrix;
#'                        concentration parameter.
#' @param log     	      logical; if TRUE, probabilities p are given as log(p).
#'
#' @details
#'
#' Probability density function
#' \deqn{
#' f(x) = \frac{\Gamma(\sum_k \alpha_k)}{\prod_k \Gamma(\alpha_k)} \prod_k x_k^{k-1}
#' }{
#' f(x) = \Gamma(sum(\alpha[k])) / prod(\Gamma(\alpha[k])) * prod(x[k]^{k-1})
#' }
#'
#' @references
#' Devroye, L. (1986). Non-Uniform Random Variate Generation. Springer-Verlag.
#'
#' @references
#' \url{http://stats.stackexchange.com/a/57313/35989}
#'
#' @name Dirichlet
#' @aliases Dirichlet
#' @aliases ddirichlet
#' @keywords distribution
#' 
#' @export

ddirichlet <- function(x, alpha, log = FALSE) {
  if (is.vector(alpha))
    alpha <- matrix(alpha, nrow = 1)
  else if (!is.matrix(alpha))
    alpha <- as.matrix(alpha)
  if (is.data.frame(x))
    x <- as.matrix(x)
  .Call('extraDistr_cpp_ddirichlet', PACKAGE = 'extraDistr', x, alpha, log)
}


#' @rdname Dirichlet
#' @export

rdirichlet <- function (n, alpha) {
  if (length(n) > 1) n <- length(n)
  if (is.vector(alpha))
    alpha <- matrix(alpha, nrow = 1)
  else if (!is.matrix(alpha))
    alpha <- as.matrix(alpha)
  .Call('extraDistr_cpp_rdirichlet', PACKAGE = 'extraDistr', n, alpha)
}
