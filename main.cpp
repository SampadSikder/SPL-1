#include <iostream>
#include "matrix_factorizations.h"

int main()
{
    printf("Welcome to matrix factorization!\n");
    printf("1. Matrix factorization using Gradient descent\n");
    printf("2. Matrix factorization using Kullback-Leibler divergence\n");
    printf("3. Matrix factorization using Weighted matrix without regularization\n");
    printf("4. Matrix factorization using Weighted matrix with regularization\n");
    printf("5. Derivative of a matrix\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("You have chosen Gradient descent\n");
        gradientDescent();
        break;
    case 2:
        printf("You have chosen Kullback-Leibler divergence\n");
        kullbackLeibler();
        break;
    case 3:
        printf("You have chosen Weighted matrix without regularization\n");
        weightedMatrix();
        break;
    case 4:
        printf("You have chosen Weighted matrix with regularization\n");
        regularizedMatrix();
        break;

    case 5:
        printf("You have chosen Derivative of a matrix\n");
        derivative();
        break;
    case 6:
        break;
    }
    // kullbackLeibler();
    //  regularizedMatrix();
    //  weightedMatrix();
    //   gradientDescent();
}