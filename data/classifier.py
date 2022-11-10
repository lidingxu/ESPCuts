import pandas as pd
from enum import Enum
import os
import csv
import shutil

class ProblemType(Enum):
    Discrete = 0
    Continuous = 1



df = pd.read_csv('instancedata.csv', sep=';')







def Stat(name):
    return {"name": name, "problem_type": ProblemType.Continuous}


discrete_set=[]
continuous_set=[]
discrete_benchmark = []
discrete_df = pd.DataFrame()
continuous_benchmark = []
continuous_df = pd.DataFrame()
ct_total = 0
ct_d = 0
ct_c = 0
for row_ind in range(len(df)):
    row = df.iloc[row_ind]

    row_stat =  Stat(row["name"])

    if row["convex"] == True:
        continue

    if row["name"] == "ex8_4_4":
        print( row["nsignomfunc"],  row["nsignomcons"])

    continous_var = row["probtype"] in ["NLP"]
    discrete_var = row["probtype"] in ["MBNLP", "MINLP", "BNLP", "INLP"]
    has_sigfunc = row["npolynomfunc"] > 0 or row["nsignomfunc"] > 0
    has_primal = not pd.isna(row["primalbound"])
    if continous_var and has_sigfunc and has_primal:
        #print(row["nsignomfunc"], row["probtype"], "continuous")
        continuous_benchmark.append(row_stat)
        continuous_df = continuous_df.append(row)
        continuous_set.append(row["name"])
        ct_total += 1
        ct_c += 1
        row_stat["problem_type"] = ProblemType.Continuous
    elif discrete_var and has_sigfunc and has_primal:
        #print(row["nsignomfunc"], row["probtype"], "discrete")
        discrete_benchmark.append(row_stat)
        discrete_df = discrete_df.append(row)
        discrete_set.append(row["name"])
        ct_total += 1
        ct_d += 1
        row_stat["problem_type"] = ProblemType.Discrete
    else:
        continue

nl_dir_path = os.getcwd() + "/minlplib/nl"
continuous_dir_path = os.getcwd() + "/Continuous"
discrete_dir_path = os.getcwd() + "/Discrete"
nl_instances = os.listdir(nl_dir_path)
nl_instances =  sorted(nl_instances)


#print(nl_instances)
#print(continuous_set)

print(ct_total, ct_c, ct_d)
copy = True
if copy:

    # copy nonconvex nl, mod instance to discrete/continuous set
    for nl_instance in nl_instances:
        if nl_instance[-2:] != "nl":
            continue
        #print(nl_instance[-2:])
        #print(nl_instance[:-2])
        if nl_instance[:-3] in continuous_set:
            #try:
            shutil.copy2(nl_dir_path + "/" + nl_instance, continuous_dir_path )
            #except Exception as e:
                #print(e)
                #continue
        elif nl_instance[:-3] in discrete_set:
            #try:
            shutil.copy2(nl_dir_path + "/" + nl_instance, discrete_dir_path )
            #except Exception as e:
                #print(e)
                #continue 
    # write dataframes and benchmarks
    discrete_df.to_csv("MixedSignomial.csv")
    continuous_df.to_csv("Signomial.csv")

