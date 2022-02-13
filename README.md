# SPL-1
The repository containing all the documentation of SPL-1

#Project Information:
There are several approaches which can be used to factorize a matrix. Multiplicative updates is one such way. 
For a non-negative matrix V, let W and H be its two factors. The dimension of W and H(Their column number k) is user defined. We initialize the matrices using gaussian distribution and then the matrices are multiplied.
Using Frobenius norm we calculate the error. If the error is above a certain threshold we continously use multiplicative updates to converge towards the original solution.

#Task done so far:
1. Initializing two matrices using Gaussian distribution.
2. Multiplying the two matrices.
3. Added a cost function
4. Changed the rng from standard normal to normal distribution with specific sigma and mu values



