# CondorDockerGeant4Example
Example how to run a simple Geant4 code with docker in condor.

In this repository there are:
   * code to run a simulation using Geant4
   * [Dockerfile](Dockerfile) to build a docker image which includes all the dependencies to run the code (presently it doesn't include the code itself but it is easy to do it)
   * [script](condor_calo_sim_wrapper.sh) to run the code 
   * [condor file](job.docker) to submit the job
   
Each time a commit is pushed to this repository a Docker image is automatically built on Docker hub: https://hub.docker.com/r/wiso/condordockergeant4example/

To run this example on condor just download this repository with `git clone` and run

    condor_submit job.docker

## How it works
When the job is executed on condor the Docker image specified by `docker_image = wiso/condordockergeant4example` is downloaded from the Docker hub and the a Docker container is started. Thanks to the option `transfer_input_files=EMCalo` the folder `EMCalo` is available in the sanbox folder, created by condor, inside the container, together with the executable `executable = ./condor_calo_sim_wrapper.sh`. The directory `EMCalo` contains the user code, while the image contains only the Geant4 framework (in principle one can also put the user code inside the image). Then the executable is run. It creates a directory to contain the build of the user code, moves to it, starts the compilation and finally run the produced executable. As specified in the condor file only one file, produced when running the executable, is transfered back to the local machine (`EMCalo_build/run_samp_em_10GeV.root`). Log, error and output file are saved. A minimum amount of memory is required.

## How to build the Docker image
The Docker image containing Geant4 is already built and pushed to the Docker hub, so this step is not needed. To do that one has just to run

    docker build .
    
 from the directory where [Dockerfile](Dockerfile) is present (with the right permissions, for example as root). You can also add a flat `-t` to tag the build
 
 ## How to push the Docker image
You can push the image to a docker-hub. This image is pushed automatically to dockerhub.com each time a commit is pushed into this git repository. If you want you can do it manually.

If you haven't tag your image do that. Without rebuilding just do `docker images` and note down the `IMAGE ID`, then tag it. If you want to push to dockerhub.com (and you have an account there) tag it as `myusername/tag`, eventually `myusername/tag:version`. If you want to push to another server `servename:port/tag`.

Before pushing you need to login into the docker hub

    docker login
    
eventually specify a server name as

    docker login distribution.mi.infn.it:1443
    
and then push, for example

    docker push distribution.mi.infn.it:1443/condordockergeant4example
