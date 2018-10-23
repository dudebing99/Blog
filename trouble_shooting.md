[TOC]

------

## [VMWare] Host SMbus controller not enabled

**系统环境**

CentOS/VMware® Workstation 12 Pro

**问题描述**

在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

在 /etc/modprobe.d/blacklist.conf 文件里添加如下内容：

```bash
blacklist i2c_piix4
```

## [VMWare] intel_rapl: no valid rapl domains found in package 0

**系统环境**

CentOS/VMware® Workstation 12 Pro

**问题描述**

在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

在 /etc/modprobe.d/blacklist.conf 文件里添加如下内容：
blacklist intel_rapl

## [VMWare] sd 0:0:0:0: [sda] Assuming drive cache: write through

**系统环境**

CentOS/VMware® Workstation 12 Pro

**问题描述**

在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

> "rhgb" 表示 "redhat graphics boot"，就是图形进度条模式

1. 在 /etc/default/grub 文件里去掉 rhgb 参数
2. 执行 grub2-mkconfig -o /boot/grub2/grub.cfg
3. reboot

## [VMWare] 虚拟机磁盘空间不足

**系统环境**

Ubuntu 14.04.5 LTS/VMware® Workstation 12 Pro

**问题描述**

虚拟机 Ubuntu 磁盘空间不足，导致无法使用，需要扩容

**解决方式**

1. 删除虚拟机的所有快照
2. 虚拟机设置 -> 硬件 -> 磁盘 -> 扩展，设置一个足够的空间，例如 200G
3. 通过 `apt-get install gparted -y` 安装 `gparted`
4. 图形界面模式下，运行 `gparted`，扩展分区即可

> 扩展前，`/dev/sda1` 实际 40G，使用将近 40G。首先，将 `/dev/sda1` 之外的分区（虚拟机安装 Ubuntu 系统时默认处理，所以关键分区是 sda1，此分区不能删除）全部删除；然后，扩展`/dev/sda1` 分区，并重新建立交换分区。

![](E:\blog\pic\troubleshooting\gparted.png)

## [MySQL] 插入关键字导致 SQL 执行失败

**系统环境**

MySQL 5.6.x

**问题描述**

在 MySQL 表中某字段包含关键字 key，导致 SQL 语句执行报错，数据无法正常插入表中。错误信息大致如下：

*You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ...*

**解决方式**

执行如下 SQL  报错：INSERT into tb_map(key, value) VALUES('a',' 123');

> key 是 MySQL 关键字之一

