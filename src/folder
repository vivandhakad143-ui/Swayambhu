#!/bin/bash

# ============================================================
# Swayambhu Layer 1: Process Integrity Monitor
# Version: 1.0
# Author: Swayambhu Security Framework
# Description: Monitors running processes for suspicious
#              activity including injection payloads,
#              ptrace attempts, and hidden processes.
# ============================================================

LOG_FILE="/tmp/swayambhu_layer1.log"
ALERT_COUNT=0

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}[+] Swayambhu Layer 1: Process Monitor Active...${NC}" | tee -a $LOG_FILE
echo "[*] Timestamp: $(date)" | tee -a $LOG_FILE
echo "-------------------------------------------" | tee -a $LOG_FILE

while true; do

    # -------------------------------------------------------
    # CHECK 1: Processes running from suspicious locations
    # /tmp or /dev/shm are common for injection payloads
    # -------------------------------------------------------
    suspicious=$(ps aux | grep -E '/tmp/|/dev/shm/' | grep -v grep)

    if [ -n "$suspicious" ]; then
        ALERT_COUNT=$((ALERT_COUNT + 1))
        echo -e "${RED}[!] ALERT #$ALERT_COUNT: Suspicious process in memory!${NC}" | tee -a $LOG_FILE
        echo "$suspicious" | tee -a $LOG_FILE

        pid=$(echo "$suspicious" | awk '{print $2}')
        kill -9 $pid 2>/dev/null
        echo -e "${GREEN}[+] Defence: Process $pid terminated.${NC}" | tee -a $LOG_FILE
    fi

    # -------------------------------------------------------
    # CHECK 2: ptrace / memory injection detection
    # Processes trying to attach to other processes
    # -------------------------------------------------------
    ptrace_suspects=$(grep -r "TracerPid" /proc/*/status 2>/dev/null | grep -v "TracerPid:	0")

    if [ -n "$ptrace_suspects" ]; then
        echo -e "${RED}[!] ALERT: ptrace/injection attempt detected!${NC}" | tee -a $LOG_FILE
        echo "$ptrace_suspects" | tee -a $LOG_FILE
    fi

    # -------------------------------------------------------
    # CHECK 3: Processes with no name (hidden/zombie)
    # -------------------------------------------------------
    hidden=$(ps aux | awk '{print $11}' | grep -E '^\[.*\]$' | grep -v -E '\[kworker|kthread|migration|rcu|watchdog|ksoftirq\]')

    if [ -n "$hidden" ]; then
        echo -e "${YELLOW}[~] WARNING: Unusual kernel-space process detected!${NC}" | tee -a $LOG_FILE
        echo "$hidden" | tee -a $LOG_FILE
    fi

    # -------------------------------------------------------
    # CHECK 4: High CPU usage by unknown processes
    # -------------------------------------------------------
    high_cpu=$(ps aux --sort=-%cpu | awk 'NR>1 && $3>80 {print $0}')

    if [ -n "$high_cpu" ]; then
        echo -e "${YELLOW}[~] WARNING: High CPU usage detected!${NC}" | tee -a $LOG_FILE
        echo "$high_cpu" | tee -a $LOG_FILE
    fi

    echo "[*] Scan complete: $(date) | Total Alerts: $ALERT_COUNT" | tee -a $LOG_FILE
    echo "-------------------------------------------" | tee -a $LOG_FILE

    sleep 5
done
