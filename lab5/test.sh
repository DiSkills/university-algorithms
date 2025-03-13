#!/bin/sh

EXEC=prog

while read a b ; do
    echo $a $b
    ./$EXEC $a $b
    printf "\n"
done <<EOF
    +1003 +912
    +1003 -912
    -1003 +912
    -1003 -912
    +912 +1003
    +912 -1003
    -912 +1003
    -912 -1003
EOF
