#!/bin/bash
PATH_ASTYLE_TOOL="../../../../../__INTERNAL__tools/tools/McuAStyle"
#PATH_ASTYLE_TOOL="./mcuastyle"

for d in ../config/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_config.log

for d in ../common/core/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_core.log

for d in ../common/modules/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_modules.log

for d in ../common/monitoring/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_monitoring.log

for d in ../common/proclist/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_proclist.log

for d in ../common/utilities/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_utilities.log

for d in ../interfaces/ ; do
  $PATH_ASTYLE_TOOL/mcuAStyle.exe -I --recursive --options=$PATH_ASTYLE_TOOL/formattingOption.txt "$d*.c" "$d*.h" >> temp.txt
  if grep -q "Formatted" temp.txt; then
    echo $d >> McuAstyleConcat.log
    grep "Formatted" temp.txt >> McuAstyleConcat.log
    echo >> McuAstyleConcat.log
  fi
  rm temp.txt
  cat ./McuAstyle.log >> ./McuAstyleConcat.log
done
mv -f ./McuAstyleConcat.log ./McuAstyle_interfaces.log
