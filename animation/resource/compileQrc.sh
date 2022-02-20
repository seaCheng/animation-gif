#!/bin/sh
source ~/.bash_profile
rcc -binary instance.qrc -o instance.rcc
rm -rf ../bin/animation.app
