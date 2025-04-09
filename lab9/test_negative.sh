#!/bin/sh

EXEC=prog

gcc main.c -o$EXEC
while read data ; do
    echo ">>> $data"
    ./$EXEC "$data"
done <<EOF
    01+(-3+(31+4~)~)~
    --123+(12+(31+0~)~)~
    -123+(12+(31+0~)~)~fd
    01+(3+(31-4~)~)~
    01+(3+(31+4~)~
    01+(f+(31+4~)~
    01+(+(31+4~)~
EOF
rm -rf $EXEC
