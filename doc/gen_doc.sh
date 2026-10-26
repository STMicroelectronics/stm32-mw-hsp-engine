#!/bin/bash
set -e

DOXYFILE="doxychm.txt"
HHC="/c/Program Files (x86)/HTML Help Workshop/hhc.exe"
HTML_OUTPUT_DIR="./html"
CHM_OUTPUT_DIR="./chm"
CHM_NAME="mw_hsp_engine.chm"

echo "=== Génération de la documentation avec Doxygen ==="
doxygen "$DOXYFILE"

echo "=== Compilation du CHM avec hhc.exe ==="

# Vérif existence de index.hhp
if [ ! -f "./html/index.hhp" ]; then
    echo "Erreur : ./html/index.hhp introuvable. La génération HTMLHELP a t-elle bien réussi ?"
    exit 1
fi

# Vérif existence de hhc.exe
if [ ! -f "$HHC" ]; then
    echo "Erreur : hhc.exe introuvable à l'emplacement :"
    echo "  $HHC"
    echo "Adapte la variable HHC dans ce script."
    exit 1
fi

# Création dossier de sortie chm si nécessaire
mkdir -p "$CHM_OUTPUT_DIR"

# Aller dans le répertoire html et lancer hhc
echo "Lancement de : \"$HHC\" $HTML_OUTPUT_DIR/index.hhp"
# Désactiver -e localement pour ne pas stopper le script si hhc retourne un code d'erreur
set +e
"$HHC" $HTML_OUTPUT_DIR/index.hhp
HHC_RC=$?
# Réactiver -e localement pour stopper le script sur erreur
set -e

echo "hhc.exe terminé avec code de retour: $HHC_RC (ignoré si le .chm est bien généré)"

# Recherche du .chm généré dans html/
CHM_GENERATED="$(ls html/*.chm 2>/dev/null | head -n 1 || true)"

if [ -z "$CHM_GENERATED" ]; then
    echo "Erreur : aucun fichier .chm généré dans html/."
    echo "Vérifie les messages de hhc (popups / console)."
    exit 1
fi

echo "=== Déplacer le fichier CHM vers $CHM_OUTPUT_DIR/$CHM_NAME ==="
mv "$CHM_GENERATED" "$CHM_OUTPUT_DIR/$CHM_NAME"

echo "Succès : CHM disponible ici : $CHM_OUTPUT_DIR/$CHM_NAME"