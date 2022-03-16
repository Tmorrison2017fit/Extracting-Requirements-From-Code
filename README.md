# ReqEx (Extracting-Requirements-From-Code)


## Automatically perform requirements generation based on source code


### Dependencies
ReqEx uses FreeLing to perform text analysis.

FreeLing depends on different C++ libraries, in particular
- Boost (regex, system, thread, program-options)
- zlib
- ICU  

### INSTALLATION INSTRUCTIONS
NOTES: As of this moment, ReqEx is only available in Linux environments. The installer script is using the pre-built versions of FreeLing that are available at the GitHub linked below. 

[https://github.com/TALP-UPC/FreeLing/releases](https://github.com/TALP-UPC/FreeLing/releases)

Currently, these pre-built versions are only available for the following canonical versions.
- Ubuntu 20.04 LTS (Focal Fossa), 64-bit
- Ubuntu 18.04 LTS (Bionic Beaver), 64-bit
- Debian 10 (buster), 64-bit

Please ensure that a proper version of Linux is installed before running the installer script.

To install, run the script ```install.sh``` in a terminal. When the installer finishes, FreeLing and its dependencies will be installed locally onto the machine, and the programs ```ReqExCLI.exe``` and ```ReqExGUI.exe``` will be built.

Alternatively, you could build FreeLing directly using the instructions below
[https://freeling-user-manual.readthedocs.io/en/v4.2/installation/installation-source/](https://freeling-user-manual.readthedocs.io/en/v4.2/installation/installation-source/)

