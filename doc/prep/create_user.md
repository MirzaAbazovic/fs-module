# Manipulation with users on Centos

## List users

To list users:

```cat /etc/passwd```

Centos:

```getent passwd``

for specific user

```getent passwd username```

## Manipulate users

Create user hamo:

```useraadd hamo```

If there is no sudo install it:

```yum install sudo -y```

Add user to sudoers

- for CentOS

```usermod -aG wheel hamo```

- for Debian

```usermod -aG sudo hamo```

or edit visudo with

```sudo visudo```

or like this

```vim /etc/sudoers```

add line

**hamo ALL=(ALL) ALL**

Delete user with username hamo

```userdel hamo```

To remove all the files for the user, then use -r:

```userdel -r hamo``
