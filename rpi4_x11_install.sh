#!/bin/bash

dir=$(/usr/bin/dirname $0)

cp -aRrf ${dir}/bin/webplay /usr/bin/
cp -aRrf ${dir}/bin/webplayrun /usr/bin/

mkdir -p /etc/webplay
cp -aRrf ${dir}/etc/log4qt.properties /etc/webplay/
ldconfig

sed -i 's/raspbian.raspberrypi.org/mirrors4.tuna.tsinghua.edu.cn\/raspbian/' /etc/apt/sources.list
sed -i 's/archive.raspberrypi.org\/debian/mirrors4.tuna.tsinghua.edu.cn\/raspberrypi/' /etc/apt/sources.list.d/raspi.list

apt-get update

dpkg --unpack ${dir}/deb/libqt5webchannel5_5.11.3-2_armhf.deb \
	${dir}/deb/libqt5webengine5_5.11.3+dfsg-2+deb10u1_armhf.deb \
	${dir}/deb/libqt5webenginewidgets5_5.11.3+dfsg-2+deb10u1_armhf.deb \
	${dir}/deb/libqt5webchannel5-dev_5.11.3-2_armhf.deb \
	${dir}/deb/libqt5webenginecore5_5.11.3+dfsg-2+deb10u1_armhf.deb \
	${dir}/deb/qtwebengine5-dev_5.11.3+dfsg-2+deb10u1_armhf.deb

apt-get install -f -y

raspi-config nonint do_memory_split 256

sync

echo "Successful installation -> Please reboot system"
