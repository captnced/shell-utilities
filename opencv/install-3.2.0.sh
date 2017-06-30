
mkdir $HOME/Downloads/opencv/
cd $HOME/Downloads/opencv/
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout 3.2.0

cd $HOME/Downloads/opencv/
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 3.2.0

cd $HOME/Downloads/opencv/opencv
mkdir build
cd build

cmake -DWITH_CUDA=ON -DCUDA_GENERATION=Auto -DBUILD_opencv_python2=ON -DWITH_FFMPEG=ON -DWITH_OPENGL=ON \
	-DOPENCV_EXTRA_MODULES_PATH=$HOME/Downloads/opencv/opencv_contrib/modules \
	-DBUILD_TIFF=ON -DBUILD_PNG=ON -DBUILD_JPEG=ON \
	-DBUILD_opencv_adas=ON \
	-DBUILD_opencv_bgsegm=ON \
	-DBUILD_opencv_bioinspired=ON \
	-DBUILD_opencv_ccalib=ON \
	-DBUILD_opencv_datasets=ON \
	-DBUILD_opencv_face=ON \
	-DBUILD_opencv_latentsvm=ON \
	-DBUILD_opencv_line_descriptor=ON \
	-DBUILD_opencv_optflow=ON \
	-DBUILD_opencv_reg=ON \
	-DBUILD_opencv_rgbd=ON \
	-DBUILD_opencv_saliency=ON \
	-DBUILD_opencv_surface_matching=ON \
	-DBUILD_opencv_text=ON \
	-DBUILD_opencv_tracking=ON \
	-DBUILD_opencv_xfeatures2d=ON \
	-DBUILD_opencv_ximgproc=ON \
	-DBUILD_opencv_xobjdetect=ON \
	-DBUILD_opencv_xphoto=ON \
	-DCMAKE_BUILD_TYPE=Release -DCMAKE_FIND_FRAMEWORK=LAST -DCMAKE_VERBOSE_MAKEFILE=ON -Wno-dev \
	-DWITH_IPP=OFF \
	-DBUILD_JASPER=OFF -DBUILD_ZLIB=OFF \
	-DBUILD_OPENEXR=OFF \
	-DBUILD_opencv_java=OFF \
	-DBUILD_opencv_python2=ON \
	-DBUILD_opencv_python3=OFF \
	-DBUILD_TESTS=OFF \
	-DBUILD_PERF_TESTS=OFF \
	-DWITH_1394=OFF -DWITH_EIGEN=ON \
	-DWITH_FFMPEG=ON \
	-DWITH_GPHOTO2=OFF \
	-DWITH_GSTREAMER=OFF \
	-DWITH_JASPER=OFF -DWITH_OPENEXR=ON \
	-DWITH_OPENGL=ON \
	-DWITH_QUICKTIME=OFF \
	-DWITH_QT=OFF \
	-DWITH_TBB=ON \
	-DWITH_VTK=OFF \
	-DJPEG_INCLUDE_DIR=/usr/local/opt/jpeg/include -DJPEG_LIBRARY=/usr/local/opt/jpeg/lib/libjpeg.dylib \
	-DWITH_CUDA=ON -DCUDA_GENERATION=Auto \
	-DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local \
     	-DPYTHON2_LIBRARY=/usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib \
	-DPYTHON2_INCLUDE_DIR=/usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/include/python2.7 \
	-DINSTALL_C_EXAMPLES=OFF -DINSTALL_PYTHON_EXAMPLES=ON \
	-DBUILD_EXAMPLES=OFF \
	..

make -j4

