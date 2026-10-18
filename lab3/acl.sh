# Illustrative rules; do not execute on your host.
iptables -A INPUT -p tcp -d 203.0.113.10 --dport 443 -j ACCEPT
iptables -A FORWARD -s 203.0.113.10 -d 10.0.0.20 -p tcp --dport 5432 -j ACCEPT
iptables -A FORWARD -d 10.0.0.20 -j DROP
iptables -A INPUT -s 198.51.100.0/24 -p tcp --dport 22 -j ACCEPT
iptables -A INPUT -j DROP
