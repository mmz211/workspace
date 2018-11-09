#! /bin/bash 
vim abc.txt << EOF i 
    Here is a document! 
    ^[ 
    :wq 
EOF
