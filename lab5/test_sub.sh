#!/bin/sh

EXEC=sub
OK=ok

make $EXEC
while read a b c ; do
    res=`./$EXEC $a $b`
    if [ x"$c" != x"$res" ]; then
        echo TEST $a $b FAILED: expected "$c", got "$res"
        OK=failed
    fi
done <<EOF
    +abc +dc +abc - +dc = +9e0
    +abc -dc +abc - -dc = +b98
    -abc +dc -abc - +dc = -b98
    -abc -dc -abc - -dc = -9e0
    +dc +abc +dc - +abc = -9e0
    +dc -abc +dc - -abc = +b98
    -dc +abc -dc - +abc = -b98
    -dc -abc -dc - -abc = +9e0
EOF
make clean

if [ $OK = "ok" ]; then
   echo "[+] Everything seems okay"
   exit 0
else
   echo "[-] Some tests failed"
   exit 1
fi
