#!/bin/sh

hostname

cd EMCalo-PhD-2017

pwd
ls -l

mkdir EMCalo-PhD-2017_build
cd EMCalo-PhD-2017_build

echo "creating Makefile"
pwd
ls -l
cmake -DGeant4_DIR=/usr/local/geant4/lib/Geant4-10.0.4/ ../EMCalo

echo "compiling"

make

echo "running"

./TestEm3 ../EMCalo/mac_files/my_run_samp.mac

pwd
ls -ltr

#cp run_samp_em_10GeV.root ../../