FROM ubuntu:bionic

RUN apt update
RUN apt install g++ qt5-default -y
RUN apt install make -y

# Copy Zappy files
WORKDIR /usr/app
COPY ./commons /usr/app/commons
COPY ./server /usr/app/server

RUN mkdir -p /usr/app/server/build
RUN cd /usr/app/server/build && qmake ../zappy.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
RUN cd /usr/app/server/build && make server -j4