正确写法：INSERT into tb_map(\`key\`, value) VALUES('a',' 123');

> 使用 转义符号：\`关键字\`

## [MySQL] 字段包含单引号、双引号导致 SQL 语法错误

**系统环境**

CentOS 6.8 x64/MySQL 5.6.35

**问题描述**

略

**解决方式**

SQL 中利用 `\` 转义即可，如下两种方式均可

```sql
-- 单引号转义
insert into blog_info_tbl (title, url) values ('kevin\'s blog', 'https://dudebing99.github.io/blog/');

-- 双引号转义
insert into blog_info_tbl (title, url) values ('\"kevin\" blog', 'https://dudebing99.github.io/blog/');
```

## [MySQL] 重置密码

**系统环境**

CentOS 6.8 x64/MySQL 5.6.35

**问题描述**

MySQL 用户密码丢失，重置用户密码

**解决方式**

```bash
service mysqld stop

mysqld_safe --skip-grant-talbes &

mysql -uroot
> use mysql;
> update user set password=PASSWORD('123456') where user='root';
> flush privileges;

pkill mysqld_safe

service mysql start
```

## [MySQL] ORDER BY clause is not in GROUP BY clause

**系统环境**

CentOS 6.8 x64/5.7.18 MySQL Community Server

**问题描述**

```sql
mysql> select org_user_id, uniq_user_id from (select * from multi_app_user_tbl) as tmp group by uniq_user_id;
ERROR 1055 (42000): Expression #1 of SELECT list is not in GROUP BY clause and contains nonaggregated column 'tmp.org_user_id' which is not functionally dependent on columns in GROUP BY clause; this is incompatible with sql_mode=only_full_group_by
```

**原因分析**

Select 语句选择的列与 Group by 包含的列不一致，MySQL 默认有此限制。

**解决方式**

1. 可以修改业务的 SQL，遵循此限制
2. 可以取消 MySQL 此限制，如下所示

```sql
mysql> select @@sql_mode\G
*************************** 1. row ***************************
@@sql_mode: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
1 row in set (0.00 sec)
mysql> set global sql_mode='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
```

**或修改 MySQL 配置文件** my.ini，添加或修改如下配置项

```bash
sql_mode=STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
```

## [SecureFX] 中文文件名乱码

**系统环境**

SecureFx Version 7.0.3 (build 480)

**问题描述**

SecretFx 显示中文文件名时出现乱码

**解决方式**

1. 打开安装目录，进入子目录：SecureCRT7\App\VanDyke Clients\CONFIG\Sessions
2. 找到 D:"Filenames Always Use UTF8"=00000000 改成 00000001，如下所示

```basic
D:"Restart Data Size"=00000000
S:"Restart Datafile Path"=
D:"Max Transfer Buffers"=00000004
D:"Filenames Always Use UTF8"=00000001
D:"Use Multiple SFTP Channels"=00000000
D:"Suppress Stat On CWD"=00000000
```

## [SecureCRT] 冻结终端/解除冻结/全屏/清屏

**系统环境**

SecureCRT Version 7.0.3 (build 480)

**问题描述**

略。

**解决方式**

- Ctrl + s：冻结终端
- Ctrl + q：解除冻结
- Alt + Enter：全屏/退出全屏
- Ctrl + L：清屏 clear

## [SourceInSight] 支持 .cc 文件

**系统环境**

Windows 7 Ultimate/SourceInSight 4.0

**问题描述**

略。

**解决方式**

Options -> Document Options，Document Type 下拉选 C++ Source File, File Filter 中加入 *.cc

## [CentOS] 设置网卡自启动

**系统环境**

CentOS

**问题描述**

略。

**解决方式**

将 /etc/sysconfig/network-scripts/ifctg-xxx 中如下内容修改

ONBOOT=no 修改为 ONBOOT=yes

> 备注：重启网卡或系统生效。

## [CentOS] 图形、多用户（命令行）模式切换

**系统环境**

CentOS 7.x

**问题描述**

CentOS 7.x 不在使用 init 托管服务，systemd 取而代之。

**解决方式**

1. 命令（多用户）模式

```bash
systemctl set-default multi-user.target
```

2. 图形模式

```bash
systemctl set-default graphical.target
```

## [CentOS] 解决 root 分区空间不足的问题

**系统环境**

CentOS release 6.8 (Final)

**问题描述**

在安装操作系统时采取默认分区策略或者当初分配的策略与后面实际使用差异，导致某些分区仍然有大量的可用空间，但是 root 分区空间不够。

**解决方式**

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

## [Ubuntu] 图形、命令行模式切换

**系统环境**

Ubuntu 14.04

**问题描述**

略。

**解决方式**

1. 修改 /etc/default/grub


```bash
# 图形模式
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
# 命令行模式
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash text"
```

2. 执行 update-grub
3. reboot

## [Ubuntu] the listen queue of a socket overflowed

**系统环境**

Ubuntu 14.04

**问题描述**

客户端连接服务端失败，利用 ss/netstat 查看网络的统计数据，发现异常 `the listen queue of a socket overflowed`

```bash
root@iZwz9iz7dge6lus7u0uvuzZ:~# netstat -s|grep -E "overflowed"
    470847 times the listen queue of a socket overflowed
```

**原因分析**

在使用 `wrk` 作为客户端对服务端进行压力测试时偶尔出现连接无响应，进而查看到网络统计信息中有如上错误。

查看系统支持的最大全连接数 128

```bash
root@:~# cat  /proc/sys/net/core/somaxconn 
128
```

而使用 `wrk` 并发的连接数设置超过了该限制，例如，设置 `wrk` 并发连接 200。此时，服务端的全连接一定会溢出，查看系统溢出之后如何处理

```bash
root@:~# cat /proc/sys/net/ipv4/tcp_abort_on_overflow
0
```

`tcp_abort_on_overflow` 为 0 表示三次握手第三步的时候，如果全连接队列满了，那么服务端扔掉客户端发过来的`ack`

> `tcp_abort_on_overflow` 设置成 1，表示三次握手第三步的时候，如果全连接队列满了，服务端发送一个`reset` 包给客户端，表示废掉连接

**解决方式**

1. 在配置文件 `/etc/sysconf.conf` 添加（或修改）该设置

```bash
net.core.somaxconn=32768
```

2. 运行 `sysctl -p` 使配置生效

## [Ubuntu] 域名解析未生效

**系统环境**

Ubuntu 14.04

**问题描述**

在 `/etc/resolv.conf` 配置域名解析如下所示

```bash
root@ubuntu:~# cat /etc/resolv.conf 
# Dynamic resolv.conf(5) file for glibc resolver(3) generated by resolvconf(8)
#     DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN
nameserver 114.114.114.114
nameserver 8.8.8.8
```

重启电脑域名解析未生效（该文件为空）

**原因分析**

如上注释说明，不要试图修改该文件，系统重启内容将被覆盖

**解决方式**

在 `/etc/resolvconf/resolv.conf.d/base` 配置即可解决

```bash
root@ubuntu:~# cat /etc/resolvconf/resolv.conf.d/base 
nameserver 114.114.114.114
nameserver 8.8.8.8
```

## [IceGrid] 应用进程权限

**系统环境**

CentOS 7.x/Ice 3.6.1

**问题描述**

IceGrid Node 节点部署的应用进程无法创建日志目录

**原因分析**

IceGrid Node 节点应用进程默认以 everyone 用户启动，进程需要在运行目录写日志文件，而 everyone 用户不具备该目录的写权限，导致无法创建日志目录。

**解决方式**

**方法 1：**将应用写日志文件的目录赋予 everyone 用户权限。

**方法 2：**IceGrid 机制允许修改用户进程启动默认启动的用户，详见 ICE 官方文档。

## [VSCode] Failed to continue: "Cannot find Delve debugger. Ensure it is in your \`GOPATH/bin\` or \`PATH\`."

**系统环境**

Windows 7 x64 Ultimate/VS Code v1.23.0

**问题描述**

略。

**解决方式**

1. 确认已经正确设置 GOPATH 环境变量，并将  %GOPATH%\bin 追加到 PATH 环境变量

2. 打开 Git Bash，运行 go get github.com/derekparker/delve/cmd/dlv

## [Django] Signal only works in main thread

**系统环境**

CentOS 7.x/Python 2.7.x/django 1.11.7

**问题描述**

运行报错

**解决方式**

运行时加入追加如下参数 --nothreading --noreload

## [Django] memory leak with gunicorn

**系统环境**

CentOS 7.x/Python 2.7.x/django 1.11.7

**问题描述**

Django 项目运行时内存泄漏，正常情况下，应当找出内存泄漏的地方并且修复，但是如果是引入的第三方库引入的（或者团队的其他成员的代码引入），无法迅速地正面解决（find it and fix it）

**解决方式**

运行时添加如下参数 --max-requests 1000，该参数指定当工作线程（gunicorn workers）在处理完 1000 个请求时，主进程将其杀掉并释放这些工作线程占用（存在内存泄漏）的内存，然后重新分配新的工作线程。

> 实际上，主进程杀掉并重新拉起新的子进程时，不会影响对客户端的请求的处理。例如，nginx 代理 Django 后端服务，客户端的请求不会受到影响。

## [Python] MySQL 结果集返回字典格式

**系统环境**

 CentOS 7.x/Python 2.7.4

**问题描述**

Python 的 MySQLdb 模块访问 MySQL 的一个模块，默认查询结果是 tuple 类型，使用只能根据字段的位置作为下标去访问，使用不方便且容易出错

**解决方式**

初始化 MySQL 连接时，显示指定结果集为字典类型 cursorclass=MySQLdb.cursors.DictCursor，如下所示

```python
import MySQLdb
import MySQLdb.cursors

def get_db_conn(mysql_config):
    db = MySQLdb.connect(host=mysql_config['host'],
                         port=mysql_config['port'],
                         user=mysql_config['user'],
                         passwd=mysql_config['passwd'],
                         db=mysql_config['db'],
                         cursorclass=MySQLdb.cursors.DictCursor)
    db.set_character_set('utf8mb4')
    cursor = db.cursor()
    cursor.execute('SET NAMES utf8mb4;')

    return db, cursor
```

## [Python] module not found error 可能原因

**系统环境**

CentOS 7.x/Python 2.7.4

**问题描述**

导入 Python 模块，提示找不到模块

**解决方式**

  1. 如果引用的模块包含多级目录，需要在每一级目录添加一个  `__init__.py` 文件（内容为空即可）
  2. 子目录中的文件引用父目录的模块，可将父目录的路径添加进来，举例如下

```bash
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
```

## [Pip] str(c.version) for c in all_candidates SyntaxError: invalid syntax

**系统环境**

CentOS 6.x/Python 2.6.6

**问题描述**

执行 pip install --upgrade pip 报错，如上所示

**解决方式**

python 版本过低，安装 python 2.7.x 或以上版本

## [Ubuntu] libssl-dev : Depends: libssl1.0.0 (= 1.0.1f-1ubuntu2) but 1.0.1f-1ubuntu2.19 is to be installed

> **类似问题：**software-properties-common : Depends: python3-software-properties (= 0.92.37.8) but it is not going to be installed

**系统环境**

Ubuntu 14.04

**问题描述**

执行 `apt-get install libssl-dev` 安装 libssl-dev 出错，具体信息如下所示

```bash
The following packages have unmet dependencies:
 software-properties-common : Depends: python3-software-properties (= 0.92.37.8) but it is not going to be installed
E: Unable to correct problems, you have held broken packages.
```

**解决方式**

```bash
root@datachain-test002:~# aptitude install libssl-dev
The following NEW packages will be installed:
  libssl-dev{b} libssl-doc{a} zlib1g-dev{ab} 
0 packages upgraded, 3 newly installed, 0 to remove and 1 not upgraded.
Need to get 2,209 kB of archives. After unpacking 8,290 kB will be used.
The following packages have unmet dependencies:
 zlib1g-dev : Depends: zlib1g (= 1:1.2.8.dfsg-1ubuntu1.1) but 1:1.2.8.dfsg-2ubuntu4.1 is installed.
 libssl-dev : Depends: libssl1.0.0 (= 1.0.1f-1ubuntu2.26) but 1.0.2g-1ubuntu4.11 is installed.
The following actions will resolve these dependencies:

     Keep the following packages at their current version:
1)     libssl-dev [Not Installed]                         
2)     zlib1g-dev [Not Installed]                         

