import pandas as pd
from enum import Enum
import os
import csv
import shutil
import numpy as np
import math 
import matplotlib.pyplot as plt


df = pd.read_csv('data/instancedata.csv', sep=';')

prb_rows = {}
ct_total = 0
for row_ind in range(len(df)):
    row = df.iloc[row_ind]

    if row["convex"] == True:
        continue

    has_sigfunc = row["npolynomfunc"] > 0 or row["nsignomfunc"] > 0
    has_primal = not pd.isna(row["primalbound"])
    if has_sigfunc and has_primal:
        prb_rows[row["name"]] = row
        ct_total += 1


MAXTIME = 3600.00
def extract_scip(entry_, file_path):
    ls = open(file_path).readlines()
    stat_keys = ["Total Time",  "Gap", "nodes (total)", "signomial", "Primal Bound", "Dual Bound"]
    stat_dict = {}
    entry = entry_
    for l in ls:
        for stat_key in stat_keys:
            if  l.split(":")[0].strip() == stat_key:
                stat_dict[stat_key] = l
    if "Total Time" not in stat_dict:
        entry["total_time"] = float("NAN")
        entry["gap"] = float("NAN")
        entry["nodes"] = float("NAN")
        return entry
    entry["total_time"] = min(MAXTIME, float(stat_dict["Total Time"].split()[3]))
    entry["nodes"] = float(stat_dict["nodes (total)"].split()[3])
    entry["gap"] = 100.0 if stat_dict["Gap"].split()[2] == "infinite" else min(float(stat_dict["Gap"].split()[2]), 100.0)
    if entry["gap"] > 100.0:
        print(stat_dict)
    entry["solved"] = 1 if entry["gap"] < 1e-4 else 0
    if "signomial" not in stat_dict:
        entry["affected"] = 0
    else:
        entry["affected"] = 1 if int(stat_dict["signomial"].split()[13]) > 0 else 0

    if stat_dict["Primal Bound"].split()[3] == "infeasible":
        entry["feasible"] = False 
        entry["primalbound"] = float("NAN")
    else:
        entry["feasible"] = True 
        entry["primalbound"] = float("NAN") if stat_dict["Primal Bound"].split()[3] == "infinite" or stat_dict["Primal Bound"].split()[3] == "-" or stat_dict["Primal Bound"].split()[3] == "unbounded" else float(stat_dict["Primal Bound"].split()[3])
    entry["dualbound"] = float("NAN") if stat_dict["Dual Bound"].split()[3] == "infinite" or stat_dict["Dual Bound"].split()[3] == "-" else float(stat_dict["Dual Bound"].split()[3])
    return entry


log_path = os.getcwd() + "/logs/All"
logs = os.listdir(log_path)
exclude = ["ann_fermentation_tanh", "t1000", "saa_2", "hadamard_9"]

entries = []


for log in logs:
    log_ = log
    log = log[0:-4]
    setting = log.split("_")[-1]
    instance = log.split(".")[0]
    if instance in exclude:
        continue
    entry={}
    entry["instance"] = instance
    entry["setting"] = setting
    entry = extract_scip(entry, log_path + "/"+log_)
    entries.append(entry)

entries.sort(key=lambda x: x.get("instance") + x.get("setting"))

iscomp = False
instances = set()
for entry in entries:
    instance = entry["instance"]
    instances.add(instance)
    print(entry)
    if iscomp:
        row = prb_rows[instance]
        #print(instance, " ", row["name"])
        if row["name"] == instance:
            if row["primalbound"] != "nan" and not entry["feasible"]:
                print(entry, " 1 ", row["primalbound"], " ", row["dualbound"])
            elif entry["dualbound"] > row["primalbound"] + 1e-2:
                print(entry, " 2 ", row["primalbound"], " ", row["dualbound"])
            elif entry["instance"] == "hda":
                print(entry, " 3 ", row["primalbound"], " ", row["dualbound"])

alls = set()
affecteds = set()
affecteds_core = set()
for entry in entries:
    if entry["affected"] == 1:
        affecteds.add(entry["instance"])
        for entry_ in entries:
            if entry_["instance"] == entry["instance"] and entry_["setting"] == "disablesig" and entry_["total_time"] > 500:
                affecteds_core.add(entry_["instance"])
    else:
        alls.add(entry["instance"])
