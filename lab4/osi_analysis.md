
# MAC 246 - Lab 4
## Section 2: OSI Layer Incident Analysis

**Student:** Shoaib Ahmed  
**Student ID:** 24364498  
**Personalization Token:** 502a6d6785d7aef5

### Objective

In this section, I analyzed four provided evidence files to understand suspicious network activity. I checked authentication logs, firewall logs, HTTP access logs, and packet captures. My goal was to identify which activities happened at each OSI layer.

### OSI Layer Analysis Table

| Layer | Indicator | Evidence Source | Interpretation |
|---|---|---|---|
| L2 - Data Link | ARP request and reply, packets 8-9 | capture.pcap | The devices used ARP to find the MAC address for a local IP address. |
| L2 - Data Link | MAC addresses in firewall entries | firewall.log | The firewall recorded Ethernet MAC addresses. A remote attacker's MAC address does not travel across routers. |
| L3 - Network | 198.51.100.23 to 10.12.0.15 | capture.pcap, auth.log | An external IP address connected to the internal web server using SSH. |
| L3 - Network | 198.51.100.23 to 10.12.0.20 | firewall.log | The same external IP attempted to reach another internal server, but the firewall denied the traffic. |
| L4 - Transport | TCP SYN, SYN-ACK, ACK, packets 1-3 | capture.pcap | A normal TCP three-way handshake completed successfully. |
| L4 - Transport | Repeated SYN packets to ports 5432, 3306, 1433 and 445 | capture.pcap, firewall.log | These attempts targeted database and SMB services. No completed connection was observed, and the firewall recorded DENY actions. |
| L4 - Transport | UDP destination port 53 | firewall.log | The firewall recorded DNS traffic using UDP. Some DNS requests were denied. |
| L5 - Session | Successful SSH login for svc-backup at 02:16:41 | auth.log | After many failed attempts from 198.51.100.23, the server accepted a password and opened an SSH session. This is suspicious. |
| L5 - Session | TCP connection established before TLS communication | capture.pcap | A connection was established before the TLS session exchanged application data. |
| L6 - Presentation | TLS Client Hello and Server Hello Done, packets 47-48 | capture.pcap | The capture shows a TLS handshake for files.example.net. |
| L6 - Presentation | TLS Application Data, packet 49 | capture.pcap | The application data was carried inside TLS rather than shown as readable HTTP. |
| L7 - Application | GET /admin/ and requests for /.env and /.git/config | http_access.log | The external IP tried to access the admin area and locate sensitive configuration files. |
| L7 - Application | POST /admin/login.php returning 401, 401 and 302 | http_access.log | There were failed login attempts followed by a redirect, suggesting a possible change in authentication state. |
| L7 - Application | POST /admin/upload.php returning 200 | http_access.log | The server accepted an upload request from the suspicious IP. |
| L7 - Application | GET /uploads/status.php?cmd=id returning 200 | http_access.log, capture.pcap | The request contained a command-like parameter. This suggests possible command execution, but the logs alone do not prove execution. |
| L7 - Application | DNS query for files.example.net, packets 42-43 | capture.pcap | The server performed a DNS lookup and received an IP address in the response. |
| L7 - Application | SSH-2.0 protocol banners, packets 13-15 | capture.pcap | The SSH client and server exchanged version information. |

### Main Findings

The most suspicious IP address in these files was 198.51.100.23.

First, I found many failed SSH login attempts from this IP address. At 02:16:41, the same IP successfully logged into the svc-backup account.

Next, I found HTTP requests targeting the admin page, configuration files, and an upload endpoint. Some requests contained command-like parameters.

Finally, the firewall blocked connection attempts from the same IP to ports 5432, 3306, 1433, and 445.

These findings suggest a possible coordinated intrusion. However, I would need additional server evidence to confirm the full extent of the compromise.

### Layer 2 vs Layer 3

Layer 2 works with MAC addresses inside the local network. Layer 3 uses IP addresses to communicate between different networks.

One important thing I learned is that a remote attacker's original MAC address does not travel across routed networks. The firewall normally sees the MAC address of the previous network hop.

### Conclusion

This exercise helped me understand how different logs show different parts of a security incident. Authentication logs show login attempts, firewall logs show blocked connections, HTTP logs show web requests, and packet captures show network communication.

By checking all four files together, I could better understand the suspicious activity and identify the OSI layers involved.

### Reference

CompTIA Security+ SY0-701, Objective 3.2.

