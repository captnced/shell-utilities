#!/usr/bin/python
# -*- coding: utf-8 -*-

#   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
#   ┃ import libraries                                                                                 ┃
#   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

from optparse import OptionParser
import os,sys, psutil
import json
import subprocess
import time,datetime
import commands
from tempfile import NamedTemporaryFile
import platform

import signal

import threading
event=threading.Event()

from subprocess import PIPE, Popen

try:
    from Queue import Queue, Empty
except ImportError:
    from queue import Queue, Empty  # python 3.x

thisProcess=psutil.Process(os.getpid())
debug_mode = True #sys.flags.debug

#   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
#   ┃ FFPROBE Stdout Queue Processor                                                                   ┃
#   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

def enqueue_output(out, queue,ID):
    for line in iter(out.readline, b''):
        #log(2,line)
        if line.find("{")>=0:
            buff=""
        buff+=line
        if line.find("}")>=0:
            try:
                js=json.loads(buff.replace("},","}"))
                queue.put({ID:js})
                #data={"bitrate":int(js['pkt_size']),"time":js['pkt_pts']}
                #queue.put({ID:data}) #"#SOW#%s#EOW#"%json.dumps({ID:data})
                #queue.put(data)
            except Exception as e:
                if(line=="}"):
                    queue.put(None)
                else:
                    #log(-1,"INVALID data : %s"%line)
                    pass
                pass
    out.close()

#q = {}
q=Queue()
ON_POSIX = 'posix' in sys.builtin_module_names

def launcher(cmd,channel):
    global q
    #if not(channel in q.keys()):
    #    q[channel]=Queue()
    log(1,"open process for : %s"%channel)
    log(2,cmd)
    p = Popen(cmd, shell=True, stdout=PIPE, bufsize=1, close_fds=ON_POSIX)
    #t = threading.Thread(target=enqueue_output, args=(p.stdout, q[channel],channel))
    t = threading.Thread(target=enqueue_output, args=(p.stdout, q,channel))
    t.daemon = True # thread dies with the program
    log(2,'start now')
    t.start()
    log(2,'start done')


def queuemonitor(q,*args):
    global _data
    while True:
        try:
            _data=q.get(timeout=10)
            os.kill(os.getpid(),signal.SIGHUP) # send SIGHUP to myself to update widget on all other connexions
        except:
            time.sleep(1)
            pass

#   -------- LOGGING -----------------------------------------------------------

def showTraceBack_Verbose(err):
    if err:
        log(-1,"%s"%err)
    for frame in traceback.extract_tb(sys.exc_info()[2]):
        fname,lineno,fn,text = frame
        log(2,"Error in %s on line %d" % (fname, lineno))
def showTraceBack_Quiet(err):
    pass


def verbose_log(*args):
    HEADER = '\033[95m'     # purple
    OKDEBUG = '\033[94m'    # blue
    OKINFO = '\033[92m'     # green
    WARNING = '\033[93m'    #
    FAIL = '\033[91m'       # red
    ENDC = '\033[0m'
    type=args[0]
    dt = datetime.datetime.now()
    ts = str(dt.day)+"/"+str(dt.month)+"/"+str(dt.year)+" "+str(dt.hour)+":"+str(dt.minute)
    text=str(args[1])
    str_type=""
    if type==0:
        str_type=""
        text=HEADER+("> "+text+" <").center(80,"=").upper()+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]
    if type==-1:
        str_type="ERROR: "
        text=FAIL+text+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]
    if type==1:
        str_type="INFO : "
        text=OKINFO+text+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]
    if type==2:
        str_type="DEBUG: "
        text=OKDEBUG+text+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]

def quiet_log(*args):
    HEADER = '\033[95m'     # purple
    OKDEBUG = '\033[94m'    # blue
    OKINFO = '\033[92m'     # green
    WARNING = '\033[93m'    #
    FAIL = '\033[91m'       # red
    ENDC = '\033[0m'    
    type=args[0]
    dt = datetime.datetime.now()
    ts = str(dt.day)+"/"+str(dt.month)+"/"+str(dt.year)+" "+str(dt.hour)+":"+str(dt.minute)
    text=str(args[1])
    str_type=""
    if type==0:
        str_type=""
        text=HEADER+("> "+text+" <").center(80,"=").upper()+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]
    if type==-1:
        str_type="ERROR: "
        text=FAIL+text+ENDC
        print "%-30s "%(ts+" : "+str_type)+text,args[2:]

if debug_mode:
    log=verbose_log
else:
    log=quiet_log



def readQueueData(q):
    while True:
        try:
            _d=q.get(timeout=10)
            yield _d
        except Empty:
            log(1,"empty queue")
            yield None
            pass
        else:
            q.task_done()
            # Handle task here and call q.task_done()


