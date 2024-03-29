# webplay

专为树莓派(Raspberry Pi)设计的基于(WebEngine)的全屏展示浏览器 ...

---

一款开箱即用，全屏展示浏览器，可以自定义分辨率，窗口化、展示页，等 ...

---

[支持硬件](#支持硬件)  
[支持系统](#支持系统)  
[目录结构](#目录结构)  
[安装方法](#安装方法)  
[开机启动](#开机启动)  

---
### 支持硬件

| 硬件 | 测试 |
| --- | --- |
| Raspberry Pi 4B | 已测试 |

---
### 支持系统

| 系统版本 | 发布日期 | 安装程序 | 测试 |
| --- | --- | --- | --- |
| Raspberry Pi OS with desktop | 2020-12-02 | rpi4_x11_install.sh | 已测试 |

---
### 目录结构

```
/usr/bin/webplayrun             启动脚本(启动参数)
/usr/bin/webplay                主程序
/etc/webplay/log4qt.properties  日志配置文件
/etc/webplay/webplay.pid        运行时进程ID
```

---
### 安装方法
 
 ***1. 安装程序***
 
 > 下载
 
 ```
 git clone https://github.com/nulijiabei/webplay.git
 或 
 git clone https://gitee.com/nljb/webplay.git
 ```
 
 > 安装
 
 ```
 cd webplay/ ; sh -x rpi4_x11_install.sh
 ```
 
 ***2. 运行程序***
 
 | 参数 | 默认 | 说明 |
 | --- | --- | --- |
 | -version | 无 | 版本号 |
 | -R x,y,width,height | 0,0,1920,1080 | 分辨率设置 |
 | -window | 无 | 窗口化 |
 | -no-cursor |	无 | 隐藏鼠标 |
 | -no-scrollbars | 无 | 隐藏滚动条 |
 | -remote-debug | 无 | 远程调试 |
 | -gpu | 无 | 显示 GPU 信息 |
 | -webpage | http://127.0.0.1:8080 | 展示页 |
 
 ```
 // 使用脚本启动(可以编辑脚本内参数) ...
 /usr/bin/webplayrun
 
 // 使用程序启动 ...
 /usr/bin/webplay -R 0,0,1920,1080 -webpage http://www.baidu.com
 ```
 
 ***3. 查看日志***
 ```
 tail -n 100 /dev/shm/webplay.log
 ```
 
 ***4. 远程调试***
 ```
 // 开启远程调试
 /usr/bin/webplay -remote-debug -webpage http://www.baidu.com
 // 远程访问调试
 使用基于 WebEngine 或 Chrome 浏览器访问 http://192.168.XXX.XXX:1112 即可
 ```
 
 ---
 #### 开机启动
 
 > 安装 xterm 
 ```
 apt-get install xterm
 ```
 
 > 修改 /etc/X11/xinit/xinitrc 
 ```
 #!/bin/sh
 
 xset -display :0 s noblank
 xset -display :0 s noexpose
 xset -display :0 s off
 xset -display :0 -dpms

 #exec /usr/bin/uxterm -geometry 1600x600+0+0 -e 'xhost +;bash;' # 调试
 exec /usr/bin/uxterm -geometry 1600x600+0+0 -e '/usr/bin/webplayrun' # 启动
 ```

 > 创建 /lib/systemd/system/webplay.service
 ```
 [Unit]
 Description=WebPlay Display Manager

 [Service]
 ExecStart=/usr/bin/startx
 Restart=always
 ```
 
 > 移除连接后建立新连接
 ```
 rm -f /etc/systemd/system/display-manager.service
 ln -s /lib/systemd/system/webplay.service /etc/systemd/system/display-manager.service
 ```
 
 ---
