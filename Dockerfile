# syntax=docker/dockerfile:1
FROM ubuntu:20.04

RUN apt-get update 
RUN DEBIAN_FRONTEND="noninteractive" apt-get install -y cmake make python3 g++ binutils python3-pip
RUN pip3 install tqdm

COPY . /app
WORKDIR /app

RUN cmake -B build
RUN make -C build -j2

