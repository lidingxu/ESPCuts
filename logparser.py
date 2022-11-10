import pandas as pd
from enum import Enum
import os
import csv
import shutil
import numpy as np
import math 
import matplotlib.pyplot as plt

class ProblemType(Enum):
    Discrete = 0
    Continuous = 1



df = pd.read_csv('data/instancedata.csv', sep=';')

osil_dir_path = os.getcwd() + "/data/osil"
continuous_dir_path = os.getcwd() + "/data/Continuous"
discrete_dir_path = os.getcwd() + "/data/Discrete"

continuous_log_path = os.getcwd() + "/logs/Continuous"
discrete_log_path = os.getcwd() + "/logs/Discrete"



def extract_scip(entry_, file_path):
    ls = open(file_path).readlines()
    #print(ls)
    #print(file)
    stat_keys = ["Total Time",  "Gap", "Dual Bound", "First LP value", "sepa_signomial", "solving"]
    stat_dict = {}
    entry = entry_
    for l in ls:
        for stat_key in stat_keys:
            if  l.split(":")[0].strip() == stat_key:
                stat_dict[stat_key] = l
    #print(stat_dict["Dual Bound"].split()[2])
    if "Total Time" not in stat_dict  or "First LP value" not in stat_dict:
        entry["total_time"] = float("NAN")
        entry["dualbound"] = float("NAN")
        entry["FirstLP"] = float("NAN")
        entry["noLP"] = True
        entry["affected"] = False
        entry["epa_signomial"] = 0
        return entry
    entry["total_time"] = float(stat_dict["Total Time"].split()[3])
    #print(entry["instance"])
    #print(stat_dict["sepa_signomial"].split())
    #entry["primal_bound"] = float(stat_dict["Primal Bound"].split()[3])
    entry["dualbound"] = float("NAN") if stat_dict["Dual Bound"].split()[3] == "-" else float(stat_dict["Dual Bound"].split()[3])
    entry["noLP"] = True if stat_dict["First LP value"].split()[4] == "-" else False
    entry["FirstLP"] =   float("NAN")  if stat_dict["First LP value"].split()[4] == "-" else float(stat_dict["First LP value"].split()[4])
    entry["affected"] =   int(stat_dict["sepa_signomial"].split()[7]) > 0 
    entry["ncuts"] =  int(stat_dict["sepa_signomial"].split()[7]) 
    entry["solving"] = float(stat_dict["solving"].split()[2])
    entry["rel_gap"] = float(float("NAN") if stat_dict["Gap"].split()[2] == "infinite" else stat_dict["Gap"].split()[2]) #float(stat_dict["Gap"].split()[2])
    return entry





discrete_set=[]
continuous_set=[]
discrete_df = pd.DataFrame()
continuous_df = pd.DataFrame()
discrete_rows = []
continuous_rows  = []
ct_total = 0
ct_d = 0
ct_c = 0
for row_ind in range(len(df)):
    row = df.iloc[row_ind]

    if row["convex"] == True:
        continue

    #print("null", row["primalbound"])
    continous_var = row["probtype"] in ["NLP"]
    discrete_var = row["probtype"] in ["MBNLP", "MINLP", "BNLP", "INLP"]
    has_sigfunc = row["npolynomfunc"] > 0 or row["nsignomfunc"] > 0
    has_primal = not pd.isna(row["primalbound"])
    if continous_var and has_sigfunc and has_primal:
        #print(row["nsignomfunc"], row["probtype"], "continuous")
        continuous_df = continuous_df.append(row)
        continuous_set.append(row["name"])
        continuous_rows.append(row)
        ct_total += 1
        ct_c += 1
    elif discrete_var and has_sigfunc and has_primal:
        #print(row["nsignomfunc"], row["probtype"], "discrete")
        discrete_df = discrete_df.append(row)
        discrete_set.append(row["name"])
        discrete_rows.append(row)
        ct_total += 1
        ct_d += 1
    else:
        continue



