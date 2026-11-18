import subprocess
cmd = ['tshark', '-r', 'wifi_sample.pcap', '-Y', 'wlan.fc.type_subtype == 0x08',
       '-T', 'fields', '-e', 'wlan.ssid', '-e', 'wlan.bssid',
       '-e', 'wlan_radio.channel']
out = subprocess.run(cmd, capture_output=True, text=True).stdout
seen = set()
for line in out.splitlines():
    ssid, bssid, chan = (line.split('\t') + ['', '', ''])[:3]
    try:
        ssid = bytes.fromhex(ssid).decode()
    except ValueError:
        pass
    seen.add((ssid, bssid, chan))
print(f"{'SSID':16} {'BSSID':18} channel")
for ssid, bssid, chan in sorted(seen):
    print(f'{ssid:16} {bssid:18} {chan}')
