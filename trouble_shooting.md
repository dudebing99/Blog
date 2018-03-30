## 解决 root 分区空间不足的问题
### 系统环境
CentOS release 6.8 (Final)
### 问题描述
在安装操作系统时采取默认分区策略或者当初分配的策略与后面实际使用差异，导致某些分区  
仍然有大量的可用空间，但是 root 分区空间不够。
### 解决方式
```bash
# 前提：home 分区仍有大量空间，root 分区空间不够
# 查看分区
df -h

# 取消挂载
umount /home

# 分区检测
e2fsck -f /dev/mapper/VolGroup-lv_home

# 将 lv_home 虚拟分区设为 100G
resize2fs -p /dev/mapper/VolGroup-lv_home 100G

# 挂载
mount /home

# 释放空间
lvreduce -L 100G /dev/mapper/VolGroup-lv_home

# 查看可用空间大小
vgdisplay

# 根据上述命令的提示，假设可用空间为 300G，扩展 lv_root 虚拟分区
lvextend -L +300G /dev/mapper/VolGroup-lv_root

# 重设分区大小
resize2fs -p /dev/mapper/VolGroup-lv_root
```
