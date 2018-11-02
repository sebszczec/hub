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

RUN pip install --upgrade pip
RUN pip install junit_xml
RUN pip install gcovr

RUN git config --global user.name "Seba"
RUN git config --global user.email "sebszczec@wp.pl"

WORKDIR /usr/src/gtest
RUN cmake . && \
    make && \
    cp libgtest.a /usr/lib/libgtest.a && \
    cp libgtest_main.a /usr/lib/libgtest_main.a

ENV WORKSPACE=/root/repo

WORKDIR /root

