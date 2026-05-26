# 🌌 Swayambhu: Next-Gen Zero-Trust Kernel Protection

**Swayambhu** is an autonomous, eBPF-based security framework designed for real-time kernel integrity monitoring and self-healing. Unlike traditional signature-based antiviruses, Swayambhu provides **Behavioral Integrity Enforcement** at the kernel level, ensuring your system remains secure against memory-corruption and unauthorized execution.

## 🚀 Vision
Security should be proactive, not reactive. Swayambhu (Sanskrit for "Self-manifested") ensures the system integrity is self-maintained, providing a resilient defense layer against modern exploits.

## 🛡️ Core Features
* **eBPF Kernel-Space Guard:** Hooks into `sys_openat` and other syscalls for real-time unauthorized access prevention.
* **Behavioral Audit:** Monitors process integrity to detect and terminate shellcode injection attempts.
* **Atomic Security:** Implements atomic locking to mitigate TOCTOU (Time-of-Check to Time-of-Use) vulnerabilities.
* **Deterministic Hashing:** Uses SHA-256 for secure, collision-resistant resource tracking.
* **Adaptive Policy Manager:** A modular TUI (Terminal User Interface) for live policy enforcement and system updates.

## 📂 Project Structure
```text
Swayambhu/
├── src/
│   ├── kernel_probe.c    # eBPF Logic (Kernel Sentinel)
│   ├── policy_manager.py # Main Control Logic (TUI)
│   └── utils.py          # Hashing & Sync modules
├── docs/                 # Architecture & Design documentation
├── README.md
└── LICENSE
Quick Start
Prerequisites
Linux Kernel 5.x+
BCC Toolkit & Python3
sudo apt install bpfcc-tools linux-headers-$(uname -r)
Installation & Usage
bash
# Clone the repository
git clone [https://github.com/vivandhakad143-ui/Swayambhu.git](https://github.com/vivandhakad143-ui/Swayambhu.git)
cd Swayambhu

# Run the Policy Manager
sudo python3 src/policy_manager.py

⚠️ Security Warning
This tool operates at the Kernel-Level. Improper configuration may impact system stability. Use only in controlled testing environments (e.g., Virtual Machines).
🤝 Contributing
Contributions are welcome! If you find a bug or have a feature request, please open an issue or submit a pull request.
📜 License
This project is licensed under the MIT License.