Accept this solution? [Y/n/q/?] n
Accept this solution? [Y/n/q/?] Y
```

## [Ubuntu] [: 1: unexpected operator

**系统环境**

Ubuntu 14.04

**问题描述**

执行 shell 脚本，报错 [: 1: unexpected operator

**原因分析**

Ubuntu shell 下默认的脚本解析器是 dash，会使一些 bash 脚本执行失败。

**解决方式**

sudo dpkg-reconfigure dash
选择 NO

## [Ubuntu] lua.c:80:31: fatal error: readline/readline.h: No such file or directory

**系统环境**

Ubuntu 14.04

**问题描述**

源码编译 lua 5.3 时，报错 lua.c:80:31: fatal error: readline/readline.h: No such file or directory

**原因分析**

缺少 libreadline-dev 依赖包

**解决方式**

执行  apt-get install libreadline-dev

## [Ubuntu] ssh root 登陆 Permission denied

**系统环境**

Ubuntu 14.04

**问题描述**

安装 ssh 服务之后，root 账户无法 ssh 登陆，提示权限不足

**解决方式**

1. 修改 /etc/ssh/sshd_config

```bash
#PermitRootLogin without-password
PermitRootLogin yes
```

2. 重启服务生效

```bash
service ssh restart
```

## [Ubuntu] 重置 root 密码

**系统环境**

Ubuntu 14.04

**问题描述**

忘记 root 登陆密码

**解决方式**

1. 开机引导界面，选择“Ubuntu 高级选项”，回车
2. 选择“Ubuntu <省略> recovery mode”，按 “e" 键进行编辑
3. 在界面中找到 “recovery nomodeset”，并替换为 quiet splash rw init=/bin/bash，回车
4. 系统进入命令行模式，输入 passwd 更改 root 密码（同理，可以更改其他账户密码）
5. 重启系统

## [Ubuntu] protobuf 冲突导致编译失败

**系统环境**

Ubuntu 14.04

**问题描述**

Ubuntu 系统自带 protobuf，项目中使用高版本 protobuf（由源码编译），与系统自带的产生冲突，导致项目编译、链接失败

**解决方式**

1. 彻底卸载系统自带 protobuf

```bash
apt-get purge --remove libprotobuf*
apt-get purge --remove protobuf-compiler
# 借助 whereis/find 查找 protobuf 相关库、可执行程序、头文件并删除（根据实际情况调整）
rm -rf /usr/local/lib/libprotobuf* /usr/lib/libprotobuf* /usr/lib/x86_64-linux-gnu/libprotobuf* /usr/local/include/google/protobuf /usr/include/google/protobuf /usr/bin/protoc /usr/bin/X11/protoc
```

2. 重新源码编译、安装高版本 protobuf

## [Ubuntu] error: C++ preprocessor "/lib/cpp" fails sanity check

**系统环境**

Ubuntu 14.04

**问题描述**

Ubuntu 源码编译 protobuf，执行 ./configure 配置时检查出错，原因是缺少必要的 C++ 库

**解决方式**

```bash
apt-get install build-essential g++ -y
```

> 如果是 CentOS，运行如下命令即可 `yum install glibc-headers gcc-c++ -y`
>

## [Ubuntu] Package libdb4.8++-dev is not available, but is referred to by another package.

**系统环境**

Ubuntu 14.04

**问题描述**

Ubuntu 无法安装 libdb4.8++-dev

**解决方式**

```bash
add-apt-repository ppa:bitcoin/bitcoin
apt-get update
apt-get install -y libdb4.8-dev libdb4.8++-dev
```

## [Golang] package xxx: cannot download, $GOPATH not set. For more details see: go help gopath

**系统环境**

Linux

**问题描述**

运行 go get 下载出错，错误信息如上，提示未设置 GOPATH 环境变量

**解决方式**

```bash
# 根据实际工程路径修改
echo "export GOPATH=$HOME/go" >> /etc/profile
# 使环境变量生效
soure /etc/profile
```

## [Golang] go-get=1: dial tcp  i/o timeout)

**系统环境**

Linux

**问题描述**

运行 go get 下载出错，提示 i/o 超时

```basic
Fetching <https://golang.org/x/net/html?go-get=1> https fetch failed: Get <https://golang.org/x/net/html?go-get=1>: dial tcp 216.239.37.1:443: i/o timeout package golang.org/x/net/html: unrecognized import path "golang.org/x/net/html" (https fetch: Get <https://golang.org/x/net/html?go-get=1>: dial tcp 216.239.37.1:443: i/o timeout)
```

**原因分析**

因为 the fucking gfw，导致无法直接通过 go get 下载，需要 git clone 对应仓库到本地并放到对应的目录，即，完成 go get 做的工作。缺少其他包，可采用同样的方式解决。

**解决方式**

```bash
# 需要设置 GOPATH 环境变量
mkdir -p $GOPATH/src/golang.org/x
cd $GOPATH/src/golang.org/x
git clone https://github.com/golang/text.git
```

## [Golang] GOPATH 环境变量被覆盖

**系统环境**

Windows 7 Ultimate x64

**问题描述**

安装 golang 之后，在系统变量设置 GOPATH=D:\go，但是未生效

```basic
$ echo $GOPATH
C:\Users\Administrator\go
```

**原因分析**

安装 golang 之后，默认给用户变量添加 GOPATH=%USERPROFILE%\go，导致覆盖了系统变量 GOPATH，如下所示：

![](pic/golang/gopath.png)

**解决方式**

删除用户变量 GOPATH 即可（当然，删除系统变量，然后修改用户变量 GOPATH 为目标目录也可）

## [geth] unexpected directory layout

**系统环境**

Ubuntu 14.04

**问题描述**

源码编译以太坊，运行 go install ./cmd/geth 报错，详细错误如下

```bash
unexpected directory layout:
        import path: github.com/elastic/gosigar
        root: /root/go/src
        dir: /root/go/src/github.com/ethereum/go-ethereum/vendor/github.com/elastic/gosigar
        expand root: /root/go/src
        expand dir: /root/go/src/github.com/ethereum/go-ethereum/vendor/github.com/elastic/gosigar
        separator: /
