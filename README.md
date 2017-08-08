# CondorDockerGeant4Example
Example how to run a simple Geant4 code with docker in condor.

In this repository there are:
   * code to run a simulation using Geant4
   * Dockerfile to build a docker image which includes all the dependencies to run the code (presently it doesn't include the code itself but it is easy to do it)
   * script to run the code
   * condor file to submit the job
   
Each time a commit is pushed to this repository a Docker image is automatically built on Docker hub: https://hub.docker.com/r/wiso/condordockergeant4example/

To run this example on condor just download this repository with `git clone` and run

    condor_submit job.docker
