#!/bin/bash

#  < BACKGROUND >        < FOREGROUND >
#Black        0;30     Dark Gray     1;30
#Red          0;31     Light Red     1;31
#Green        0;32     Light Green   1;32
#Brown/Orange 0;33     Yellow        1;33
#Blue         0;34     Light Blue    1;34
#Purple       0;35     Light Purple  1;35
#Cyan         0;36     Light Cyan    1;36
#Light Gray   0;37     White         1;37


reset="\033[0m"
fg_red="\033[1;31m"
fg_yellow="\033[1;33m"


if [ $# -eq 0 ]
then
    echo -e $fg_red"No arguments specified.$reset\nUsage: $0 [files or folders to transfer]";
    exit 1
fi

gen_password () {
    #cat /dev/urandom | tr -dc 'a-zA-Z0-9-!@#$%^&*()_+~' | fold -w 10 | head -n 1
    echo `cat /dev/urandom | env LC_CTYPE=C tr -cd 'a-f0-9' | head -c 16`
}

function get_common_prefix() {
    list="$@"
    sep=" "
    printf "$list" | awk '(NR==1) {pcount=split($0,prefix)}
    (NR>1) {for (i=pcount;i>0;i--) {if ($i!=prefix[i]) {pcount=i-1}}}
    END {NF=pcount;print}' RS=' ' FS=$sep OFS=$sep
}


archive=$(mktemp -t cedric).zip
basefile=$(basename $archive)
passwd=$(gen_password 16)

totalsize=$(du -sk "$@"|awk '{ sum += $1; } END { print sum; }')
echo "Total size :"$totalsize"kb"
onepc=$((totalsize/100))
buffersize=$((totalsize/5))

# FIND COMMON PATH OF ALL INPUTS
root=$(realpath "$@"|sed -e 's,$,/,;1{h;d;}' -e 'G;s,\(.*/\).*\n\1.*,\1,;h;$!d;s,/$,,')
if [ -z "$root" ]
then
    root=$(dirname "$@")
fi
if [ -z "$root" ]
then
    root="/"
fi

# WORKS BEST WITH LARGE FILES::
echo -e $fg_yellow"zipping..."$reset && (cd $root && realpath "$@" --relative-to=$root|zip -r0 -q -P $passwd -X - -@)|pv -W -D 20 -r -p -s $totalsize"k" --buffer-size $buffersize"k">$archive && echo -e $fg_yellow"uploading..."$reset && URL=$(wget --method PUT --body-file=$archive "https://transfer.sh/$basefile" -O - -nv 2>/dev/null) && echo -e $fg_red"secured with password$reset '$passwd' --> $URL\r" && rm -f $archive

echo

#pv -p -s $totalsize"k"
#|mail -s "transfered file" cedric.m.hamelin@gmail.com
#



