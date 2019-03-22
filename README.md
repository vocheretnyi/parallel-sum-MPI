# parallel-sum-MPI
Implementation of sum of two vectors using MPI.

I've added generated output.csv file with size of vectors, number of processes and run-time.

Here is command to run it, if you use Linux:

```bash
for j in 2 4 8 12 16 24; do for i in `seq 3`; do /usr/bin/mpirun -np $j /your/path/to/project/cmake-build-release/MPI >> output.csv; done done
```
# Results of sum

| Size    | Processes | Run-time |
| ------- |:---------:| --------:|
|200000000|1 |1.3044|
|200000000|1 |1.3092|
|200000000|1 |1.2215|
|200000000|2 |2.3942|
|200000000|2 |2.4517|
|200000000|2 |2.3716|
|200000000|4 |3.2577|
|200000000|4 |2.6539|
|200000000|4 |2.3973|
|200000000|8 |2.3643|
|200000000|8 |2.5601|
|200000000|8 |2.5600|
|200000000|12|2.4458|
|200000000|12|2.5164|
|200000000|12|2.5755|
|200000000|16|3.4011|
|200000000|16|3.2230|
|200000000|16|2.8996|
|200000000|24|3.1183|
|200000000|24|3.1636|
|200000000|24|3.1457|

As you see, we haven't got speed acceleration, parallel version working longer than sequential.
That's because cost of MPI_Gather/MPI_Scatter operations
bigger that cost of sum.

But if we change sum to another function we can get better results of parallel optimizations.
So I choose such function:

```cpp
double f(double a, double b) {
    if (a > b) {
        return sqrt(a) + cbrt(b);
    }
    return cbrt(b) + sqrt(a);
}
```

And now get better results:

# Results of new function

| Size    | Processes | Run-time |
| ------- |:---------:| --------:|
|200000000|1 |10.9111|
|200000000|1 |10.7411|
|200000000|1 |9.9409|
|200000000|2 |8.0377|
|200000000|2 |9.7273|
|200000000|2 |7.4046|
|200000000|4 |5.3152|
|200000000|4 |5.3474|
|200000000|4 |4.8490|
|200000000|8 |3.7550|
|200000000|8 |3.7938|
|200000000|8 |3.5647|
|200000000|12|3.6919|
|200000000|12|4.4344|
|200000000|12|3.4221|
|200000000|16|4.2836|
|200000000|16|3.9359|
|200000000|16|3.9416|
|200000000|24|4.0231|
|200000000|24|3.8237|
|200000000|24|3.8215|

So now we see better results, because new function not so easy, and cost of it
bigger that simple sum.

OS: Ubuntu 16.04.

Processor: Intel® Xeon(R) CPU X5650 @ 2.67GHz × 24.
