# Test codes of cutting planes for signomial programming

We develop two kinds of cutting planes for signomial  programming: outer approximation cuts and intersection cuts.
The cuts and experiments are described in the paper [Cutting planes for signomial programming](https://arxiv.org/abs/2212.02857). 

The cutting planes are generated in each node of the branch and bound algorithm, and we use [SCIP](https://www.scipopt.org/) to implement them. Note that the codes are developed in a Linux environment. Before running the code, please build them using an appropriate environment. The outer approximation cuts are integrated in a new version of [SCIP9](https://scipopt.org/doc-9.0.0/html/RN90.php).

The benchmark contains selected instances from MINLPLib (which have signomial terms). There is a bash file to run the experiments. 
