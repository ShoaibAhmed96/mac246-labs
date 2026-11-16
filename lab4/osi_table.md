
# MAC 246 - Graded Lab 4
## Session 15: OSI Layer Incident Analysis

**Student:** Shoaib Ahmed
**Student ID:** 24364498
**Personalization Token:** 502a6d6785d7aef5

### Objective

In this exercise, I used four provided evidence files: auth.log, firewall.log, http_access.log, and capture.pcap. I checked the suspicious network activity and connected each finding to the correct OSI layer. All the analysis was done using the provided evidence files.

### OSI Layer Analysis Table

| Layer | Indicator | Evidence source | Interpretation |
|---|---|---|---|
| L2 (MAC) | ARP request and reply | capture.pcap, frames 8-9 | ARP is used to find the MAC address of a local device. |
| L2 (MAC) | Ethernet MAC fields | firewall.log, lines 1-10 | The firewall recorded hardware addresses belonging to the local network hops. |
| L3 (IP) | 198.51.100.23 communicating with 10.12.0.15 | capture.pcap, frames 10-15 | An external IP connected to the internal server using SSH. |
| L3 (IP) | 198.51.100.23 targeting 10.12.0.20 | firewall.log, lines 6-9 | The same external IP tried to reach another internal server, but its traffic was denied. |
| L4 (TCP or UDP) | TCP SYN, SYN-ACK, ACK | capture.pcap, frames 1-3 | A normal TCP three-way handshake completed successfully. |
| L4 (TCP or UDP) | Repeated SYN packets to ports 5432, 3306, 1433 and 445 | capture.pcap, frames 60-71 | These repeated connection attempts did not complete a handshake. They suggest possible service probing. |
| L4 (TCP or UDP) | Firewall denied TCP traffic to four ports | firewall.log, lines 6-9 | The firewall blocked attempted access to PostgreSQL, MySQL, Microsoft SQL Server, and SMB services. |
| L4 (TCP or UDP) | UDP destination port 53 | firewall.log, lines 2, 4, 5 and 10 | The log shows DNS traffic, including allowed and denied UDP requests. |
| L5 (Session) | SSH session opened for svc-backup | auth.log, lines 33-34 | After repeated failed logins, the same external IP successfully authenticated and opened a session. |
| L5 (Session) | TLS session established over TCP port 443 | capture.pcap, frames 44-49 | The TCP connection carried a TLS handshake followed by application data. |
| L6 (Presentation) | TLS Client Hello and Server Hello Done | capture.pcap, frames 47-48 | These packets show the TLS handshake for files.example.net. |
| L6 (Presentation) | TLS Application Data | capture.pcap, frame 49 | Application data was transferred through TLS instead of appearing as readable plain-text HTTP. |
| L7 (Application) | SSH version banners | capture.pcap, frames 13-15 | The SSH client and server exchanged protocol version information. |
| L7 (Application) | DNS query and response | capture.pcap, frames 42-43 | The internal server requested the IP address of files.example.net and received a DNS response. |
| L7 (Application) | Requests for /admin/, /.env and /.git/config | http_access.log, lines 4-6 | The external IP tried to access the administration page and locate sensitive configuration files. |
| L7 (Application) | Repeated admin login requests | http_access.log, lines 9-11 | Two requests returned 401, followed by a 302 redirect. The redirect alone does not prove successful authentication. |
| L7 (Application) | POST request to /admin/upload.php | http_access.log, line 12 | The upload endpoint returned HTTP 200, showing that the server processed the request. |
| L7 (Application) | Command-like requests to /uploads/status.php | http_access.log, lines 13-19 | Requests included command parameters such as id and uname. This suggests possible command execution, but further evidence is needed for confirmation. |
| L7 (Application) | Repeated failed SSH passwords | auth.log, lines 4-32 | The external IP repeatedly attempted different usernames and passwords, suggesting brute-force activity. |

### Main Incident Findings

The most suspicious IP in these files is 198.51.100.23.

First, I found repeated failed SSH login attempts. At 02:16:41, the server accepted a password for the svc-backup account. Two seconds later, the session was opened.

Next, I found suspicious HTTP requests. The external IP tried accessing admin pages, configuration files, and an upload endpoint. Some requests contained command-like parameters.

Finally, the firewall blocked attempts from the same IP to ports 5432, 3306, 1433, and 445.

These findings suggest a possible coordinated intrusion. However, the logs alone cannot confirm every action or determine whether the successful login was authorized.

### Layer 2 vs Layer 3

Layer 2 is the Data Link layer. It works with MAC addresses and local network communication. Switches mainly operate at this layer.

Layer 3 is the Network layer. It works with IP addresses and routing traffic between different networks. Routers mainly operate at this layer.

The firewall's MAC fields identify hardware addresses on the local link. When traffic crosses a router, the Layer 2 header changes. The original MAC address from an external attacker does not travel through every routed network.

Because of this, a MAC address recorded on the local network cannot reliably identify an attacker outside the same broadcast domain.

### Security Controls

**Layer 2 - Switch Security**

I would use port security on switches. This helps restrict which MAC addresses are allowed on switch ports and reduces unauthorized device connections.

**Layer 3 - Router Security**

I would configure router access control lists (ACLs) to block unnecessary traffic between networks. For example, external devices should not be allowed to directly access internal database ports unless there is an authorized business need.

### Conclusion

This exercise helped me understand how different logs provide different types of security evidence.

The authentication log showed SSH login attempts. The HTTP access log showed web requests. The firewall log showed allowed and blocked connections. The packet capture showed the network communication and protocols.

By checking these sources together, I was able to understand the suspicious activity and identify which OSI layers were involved.

### Reference

CompTIA Security+ SY0-701 Exam Objectives, Objective 3.2.
