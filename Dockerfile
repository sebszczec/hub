FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get -y install git cmake g++ libconfig++-dev mc libgtest-dev python valgrind vim expect telnet python-pip screen inetutils-ping
RUN apt-get -y install sqlite3 libsqlite3-dev cloc sloccount xsltproc dos2unix netcat iperf

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

WORKDIR /root

