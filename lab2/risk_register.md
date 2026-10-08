| Asset | Threat | Likelihood | Impact | Inherent Risk | Treatment | Control | Residual Risk |
|---|---|---|---|---|---|---|---|
| Web Server (Linux VM) | Web shell or unauthorized command execution | High | High | H | Mitigate | Patch the web app and restrict file uploads | M |
| Database Server (Linux VM) | Unauthorized database access | Medium | High | H | Mitigate | Firewall rules and network segmentation | M |
| Backup/Utility Server (Linux VM) | SSH credential compromise | High | High | H | Mitigate | MFA, SSH keys, and restricted SSH access | M |
| Windows Analysis Host | Malware execution during analysis | Medium | High | H | Mitigate | Use an isolated VM and endpoint protection | L |
| Firewall/VPN Gateway | Remote Access VPN denial of service | Medium | High | H | Mitigate | Apply vendor patches and monitor VPN traffic | M |
