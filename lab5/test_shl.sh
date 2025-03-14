#!/bin/sh

EXEC=shl
OK=ok

make $EXEC
while read a b c ; do
    res=`./$EXEC $a $b`
    if [ x"$c" != x"$res" ]; then
        echo TEST $a $b FAILED: expected "$c", got "$res"
        OK=failed
    fi
done <<EOF
    +abc +2 +abc << 2 = +abc00
    -dc +3 -dc << 3 = -dc000
EOF
make clean

if [ $OK = "ok" ]; then
   echo "[+] Everything seems okay"
   exit 0
else
   echo "[-] Some tests failed"
   exit 1
fi
