# Disable ssh access to root user

Open file 

**/etc/ssh/sshd_config**

change/create/uncomment line to the following:

**PermitRootLogin no**

Restart SSHD server.

- CentOS

```service sshd restart```

- Ubuntu

```service ssh restart```