index_html="""<html>
    <head>
        <script>%DATA%</script>
        <script>
        CanvasRenderingContext2D.prototype.clear = CanvasRenderingContext2D.prototype.clear || function (preserveTransform) {
                if (preserveTransform) {
                    this.save();
                    this.setTransform(1, 0, 0, 1, 0, 0);
                }
                this.clearRect(0, 0, this.canvas.width, this.canvas.height);
                if (preserveTransform) {
                    this.restore();
                }
            };
        function normalize(arr) {
            var _min = Math.min.apply(Math,arr);
            var _max = Math.max.apply(Math,arr);
            var _arr = [];
            arr.forEach(function(el,idx) {
                        this[idx] = ((el-_min)/(_max-_min));
                        },_arr);
                        return _arr;
        }
        function RTGraph(canvasid,options) {
            this.name = canvasid;
            this.xdata = [];
            this.ydata = [];
            this.xMin = Number.NaN;this.xMax = Number.NaN;
            this.yMin = Number.NaN;this.yMax = Number.NaN;
            this.canvas=document.getElementById(canvasid);
            this.setSize(options.width,options.height);
            this.ctx=this.canvas.getContext("2d");
        };
        RTGraph.prototype.setMouseCallback = function(cb) {
            this.mousemove = cb;
            this.canvas.addEventListener("mousemove", this.mousemove, false);
        };
        RTGraph.prototype.init = function() {
            this.clear();
        };
        RTGraph.prototype.setSize = function(w,h) {
            this.canvas.width=w;
            this.canvas.height=h;
        };
        RTGraph.prototype.drawGrid = function() {
            this.ctx.beginPath();
            this.ctx.strokeStyle="#eee";
            //xstep=this.canvas.width/5;
            xstep=20;
            for (var x = 0.5+xstep; x < this.canvas.width; x += xstep<<0) {
                this.ctx.fillStyle = "#3E3E3E";
                this.ctx.moveTo(x, 0);
                this.ctx.lineTo(x, this.canvas.height);
            }
            this.ctx.font = "15px HelveticaNeue-UltraLight";
            this.ctx.textAlign = "left";

            if(this.yMax>0) {
                var ystep=this.canvas.height/5;
                var nb_steps=(this.canvas.height/ystep)<<0;
                var v_step = (this.yMax-this.yMin)/nb_steps;
                for (var y = 0.5+ystep; y < this.canvas.height; y += ystep<<0) {
                    this.ctx.fillStyle = "#3E3E3E";
                    this.ctx.moveTo(0, y);
                    this.ctx.lineTo(this.canvas.width, y);
                    this.ctx.fillStyle = "#ffffff";
                        v_level=this.yMax-v_step*((y-0.5)/ystep);
                        this.ctx.fillText(""+((v_level*8)<<0)+"kb",5, y);
                }
            }
            this.ctx.lineWidth=0.5;
            this.ctx.stroke();
            this.ctx.font = "30px HelveticaNeue-UltraLight";
            this.ctx.textAlign = "center";
            this.ctx.fillStyle = "white";
            this.ctx.fillText("[ I frames pkt_size/pkt_pts ]",(this.canvas.width/2)<<0, 30);
        };
        RTGraph.prototype.drawBackground = function() {
            var gradient = this.ctx.createLinearGradient(0, 0, 0, this.canvas.height);
            gradient.addColorStop(0, "rgba(40, 40, 40,0.8)");
            gradient.addColorStop(1, "rgba(0, 0, 0,0.8)");
            this.ctx.save();
            this.ctx.fillStyle = gradient;
            this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
        };
        RTGraph.prototype.clear = function() {
            this.ctx.clear();
            this.drawBackground();
            this.drawGrid();
        };
        RTGraph.prototype.update = function() {
            if(this.xdata.length<2) {
                return;
            }
            this.xMin = Math.min.apply(Math,this.xdata);
            this.xMax = Math.max.apply(Math,this.xdata);
            this.yMin = Math.min.apply(Math,this.ydata);
            this.yMax = Math.max.apply(Math,this.ydata);
            this.clear();
            this.ctx.strokeStyle="#e00";
            var xpx = normalize(this.xdata);
            var ypx = normalize(this.ydata);
            this.ctx.beginPath();
            this.ctx.lineWidth=1;
            this.ctx.moveTo(xpx[0], ypx[0]);
            for(var i = 1; i< ypx.length; i++){
                this.ctx.lineTo(this.canvas.width*xpx[i], this.canvas.height*(1-ypx[i]));
            }
            this.ctx.stroke();
        },
        RTGraph.prototype.pushdata = function(x,y) {
            while(this.xdata.length>this.canvas.width) {
                this.xdata.splice(0,1);
                this.ydata.splice(0,1);
            }
            this.xdata.push(x);
            this.ydata.push(y);
        };
        RTGraph.prototype.setData = function(x,y) {
            this.xdata=x;
            this.ydata=y;
        }
        </script>
    </head>
    <style>
        body {
            background-color:rgb(40,40,40);
            margin-top:20px;
        }
    </style>
    <body>
        <div class="graph" id="GRAPH_CONTAINER"><canvas id="chart" style="background:rgba(0,0,0,0);"></canvas></div>
        <script>
            graphOptions={
                width: window.innerWidth?(window.innerWidth<<0):500,
                height: window.innerWidth?((window.innerWidth*9/16)<<0):281<<0
            }
            var graph = new RTGraph("chart",graphOptions);
            graph.init();
            graph.setMouseCallback(function(e) {
                var _x=e.clientX;
                var _y=e.clientY;
                //console.log("mouse at "+_x+"/"+_y);
            });
            var arrayLength = data.length;
            for (var i = 0; i < arrayLength; i++) {
                graph.pushdata(parseInt(data[i]["pkt_pts"]),parseInt(data[i]["pkt_size"]));
            }
            console.log("UPDATE GRAPH NOW");
            graph.update();
        </script>
    </body>
</html>
"""

