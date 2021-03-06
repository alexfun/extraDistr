% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/discrete-normal-distribution.R
\name{DiscreteNormal}
\alias{DiscreteNormal}
\alias{ddnorm}
\alias{pdnorm}
\alias{rdnorm}
\title{Discrete normal distribution}
\usage{
ddnorm(x, mean = 0, sd = 1, log = FALSE)

pdnorm(q, mean = 0, sd = 1, lower.tail = TRUE, log.p = FALSE)

rdnorm(n, mean = 0, sd = 1)
}
\arguments{
\item{x, q}{vector of quantiles.}

\item{mean}{vector of means.}

\item{sd}{vector of standard deviations.}

\item{log, log.p}{logical; if TRUE, probabilities p are given as log(p).}

\item{lower.tail}{logical; if TRUE (default), probabilities are \eqn{P[X \le x]}
otherwise, \eqn{P[X > x]}.}

\item{n}{number of observations. If \code{length(n) > 1},
the length is taken to be the number required.}
}
\description{
Probability mass function, distribution function and random generation
for discrete normal distribution.
}
\details{
Probability mass function

\deqn{
f(x) = \Phi\left(\frac{x-\mu+1}{\sigma}\right) - \Phi\left(\frac{x-\mu}{\sigma}\right)
}{
f(x) = \Phi((x-\mu+1)/\sigma) - \Phi((x-\mu)/\sigma)
}

Cumulative distribution function

\deqn{
F(x) = \Phi\left(\frac{\lfloor x \rfloor + 1 - \mu}{\sigma}\right)
}{
F(x) = \Phi((floor(x)+1-\mu)/\sigma)
}
}
\examples{

x <- rdnorm(1e5, 0, 3)
xx <- -15:15
plot(prop.table(table(x)))
lines(xx, ddnorm(xx, 0, 3), col = "red")
hist(pdnorm(x, 0, 3))
plot(ecdf(x))
xx <- seq(-15, 15, 0.1)
lines(xx, pdnorm(xx, 0, 3), col = "red", lwd = 2, type = "s")

}
\references{
Roy, D. (2003). The discrete normal distribution.
Communications in Statistics-Theory and Methods, 32, 1871-1883.
}
\seealso{
\code{\link[stats]{Normal}}
}
\concept{
Univariate

Discrete
}
\keyword{distribution}
