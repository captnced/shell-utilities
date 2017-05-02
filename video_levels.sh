#!/bin/bash


#[a] = image 864x486

#[b2] = video waveform
#[c2] = video waveform

#[d1] = color vectorscope           512x512
#[e1] = signalstats                 512x ih

#[s1a] = volume bars                400x98
#[s2a] = lissajous audio scope      400x400
#[s3a] = wave forms audio           400x500
#--> [sound]


# LAYOUT
#   video + vdo_wave *2             = 610 + 2*256 = 1122
#   volume bars + lissajous + color = 98 + 512 + 512 = 1122

#http://live.francetv.fr/simulcast/France_Info/hls/index.m3u8
#http://live.francetv.fr/simulcast/France_O/hls/index.m3u8
#http://live.francetv.fr/simulcast/France_5/hls/index.m3u8
#http://live.francetv.fr/simulcast/France_4/hls/index.m3u8
#http://live.francetv.fr/simulcast/France_3/hls/index.m3u8
#http://live.francetv.fr/simulcast/France_2/hls/index.m3u8
#SMPTE-colorbars.mp4
#http://live.francetv.fr/simulcast/France_Info/hls/index.m3u8


ffmpeg -i "$1" -filter_complex "[0:v]scale=1084x610[vvv];\
[vvv]split=3[a][b][d];\
[b]format=yuv422p,waveform=intensity=0.1:mode=column:mirror=1:c=1:f=lowpass:e=instant,lutyuv=v=110[b1];[b1]scale=1084x512[b2];\
[0:a:0]asplit=3[out1][s1][s2];\
[s1]showvolume=t=0:b=1:h=19:w=400,scale=512:98[s1a];\
[s2]avectorscope=mode=lissajous_xy:s=512x512:zoom=8[s2a];\
[a][b2]vstack=inputs=2,format=yuv422p[abc1];\
[d]format=yuv422p,vectorscope=i=0.04:mode=color2:envelope=instant,vflip,scale=512:512,drawgrid=w=32:h=32:t=1:c=white@0.1,drawgrid=w=256:h=256:t=1:c=white@0.2,drawbox=w=9:h=9:t=1:x=180-3:y=512-480-5:c=red@0.6,drawbox=w=9:h=9:t=1:x=108-3:y=512-68-5:c=green@0.6,drawbox=w=9:h=9:t=1:x=480-3:y=512-220-5:c=blue@0.6,drawbox=w=9:h=9:t=1:x=332-3:y=512-32-5:c=cyan@0.6,drawbox=w=9:h=9:t=1:x=404-3:y=512-444-5:c=magenta@0.6,drawbox=w=9:h=9:t=1:x=32-3:y=512-292-5:c=yellow@0.6,drawbox=w=9:h=9:t=1:x=199-3:y=512-424-5:c=red@0.8,drawbox=w=9:h=9:t=1:x=145-3:y=512-115-5:c=green@0.8,drawbox=w=9:h=9:t=1:x=424-3:y=512-229-5:c=blue@0.8,drawbox=w=9:h=9:t=1:x=313-3:y=512-88-5:c=cyan@0.8,drawbox=w=9:h=9:t=1:x=367-3:y=512-397-5:c=magenta@0.8,drawbox=w=9:h=9:t=1:x=88-3:y=512-283-5:c=yellow@0.8,drawbox=w=9:h=9:t=1:x=128-3:y=512-452-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=160-3:y=512-404-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=192-3:y=512-354-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=224-3:y=512-304-5:c=sienna@0.8[d1];\
[s1a][s2a][d1]vstack=inputs=3,setsar=1/1[de1];\
[abc1][de1]hstack=inputs=2[out]" -map "[out]" -map "[out1]"  -pix_fmt yuv420p -f matroska -|ffplay -i -



#ffmpeg -i http://live.francetv.fr/simulcast/France_2/hls/index.m3u8 -filter_complex "[0:v:4]scale=1084x610[vvv];\
#		[vvv]split=4[a][b][c][d];\
#		[b]field=top[b1];\
#		[c]field=bottom[c1];\
#		[b1]format=yuv422p,waveform=intensity=0.1:mode=column:mirror=1:c=1:f=lowpass:e=instant,split=3[w1][w2][w3];\
#		[w1]crop=in_w:16:0:0,lutyuv=v=146[wtop];\
#		[w2]crop=in_w:220:0:16,lutyuv=v=110[wmid];\
#		[w3]crop=in_w:20:0:235,lutyuv=u=146[wlow];\
#		[wtop][wmid][wlow]vstack=3[b2];\
#		[c1]format=yuv422p,waveform=intensity=0.1:mode=column:mirror=1:c=1:f=lowpass:e=instant,split=3[w1][w2][w3];\
#		[w1]crop=in_w:16:0:0,lutyuv=v=146[wtop];\
#		[w2]crop=in_w:220:0:16,lutyuv=v=110[wmid];\
#		[w3]crop=in_w:20:0:235,lutyuv=u=146[wlow];\
#		[wtop][wmid][wlow]vstack=3[c2];\
#		[0:a:0]asplit=3[out1][s1][s2];\
#		[s1]showvolume=t=0:b=1:h=19:w=400,scale=512:98[s1a];\
#		[s2]avectorscope=mode=lissajous_xy:s=512x512:zoom=8[s2a];\
#		[a][b2][c2]vstack=inputs=3,format=yuv422p[abc1];\
#    [d]format=yuv422p,vectorscope=i=0.04:mode=color2:envelope=instant,vflip,scale=512:512,drawgrid=w=32:h=32:t=1:c=white@0.1,drawgrid=w=256:h=256:t=1:c=white@0.2,drawbox=w=9:h=9:t=1:x=180-3:y=512-480-5:c=red@0.6,drawbox=w=9:h=9:t=1:x=108-3:y=512-68-5:c=green@0.6,drawbox=w=9:h=9:t=1:x=480-3:y=512-220-5:c=blue@0.6,drawbox=w=9:h=9:t=1:x=332-3:y=512-32-5:c=cyan@0.6,drawbox=w=9:h=9:t=1:x=404-3:y=512-444-5:c=magenta@0.6,drawbox=w=9:h=9:t=1:x=32-3:y=512-292-5:c=yellow@0.6,drawbox=w=9:h=9:t=1:x=199-3:y=512-424-5:c=red@0.8,drawbox=w=9:h=9:t=1:x=145-3:y=512-115-5:c=green@0.8,drawbox=w=9:h=9:t=1:x=424-3:y=512-229-5:c=blue@0.8,drawbox=w=9:h=9:t=1:x=313-3:y=512-88-5:c=cyan@0.8,drawbox=w=9:h=9:t=1:x=367-3:y=512-397-5:c=magenta@0.8,drawbox=w=9:h=9:t=1:x=88-3:y=512-283-5:c=yellow@0.8,drawbox=w=9:h=9:t=1:x=128-3:y=512-452-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=160-3:y=512-404-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=192-3:y=512-354-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=224-3:y=512-304-5:c=sienna@0.8[d1];\
#		[s1a][s2a][d1]vstack=inputs=3,setsar=1/1[de1];\
#		[abc1][de1]hstack=inputs=2[out]" -map "[out]" -map "[out1]"  -pix_fmt yuv420p -f matroska -|ffplay -i -