maps = [alls, affecteds, affecteds_core]

print(len(alls), " ", len(affecteds), " ", len(affecteds_core))



display_keys = ["setting", "solved", "affected", "nodes", "total_time", "gap"]
total_keys = ["solved"]
avg_keys = ["nodes", "total_time", "gap"]
avg_bias = {"gap": 1.0, "nodes": 100.0, "total_time": 1.0}


def classdata():
    return {"total": 0, "solved": 0,  "affected": 0, "gap":[0.0, []], "nodes":[0.0, []], "total_time":[0.0, []]} 

def checklst(lst):
    for ele in lst:
        if ele > 101.0:
            return False
    return True

def SGM(lst, total, bias):
    return np.exp(np.sum([np.log(ele + bias) for ele in lst ]) / total) - bias

def isinsclass(sclass, entry):
    if sclass[0] - 1e-3 <= entry["total_time"] and sclass[1] + 1e-3 > entry["total_time"] and  entry["instance"] in maps[sclass[2]]:
        return True
    else:
        return False


class Stat:
    def __init__(self, setting, sclasses):
        self.sclassdata = {}
        self.setting = setting
        self.sclasses = sclasses
        for sclass in sclasses:
            self.sclassdata[sclass] = classdata()

    def add_entry(self, entry):
        #print(entry)
        for sclass in self.sclasses:
            if isinsclass(sclass, entry):
                self.sclassdata[sclass]["total"] += 1
                self.sclassdata[sclass]["solved"] += entry["solved"]
                self.sclassdata[sclass]["affected"] += entry["affected"]
                for avg_key in avg_keys:
                    self.sclassdata[sclass][avg_key][1].append(entry[avg_key])    
                #print(self.sclassdata[sclass])

    def avg(self):
        for sclass in self.sclasses:
            for avg_key in avg_keys:
                self.sclassdata[sclass][avg_key][0] =  SGM(self.sclassdata[sclass][avg_key][1], self.sclassdata[sclass]["total"], avg_bias[avg_key])
                #if avg_key == "gap":
                #    print(len(self.sclassdata[sclass][avg_key][1]), self.sclassdata[sclass][avg_key][0])

    def printdata(self):
        print("data: ",self.setting," ", self.sclassdata[sclasses[2]])

    def print(self, islatex = True):
        printstr = str(self.setting) + " & "
        if islatex:
            for sclass in self.sclasses:
                ltstring = [str(self.sclassdata[sclass][display_key]) + " & " for display_key in total_keys] + [ str(round(self.sclassdata[sclass][display_key][0],1)) + ("\%" if display_key == "gap"  else "") + " & " for display_key in avg_keys]
                strs = ""
                for lts in ltstring:
                    strs += lts
                printstr += strs
        return printstr

    def normprint(self, norm,  islatex = True):
        printstr = str(self.setting)  + " & "
        if islatex:
            for sclass in self.sclasses:
                ltstring = [str(self.sclassdata[sclass][display_key]) + " & " for display_key in total_keys] + [ str(round(self.sclassdata[sclass][display_key][0] / norm.sclassdata[sclass][display_key][0], 2)) +  ("" if display_key == "gap" else "") + " & " for display_key in avg_keys]
                strs = ""
                for lts in ltstring:
                    strs += lts
                printstr += strs
        return printstr

details = ""
settings = ["disablesig", "sigestimate", "sigenfo", "sigestimateenfo"]
stats = {}

sclasses = [(0.0, 3600.0, 0), (0.0, 3600.0, 1), (0.0, 3600.0, 2)]


for setting in settings: 
    stats[setting] = Stat(setting, sclasses)


for entry in entries:
    for setting in settings: 
        if entry["setting"] == setting:
            stats[setting].add_entry(entry)


for instance in instances:
    ins_entries = []
    for setting in settings: 
        for entry in entries:
            if entry["instance"] == instance and entry["setting"] == setting:
                ins_entries.append(entry)


for setting in settings:
    stats[setting].avg()
    stats[setting].printdata()
    printstr = stats[setting].print()
    printstrn = stats[setting].normprint(stats["disablesig"])
    print(printstr, "\n", printstrn)

