# parallel-sum-MPI
Implementation of sum of two vectors using MPI

Also I've added generated output.csv file with size of vectors, number of processes and run-time.

```bash
for j in 2 4 8 12 16 24; do for i in `seq 3`; do /usr/bin/mpirun -np $j /your/path/to/project/cmake-build-release/MPI >> output.csv; done done
```
# Results

| Size        | Processes           | Run-time  |
| ------------- |:-------------:| -----:|
|200000000|2|2.3942|
|200000000|2|2.4517|
|200000000|2|2.3716|
|200000000|4|3.2577|
|200000000|4|2.6539|
|200000000|4|2.3973|
|200000000|8|2.3643|
|200000000|8|2.5601|
|200000000|8|2.5600|
|200000000|12|2.4458|
|200000000|12|2.5164|
|200000000|12|2.5755|
|200000000|16|3.4011|
|200000000|16|3.2230|
|200000000|16|2.8996|
|200000000|24|3.1183|
|200000000|24|3.1636|
|200000000|24|3.1457|
