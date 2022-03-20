# The k-nearest neighbors (KNN) algorithm

A simple k-nn algorithm with 4 numeric and 1
decision parameter

## Program arguments

1: k  
2: Training set(CVS)  
3: Test set(CVS)

```bash
0 TreningSet.cvs TestCase.cvs
```

## Examples

TrainingSet.cvs
```bash
5.1,3.3,1.7,0.5,Iris-setosa
```
TestSet.cvs
```bash
5.2,3.5,1.5,0.2,UNDEFIEND
```



## Supplement

If "k" as start parameter is 0, it will be redefined to standard case (3)  
If "k" as start parameter is greater than the number of training cases , it will be redefinedto the number of training data (N)
