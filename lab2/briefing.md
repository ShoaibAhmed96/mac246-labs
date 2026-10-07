# MAC246 Lab 2 Security Briefing


## Incident Summary
The incident started with repeated failed SSH login attempts from 198.51.100.23. A successful login to the svc-backup account was later recorded. Soon after, the same source accessed the web admin area, uploaded a file, and executed commands through status.php. Firewall logs also showed attempts to reach internal database and SMB ports.

## Key Evidence
The authentication log showed many failed SSH attempts followed by an accepted password for svc-backup. The web access log showed a successful admin login, an upload request, and command execution through status.php. The firewall log recorded denied connection attempts to database and SMB ports.

## Highest Risks
The highest risks were compromise of the svc-backup account, unauthorized web admin access, command execution through the uploaded web shell, and attempts to reach internal services.

## Recommended Actions
Immediately reset the svc-backup credentials, enable MFA, restrict SSH access, isolate the affected web server, remove the uploaded web shell, review admin activity, and block unnecessary access to internal database and SMB services.

## Lessons Learned
This incident shows how one compromised account can lead to broader system access. Centralized logging, MFA, network segmentation, patching, and faster investigation of repeated login failures can reduce the chance and impact of a similar attack.
