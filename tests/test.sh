#!/bin/bash

# Chemin vers les tests
TEST_PATH="tests"

# Dossier pour les logs
LOG_DIR="logs"
mkdir -p "$LOG_DIR"

# Exécuter les tests de 1 à 15 et le test 7_1
for i in {1..15} 7_1; do
    TEST_CMD="./minishell"
    LOG_FILE="$LOG_DIR/test_${i}.log"
    
    echo "Lancement du test $i..."
    $TEST_CMD < $TEST_PATH/cmd${i} > "$LOG_FILE" 2>&1
    
    echo "Log du test $i stocké dans $LOG_FILE"
done
