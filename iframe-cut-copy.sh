#!/bin/bash

IN=$1
TCIN=$2
TCOUT=$3

function tcToSec {
    hms=$1
    IFS=: read h m s<<<"${hms%.*}"
    seconds=$((10#$s+10#$m*60+10#$h*3600))
    echo $seconds
}

function secToTc {
    ((h=${1}/3600))
    ((m=(${1}%3600)/60))
    ((s=${1}%60))
    printf "%02d:%02d:%02d\n" $h $m $s
}


TCINS=$(tcToSec $TCIN)
TCOUTS=$(tcToSec $TCOUT)
TCMARGIN=5

TCINM1=$(($TCINS))
TCINM2=$(($TCINS+$TCMARGIN))
TCIN1=$(secToTc $TCINM1)
TCIN2=$(secToTc $TCINM2)

echo "Input file: "$IN
echo "TC In: "$TCIN", "$TCINS
echo "TC Out: "$TCOUT", "$TCOUTS

I_TCIN=$(ffprobe -show_frames -select_streams v -show_entries frame=pict_type,pkt_dts_time -print_format csv -read_intervals $TCIN1%$TCIN2 $IN 2>/dev/null|grep ",I"|head -n1|cut -d',' -f2)

echo "Iframe TC In "$I_TCIN


DIR=$(dirname $IN)
BN=$(basename $IN)
RN=${BN%.*}

if [ $TCOUTS -eq 0 ]
then
    #capture to the end
    OUT=$DIR"/"$RN"_"$TCINS".ts"
    FF_DUR=""
else
    OUT=$DIR"/"$RN"_"$TCINS_$TCOUTS".ts"
    #capture to duration
    TCOUTM1=$(($TCOUTS))
    TCOUTM2=$(($TCOUTS+$TCMARGIN))
    TCOUT1=$(secToTc $TCOUTM1)
    TCOUT2=$(secToTc $TCOUTM2)
    I_TCOUT=$(ffprobe -show_frames -select_streams v -show_entries frame=pict_type,pkt_dts_time -print_format csv -read_intervals $TCOUT1%$TCOUT2 $IN 2>/dev/null|grep ",I"|head -n1|cut -d',' -f2)
    echo "Iframe TC Out "$I_TCOUT
    DUR=$(($TCOUTS-$TCINS))
    I_DUR=$(bc <<< "$I_TCOUT-$I_TCIN")
    echo "Duration "$DUR" >> "$I_DUR
    #FF_DUR="-t "$I_DUR
    FF_DUR="-to "$I_TCOUT
fi


echo $OUT
ffmpeg -i "$IN" -ss $I_TCIN $FF_DUR -c:v copy -c:a copy -c:s copy -async 1 -y "$OUT"







#-print_format json=c=1
