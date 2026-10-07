# MAC246 Lab 2 Incident Response Report

## Detection
Repeated failed SSH login attempts from 198.51.100.23 began at 10:07:12 PM EDT on September 29, 2026. At 10:16:41 PM, the same source successfully authenticated to the svc-backup account.

## Analysis
After the SSH compromise, the same IP accessed the web server, attempted several administrative paths, successfully logged in to /admin/login.php, uploaded a file, and executed commands through /uploads/status.php. Firewall logs later showed attempts to reach internal services on ports 5432, 3306, 1433, and 445.

## Containment
The affected web server should be isolated from the network. Access from 198.51.100.23 should be blocked, and the svc-backup account should be disabled or have its credentials reset immediately.

## Eradication
Remove the uploaded status.php file, review the host for additional unauthorized files or persistence, patch the affected web application, and remove any compromised credentials or accounts.

## Recovery
Restore the server from a trusted state if necessary, re-enable services only after validation, reset affected passwords, enforce MFA, and monitor logs for additional suspicious activity.

## Lessons Learned
Repeated authentication failures should trigger faster investigation. MFA, network segmentation, stronger monitoring, and tighter administrative access controls could reduce the likelihood and impact of a similar incident.

## Timeline

| Local Time (EDT) | Event |
|---|---|
| Sep 29 10:07:12 PM | First failed SSH login from 198.51.100.23 |
| Sep 29 10:16:41 PM | Successful login to svc-backup |
| Sep 29 10:17:33 PM | Web reconnaissance begins |
| Sep 29 10:18:45 PM | Admin login returns HTTP 302 |
| Sep 29 10:19:07 PM | File uploaded through admin upload page |
| Sep 29 10:19:58 PM | First command executed through status.php |
| Sep 29 10:26:41 PM | Firewall blocks PostgreSQL connection attempt |
| Sep 29 10:31:05 PM | Firewall blocks SMB connection attempt |