#   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
#   ┃ MAIN                                                                                             ┃
#   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛


if __name__=="__main__":
    log(0,"cedric video GOP analyzer v1.0.0 20140816")
    # PROCESS COMMAND LINE ARGUMENTS--------------------------------------------
    parser = OptionParser()
    parser.add_option("-q", "--quiet",action="store_false", dest="verbose", default=True,help="don't print status messages to stdout")
    parser.add_option("-f", "--video-file", dest="videofile",help="input video file", metavar="FILE")
    parser.add_option("-g", "--save-graph", dest="savegraph",help="save graph data", metavar="FOLDER")
    parser.add_option("-i", "--save-iframes", dest="framewidth",help="save iframes",metavar="WIDTH")

    (options, args) = parser.parse_args()


    if debug_mode:
        log=verbose_log
        showTraceBack=showTraceBack_Verbose
    else:
        log=quiet_log
        showTraceBack=showTraceBack_Quiet
    
    STREAMS={}
    if options.videofile:
        STREAMS={os.path.basename(options.videofile):options.videofile}
        log(2,STREAMS)
    
    if options.framewidth and not(options.savegraph):
        parser.error("this options requires --save-graph (-g)")

    if options.savegraph:
        if(not(os.path.exists(options.savegraph))):
            os.makedirs(options.savegraph)
    else:
        parser.error("this requires --save-graph (-g)")

    if STREAMS=={}:
        parser.error("you need to provide a video file (-f)")

    # START FFPROBES -----------------------------------------------------------
    for _strm in STREAMS.keys():
        if(not(os.path.exists(STREAMS[_strm]))):
            del STREAMS[_strm]
    for _strm in STREAMS.keys():
        launcher('ffprobe -v quiet -print_format json -show_frames -pretty -i "%s"'%STREAMS[_strm],_strm)

    if(len(STREAMS.keys())==0):
        log(-1,"no file for processing")
        sys.exit(0)
    GOPstr={}
    GOPstats={}
    Iframes={}
    ALLdata={}

    for data in readQueueData(q):
        if(data==None):
            log(2,"get out")
            break
        k=data.keys()[0]
        a=data[k]
        if(a['media_type']==u'video'):
        
            if options.savegraph:
                try:
                    ALLdata[k].append(a)
                except:
                    ALLdata[k]=[]
                    ALLdata[k].append(a)
                    
            try:
                GOPstr[k]="%s%s"%(GOPstr[k],a[u'pict_type'].replace('I','\nI'))
            except:
                GOPstr[k]=""
                GOPstr[k]="%s%s"%(GOPstr[k],a[u'pict_type'].replace('I','\nI'))
            if(a['pict_type']=='I'):
                try:
                    Iframes[k].append(a)
                except:
                    Iframes[k]=[]
                    Iframes[k].append(a)
                if options.savegraph and options.framewidth:
                    cmd="ffmpeg -v quiet -y -i %s -vf \"select=gte(n\,%d),scale=%s:-1\" -vframes 1 %s/%s-%d.png"%(STREAMS[_strm],a['coded_picture_number'],options.framewidth,options.savegraph,_strm,a['coded_picture_number'])
                    os.system(cmd)
                    log(2,cmd)

                    #Popen(cmd, shell=True)
                #ffmpeg -v quiet -y -i /Volumes/32GO/Elemental/F2_main.ts -vf "select=gte(n\,277),scale=180:-1" -vframes 1 /Users/cedric/Downloads/mytest//F2_main.ts-277.png


    log(0,"detected GOP structure")
    for _strm in STREAMS.keys():
        GOPS=[len(z) for z in GOPstr[_strm].split('\n') if len(z)>0]
        GOPstats[_strm]=(max(GOPS),min(GOPS))
        log(1,"--> %s <--"%_strm)
        log(1,"max GOP : %d"%GOPstats[_strm][0])
        log(1,"min GOP : %d"%GOPstats[_strm][1])

        if(options.savegraph):
            #with open(os.path.join(options.savegraph,'data.js'), 'w') as dfile:
            #    dfile.write('data=%s\n'%json.dumps(ALLdata[_strm]))
            webpage="%s.html"%os.path.splitext(os.path.basename(options.videofile))[0]
            with open(os.path.join(options.savegraph,webpage), 'w') as dfile:
                #htmlcode=open('index.html','r').read()
                htmlcode=index_html.replace('%DATA%','data=%s\n'%json.dumps(ALLdata[_strm]))
                dfile.write(htmlcode)




