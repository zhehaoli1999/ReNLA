# Re: Numerical Linear Algebra

I am Richard from USTC, and I am developing this library for the course "Numerical Linear Algebra" which I am taking this semester.
The textbook we are using is "《数值线性代数》，徐树方，北京大学出版社". 

### Feature
1. Basic `Vec` class for column vectors with basic slicing supported. 
    +  Example: 
    Create a Vec: ``Vec v({1,2,3})``. Slice a Vec: ``v[{1,2}]``. Change a slice of Vec: Use `v.addToSlice` or
    ``v.mulToSlice``.

2. Basic `Matrix` class represented by vector of column `Vec`, with basic slicing supported.
    + Example: Create a Matrix: ``Matrix m({{1,2,3},{4,5,6}})``. 
    Slice a Matrix: Use ``m[1][{0,2}]`` or ``m[{{0,2}, 1}]`` to get the 0-2 entries of column 1. 
    Use ``m[{1,{0,2}}]`` to get 0-2 entries of row 1. Use `m[{{0,2},{1,3}}]` to get sub-matrix of m.

3. Linear system solver, including:
    + LU decomposition
    + Cholesky decomposition
    + Basic gauss elimination 
    + Gauss elimination with column pivot selecting
    + Gauss elimination with Cholesky decomposition for positive definite matrices

4. Basic `Timer` class for speed measurement. 

5. Iterative solver, including:
    + Jacobi iteraton
    + Gauss-Seidel iteration
    + SOR(Successive Over Relaxation) iteration
    + Conjugate gradient iteration 

6. Least square system solver, including:
    + QR decomposition

7. General eigen solver, including:
    + Power method 
    + Implicit QR method

8. Symmetric eigen solver, including:
    + Threshold Jacobi method
    + Binary search method

### Future Features
+ Parallel computing 
+ Performance optimization to make ReNLA elegant and powerful.  

### Note for homework
+ Homework are named `chap$chapterNum$.cpp` with functions named `homework$chapterNum$_$questionNum$` in `src/`;

### Note for test
+ Test codes can be found in `test/` with plenty of test examples.

