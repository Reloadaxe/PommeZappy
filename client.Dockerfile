FROM ubuntu:bionic

RUN apt update
RUN apt install g++ qt5-default make -y

# Copy Zappy files
WORKDIR /usr/app
COPY ./commons /usr/app/commons
COPY ./client /usr/app/client

RUN mkdir -p /usr/app/client/build
RUN cd /usr/app/client/build && qmake ../client.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
RUN cd /usr/app/client/build && make client -j4
