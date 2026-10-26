#!/usr/bin/env bash

###########################################################################################################
# DESCRIPTION
#   The goal of CodeSpell Checker scripts is to help catch common spelling errors.
#   it's designed for checking misspelled words (and/or typo) in Source Code. 
#   This script is supposed to be executed from a user created job in jenkins
#
# Author: GAMMOUDI Chokri 
# Date:   15/04/2020
###########################################################################################################

declare PATH2CHECK=$1

#to skip directories, invoke codespell --skip="./src/3rd-Party,./src/Test"
declare SKIPPED_DIR=$2

prog=`readlink -e $0`
dir=`dirname $prog`
basename=$(basename $prog)
script_path=$(dirname "${BASH_SOURCE[0]}")

usage()
{
    printf '\n'
    cat <<EOF
The goal of CodeSpell Checker scripts is to help catch common spelling errors.
Usage: ./$basename <Path-to-Check> 
       ./$basename "<Path1-to-Check> <Path2-to-Check> ... "
     Examples:
       ./$basename /c/git/wl_master/Firmware/Projects/NUCLEO-WL55JC/Examples/I2C
EOF
exit
}
if [ "$1" = "--help" ]; then
    usage
fi

# The files blacklist to check
[[ ! -z "$codespell_ignore_words" ]] && echo "INFO : CodeSpell ignored words in the file : $codespell_ignore_words" || export codespell_ignore_words=$dir/codespell_ignore-words.txt

codespell_skip_ext=$dir/codespell_skip_ext.txt

declare SKIPEXT=`sed -e 's/ /+/g' $codespell_skip_ext |xargs|sed 's/ /,/g;s/+/ /g'`


set -e
[ "$DEBUG" = "" ] || set -x


set +x 
set +e

EXITVAL=0

for lpath in $PATH2CHECK; do
	if  [[ ! -d $lpath ]]
	then
		echo -e "\nError : $Wrong Path or Path does not exist! !\n"
		usage
	else
      $dir/codespell.exe -c -q4 --skip "$SKIPEXT,$SKIPPED_DIR" --ignore-words=$codespell_ignore_words -e utf-8 $lpath -d
      let EXITVAL+=$?
	  echo -e "\n*** Check Restrict the character and No accent or local decoration : \n"
	  #{Req} Restrict the character set of source files to the 7-bit ASCII set. No accent or local decoration.
	  LC_ALL=en_US.utf8
	  grep -nr -P  --include=*.[ch] --exclude-dir={Third_Party,CMSIS} '[^\x00-\x7F]' $lpath
	  if [ "$?" == "0" ]
	  then 
            echo -e "\nError : Restrict the character set of source files to the 7-bit ASCII set. No accent or local decoration.!\n"
            let EXITVAL+=1
	  fi
    echo -e "\n*** End Check Restrict the character and No accent or local decoration\n"
	fi
done

if [ "${EXITVAL}" != "0" ] ; then
	exit 2
fi
