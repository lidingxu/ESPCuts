Test codes of cutting planes for signomial programming

We develop two kinds of cutting planes for signomial programming: outer approximation cuts and intersection cuts. The cuts and experiments are described in the paper Submodular maximization and its generalization through an intersection cut lens.

The cutting planes are generated in each node of the branch and bound algorithm, and we use SCIP to implement them. Note that the codes are developed in a Linux environment and the building requires the Armadillo library.

There are three benchmarks. In each benchmark file, there are codes and bash files to run the experiments. Before running the code, please build them using an appropriate environment.
