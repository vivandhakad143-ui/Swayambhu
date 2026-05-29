import subprocess
import os

# Jise protect karna hai
PROTECTED_FILE = "secret.txt"

print(f"Swayambhu Sentinel Active: Monitoring {PROTECTED_FILE}...")

# inotifywait command: 'modify' use kiya hai taaki sirf access nahi,
# file mein change (tampering) bhi detect ho
cmd = ["inotifywait", "-e", "modify", "-e", "open", PROTECTED_FILE]

while True:
    try:
        # File access ya modify hote hi trigger hoga
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        # Alert trigger
        print(f"\n[!] ALERT: Unauthorized access/tampering attempt on {PROTECTED_FILE}!")
        print("[!] Swayambhu Sentinel: Blocked Access at Kernel-Level (Simulation).")
        
    except KeyboardInterrupt:
        print("\nSentinel Stopped.")
        break
