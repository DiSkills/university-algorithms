#!/bin/sh

EXEC=mul
OK=ok

make $EXEC
while read a b c ; do
    res=`./$EXEC $a $b`
    if [ x"$c" != x"$res" ]; then
        echo TEST $a $b FAILED: expected "$c", got "$res"
        OK=failed
    fi
done <<EOF
    +3 +5 +3 * +5 = +f
    +3 -5 +3 * -5 = -f
    -3 +5 -3 * +5 = -f
    -3 -5 -3 * -5 = +f
    +abc +dc +abc * +dc = +93990
    +abc -dc +abc * -dc = -93990
    -abc +dc -abc * +dc = -93990
    -abc -dc -abc * -dc = +93990
    +dc +abc +dc * +abc = +93990
    +dc -abc +dc * -abc = -93990
    -dc +abc -dc * +abc = -93990
    -dc -abc -dc * -abc = +93990
    +aaaa89321aa +55532a +aaaa89321aa * +55532a = +38e210d81897fa3e4
EOF
make clean

if [ $OK = "ok" ]; then
   echo "[+] Everything seems okay"
   exit 0
else
   echo "[-] Some tests failed"
   exit 1
fi
