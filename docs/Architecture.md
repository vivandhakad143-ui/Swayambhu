# 🏛️ Swayambhu Architecture Design

Swayambhu is designed as a **Kernel-Level Integrity Sentinel**. Its architecture follows a decoupled design to ensure maximum performance (Zero-Overhead) while maintaining strict security enforcement.

## 1. High-Level Flow
The system operates in three distinct layers:
1.  **Monitoring Layer (eBPF):** Hooking syscalls (e.g., `sys_openat`) at the kernel level.
2.  **Verification Layer (Memory/eBPF Map):** Cross-referencing file hashes against a secure, immutable BPF map.
3.  **Governance Layer (Policy Manager):** A user-space Python controller to manage policies and log audit trails.

## 2. Component Diagram
```text
[User Space]
    |-- Policy Manager (Python) <---> [eBPF Map (protected_hashes)]
    |
[Kernel Space]
    |-- eBPF Program (Sentinel)
    |-- Hook Point: kprobe__sys_openat
    |-- Action: Block/Allow based on Map lookup

3. Data Integrity Flow
Deterministic Hashing: We utilize SHA-256 to generate truncated, kernel-compatible identifiers for system files.
Atomic Enforcement: By using BPF maps, we eliminate race conditions (TOCTOU) common in traditional user-space antivirus solutions.
Self-Healing Loop: Any unauthorized change to a protected path triggers a kernel-space exception, effectively neutering the exploit before execution.

4. Why eBPF?
Standard AV/EDR solutions operate in User-Space, introducing latency and bypassing capability. Swayambhu resides in the kernel, executing logic in nanoseconds with zero context switching, providing Hardened Integrity that is immune to process-hollowing or code-injection attacks.

5. Future Roadmap
Log Exporter: Integration with syslog for centralized monitoring.
Adaptive Baseline: Automatic hash updates via signed system update scripts.
TUI Enhancements: Real-time attack heatmaps.