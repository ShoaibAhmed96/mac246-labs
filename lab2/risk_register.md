| Risk | Evidence | Likelihood | Impact | Mitigation |
|------|----------|------------|--------|------------|
| Compromised service account | Repeated SSH failures followed by successful login to svc-backup | High | High | Reset credentials, enforce MFA, restrict SSH access |
| Web admin compromise | Successful admin login followed by upload activity | High | High | Patch app, disable exposed admin access, review uploaded files |
| Web shell / command execution | Requests to status.php executed commands such as id and uname | High | Critical | Remove web shell, isolate host, rebuild if needed |
| Internal network reconnaissance | Firewall logs show probes to database and SMB ports | Medium | High | Segment network, block unnecessary ports, monitor east-west traffic |
| Phishing credential theft | Email showed SPF/DMARC failures and misleading link | Medium | High | User training, email filtering, enforce MFA |