```

**解决方式**

安装缺失的库

```bash
go get -u -v github.com/elastic/gosigar
```

## [geth] Block sealing failed err="waiting for transactions"

> **参考资料：**https://github.com/ethereum/go-ethereum/issues/15646

**系统环境**

Ubuntu 14.04/geth 1.8.13

**问题描述**

以太坊以开发者模式运行，启动挖矿时报错，如下所示：

```bash
> miner.start()
INFO [07-24|20:13:55.983] Transaction pool price threshold updated price=1
INFO [07-24|20:13:55.983] Starting mining operation 
null
> INFO [07-24|20:13:55.983] Commit new mining work                   number=1 txs=0 uncles=0 elapsed=148.484µs
WARN [07-24|20:13:55.984] Block sealing failed                     err="waiting for transactions"
```

**解决方式**

开发者模式运行，当有交易时节点才启动挖矿，因此，创建一个交易即可触发节点的挖矿。

## [geth] Please enable network time synchronisation in system settings

**系统环境**

Ubuntu 14.04/geth 1.8.13

**问题描述**

以太坊 Testnet 运行 `./geth --datadir="./testnet" --testnet console`，错误信息如上所示

**原因分析**

节点所在机器时间未同步

**解决方式**

> 参考资料：https://github.com/ethereum/go-ethereum/issues/14717

同步节点所在机器时间，参考方式如下

```bash
sudo apt-get update
sudo apt-get install ntp
sudo service ntp start
```

## [geth] Cannot start mining without etherbase err="etherbase must be explicitly specified"

**系统环境**

Ubuntu 14.04/geth 1.8.13

**问题描述**

以太坊 Testnet 运行，开启挖矿时报错

**原因分析**

原因是当前环境没有账户，需要建立一个账户 

**解决方式**

创建账户，并解锁账户，之后启动挖矿即可

```basic
personal.newAccount('123')
personal.unlockAccount(eth.accounts[0])
miner.start()
```

## [geth] first argument must be the account to unlock

**系统环境**

Windows 7 Ultimate x64/geth 1.8.13

**问题描述**

以太坊私有网络，在控制台尝试解锁账户时报错，如上所示

**原因分析**

以太坊私有网络初始无账户，对不存在的账户解锁必然出错

**解决方式**

首先先建立账户 `personal.newAccount('password')` 即可，然后尝试解锁账户

## [NPM] sh: 1: node: not found npm WARN This failure might be due to the use of legacy binary 

**系统环境**

Ubuntu 14.04

**问题描述**

npm install 安装包的时候报错，如上所示。

**原因分析**

新版本的 nodejs，已经将原来 /usr/bin/node 改成 /usr/bin/nodejs，所以报如上错误。 

**解决方式**

```bash
apt-get install nodejs-legacy
```

## [NPM] npm WARN enoent ENOENT: no such file or directory

**系统环境**

Ubuntu 14.04

**问题描述**

npm install 安装包的时候报错，npm WARN enoent ENOENT: no such file or directory, open '\<root>/node_modules/supertest/package.json'

**解决方式**

运行 npm init 进行初始化即可

## [web3.js] Error: Error: Method eth_compileSolidity not supported.

**系统环境**

Ubuntu 14.04/Solc 0.20.1/node 8.11.3/npm 5.6.0

**问题描述**

调用 web3.js 编译合约接口时，报错，对应代码如下所示：

```javascript
let calc = web3.eth.compile.solidity(source);
```

**原因分析**

> the developers decided that making a node compile a contract like this to be out of scope. So this functionality has been [deprecated](https://github.com/ethereum/EIPs/issues/209). There were many reasons behind this, but the main ones are that RPC calls are beyond the responsibilities of the eth API, and node compilation like this is not sufficient. You can use an on-line compiler like Remix, or a compiler like solc to get the bytecode and go from there. 

新版本 web3.js 废弃了该接口

**解决方式**

利用 Solc 提前编译好合约，js 代码中不依赖该接口即可

## [web3.js] 监听合约事件失败

**系统环境**

Ubuntu 14.04/Solc 0.20.1/node 8.11.3/npm 5.6.0

**问题描述**

监听合约事件，但是无法捕获事件，代码如下所示

```javascript
contract_.Sent().watch(function(error, result) {
    if (!error) {
        console.log("\nCoin transfer: " + result.args.amount +
            " coins were sent from " + result.args.from +
            " to " + result.args.to + ".");
        console.log("Sender: " + contract_.balances.call(result.args.from) +
            ", Receiver: " + contract_.balances.call(result.args.to) + "\n");
    }
})

