#!/bin/bash

switchcube 1

# Trouver le chemin absolu du dossier courant
HSP_INTERNAL_DIR="$(pwd)"
HSP_INTERNAL_DIR_WIN="$(pwd -W)"
# Remonter jusqu'à trouver le dossier __INTERNAL__cubeDriver
WORKSPACE_DRIVER_PATH="$HSP_INTERNAL_DIR"
while [[ "$WORKSPACE_DRIVER_PATH" != "/" && ! -d "$WORKSPACE_DRIVER_PATH/__INTERNAL__cubeDriver" ]]; do
    WORKSPACE_DRIVER_PATH="$(dirname "$WORKSPACE_DRIVER_PATH")"
done

if [[ ! -d "$WORKSPACE_DRIVER_PATH/__INTERNAL__cubeDriver" ]]; then
    echo "Erreur : Impossible de trouver le dossier __INTERNAL__cubeDriver dans la hiérarchie."
    exit 1
fi

CUBEDRIVER_PATH=$WORKSPACE_DRIVER_PATH/__INTERNAL__cubeDriver

echo "HSP_INTERNAL_DIR: $HSP_INTERNAL_DIR"
echo "HSP_INTERNAL_DIR_WIN: $HSP_INTERNAL_DIR_WIN"
echo "WORKSPACE_DRIVER_PATH: $WORKSPACE_DRIVER_PATH"
echo "CUBEDRIVER_PATH: $CUBEDRIVER_PATH"

#ln -s $HSP_INTERNAL_DIR/../../hsp_engine_cube1 $HSP_INTERNAL_DIR/../../hsp_engine
cmd //c mklink /D "$HSP_INTERNAL_DIR_WIN\\..\\..\\hsp_engine" "$HSP_INTERNAL_DIR_WIN\\..\\..\\hsp_engine_cube1"

cd $WORKSPACE_DRIVER_PATH/__INTERNAL__tools/tools/NonRegressionScript
python automatic_check.py -f $HSP_INTERNAL_DIR/jenkins/jenkins_config.xml -p_iar "C:\Program Files\IAR Systems\Embedded Workbench 9.2" > $HSP_INTERNAL_DIR/compilation_result.txt
date >> $HSP_INTERNAL_DIR/compilation_result.txt
read -n1 -r -p "Press any key to continue..." key

#rm $HSP_INTERNAL_DIR/../../hsp_engine