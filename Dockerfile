FROM ubuntu:20.04

ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt install -y build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

RUN apt-get install -y wget

RUN apt-get install -y vim
RUN apt-get install -y unzip

RUN cd \
    && wget https://github.com/opencv/opencv/archive/4.5.0.zip \
    && unzip 4.5.0.zip \
    && cd opencv-4.5.0 \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && make install \
    && cd \
    && rm 4.5.0.zip

WORKDIR /app
COPY . .

RUN git submodule update --init --recursive \
    && mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build .

CMD ["build/test/Tests"]
