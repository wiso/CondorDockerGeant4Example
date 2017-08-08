#!/bin/sh

hostname

mkdir EMCalo_build
cd EMCalo_build

cmake -DGeant4_DIR=/usr/local/geant4/lib/Geant4-10.0.4/ ../EMCalo
make

./TestEm3 ../EMCalo/mac_files/my_run_samp.mac

