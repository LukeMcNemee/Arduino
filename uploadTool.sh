#!/bin/sh

#-p path to MyMakefile
#-h print help and exit


## GLOBAL definitions ##
red='\e[0;31m'
green='\e[0;32m'
NC='\e[0m' # No Color


## HELP ##

function help {
    echo "help etc"
}

## PRECHECK ##
function precheck {
  if [ -f ./MyMakefile ]
  then
  #found my MyMakefile
      echo "FileName - Found, take some action here" 2>&1 | tee compilationReport.txt
      cat MyMakefile > Makefile
      echo "ARDUINO_PORT = \$(PORT)" >> Makefile
      $PORT = /dev/ttyACM0
      make 2>&1 | tee compilationReport.txt 
      
      #rm Makefile
  else
  #MyMakefile not found error
      >&2 echo "FileName - Not found, take some action here" 
      echo "FileName - Not found, take some action here" >> compilationReport.txt
  fi
}
## MAIN ##

if [ -z "$1"  ] || [ "$1" == "-h" ] || [ "$1" == "--help" ]
then
  help
  exit 
fi  


