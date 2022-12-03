# Cutting Planes for Extended Formulation of Signomial Programming

Three cutting planes for approximating graphs of signomial terms, arising in an extended formulation of 
Signomial Programming (SP). These cuts include: intersection cuts, supermodular outer approximation cuts, and projected outer approximation cuts. These cuts are implemented in  the global optimization solver [SCIP](https://www.scipopt.org/).

## Installation
Require `Cmake`, `SCIP` (version >= 8.0.0), and a POSIX style build environment. 

Enter the `build` directory, and execute the following command:
```
cmake .. -DCMAKE_BUILD_TYPE=[Release, Debug] -DSCIP_DIR=[path/to/yourscip/build]
make
```

This will procude a binary executable called `misp`.

## Setting files
In `setting` directory, there are four SCIP's setting files:
* `default.set`: SCIP's default setting with time limit set to 3600 CPU seconds and node limit set to 1;
* `icuts.set`: intersection cuts are enabled;
* `lcpcuts.set`: projected outer approximation cuts are enabled.;
* `supcuts.set`: supermodular outer approximation cuts are enabled.

Modify a setting file to obtain desired parameter setting, e.g., change node limit to enable a full branch-and-bound experiment.

## Benchmark and Test
In `benchmark` directory, there are two subdirectories `Continuous` and `Discrete` of [MINLPLib](https://www.minlplib.org/) instances. `Continuous` contains MINLP instances with signomial terms, and `Discrete` contains MINLP instances with signomial terms.

Run the bash script `runtest.sh` to reproduce all computational results in the draft paper:
```
/bin/bash runtest.sh
```
If you want to use GNU Parallel to run tests parallelly, make sure that you haved installed it and set `gnuparalleltest=1`.


## Example usage

Execute `misp`:
```
./misp
```
Load a setting file:
```
set load xxx.set
```
Read an instance in `benchmark`
```
read xx.nl
```
Optimize:
```
optimize
```


## References

If you find our codes useful in your work, we kindly request that you cite the following paper draft, which is recommended reading for advanced users:

