# make IPOPT=true MEM=50000 TEST=signomial TIME=3600 EXECUTABLE=build/bin/scip SETTINGS="default,sigcut" test
# make IPOPT=true MEM=50000 TEST=signomial_debug TIME=3600 EXECUTABLE=build/bin/scip SETTINGS="default,sigcut" test
import os

dir = "/home/ldx/Downloads/signomial_cut_reimplement/zib/data/All"

ls = os.listdir(dir)

for l in ls:
   print("instances/Signomial/"+ l)
