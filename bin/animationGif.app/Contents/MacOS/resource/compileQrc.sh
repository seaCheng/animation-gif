#!/bin/sh
source ~/.bash_profile
rcc -binary instance.qrc -o instance.rcc
rm -rf ./../../bin/animationGif.app
cp -rf ./../resource ./../../bin
