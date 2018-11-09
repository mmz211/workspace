#! /bin/bash

for ((i=1;i<$#+1;i++))

do

    #echo \$$i
    eval currParam=\$$i;

    #引用当前变量

    echo "${currParam}"

done
