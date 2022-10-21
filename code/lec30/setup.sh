#!/usr/bin/env bash
OTHERUSER=$1
if [[ "$OTHERUSER" == "" ]]; then
 echo 'Specify username e.g. _sshd (mac), sshd (Linux), admin (my mac)'
 exit 1
fi

echo "Chocolate" > secret.txt

echo "On Ubuntu you may need to  sudo apt install uuid-dev"
echo "Changing permisions and Setting secret.txt and a.out to be owned by $OTHERUSER"
echo "After compiling, try running a.out under sudo and try setuid too"

sudo chown "$OTHERUSER" secret.txt
sudo chmod 400 secret.txt
sudo rm hal 2>/dev/null
gcc hal.c -o hal
sudo chown "$OTHERUSER" hal
ls -al
