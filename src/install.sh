#!/bin/bash

##### Install some basic text tools that are used to check for OS versions#####

# -- Works --
### Install grep if it is not already present ###
echo "sudo apt install grep -y"

# -- Works --
### Install sed command if it is not already present ###
echo "sudo apt install sed -y"




##### First grab distro information to determine which file to download #####

### Grab information from OS-Realease, and pretty up that output to only get values after '=' ###
VAR="`cat /etc/os-release | grep -Eo '*=.{1,50}' | cut -d "=" -f 2 | sed 's/^\(\"\)\(.*\)\1\$/\2/g' `"

### These are the available prebuilts that freeling has downloadable
UBUNTU_20='20.04'  # Version number
FOCAL='Focal'      # Code Name
FOSSA='Fossa'

UBUNTU_18='18.04'
BIONIC='Bionic'
BEAVER='Beaver'

DEBIAN_10='10'
BUSTER='buster'

### Depending on the values from /etc/os-release, choose different value for OS_VER
case $VAR in 
	*"$UBUNTU_20"* | *"$FOCAL"* | *"$FOSSA"*)
		echo -n "Found Ubuntu 20.04\n"
		OS_VER='focal'
	;;

	*"$UBUNTU_18"* | *"$BIONIC"* | *"$BEAVER"*)
		echo -n "Found Ubuntu 18.04\n"
		OS_VER='bionic'
	;;

	*"$DEBIAN_10"* | *"$BUSTER"*)
		echo -n "Found Debian 10\n"
		OS_VER='buster'
	;;

	*)
		echo -n "Unsupported Linux Variant"
		exit 0
esac




## -- WORKING --
##### Install Freeling and Dependencies #####


### Boost Libs ###
echo "sudo apt install libboost-all-dev -y"

### ZLib ###
echo "sudo apt install zlib1g -y"

### ICU ###
echo "sudo apt-get install libicu-dev -y"


### Use the Info from /etc/os-release to download and install the proper FreeLing binary
echo "wget https://github.com/TALP-UPC/FreeLing/releases/download/4.2/freeling-4.2-$OS_VER-amd64.deb"
echo "sudo dpkg -i freeling-4.2-$OS_VER-amd64.deb -y"




# -- WORKS --
###### Install g++ to compile ReqEx ##### 
echo "sudo apt install g++ -y"

	

# Once the repo is updated to actually call the library, this works
##### Build and Compile EXE file for Command Line Use#####
echo "g++ main.cpp -o ReqExCLI.exe -lfreeling -std=c++0x"





## WORK ON THIS ONCE MAIN GETS CONVERTED

##### Grab U++ Toolkit to use umk and build GUI #####
echo "wget -O upp-posix-15947.tar.xz https://sourceforge.net/projects/upp/files/upp/2021.1/upp-posix-15947.tar.xz/download"

echo "tar -xf upp-posix-15947.tar.xz"

echo "cd upp"

echo "./install"

echo "y"

echo "y"

#### This installs the full IDE, I wonder if we can just get a tool to build our specific GUI