console.log("mint's hash: ", contract_.mint(web3.eth.accounts[0], 666, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("mint's hash ", contract_.send(web3.eth.accounts[3], 99, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("receiver's balance: ", contract_.balances.call(web3.eth.accounts[3]));

process.exit(0);
```

**原因分析**

由于事件监听属于回调，执行合约交易之后，立即调用 process.exit(0) 退出程序，导致监听合约事件失败。

**解决方式**

去掉 process.exit(0) 即可，如下所示

```javascript
contract_.Sent().watch(function(error, result) {
    if (!error) {
        console.log("\nCoin transfer: " + result.args.amount +
            " coins were sent from " + result.args.from +
            " to " + result.args.to + ".");
        console.log("Sender: " + contract_.balances.call(result.args.from) +
            ", Receiver: " + contract_.balances.call(result.args.to) + "\n");
    }
})

console.log("mint's hash: ", contract_.mint(web3.eth.accounts[0], 666, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("mint's hash ", contract_.send(web3.eth.accounts[3], 99, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("receiver's balance: ", contract_.balances.call(web3.eth.accounts[3]));

setTimeout(function() {
    process.exit(0);
}, 5000);
```

## [remix-ide] 通过 Web3 Provider 连接本地节点失败

**系统环境**

Windows 7 Ultimate x64/geth 1.8.13

**问题描述**

通过浏览器（http://localhost:8080）打开 remix-ide 主页，运行环境选择本地节点时（running 菜单，运行环境选择 Web3 Provider 连接本地节点），连接本地节点失败

**原因分析**

本地运行 geth 节点，参数中未添加 `--rpccorsdomain`，导致浏览器无法访问本地节点，如 geth 帮助信息所示

```bash
$ ./geth.exe help|grep rpc
  --rpc                  Enable the HTTP-RPC server
  --rpcaddr value        HTTP-RPC server listening interface (default: "localhost")
  --rpcport value        HTTP-RPC server listening port (default: 8545)
  --rpcapi value         API's offered over the HTTP-RPC interface
  --rpccorsdomain value  Comma separated list of domains from which to accept cross origin requests (browser enforced)
  --rpcvhosts value      Comma separated list of virtual hostnames from which to accept requests (server enforced). Accepts '*' wildcard. (default: "localhost")
```

**解决方式**

运行 geth 节点加入 `--rpccorsdomain`，例如，` ./geth --datadir "./dev" --dev --rpc --rpccorsdomain "*" console`

## [julia] ERROR: UndefVarError: Pkg not defined

> **参考资料：**https://github.com/JuliaLang/julia/issues/28574

**系统环境**

Windows 7 Ultimate x64/julia 1.0.0

**问题描述**

julia 安装包失败，如下所示

```bash
julia> Pkg.add("IJulia")
ERROR: UndefVarError: Pkg not defined
Stacktrace:
 [1] top-level scope at none:0
```

**原因分析**

julia 1.0.0 版本安装包方式已经不兼容旧版本

**解决方式**

julia 控制台输入 `]` 进入包管理模式（输入 `backspace` 退出包管理模式），如下所示

```bash
(v1.0) pkg> add IJulia
 Resolving package versions...
  Updating `C:\Users\Administrator\.julia\environments\v1.0\Project.toml`
 [no changes]
  Updating `C:\Users\Administrator\.julia\environments\v1.0\Manifest.toml`
 [no changes]
```

## [julia] ERROR: LoadError: LoadError: LoadError: UndefVarError: @printf not defined

**系统环境**

Windows 7 Ultimate x64/julia 1.0.0

**问题描述**

代码中使用 @printf，如下所示

```julia
@printf "volume = %0.3f\n" vol
```

运行时报错 `ERROR: LoadError: LoadError: UndefVarError: @printf not defined`

**原因分析**

Julia 1.0.0 之后，很多特性从基础库中移除，需要显示引用

**解决方式**

使用 `@printf` 需要显示引用 `using Printf`

## [solidity] Internal compiler error: Stack too deep, try removing local variables.

> **参考资料：**https://ethereum.stackexchange.com/questions/6061/error-while-compiling-stack-too-deep

**系统环境**

solidity 0.4.24

**问题描述**

solidity 函数编译报错，对应的代码如下

```javascript
function getHistoryRoundInfo(uint256 _rid)
        public
        view
        returns(uint256, uint256, uint256, uint256, uint256, uint256, address[], uint256[])
{
    uint256 length = round_[_rid].winners.length;
    uint256[] memory numbers = new uint256[](length);
    if (round_[_rid].winners.length > 0) {
        for (uint256 idx = 0; idx < length; idx ++) {
            numbers[idx] = round_[_rid].winnerNum[round_[_rid].winners[idx]];
        }
    }

    return (
        uint256(round_[_rid].state),
        round_[_rid].roundDeadline,
        round_[_rid].claimDeadline,
        round_[_rid].drawCode,
        round_[_rid].pot,
        round_[_rid].blockNumber,
        round_[_rid].winners,
        numbers
    );
}
```

**原因分析**

solidity 编译器限制本地变量不超过 16 个，否则报错

```bash
assertThrow(instructionNum <= 16, StackTooDeepException, "Stack too deep, try removing local variables.");
```

**解决方式**

解决思路：1. 将部分逻辑封装成更小的函数；2. 将参数返回值组成数组；3. 减少函数返回值。例如，将返回值组成数组，达到减少本地变量的效果，如下所示

```javascript
function getHistoryRoundInfo(uint256 _rid)
	public
	view
	returns(uint256[], address[], uint256[])
{
    uint256 length = round_[_rid].winners.length;
    uint256[] memory numbers = new uint256[](length);
    if (round_[_rid].winners.length > 0) {
        for (uint256 idx = 0; idx < length; idx ++) {
            numbers[idx] = round_[_rid].winnerNum[round_[_rid].winners[idx]];
        }
    }

    uint256[] memory items = new uint256[](6);
    items[0] = uint256(round_[_rid].state);
    items[1] = round_[_rid].roundDeadline;
    items[2] = round_[_rid].claimDeadline;
    items[3] = round_[_rid].drawCode;
    items[4] = round_[_rid].pot;
    items[5] = round_[_rid].blockNumber;

    return (items, round_[_rid].winners, numbers);
}
```

## [remix-ide] Error: exceeds block gas limit

**系统环境**

Windows 7 Ultimate x64/geth 1.8.13

**问题描述**

`remix-ide` 连接以太坊私有网络调试时，执行交易报错，如上所示

**原因分析**

以太坊节点的 `gaslimit` 小于交易所需消耗的 `gas`，导致交易失败，可以通过 `eth.getBlock("latest")` 进行确认，深层次的原因如下，

- 创世区块指定的 `gaslimit` 太小，导致需要消耗大量 `gas` 的交易失败
- 以太坊私有网络运行过程，如，挖出大量空块，节点不断调低 `gaslimit`，导致交易失败

**解决方式**

- 创世区块指定的 `gaslimit` 设置足够大
- 运行以太坊私有网络节点，添加参数 `--targetgaslimit '9000000000000'`（该设置保证随着挖矿的进行，节点不断调高 `gaslimit` 直到接近 `9000000000000`）

## [nginx] "POST / HTTP/1.1" 499 0 "-" "-"

**系统环境**

Ubuntu 14.04/nginx 1.4.6

**问题描述**

nginx 访问日志（默认路径 `/var/log/nginx/access.log`）存在大量的 499 错误码信息，如下所示

```bash
127.0.0.1 - - [18/Sep/2018:15:50:02 +0800] "POST / HTTP/1.1" 499 0 "-" "-"
```

**原因分析**

在使用 wrk 工具对 nginx 负载的多个后端服务进行性能测试时，nginx 访问日志存在大量的 499 错误码信息。

499 错误码是 nginx 扩展的 HTTP 错误码，如下定义

```cpp
/*
* HTTP does notdefine the code for the case when a client closed
* the connectionwhile we are processing its request so we introduce
* own code to logsuch situation when a client has closed the connection
* before we even tryto send the HTTP header to it
*/
#define NGX_HTTP_CLIENT_CLOSED_REQUEST 499
```

当客户端在请求的响应返回之前主动关闭连接，nginx 记录 499 错误码

**解决方式**

一般情况下，需要优化后端服务，在客户端超时关闭连接之前返回响应就能避免此类问题。

##  [bitcoin] non-mandatory-script-verify-flag (Signature must be zero for failed CHECK(MULTI)SIG operation) (code 64)

**系统环境**

Ubuntu 14.04/bitcoind v0.16.99.0

**问题描述**

2/3 多签交易时，对原始交易签名报错

```bash
root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400483045022100e17bb27cb49c91bb46dbd60c63dfb08a0f1d0d153b0ca57d5804454921797df50220020a8f79a51d7762a022443313982e8896e56609594522d61737bda06f750d4201483045022100c41206829f3ec4969f2e6e6d4d52ac6b67c5c64248aef34933d5c0baa27c04d7022075b1f4bbac089d9aaa6943c726223a31911438b9acf90884b72be097eda15f7a0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000  
error code: -26
error message:
non-mandatory-script-verify-flag (Signature must be zero for failed CHECK(MULTI)SIG operation) (code 64)
```

**原因分析**

2/3 多签的未花费输出为 0.527 BTC

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent 0 1000000 "[\"2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3\"]"
[
  {
    "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
    "vout": 1,
    "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
    "label": "test account",
    "redeemScript": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "scriptPubKey": "a91430b5e8e9151e46be789562580b0118911d875f3d87",
    "amount": 0.52700000,
    "confirmations": 619,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

构造的原始交易找零金额为 0.5269 BTC

```bash
root@ubuntu:~# bitcoin-cli -testnet createrawtransaction "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\",\"vout\":1}]" "[{\"2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL\":0.5269}]"
02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000
```

但是，在给原始交易签名时，amount 未设置为未花费输出 0.527 BTC，如下所示

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000 "[\"cPegPf2xaeaqYB9kqqM2gzVPPXnAmwCME2KjsAQG6gkVnbxZpTKo\", \"cQ8ZUeBy27NKafYioHp4f3isHFTFuAx65vPf6dgUgxdNSBegsW3W\"]" "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\", \"vout\":1, \"scriptPubKey\": \"a91430b5e8e9151e46be789562580b0118911d875f3d87\", \"redeemScript\": \"522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae\", \"amount\": 0.5269}]"
{
  "hex": "020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400483045022100e17bb27cb49c91bb46dbd60c63dfb08a0f1d0d153b0ca57d5804454921797df50220020a8f79a51d7762a022443313982e8896e56609594522d61737bda06f750d4201483045022100c41206829f3ec4969f2e6e6d4d52ac6b67c5c64248aef34933d5c0baa27c04d7022075b1f4bbac089d9aaa6943c726223a31911438b9acf90884b72be097eda15f7a0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000",
  "complete": true
}
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400483045022100e17bb27cb49c91bb46dbd60c63dfb08a0f1d0d153b0ca57d5804454921797df50220020a8f79a51d7762a022443313982e8896e56609594522d61737bda06f750d4201483045022100c41206829f3ec4969f2e6e6d4d52ac6b67c5c64248aef34933d5c0baa27c04d7022075b1f4bbac089d9aaa6943c726223a31911438b9acf90884b72be097eda15f7a0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000
{
  "txid": "05dfc6503286f2472246ea43cdcf3004d0553df8da2635a42eaf2c321b889a03",
  "hash": "549a002ececbfea510d8391f3da54cde2208388b3272a2d8ef9f70523861e011",
  "version": 2,
  "size": 374,
  "vsize": 182,
  "weight": 728,
  "locktime": 0,
  "vin": [
    {
      "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
      "vout": 1,
      "scriptSig": {
        "asm": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
        "hex": "220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a"
      },
      "txinwitness": [
        "",
        "3045022100e17bb27cb49c91bb46dbd60c63dfb08a0f1d0d153b0ca57d5804454921797df50220020a8f79a51d7762a022443313982e8896e56609594522d61737bda06f750d4201",
        "3045022100c41206829f3ec4969f2e6e6d4d52ac6b67c5c64248aef34933d5c0baa27c04d7022075b1f4bbac089d9aaa6943c726223a31911438b9acf90884b72be097eda15f7a01",
        "522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae"
      ],
      "sequence": 4294967295
    }
  ],
  "vout": [
    {
      "value": 0.52690000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 debb602e1c37628d1f411918f87f1680d59e1a0f OP_EQUAL",
        "hex": "a914debb602e1c37628d1f411918f87f1680d59e1a0f87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL"
        ]
      }
    }
  ]
}
```

从而导致发送签名之后的交易报错，如下所示

```bash
root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400483045022100e17bb27cb49c91bb46dbd60c63dfb08a0f1d0d153b0ca57d5804454921797df50220020a8f79a51d7762a022443313982e8896e56609594522d61737bda06f750d4201483045022100c41206829f3ec4969f2e6e6d4d52ac6b67c5c64248aef34933d5c0baa27c04d7022075b1f4bbac089d9aaa6943c726223a31911438b9acf90884b72be097eda15f7a0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000
error code: -26
error message:
non-mandatory-script-verify-flag (Signature must be zero for failed CHECK(MULTI)SIG operation) (code 64)
```

**解决方式**

在给原始交易签名时，amount 未设置为未花费输出即可（本示例中， amount 对应 0.527）