stty sane
#ffmpeg -i http://live.francetv.fr/simulcast/France_2/hls/index.m3u8 -filter_complex "[0:v:4]scale=864x486[vvv];\
#		[vvv]split=5[a][b][c][d][e];\
#		[b]field=top[b1];\
#		[c]field=bottom[c1];\
#		[b1]format=yuv422p,waveform=intensity=0.1:mode=column:mirror=1:c=1:f=lowpass:e=instant,split=3[w1][w2][w3];\
#		[w1]crop=in_w:16:0:0,lutyuv=v=146[wtop];\
#		[w2]crop=in_w:220:0:16,lutyuv=v=110[wmid];\
#		[w3]crop=in_w:20:0:235,lutyuv=u=146[wlow];\
#		[wtop][wmid][wlow]vstack=3[b2];\
#		[c1]format=yuv422p,waveform=intensity=0.1:mode=column:mirror=1:c=1:f=lowpass:e=instant,split=3[w1][w2][w3];\
#		[w1]crop=in_w:16:0:0,lutyuv=v=146[wtop];\
#		[w2]crop=in_w:220:0:16,lutyuv=v=110[wmid];\
#		[w3]crop=in_w:20:0:235,lutyuv=u=146[wlow];\
#		[wtop][wmid][wlow]vstack=3[c2];\
#		[0:a:0]asplit=4[out1][s1][s2][s3];\
#		[s1]showvolume=t=0:b=1:h=19:w=400,scale=400:98[s1a];\
#		[s2]avectorscope=mode=lissajous_xy:s=400x400:zoom=8[s2a];\
#		[s3]showwaves=split_channels=1:scale=log:mode=cline:s=400x500[s3a];\
#		[s1a][s2a][s3a]vstack=inputs=3,setsar=1/1[sound];\
#		[a][b2][c2]vstack=inputs=3,format=yuv422p[abc1];\
#[d]format=yuv422p,vectorscope=i=0.04:mode=color2:envelope=instant,vflip,scale=512:512,drawgrid=w=32:h=32:t=1:c=white@0.1,drawgrid=w=256:h=256:t=1:c=white@0.2,drawbox=w=9:h=9:t=1:x=180-3:y=512-480-5:c=red@0.6,drawbox=w=9:h=9:t=1:x=108-3:y=512-68-5:c=green@0.6,drawbox=w=9:h=9:t=1:x=480-3:y=512-220-5:c=blue@0.6,drawbox=w=9:h=9:t=1:x=332-3:y=512-32-5:c=cyan@0.6,drawbox=w=9:h=9:t=1:x=404-3:y=512-444-5:c=magenta@0.6,drawbox=w=9:h=9:t=1:x=32-3:y=512-292-5:c=yellow@0.6,drawbox=w=9:h=9:t=1:x=199-3:y=512-424-5:c=red@0.8,drawbox=w=9:h=9:t=1:x=145-3:y=512-115-5:c=green@0.8,drawbox=w=9:h=9:t=1:x=424-3:y=512-229-5:c=blue@0.8,drawbox=w=9:h=9:t=1:x=313-3:y=512-88-5:c=cyan@0.8,drawbox=w=9:h=9:t=1:x=367-3:y=512-397-5:c=magenta@0.8,drawbox=w=9:h=9:t=1:x=88-3:y=512-283-5:c=yellow@0.8,drawbox=w=9:h=9:t=1:x=128-3:y=512-452-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=160-3:y=512-404-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=192-3:y=512-354-5:c=sienna@0.8,drawbox=w=9:h=9:t=1:x=224-3:y=512-304-5:c=sienna@0.8[d1];\
#		[e]signalstats=out=brng,scale=512:ih[e1];\
#		[e1][d1]vstack[de1];\
#		[sound][abc1][de1]hstack=inputs=3[out]" -map "[out]" -map "[out1]"  -pix_fmt yuv420p -f matroska -|ffplay -i -
