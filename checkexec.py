from pathlib import Path
import os
import sys

# 1: solved. 2: unsolved
def main(argv):
    path = os.getcwd()
    solvername=argv[1]
    dataname=argv[2]
    log_path =argv[3]
    test_path = os.getcwd() + "/" + log_path
    log_path = test_path + "/" + dataname + "_" + solvername + ".log"
    #result_path = test_path + "/" + benckmarkname + "/results/"+ solvername + "/" + dataname +  "_" + solvername + ".result"
    #print(benckmarkname, solvername, dataname, log_path, result_path)
    if os.path.isfile(log_path) and os.path.getsize(log_path) > 0:
        return 1
    else:
        if os.path.isfile(log_path):
            os.remove(log_path)
        return 2
    return 0

if __name__ == "__main__":
    rtcode = main(sys.argv)
    sys.exit(rtcode)