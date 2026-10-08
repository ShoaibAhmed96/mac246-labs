# MAC246 Lab 2 Security Briefing

## To: IT Director
## Subject: CVE-2026-20105 - Cisco Remote Access SSL VPN DoS

The highest-priority CVE from my CVSS work is CVE-2026-20105. It affects Cisco Secure Firewall ASA and FTD Remote Access SSL VPN.

The vulnerability can be used by an authenticated remote attacker who already has a valid VPN connection. The attacker can send specially made packets to the VPN service and cause the device to run out of memory. This can make the firewall reload and create a denial-of-service condition.

The CVSS v3.1 score is 7.7, which is High. Because this affects a firewall/VPN gateway, I would treat it as an important issue.

My risk register includes a Firewall/VPN Gateway row. I marked the treatment as Mitigate. Because of that, the organization should check the affected software version immediately and plan the vendor update as soon as possible. Until the update is completed, VPN activity should be monitored for unusual traffic or repeated connection problems.

NVD:
https://nvd.nist.gov/vuln/detail/CVE-2026-20105

Cisco Advisory:
https://sec.cloudapps.cisco.com/security/center/content/CiscoSecurityAdvisory/cisco-sa-asaftd-vpn-m9sx6MbC