def SGM(lst, total, bias):
    return np.exp(np.sum([np.log(ele + bias) for ele in lst ]) / total) - bias

def Stat(name):
    return {"setting": name, "solved": 0, "closed": 0, "closed_lst": [], "ncuts": 0, "ncuts_lst" : [], "total_time": 0.0, "total": 0} 




clogs = os.listdir(continuous_log_path)
dlogs = os.listdir(discrete_log_path)

details = ""

settings = ["default", "icuts", "supcuts", "lcpcuts"]

banks = {"default": [], "icuts": [], "supcuts" : [], "lcpcuts": []}

stats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}

affectstats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}


dstats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}

daffectstats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}

allstats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}

allaffectstats = {"default": Stat("default"), "icuts": Stat("icuts"), "supcuts": Stat("supcuts"), "lcpcuts": Stat("lcpcuts")}


def add(stat, entry):
    #print(stat, entry, entry["closed"] is float("nan"))
    if math.isnan(entry["closed"]):
        return
    #print(entry)
    stat["solved"] += entry["issolved"] 
    stat["total"] += 1
    stat["ncuts_lst"].append(entry["ncuts"])
    stat["closed_lst"].append(entry["closed"])
    stat["total_time"] += entry["total_time"] 

def avgStat(stat):
    stat["closed"] /=  stat["total"]
    stat["total_time"] /= stat["total_time"]
    stat["closed"] = SGM(stat["closed_lst"], stat["total"], 1)
    stat["ncuts"] = SGM(stat["ncuts_lst"], stat["total"], 1)

#nolp = ["saa_2","truck", "fct", "transswitch2736spr", "blendgap"]
nolp = []

for log in clogs:
    instance = log.split(".nl")[0]
    setting =  log.split("_")[-1].strip()[0:-4] 
    entry={}
    entry["instance"] = instance
    entry["setting"] = setting
    entry["iscontinuous"] = True
    entry = extract_scip(entry, continuous_log_path + "/"+log)
    banks[setting].append(entry)
    if entry["setting"] == "default" and entry["noLP"]:
        nolp.append(entry["instance"])
    #print(entry)

for log in dlogs:
    instance = log.split(".nl")[0]
    setting =  log.split("_")[-1].strip()[0:-4] 
    entry={}
    entry["instance"] = instance
    entry["setting"] = setting
    entry["iscontinuous"] = False
    entry = extract_scip(entry, discrete_log_path + "/"+log)
    banks[setting].append(entry)
    if entry["setting"] == "default" and entry["noLP"]:
        nolp.append(entry["instance"])
    #print(entry)


print(nolp)


def parse_name(name):
    s = ""
    for c in name:
        if c == "_":
            s += "\_"
        else:
            s +=c
    return s
