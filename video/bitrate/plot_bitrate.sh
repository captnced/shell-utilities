#!/bin/sh
# plot-bitrate

check_file() {
	if [ ! -s "${1}" ]
	then
		echo "ERROR: \"${1}\" does not exist or is empty"
		exit 1
	fi
}

width=1920
height=1080

while (($#))
do

media_file="${1}"
media_basename=${media_file%.*}
check_file "${media_file}"
media_name="$(basename "${media_file}")"
data_file=$(mktemp)
streams_file=$(mktemp)

libav-bitrate -P -e -I 1 "${media_file}" 2>&1 > "${data_file}"|tee /dev/tty|\
sed -n -e '/^[[:space:]]*Stream/s|^[[:space:]]*||p' > "${streams_file}"

for i in "${data_file}" "${streams_file}"
do
	check_file "${i}"
done

{
echo "
set title \"${media_name}\"
set xdata time
set timefmt '%s'
set format x '%R'
set xlabel 'time'
set ylabel 'bitrate (Kb/s)'
set style data lines
set terminal png size ${width},${height}
"

plotline='plot "'"${data_file}"'" using 1:($2/1024) title "Total"'
stream_n='2'

while read line
do
	stream_n="$((${stream_n}+1))"
	plotline=$plotline', "'"${data_file}"'" using 1:($'"${stream_n}"'/1024) title "'"${line}"'"'
done < "${streams_file}"
echo $plotline
}|gnuplot > $media_basename.png
rm "${data_file}" "${streams_file}"
open $media_basename.png

shift
done


