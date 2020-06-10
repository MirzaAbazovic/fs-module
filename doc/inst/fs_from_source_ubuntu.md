# INSTALL FreeSWITCH (FS) from source code

## Compiling from source code (latest master) 

### Prepare:

1. Install: gnupg2, wget, lsb-release
2. Add GPG FS key freeswitch_archive_g0.pub from
 https://files.freeswitch.org/repo/deb/debian-unstable
3. Update apt source list with freeswitch
4. Install FS dependencies
5. Clone
6. Run bootstrap script that starts building 


```bash
apt-get update && apt-get install -yq gnupg2 wget lsb-release
wget -O - https://files.freeswitch.org/repo/deb/debian-unstable/freeswitch_archive_g0.pub | apt-key add -
 
echo "deb http://files.freeswitch.org/repo/deb/debian-unstable/ `lsb_release -sc` main" > /etc/apt/sources.list.d/freeswitch.list
echo "deb-src http://files.freeswitch.org/repo/deb/debian-unstable/ `lsb_release -sc` main" >> /etc/apt/sources.list.d/freeswitch.list
 
apt-get update
 
# Install dependencies required for the build
apt-get build-dep freeswitch
 
cd /usr/src/
# Then let's get the source. Use the -b flag to get a specific branch. For example:
# git clone https://github.com/signalwire/freeswitch.git -bv1.10.2 freeswitch
git clone https://github.com/signalwire/freeswitch.git freeswitch
cd freeswitch
 
# Because we're in a branch that will go through many rebases, it's
# better to set this one, or you'll get CONFLICTS when pulling (update).
git config pull.rebase true
 
# ... and do the build
 
# The -j argument spawns multiple threads to speed the build process, but causes trouble on some systems
./bootstrap.sh -j
```

### Select modules

    if you want to add or remove modules from the build, edit modules.conf
    
    ```vi modules.conf```
    
    add a module by removing '#' comment character at the beginning of the line
    
    remove a module by adding the '#' comment character at the beginning of the line  containing the name of the module to be skipped in the build process

 
### Build

 ```bash
./configure
make
make install
# Install audio files:
make cd-sounds-install cd-moh-install
```

### Update

```bash
# To update an installed build:
cd /usr/src/freeswitch
make current
```
## Build module

If You make changes on some module rebuild him using make mod_XXX-install

```bash
make mod_sofia-install
```

# Post install

```bash
# create user 'freeswitch'
cd /usr/local
groupadd freeswitch
# add it to group 'freeswitch'
adduser --quiet --system --home /usr/local/freeswitch --gecos "FreeSWITCH open source softswitch" --ingroup freeswitch freeswitch --disabled-password
# change owner and group of the freeswitch installation
chown -R freeswitch:freeswitch /usr/local/freeswitch/
chmod -R ug=rwX,o= /usr/local/freeswitch/
chmod -R u=rwx,g=rx /usr/local/freeswitch/bin/*
```



**Have scripts just make them executable (and optionally edit modules.conf before running install-fs):**

```bash
chmod +x prepare-fs.sh 
chmod +x install-fs.sh 
chmod +x post-install-fs.sh 
chmod +x update-fs.sh 
```

Scripts:

- [prepare-fs.sh](../../src/install/ubuntu-scripts/prepare-fs.sh)
- [install-fs.sh](../../src/install/ubuntu-scripts/install-fs.sh)
- [post-install-fs.sh](../../src/install/ubuntu-scripts/post-install-fs.sh)
- [update-fs.sh](../../src/install/ubuntu-scripts/update-fs.sh)

## RUN it

Manually:

```/usr/local/freeswitch/bin/freeswitch- u freeswitch -g freeswitch -c```

As service:

You can also install it as a service by cretaing file /etc/systemd/system/freeswitch.service
with content [freeswitch.service](../../src/conf/freeswitch.service)

Relaod systemd config

```systemctl daemon-reload```

Start FreeSWITCH

```systemctl start freeswitch```

Stop FreeSWITCH:

```systemctl stop freeswitch```

Configure FreeSWITCH to start automatically at boot time:

```systemctl enable freeswitch```

To determine if FreeSWITCH is actually running, use one of these commands:

```ps aux | grep freeswitch```

```ps -e | grep freeswitch```

Either of the above should display a line beginning with the pid (process id) of freeswitch if it is indeed running. Ignore the line that matches the grep command since it also contains the string "freeswitch".

```pidof freeswitch```

pidof returns the process id of the named process. In this case, if FreeSWITCH is running you will see only its pid; if it prints nothing at all, then FreeSWITCH is not running.

