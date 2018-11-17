FROM ubuntu:latest

ENV TZ=Europe/Amsterdam
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -y update
RUN apt-get -y install git 
RUN apt-get -y install cmake 
RUN apt-get -y install g++ 
RUN apt-get -y install libconfig++-dev 
RUN apt-get -y install mc 
RUN apt-get -y install libgtest-dev 
RUN apt-get -y install python 
RUN apt-get -y install valgrind 
RUN apt-get -y install vim  
RUN apt-get -y install telnet 
RUN apt-get -y install python-pip 
RUN apt-get -y install screen 
RUN apt-get -y install inetutils-ping
RUN apt-get -y install sqlite3 
RUN apt-get -y install libsqlite3-dev 
RUN apt-get -y install cloc 
RUN apt-get -y install sloccount 
RUN apt-get -y install xsltproc 
RUN apt-get -y install dos2unix 
RUN apt-get -y install netcat 
RUN apt-get -y install iperf 
RUN apt-get -y install libssl-dev
RUN apt-get -y install tcpdump
RUN apt-get -y install tcpflow 
RUN apt-get -y install autoconf 
RUN apt-get -y install automake 
RUN apt-get -y install libtool 
RUN apt-get -y install curl 
RUN apt-get -y install unzip
RUN apt-get -y install wget

RUN pip install --upgrade pip
RUN pip install junit_xml
RUN pip install gcovr

WORKDIR /usr/src/gtest
RUN cmake . && \
    make && \
    cp libgtest.a /usr/lib/libgtest.a && \
    cp libgtest_main.a /usr/lib/libgtest_main.a

WORKDIR /root
RUN wget https://dl.bintray.com/boostorg/release/1.68.0/source/boost_1_68_0.tar.bz2
RUN tar -jxf boost_1_68_0.tar.bz2
RUN wget https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/protobuf-all-3.6.1.tar.gz
RUN tar -zxf protobuf-all-3.6.1.tar.gz

WORKDIR /root/protobuf-3.6.1
RUN ./configure
RUN make -j2
RUN make install
RUN ldconfig

WORKDIR /root/boost_1_68_0
RUN mkdir /root/include
RUN cp -R boost /root/include

WORKDIR /root
RUN rm boost_1_68_0.tar.bz2
RUN rm protobuf-all-3.6.1.tar.gz
RUN rm -Rf protobuf-3.6.1
RUN rm -Rf boost_1_68_0


ENV WORKSPACE=/root/repo

WORKDIR /root

