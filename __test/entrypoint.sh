#!/bin/sh
ROOT="/usr/src/app"

export TERM=xterm

set -e

#if [ ! -f "$ROOT/*.test.c" ]; then
#echo "Erro: Nenhum '.test.c' não encontrado!"
#exit 1
#fi

clear
echo "Monitorando alterações em test.c..."

while inotifywait -e close_write $ROOT/*.test.c; do
    clear
    echo "Compilando test.c..."
    gcc $ROOT/*.test.c -o $ROOT/test -lcriterion
    chmod +x $ROOT/test
    $ROOT/test || true
done