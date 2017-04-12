#!/bin/bash

source=$1
destination=$2

echo $source
echo $destination

cd $source 
size=$(($(du -sk . | awk '{print $1}') * 1024)) 
echo "SIZE "$size
tar cf - * -P | pv -s $size | ( cd "$destination"; tar xfp -)
