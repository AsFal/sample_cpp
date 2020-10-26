FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev \
libavformat-dev libswscale-dev python-dev python-numpy libtbb2 libtbb-dev \
libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev unzip

RUN git clone --depth 1 --branch 4.5.0 https://github.com/opencv/opencv \
    && mkdir build \
    && cd build \
    && cmake ../opencv \
    && cmake --build . \
    && make install \
    && cd .. \
    && rm -rf opencv

WORKDIR tests
COPY . .
RUN git submodules --update --recursive

RUN mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build .

WORKDIR app/build
CMD ["make", "test"]