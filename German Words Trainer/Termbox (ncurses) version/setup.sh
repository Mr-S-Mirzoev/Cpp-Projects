#! /usr/bin/env bash

cd lib/termbox

./waf configure --prefix=/usr                                #(configure)
./waf                                                        #(build)
./waf install --destdir=../         #(install)

cd ../..