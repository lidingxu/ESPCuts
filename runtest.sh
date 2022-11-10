#!/bin/bash
timelimit=3600
gnuparalleltest=0 # 1: use GNU parallel to speed up test; 0: not use
algorithms=("default" "icuts" "supcuts" "lcpcuts")
benchmarks=("Continuous" "Discrete")
datapath="benchmark"
logpath="logs"
settingpath="setting"

# create and clear test files
#python3 ./testdir.py

runInstance() {
    timelimit=$1
    instance=$2
    algo=$3
    benchmark=$4
    settingpath=$5
    datapath=$6
    logpath=$7

    #echo $timelimit $instance $benchmark $benchmarkpath $logpath $resultpath $algo
    
    python3 ./checkexec.py $algo $instance $logpath/$benchmark
    if [ $? == 1 ]
    then
        return 1
    fi

    echo $logpath $instance $algo $instance $algo
    build/misp -c "set limits time $timelimit" -c  "set load $settingpath/$algo.set" -c  "read $datapath/$benchmark/$instance" -c "opt write statistics" -c "$logpath/$benchmark/${instance}_${algo}.log"  -c "quit"

}

export -f runInstance



for benchmark in $benchmarks
do
    echo "$datapath" "$benchmark"
    instances=$(ls $datapath/$benchmark)
    if [ $gnuparalleltest == 0 ]
    then
        for instance in  $instances
        do
            for algo in ${algorithms[@]}
                do
                    runInstance "$timelimit" "$instance" "$algo" "$benchmark"  "$settingpath" "$datapath" "$logpath"
            done
        done
    else
        parallel --will-cite --jobs 37% runInstance  "$timelimit" ::: "$instances" :::  "${algorithms[@]}" ::: "$benchmark" ::: "$settingpath" ::: "$datapath" ::: "$logpath"
    fi
done 


