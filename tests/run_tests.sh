#!/usr/bin/env bash
# Executa cada joc de prova (tests/*.ent) i compara la sortida amb el .cor corresponent.
# El programa mostra el títol i el menú abans de llegir la primera ordre: es descarten
# fins al primer "Introduïu l'opció desitjada:", igual que les línies en blanc.
set -u
BIN="${1:-./crypto}"
DIR="$(cd "$(dirname "$0")" && pwd)"
pass=0; fail=0

run() {
    "$BIN" < "$1" \
        | sed -n "/^Introduïu l'opció desitjada:/,\$p" \
        | sed "1s/^Introduïu l'opció desitjada: *//" \
        | sed '/^[[:space:]]*$/d'
}

for ent in "$DIR"/*.ent; do
    name="$(basename "$ent" .ent)"
    cor="${ent%.ent}.cor"
    if diff -u "$cor" <(run "$ent") > /dev/null; then
        echo "OK    $name"
        pass=$((pass + 1))
    else
        echo "FAIL  $name"
        diff -u "$cor" <(run "$ent") | head -30
        fail=$((fail + 1))
    fi
done

echo "--------------------"
echo "$pass OK, $fail FAIL"
[ "$fail" -eq 0 ]