fullaffect  = []
for ind, rows in enumerate([continuous_rows, discrete_rows]):
    for row in rows:
        instance = row["name"]
        if instance in nolp:
            continue
        primal = row["primalbound"]    
        dual = row["dualbound"]
        #print(instance, primal, dual)
        defaultdual =  float("NAN")
        nodual  = 0 
        for entry in banks["default"]:
            if entry["instance"] == instance:
                defaultdual = entry["FirstLP"]
        if defaultdual ==  float("NAN"):
            nolp.append(entry["instance"])
            continue
        for setting in settings:
            for entry in banks[setting]:
                if entry["instance"] == instance and entry["dualbound"] == float("NAN"):
                    nodual += 1
                    continue
        if nodual == 3:
            nolp.append(entry["instance"])
            continue
        isaffteced = 0
        for setting in settings:
            if setting == "default":
                continue
            for entry in banks[setting]:
                if entry["instance"] == instance and entry["affected"]:
                    isaffteced += 1
                    break
        numadded = 0
        tmp_detail = str(parse_name(row["name"])) +  " & " +  ("\\textbf{C}"if ind == 0 else "\\textbf{MI}") + " & " +  str(row["nsignomfunc"]) + " & " + str(row["npolynomfunc"])
        for setting in settings:
            for entry in banks[setting]:
                if entry["instance"] == instance:
                    #if  setting == "default":
                    #    closed = 0
                    #elif abs(primal - defaultdual ) < 1e-9:
                    #    closed = 100
                    #else:
                    if instance == "gear4":
                        print(setting, instance)
                    if abs(primal - defaultdual ) < 1e-6:
                        closed = 1
                    else:
                        closed = (entry["dualbound"] - defaultdual) / (primal - defaultdual ) 
                        if closed > 1:
                            #detail += " & " + str(entry["solving"]) + " & " + str(float("NAN")) + " & " + str(entry["sepa_signomial"])
                            continue
                    if instance == "gear4":
                        print(setting, instance)
                    entry["closed"] =   min(closed, 1)
                    entry["issolved"] = 1 if  entry["rel_gap"] < 1e-4  else 0
                    #print(entry["setting"], closed, defaultdual, entry["dualbound"], primal)# entry["dualbound"])
                    #if dstats[setting]["closed"] is float("NAN"):
                    #print(instance, dstats[setting])
                    #detail += " & " + str(round(entry["solving"], 1)) + " & " + str(round(entry["closed"],1)) + " & " + str(entry["sepa_signomial"])
                    tmp_detail += " & " + str(round(entry["solving"], 1)) + " & " + str(round(entry["closed"],2)) + " & " + str(entry["ncuts"])
                    #if instance == "gear4":
                    #    print(setting, entry, str(round(entry["solving"], 1)) + " & " + str(round(entry["closed"],1)) + " & " + str(entry["sepa_signomial"]))
                    add(allstats[setting], entry)
                    if isaffteced > 0:
                        numadded+=1
                        add(allaffectstats[setting], entry)
                    if entry["iscontinuous"]:
                        add(stats[setting], entry)
                        if isaffteced > 0:
                            add(affectstats[setting], entry)
                        break
                    else:
                        add(dstats[setting], entry)
                        if isaffteced > 0:
                            add(daffectstats[setting], entry)
                        break   
        #print(instance, " ", tmp_detail)
        details += tmp_detail + "\\\\" + "\n"   
        isfullaffect = isaffteced == 3 and numadded == 4
        if isfullaffect:
            fullaffect.append(instance)

file = open("details.txt", "w")
file.write(details)
file.close()
#print(details)
printrow1 = ""
#print(stats)
for setting in settings:
    avgStat(stats[setting])
    #print(stats[setting], affectstats[setting])
    printrow1 += str(stats[setting]["solved"]) + "/" + str(stats[setting]["total"]) + "&" + str(round(stats[setting]["closed"],2)) + "&" 
    printrow1 +=  (str(round(stats[setting]["closed"]/stats["default"]["closed"],2)) + "&" + str(round(stats[setting]["ncuts"],0)) + "&" ) if setting != "default" else ""  

print(printrow1)


printrow2 = ""
for setting in settings:
    avgStat(affectstats[setting])
    printrow2 += str(affectstats[setting]["solved"]) + "/" + str(affectstats[setting]["total"]) + "&" + str(round(affectstats[setting]["closed"],2)) + "&" 
    printrow2 +=  (str(round(affectstats[setting]["closed"]/affectstats["default"]["closed"],2)) + "&" + str(round(affectstats[setting]["ncuts"],0)) + "&") if setting != "default" else ""  

print(printrow2)

#print(dstats, daffectstats)
printrow1 = ""
#print(dstats)
for setting in settings:
    avgStat(dstats[setting])
    printrow1 += str(dstats[setting]["solved"]) + "/" + str(dstats[setting]["total"]) + "&" + str(round(dstats[setting]["closed"],2)) + "&"  
    printrow1 +=  (str(round(dstats[setting]["closed"]/dstats["default"]["closed"],2)) + "&"  + str(round(dstats[setting]["ncuts"],0)) + "&") if setting != "default" else ""


