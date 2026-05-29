#!/bin/bash

# Swayambhu Layer 1: Process Integrity Monitor
LOG_FILE="/tmp/swayambhu_layer1.log"

echo "[+] Swayambhu Layer 1: Process Monitor Active..." | tee -a $LOG_FILE

while true; do
    # 1. Check for suspicious processes (e.g., processes with no name or hidden in tmp)
    # Check if any process is running from /tmp or /dev/shm (Common for injection payloads)
    suspicious=$(ps aux | grep -E '/tmp/|/dev/shm/' | grep -v grep)

    if [ -n "$suspicious" ]; then
        echo "[!] SECURITY ALERT: Suspicious process detected in memory!" | tee -a $LOG_FILE
        echo "$suspicious" | tee -a $LOG_FILE
        
        # Auto-Kill Action
        pid=$(echo "$suspicious" | awk '{print $2}')
        kill -9 $pid
        echo "[+] Defence: Process $pid terminated successfully." | tee -a $LOG_FILE
    fi

    # 2. Monitor for new PIDs
    # Logic to detect if a process is suddenly trying to ptrace another process
    # (Memory injection detection)
    
    sleep 5 # Monitor cycle (5 seconds)
done