print(printrow1)


printrow2 = ""
for setting in settings:
    avgStat(daffectstats[setting])
    printrow2 += str(daffectstats[setting]["solved"]) + "/" + str(daffectstats[setting]["total"]) + "&" + str(round(daffectstats[setting]["closed"],2)) + "&"  
    printrow2 +=  (str(round(daffectstats[setting]["closed"]/daffectstats["default"]["closed"],2)) + "&" + str(round(daffectstats[setting]["ncuts"],0)) + "&") if setting != "default" else "" 

print(printrow2)


printrow1 = ""
#print(dstats)
for setting in settings:
    avgStat(allstats[setting])
    printrow1 += str(allstats[setting]["solved"]) + "/" + str(allstats[setting]["total"]) + "&" + str(round(allstats[setting]["closed"],2)) + "&"  
    printrow1 +=  (str(round(allstats[setting]["closed"]/allstats["default"]["closed"],2)) + "&" + str(round(allstats[setting]["ncuts"],0)) + "&") if setting != "default" else ""


print(printrow1)


printrow2 = ""
for setting in settings:
    avgStat(allaffectstats[setting])
    printrow2 += str(allaffectstats[setting]["solved"]) + "/" + str(allaffectstats[setting]["total"]) + "&" + str(round(allaffectstats[setting]["closed"],2)) + "&" 
    printrow2 +=  (str(round(allaffectstats[setting]["closed"]/allaffectstats["default"]["closed"],2)) + "&" +  str(round(allaffectstats[setting]["ncuts"],0)) + "&") if setting != "default" else ""

print(printrow2)


data=  {"default": [], "icuts": [], "supcuts": [], "lcpcuts": []}
for instance in fullaffect:
    for setting in settings:
        for entry in banks[setting]:
            if entry["instance"] == instance:
                data[setting].append(entry["closed"])


fig, axes = plt.subplots(nrows=3, ncols=2, figsize=(10, 9))  # define the figure and subplots


axes[0,0].scatter(data["default"], data["icuts"], color = 'blue', marker = '+')
axes[0,0].plot(data["default"], data["default"], color = 'green')
axes[0,0].set_xlabel('Default')
axes[0,0].set_ylabel('ICUT')


axes[0,1].scatter(data["default"], data["supcuts"], color = 'blue', marker = '+')
axes[0,1].plot(data["default"], data["default"], color = 'green')
axes[0,1].set_xlabel('Default')
axes[0,1].set_ylabel('SOCUT')

axes[1,0].scatter(data["default"], data["lcpcuts"], color = 'blue', marker = '+')
axes[1,0].plot(data["default"], data["default"], color = 'green')
axes[1,0].set_xlabel('Default')
axes[1,0].set_ylabel('POCUT')

axes[1,1].scatter(data["icuts"], data["supcuts"], color = 'blue', marker = '+')
axes[1,1].plot(data["icuts"], data["icuts"], color = 'green')
axes[1,1].set_xlabel('ICUT')
axes[1,1].set_ylabel('SOCUT')


axes[2,0].scatter(data["icuts"], data["lcpcuts"], color = 'blue', marker = '+')
axes[2,0].plot(data["icuts"], data["icuts"], color = 'green')
axes[2,0].set_xlabel('ICUT')
axes[2,0].set_ylabel('POCUT')

axes[2,1].scatter(data["supcuts"], data["lcpcuts"], color = 'blue', marker = '+')
axes[2,1].plot(data["supcuts"], data["supcuts"], color = 'green')
axes[2,1].set_xlabel('SOCUT')
axes[2,1].set_ylabel('POCUT')






fig.tight_layout()
plt.savefig('scatter.pdf') 
