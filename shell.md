[TOC]

------

## 统计网络连接状态及数目

```bash
# netstat 工具
netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'

# ss 工具(自动统计)
ss -s

# 示例
[root@localhost ~]# netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'
ESTABLISHED 1
[root@localhost ~]# ss -s
Total: 425 (kernel 442)
TCP:   8 (estab 1, closed 0, orphaned 0, synrecv 0, timewait 0/0), ports 3

Transport Total     IP        IPv6
*         442       -         -        
RAW       0         0         0        
UDP       1         1         0        
TCP       8         5         3        
INET      9         6         3        
FRAG      0         0         0
```

## 统计进程打开的文件句柄数目
```bash
lsof -p PID
lsof -p PID|wc -l
```

## 字符串截取

> **Tips:** man bash 获取更全面的语法（[在线手册](http://www.gnu.org/software/bash/manual/bash.html)）

```bash
# ${parameter#word} 最小限度从前面截取 word
[root@localhost ~]# str="http://www.bigsillybear.com/index.html"
[root@localhost ~]# echo ${str#*//}
www.bigsillybear.com/index.html

# ${parameter##word} 最大限度从前面截取 word
[root@localhost ~]# str="http://www.bigsillybear.com/index.html"
[root@localhost ~]# echo ${str##*/}                             
index.html

# ${parameter%word} 最小限度从后面截取 word
[root@localhost ~]# str="http://www.bigsillybear.com/index.html"
[root@localhost ~]# echo ${str%/*}
http://www.bigsillybear.com

# ${parameter%%word} 最大限度从后面截取 word
[root@localhost ~]# str="http://www.bigsillybear.com/index.html"
[root@localhost ~]# echo ${str%%/*}
http:

# ${parameter:offset} 从指定位置截取字
# ${parameter:offset:length} 从指定位置截取指定长度
[root@localhost ~]# str="http://www.bigsillybear.com/index.html"
[root@localhost ~]# echo ${str:7}
www.bigsillybear.com/index.html
[root@localhost ~]# echo ${str:7:20}                            
www.bigsillybear.com
[root@localhost ~]# echo ${str:0-10}                            
index.html
[root@localhost ~]# echo ${str:0-10:5}
index
```



## awk getline: 过滤行、改变奇数偶数行

### 打印出从 1 到 10 之间的偶数
```bash
seq 10|awk '{getline; print $0}'
```

### 打印出从 1 到 10 之前的奇数
```bash
seq 10|awk '{print $0; getline}'
```

### 交换奇数、偶数行

```bash
seq 10|awk '{getline tmp; print tmp; print $0}'
```

## for 循环的常用写法
### 数值类型
```bash
# i = i*3+1
for((i=1; i<=10; i++))
do
    echo $(expr $i \*3 + 1)
done
```

```bash
for i in $(seq 1 10)
do
    echo $(expr $i \* 3 + 1);
done
```

```bash
for i in {1..10}
do
    echo $(expr $i \* 3 + 1);
done
```

```bash
awk 'BEGIN {for(i=1; i<=10; i++) print i}'
```

### 字符串类型
```bash
for i in `ls`
do
    echo $i
done
```

```bash
for i in $*
do
    echo $i
done
```

```bash
for i in f1 f2 f3
do
    echo $i
done
```

```bash
list="rootfs usr data"
for i in $list
do
    echo $i
done
```

## 分割、合并大文件
```bash
# 按照指定行数分割
split -l 500 large_file.log new_file_prefix

# 按照文件大小分割
split -b 100m large_file.log new_file_prefix

# 使用 cat 进行文件合并
cat new_file_prefix* > large_file.log
```

## 检查 IPv4 地址合法性
```bash
CheckIPAddr()
{
    # IP地址必须为全数字
    echo $1|grep "^[0-9]\{1,3\}\.\([0-9]\{1,3\}\.\)\{2\}[0-9]\{1,3\}$" > /dev/null

    if [ $? -ne 0 ]
    then
        return 1
    fi

    ipaddr=$1
    a=`echo $ipaddr | awk -F . '{print $1}'`  # 以"."分隔，取出每个列的值
    b=`echo $ipaddr | awk -F . '{print $2}'`
    c=`echo $ipaddr | awk -F . '{print $3}'`
    d=`echo $ipaddr | awk -F . '{print $4}'`

    for num in $a $b $c $d
    do
        if [ $num -gt 255 ] || [ $num -lt 0 ]; then
            return 1
        fi
    done

    return 0
}

# 调用
CheckIPAddr 192.168.1.1

if [ $? -ne 0 ]; then
    echo "invalid"
fi
```

## 替换文件中所有 \r
```bash
sed -i 's/\r//g' FILE
```

## 检查进程是否重启
```bash
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: [Process Name]"
    exit 0
fi

PID=`ps afx|grep $1|grep -v "grep"|grep -v "/bin/bash"|head -n 1|awk '{print $1}'`

while [ 1 ]
do
    PID2=`ps afx|grep $1|grep -v "grep"|grep -v "/bin/bash"|head -n 1|awk '{print $1}'`

    if [ $PID2 ]; then
        if [ ! $PID ]; then
            PID=$PID2
            echo "PID: $PID"
        else
            if [ $PID -ne $PID2 ]; then
                echo "Server is reboot, PID: $PID --> $PID2"
                PID=$PID2
            else
                echo "Server is running, PID: $PID2"
            fi
        fi
    else
        echo "Server is not running"
    fi

    sleep 1
done
```

## nohup 后台启动 java 进程
```bash
nohup java -classpath xxx_service_1.0.jar xxx_entry > xxx_service.log 2>&1 &
```

## 获取进程号、杀进程
```bash
ps afx|grep 进程名|grep -v grep|awk '{print $1}'|xargs kill -9
pgrep 进程名|xargs kill -9
pidof 进程名|xargs kill -9
pkill -9 进程名
killall -9 进程名
```

## 查询、启动、停止服务
```bash
# 新管理方式，如 Cent OS >= 7.x
systemctl start/status/enable/disable/stop/restart xxx_service

# 旧管理方式，如 Cent OS < 7.x
service xxx_service start/status/stop/restart
```

## 显示已经登录的用户、执行的命令
```bash
# 显示已经登录的用户以及正在执行的命令
w

# 示例
> w
 18:27:34 up 89 days,  6:41,  6 users,  load average: 0.46, 0.46, 0.34
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
root     pts/1    172.13.30.133    14:30    3:56m  0.33s  0.33s -bash
kevin    pts/2    172.13.30.219    Thu08   19:14   3.06s  3.06s -bash
kevin    pts/5    172.13.30.219    17:48    0.00s  0.60s  0.01s w
root     pts/6    172.13.30.219    18:09   17:10   0.04s  0.04s -bash
kevin    pts/7    172.13.30.219    18:06   20:42   0.00s  0.00s -bash

# 显示已经登录的用户、登录的终端
who

# 示例
> who
root     pts/1        2018-03-27 14:30 (172.13.30.133)
kevin    pts/2        2018-03-22 08:09 (172.13.30.219)
root     pts/3        2018-03-27 14:31 (172.13.30.133)
kevin    pts/5        2018-03-27 17:48 (172.13.30.219)
root     pts/6        2018-03-27 18:09 (172.13.30.219)
kevin    pts/7        2018-03-27 18:06 (172.13.30.219)
```

## 添加定时任务
### at 定时任务
```bash
# 示例：添加一个 1 分钟之后执行的任务，按 Ctrl + D 退出
> at now +1 minutes
at> echo hello > ~/at.log
at> <EOT>
job 6 at 2018-03-27 19:20

# 示例：查询所有 at 任务
> atq
6       2018-03-27 19:20 a kevin

# 示例：删除 at 定时任务（6 位 job ID）
> atrm 6
```

### crontab 定时任务
```bash
# 添加定时任务
crontab -e

# 查询所有 crontab 任务
crontab -l

# 示例
# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR
# sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name command to be executed
# 每个小时第 05 分执行同步系统时间、硬件时钟
05 */1 * * * rdate -t 30 -s time.nist.gov && /usr/sbin/hwclock -w
```

## watch 持续监视命令的执行情况
```bash
# 每隔 3s，打印一次指定端口 9999 处于连接已建立的连接数目
watch -n 3 'netstat -anp|grep 9999|wc -l'
```

## TCP/UDP 收发数据、探测端口是否打开
### nc
```bash
# 监听 1234
nc -l 1234

# 连接 1234
nc 127.0.0.1 1234
```
### telnet
```bash
telnet 127.0.0.1 1234
```

## 逐行读取文件
### while 循环
```bash
while read LINE
do
    echo $LINE
done < $FILE
```
### 重定向法（管道法）
```bash
cat $FILE|while read LINE
do
    echo $LINE
done
```
### 文件描述符法
```bash
# 如下两个操作可合并
# exec 3<&0 exec 0<$FILE
exec 3<&0
exec 0<$FILE

while read LINE
do
    echo $LINE
done

exec 0<&3
```
### for 循环
```bash
for LINE in `cat $FILE`
do
    echo $LINE
done
```

## 如何解决 Linux Error: No space left on device
### 判断磁盘空间是否满，inode 是否耗尽
```bash
df -h
df -i
```
### 查找大文件
```bash
# 按照大小降序排列（取出前 10 个大文件）
du -sh target.dir|sort -n|head

# 查找目录下大于 1M 且小于 10M 的文件
find  target.dir -size +1M -size -10M -type f -name "*.jpg"

# 指定查询目录层级
du -h --max-depth=1
```
### 查找访问某个目录的进程
```bash
lsof +d /tmp

# 示例
> lsof +d ~/blog/
COMMAND   PID  USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
bash     6936 kevin  cwd    DIR  253,2     4096 3675368 /home/kevin/blog
vim     24969 kevin  cwd    DIR  253,2     4096 3675368 /home/kevin/blog
vim     24969 kevin    4u   REG  253,2    20480 3675605 /home/kevin/blog/.SHELL.md.swp
```
### 删除文件（少量）
```bash
find /tmp -type f -exec rm {} \;

# 注意：xargs 默认是以空白字符（空格，TAB，换行符）来分割记录的，如果文件名中间有空格，例如 /tmp/file 1.log，
# 此时自动被当做两个文件 /tmp/file 与 1.log，执行命令报错：No such file or directory
find -name '*.log' -print0|xargs -0 rm

# 可能存在大小为 0 字节的空文件，同样也会占用 inode
find /tmp -type f -size 0 -exec rm {} \;
```
### 删除文件（大量）
```bash
# 先建立一个空目录
mkdir /data/blank

# 用 rsync 删除目标目录
rsync --delete-before -d /data/blank/ /tmp/
```
### 删除大文件
```bash
cat /dev/null > target.file
```

## 查找指定范围内的日志信息
```bash
# 查找时间范围 2018/03/28 05:00:00 ~ 2018/03/28 07:59:59 的所有日志
sed -n '#2018/03/28 05:[0-9][0-9]:[0-9][0-9]#,#2018/03/28 07:[0-9][0-9]:[0-9][0-9]#p' log

# 查找 2018-03-29 00:24:00 ~ 2018-03-29 00:25:59 的所有日志
cat log|grep  -E '2018-03-29 00:2[4-5]:[0-9][0-9]'
```

## tr 字符进行替换、压缩和删除
```bash
# 将输入字符由大写转换为小写
> echo "Hello World"|tr 'a-z' 'A-Z'
HELLO WORLD

# 删除字符
> echo "hello 123 world 456"|tr -d '0-9'
hello world

# 将制表符转换为空格
cat text|tr '\t' ' '

# 将不在指定字符集合中的所有字符删除
> echo "aa.,a 1 b#$bb 2 c*/cc 3 ddd 4"|tr -d -c '0-9 \n'
1 2 3 4

# 去掉重复的字符
> echo "hell   oooo wwwworld"|tr -d ' ow'
hello world

# 数字相加操作
> seq 100|xargs -n1|echo $[ $(tr '\n' '+')0 ]
5050

# 取出 mac 地址，去掉冒号，转换为大写
> echo "2018/03/29 16:00:22 bc:ec:29:39:d4:2f online"|awk -F ' ' '{print $3}'|tr  'a-z' 'A-Z'|tr -d ':'
BCEC2939D42F
```

## 编译、打包脚本
```bash
#!/bin/sh

usage() {
    echo "usage: $0 <Ver> <Env>"
    echo "  Option:"
    echo "      Ver     consist of 4 parts, i.e. 1.0.1.0"
    echo "      Env     [dev|test|prod]"
    echo ""
    exit 1
}

# Return: 0, valid; 1, invalid
check_env() {
    envs=('dev test prod')
    for env in $envs
    do
        if [[ "$1" == "$env" ]]; then
            return 0;
        fi
    done

    return 1;
}

if [ $# -ne 2 ]; then
    usage
fi

check_env $2

if [ $? != 0 ]; then
    echo "Option Env invalid, check again"
    echo ""
    usage
    exit 1;
fi

VERSION=$1
ENV=$2
echo "[INFO] Version: $VERSION, Environment: $ENV"

echo "[INFO] clean all ..."
cd ..
find . -name cmake_install.cmake | xargs rm -rf
find . -name CMakeFiles | xargs rm -rf
find . -name CMakeCache.txt | xargs rm -rf
find . -name Makefile | xargs rm -rf
cd - > /dev/null
ls -d * | grep -v make_release.sh | xargs rm -rf

echo "[INFO] compile all ..."
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4

echo "[INFO] packing all ..."
PKGNAME=xxx_access_$ENV\_$VERSION
PKGACCESS=$PKGNAME/access
PKGPROXY=$PKGNAME/proxy
PKGLOGGER=$PKGNAME/logger
mkdir -p $PKGNAME $PKGLIB $PKGACCESS $PKGLOGGER $PKGPROXY

cp -rP test/access/test_access $PKGACCESS/access
cp -rP ../test/access/access_cmd.sh $PKGACCESS/remote_access_client.sh
chmod +x $PKGACCESS/remote_access_client.sh
cp -rP test/logger_server/test_logger_server $PKGLOGGER/logger
cp -rP test/logger_server/test_logger_client $PKGLOGGER/client
cp -rP test/proxy/test_proxy $PKGPROXY/proxy
cp -rP test/proxy/test_client $PKGPROXY/client

echo "[INFO] generating default configuration file"
cat > $PKGACCESS/default.conf << EOF
{
    "sub_topic" : "$ENV-access",
    "pub_topic" : "$ENV-device_management_system",
    "proxy_topic" : "$ENV-proxy",
    "kafka_brokers" : "xxx.xxx.xxx.xxx:9092",

    "oauth_server_addr" : "xxx.xxx.xxx.xxx",
    "oauth_server_port" : 9006,
    "oauth_username" : "dbaccess",
    "oauth_password" : "123456",

    "listen_addr" : "xxx.xxx.xxx.xxx",
    "listen_port" : 10999,
    "heartbeat_timeout" : 60,

    "http_listen_addr" : "xxx.xxx.xxx.xxx",
    "http_listen_port" : 10086,
    "http_username" : "dbaccess",
    "http_password" : "123456",

    "enable_debug" : true,
    "reserved" : false
}
EOF

cat > $PKGLOGGER/default.conf << EOF
{
    "listen_port" : 10998
}
EOF

cat > $PKGPROXY/default.conf << EOF
{
    "sub_topic" : "$ENV-proxy",
    "kafka_brokers" : "xxx.xxx.xxx.xxx:9092",
    "listen_port" : 12306,
    "active_timeout" : 15,

    "loadbalance_type": 1,
    "mac_rule": [
        {
            "mac_set": [],
            "mac_instance_set": []
        }
    ],
    "ip_rule": [
        {
            "ip_set": [],
            "ip_instance_set": []
        }
    ]
}
EOF

echo "[INFO] generating version info ..."
COMMITID=$(git rev-list -1 HEAD)
cat > VERSION << EOF
COMMIT ID: $COMMITID
VERSION  : $VERSION
EOF
for dir in $(find $PKGNAME -mindepth 1 -maxdepth 1 -type d)
do
    cd $dir
    md5sum $(find . -type f) > /tmp/MD5SUM
    mv /tmp/MD5SUM .
    cp ../../VERSION .
    cd - > /dev/null
done
rm -rf VERSION

echo "[INFO] generating ChangeLog"
cp ../ChangeLog $PKGNAME

echo "[INFO] generating INSTALL"
cat > INSTALL << EOF
===========================================================================
1. 接入服务 access

a. 修改配置文件

b. 配置防火墙，vim /etc/sysconfig/iptables 加入一条（以端口号 10999 为例）
-A INPUT -p tcp -m state --state NEW -m tcp --dport 10999 -j ACCEPT

c. 启动服务
./access -d -w --conf default.conf

===========================================================================
2. 接入代理服务 proxy

a. 修改配置文件

b. 配置防火墙，vim /etc/sysconfig/iptables 加入一条（以端口号 12306 为例）
-A INPUT -p tcp -m state --state NEW -m tcp --dport 12306 -j ACCEPT

c. 启动服务
./proxy -d -w --conf default.conf

===========================================================================
3. 网关日志服务 logger

a. 修改配置文件，最小配置只需要修改监听的端口号（listen_port）
注意：由于中控插件上传日志时，作为 logger 的客户端，因此，监听的端口
号需要与中控插件配置的日志服务器端口对应。

b. 配置防火墙，vim /etc/sysconfig/iptables 加入一条（以端口号 10998 为例）
-A INPUT -p tcp -m state --state NEW -m tcp --dport 10998 -j ACCEPT

c. 启动服务
./logger -d -w --conf default.conf
EOF
cp -rP INSTALL $PKGNAME
rm -rf INSTALL

echo "[INFO] generating README.md ..."
cat > README.md << EOF
===========================================================================
[ACCESS]
DESC:
    xxx's access service, connecting gateway and cloud.

LIST:
    access          xxx's access service

Usage:
    ./access -h     show help

ATTENTION:
    Do not forget to config iptables or firewall's in/out strategies in
order to ensure the forwarding client can access the listening port.

===========================================================================
[PROXY]
DESC:
    xxx's access proxy service, assigning access service instances to
gateway.

LIST:
    proxy           xxx's access proxy service
    client          fetch an access instance by sending a request

Usage:
    ./proxy -h      show help

ATTENTION:
    Do not forget to config iptables or firewall's in/out strategies in
order to ensure the forwarding client can access the listening port.

===========================================================================
[LOGGER]
DESC:
    xxx's logger server for HuaWei gateway

LIST:
    logger          xxx's logger server
    client          test logger server's health by sending 'helloworld'

Usage:
    ./logger -h     show help

    If logger is running, you can run client to test. For example, logger
is running on host 192.168.1.1, listening on port 10998, run
./client 192.168.1.1 10998 to test whether the logger service is working.

ATTENTION:
    Do not forget to config iptables or firewall's in/out strategies in
order to ensure the forwarding client can access the listening port.
EOF

cp -rP README.md $PKGNAME
rm -rf README.md

echo "[INFO] archiving all ..."
tar -czf $PKGNAME.tar.gz $PKGNAME

echo "[INFO] clean tmp files ..."
ls -d * | grep -v "make_release.sh\|$PKGNAME.tar.gz" | xargs rm -rf

echo ""
echo "[INFO] =========================================="
echo "[INFO]        Congratulations, all is done"
echo "[INFO] =========================================="
echo ""

exit $?
```

## openssl 自签证书

> **download:** [自签证书](https://github.com/dudebing99/blog/blob/master/archives/script/ca.tar.gz)

### 初始化 CA

```bash
#!/bin/sh

# name: init_ca.sh
# author: kevin

echo ""
echo -e "\e[1;33m===============================================\e[0m"
echo -e "\e[1;33mFunction: construct your own private CA.\e[0m"
echo -e "\e[1;33mSupported OS: CentOS 6.8\e[0m"
echo -e "\e[1;33m===============================================\e[0m"
echo ""

# check root permission
if [ $UID -ne 0 ]; then
    echo -e "\e[1;31m[Failed] superuser privileges are required\e[0m"
    exit 1
else
    echo -e "\e[1;32m[Passed] superuser privileges meeted\e[0m"
fi

if [ -e /etc/pki/CA/cacert.pem ]; then
    echo -e -n "\e[1;31m[WARN] re-init CA? (Y/n)\e[0m"
    while [ 1 ]
    do
        read Confirm
        if [ "$Confirm"x = "Y"x -o "$Confirm"x = "y"x ]; then
            echo -e "\e[1;33m[INFO] start to re-init CA\e[0m"
            break;
        elif [ "$Confirm"x = "n"x ]; then
            exit 1
        else
            echo -e -n "\e[1;31m[ERROR] invalid option, re-init CA? (Y/n)\e[0m"
            continue
        fi
    done
fi

OS=`cat /etc/redhat-release | awk '{print $1 " " $3}'`
SupportedOS="CentOS 6.8"
if [ "$OS"x = "$SupportedOS"x ]; then
    echo -e "\e[1;32m[Passed] OS: $OS\e[0m"
else
    echo -e "\e[1;31m[Failed] $SupportedOS supported only\e[0m"
    exit 1;
fi

# install openssl
Found=`openssl version | grep "command not found"`
if [ -n $Found ]; then
    echo -e "\e[1;33m[INFO] openssl installed\e[0m"
else
    echo -e "\e[1;33m[INFO] install openssl\e[0m"
    yum install openssl -y > /dev/null
fi

echo -e "\e[1;33m[INFO] generate CA's private key\e[0m"
(umask 077; openssl genrsa -out /etc/pki/CA/private/cakey.pem 2048)

echo -e "\e[1;33m[INFO] generate CACert\e[0m"
cat > gen_cert.exp << EOF
#!/usr/bin/expect -f

set timeout 30

spawn openssl req -new -x509 -key /etc/pki/CA/private/cakey.pem -out \
/etc/pki/CA/cacert.pem -days 3655

expect {
    "Country Name (2 letter code)" {
        send "cn\r";
        exp_continue
    }

    "State or Province Name (full name)" {
        send "Guang Dong\r";
        exp_continue
    }

    "Locality Name (eg, city)" {
        send "Shen Zhen\r";
        exp_continue
    }

    "Organization Name (eg, company)" {
        send "XXX Tech Ltd.\r";
        exp_continue
    }

    "Organizational Unit Name (eg, section)" {
        send "XXX's CA\r";
        exp_continue
    }

    "Common Name (eg, your name or your server's hostname)" {
        send "xxx.cn\r";
        exp_continue
    }

    "Email Address" {
        send "cloud@xxx.cn\r";
        exp_continue
    }
}
EOF

chmod +x gen_cert.exp
./gen_cert.exp
rm -rf gen_cert.exp

echo -e "\e[1;33m[INFO] CACert's information in detail:\e[0m"
openssl x509 -noout -text -in /etc/pki/CA/cacert.pem

echo -e "\e[1;33m[INFO] Verify CACert's invalidism\e[0m"
openssl verify /etc/pki/CA/cacert.pem

echo -e "\e[1;33m[INFO] init CA's serial\e[0m"
touch /etc/pki/CA/{index.txt,serial}
echo 01 > /etc/pki/CA/serial

echo -e "\e[1;33m[INFO] Congratulations! Everything is done.\e[0m"
```

### 颁发证书

```bash
#!/bin/sh

# name:  gen_cert.sh
# author: kevin

# check root permission
validate_superuser() {
    if [ $UID -ne 0 ]; then
        echo -e "\e[1;31m[Failed] superuser privileges are required\e[0m"
        exit 1
    else
        echo -e "\e[1;32m[Passed] superuser privileges meeted\e[0m"
    fi
}

usage() {
    echo -e "\e[1;31mUsage: $0 <organization> <number>\e[0m"
    echo -e "\e[1;33mOption:\e[0m"
    echo -e "\e[1;33m    Organization   for example, Gateway or Access\e[0m"
    echo -e "\e[1;33m    number         [1, 9999] number of certification(s) \
generated in batch\e[0m"
}

introduction() {
    echo ""
    echo -e "\e[1;33m====================================================\e[0m"
    echo -e "\e[1;33mFunction: Issue Certification.\e[0m"
    echo -e "\e[1;33mSupported OS: CentOS 6.8\e[0m"
    echo -e "\e[1;33m====================================================\e[0m"
    echo ""
}

if [ $# -ne 2 ]; then
    usage
    exit 1
else
    echo $2|grep "^[1-9][0-9]\{0,3\}$" > /dev/null

    if [ $? -ne 0 ]; then
        usage
        echo -e "\e[1;31m[ERROR] ARGUMENT INVALID\e[0m"
        exit 1
    fi
fi

validate_superuser

introduction

if [ -e /etc/pki/CA/cacert.pem ]; then
    echo -e "\e[1;33m[INFO] start to issue certification\e[0m"
else
    exit 1
fi

OS=`cat /etc/redhat-release | awk '{print $1 " " $3}'`
SupportedOS="CentOS 6.8"
if [ "$OS"x = "$SupportedOS"x ]; then
    echo -e "\e[1;32m[Passed] OS: $OS\e[0m"
else
    echo -e "\e[1;31m[Failed] $SupportedOS supported only\e[0m"
    exit 1;
fi

# install openssl
Found=`openssl version | grep "command not found"`
if [ -n $Found ]; then
    echo -e "\e[1;33m[INFO] openssl installed\e[0m"
else
    echo -e "\e[1;33m[INFO] install openssl\e[0m"
    yum install openssl -y > /dev/null
fi

mkdir -p cert
rm -rf cert/*

for ((count=1; count <= $2; ++ count))
do
echo -e "\e[1;33m[INFO] generate $1's private key\e[0m"
(umask 077;openssl genrsa -out ./cert/$1\.key 2048)

echo -e "\e[1;33m[INFO] generate $1's Cert\e[0m"
cat /etc/pki/CA/index.txt >> /etc/pki/CA/index.txt.bak
cat /dev/null > /etc/pki/CA/index.txt

cat > gen_cert.exp << EOF
#!/usr/bin/expect -f

set timeout 30

spawn openssl req -new -key ./cert/$1\.key -out ./cert/$1\.csr

expect {
    "Country Name (2 letter code)" {
        send "cn\r";
        exp_continue
    }

    "State or Province Name (full name)" {
        send "Guang Dong\r";
        exp_continue
    }

    "Locality Name (eg, city)" {
        send "Shen Zhen\r";
        exp_continue
    }

    "Organization Name (eg, company)" {
        send "xxx Tech Ltd.\r";
        exp_continue
    }

    "Organizational Unit Name (eg, section)" {
        send "$1\r";
        exp_continue
    }

    "Common Name (eg, your name or your server's hostname)" {
        send "xxx.cn\r";
        exp_continue
    }

    "Email Address" {
        send "cloud@xxx.cn\r";
        exp_continue
    }

    "A challenge password" {
        send "xxx666!\r";
        exp_continue
    }

    "An optional company name" {
        send "XXX Tech Ltd.\r";
        exp_continue
    }
}
EOF

chmod +x gen_cert.exp
./gen_cert.exp

# sign certification
cat > sign_cert.exp << EOF
#!/usr/bin/expect -f

set timeout 30

spawn openssl ca -in ./cert/$1\.csr -out ./cert/$1\.crt -days 3655

expect {
    "Sign the certificate" {
        send "y\r";
        exp_continue
    }

    "1 out of 1 certificate requests certified, commit" {
        send "y\r";
        exp_continue
    }
}
EOF

chmod +x sign_cert.exp
./sign_cert.exp

(umask 077;touch ./cert/$1\.pem)
cat ./cert/$1\.crt >> ./cert/$1\.pem
cat ./cert/$1\.key >> ./cert/$1\.pem
openssl rsa -in ./cert/$1\.pem -pubout -out ./cert/$1\.pub

# rename
cd cert > /dev/null
rm -rf $1\.csr
for file in `ls $1\.*`
do
    mv $file `echo "$count-$file" `
done
cd - > /dev/null
done

rm -rf gen_cert.exp
rm -rf sign_cert.exp

echo -e "\e[1;33m[INFO] Total: $2 certification(s).\e[0m"
echo -e "\e[1;33m[INFO] Output Directory: ./cert\e[0m"
echo -e "\e[1;33m[INFO] Congratulations! Everything is done.\e[0m"
```
## sudo 保存 vim 打开的文件
```bash
:w !sudo sh -c "cat >'%'" or :w !sudo tee "%"
```

## 拷贝并忽略特定的文件

```bash
cp `ls|grep -v dummy.txt|xargs` target_dir
```

## 统计文件数目

```bash
# 统计普通文件数目，不包括隐藏文件(即，以'.'开头的文件)
ls -l|grep "^-"|wc -l
find . -maxdepth 1 -type f|grep  -v "\./\."|wc -l

# 统计普通文件数目，包括隐藏文件
ls -al|grep "^"|wc -l
find . -maxdepth 1 -type f|wc -l

# 统计目录数目
ls -l|grep "^d"|wc -l
find . -maxdepth 1 -type f|grep  -v "\./\."|wc -l
```

## shell 实现多进程

```bash
#!/bin/bash
# 命令加'&'后台运行
cmd1 &
cmd2 &
# ...
cmdN&
# 必须加上，否则脚本执行完毕导致所以进程被结束
wait
```

## expect 自动登陆

```bash
#!/usr/bin/expect -f

# 脚本运行参数：ip、root 用户密码

set ip [lindex $argv 0]
set password [lindex $argv 1]
set timeout 30000

spawn ssh root@$ip
expect {
  "*yes/no" {
    send "yes\r"; 
    exp_continue
  }
  
  "*password:" { 
    send "$password\r" 
  }
}

expect "*#"

# 在目标机器执行任何命令，例如 echo
send "echo hello\r"
expect "*#"

# 退出
send "exit\r"
expect eof
```

## 获取字符串的长度

```bash
# 利用${#str}来获取字符串的长度
[root@localhost ~]# str="hello"
[root@localhost ~]# echo ${#str}
5

# 利用 awk 的 length 方法来获取字符串的长度
[root@localhost ~]# echo hello|awk '{print length($0)}'
5

# 利用 awk 的 NF 项来获取字符串的长度
[root@localhost ~]# echo hello|awk -F '' '{print NF}'
5

# 利用 wc -L 来获取字符串的长度，详见 man wc
[root@localhost ~]# echo hello|wc -L
5

# 利用 wc -c 来获取字符串的长度
[root@localhost ~]# echo hello|wc -c
6
# -n: 不统计换行符
[root@localhost ~]# echo -n hello|wc -c 
5

# 利用 expr 的 length 方法来获取字符串的长度
[root@localhost ~]# str=hello
[root@localhost ~]# expr length ${str}
5

# 利用 expr 的 $str : ".*" 来获取字符串的长度
# 备注：.* 代表任意字符，即，用任意字符来匹配字符串 hello，结果能够匹配 5 个
[root@localhost ~]# str="hello"; expr $str : ".*"
5
```

## 一键部署 zookeeper/kafka 集群

> **功能：**部署 zookeeper/kafka 集群
>
> **说明：**
> 1. 需要提前规划好 zookeeper/kafka 集群，并配置好 basic.info，详见 basic.info。
>
> 2. 可以支持 zookeeper/kafka 单机或集群部署
>   单机部署，配置信息参考 basic_example_standalone.info
>   集群部署，配置信息参考 basic_example_cluster.info
>
> **使用步骤：**
>
> 1. 修改 install_zk_kafka.tar.gz 中 install_zookeeper.sh/install_kafka 中安装包的路径（建议从内网下载安装包，可搭建 ftp 或 http 服务器），重新生成 install_zk_kafka.tar.gz
> 2. 将步骤 1 中生成的压缩包上传到  ftp 或 http 服务器
> 3. 将 zk_kafka_deploy.tar.gz 拷贝到操作机器（操作机器能够访问集群中所有机器即可）
> 4. 解压，修改 zk_kafka_deploy.sh 中 install_zk_kafka.tar.gz 的路径
> 5. 修改集群配置信息 basic.info
> 6. 执行脚本 ./zk_kafka_deploy.sh
>
> **download：**
>
> 1. install_zk_kafka.tar.gz: [安装](https://github.com/dudebing99/blog/blob/master/archives/script/install_zk_kafka.tar.gz)
> 2. zk_kafka_deploy.tar.gz: [一键部署](https://github.com/dudebing99/blog/blob/master/archives/script/zk_kafka_deploy.tar.gz)

### 部署

```bash
#!/bin/bash

# name: zk_kafka_deploy.sh
# author: kevin

# check root permission
if [ $UID -ne 0 ]; then
    echo "Superuser privileges are required to run this script."
    echo "e.g. \"sudo $0\""
    exit 1
fi

zookeepers=`cat basic.info | grep zookeeper`
zookeepers=`echo ${zookeepers#*=}`

kafkas=`cat basic.info | grep kafka`
kafkas=`echo ${kafkas#*=}`

password=`cat basic.info | grep cluster_common_passwd`
password=`echo ${password#*=}`

zookeeper_array=($zookeepers)
kafka_array=($kafkas)
zookeeper_num=${#zookeeper_array[@]}
kafka_num=${#kafka_array[@]}

# 校验 IP 是否有效
CheckIPAddr()
{
    # IP地址必须为全数字
    echo $1|grep "^[0-9]\{1,3\}\.\([0-9]\{1,3\}\.\)\{2\}[0-9]\{1,3\}$" > /dev/null

    if [ $? -ne 0 ]
    then
        return 1
    fi

    ipaddr=$1
    a=`echo $ipaddr | awk -F . '{print $1}'`  # 以"."分隔，取出每个列的值
    b=`echo $ipaddr | awk -F . '{print $2}'`
    c=`echo $ipaddr | awk -F . '{print $3}'`
    d=`echo $ipaddr | awk -F . '{print $4}'`

    for num in $a $b $c $d
    do
        if [ $num -gt 255 ] || [ $num -lt 0 ]; then
            return 1
        fi
    done

    return 0
}

if [ $zookeeper_num -eq 0 -o $kafka_num -eq 0 ]; then
    echo "ERROR: cluster info invalid"
    exit 1;
fi

for zk in $zookeepers
do
    CheckIPAddr $zk

    if [ $? -ne 0 ]; then
        echo "ERROR: ip addr [$zk] invalid"
        exit 1;
    fi
done

for kafka in $kafkas
do
    CheckIPAddr $kafka

    if [ $? -ne 0 ]; then
        echo "ERROR: ip addr [$kafka] invalid"
        exit 1;
    fi
done

cat > gen_rsa_pub.exp << EOF
#!/usr/bin/expect -f

set ip [lindex \$argv 0]
set password [lindex \$argv 1]
set timeout 30

spawn ssh root@\$ip
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

expect "*#"

send "yum install expect -y\r"
expect "*#"

send "curl -O ftp://192.168.2.2/pub/install_zk_kafka.tar.gz\r"
expect "*#"

send "tar -xzvf install_zk_kafka.tar.gz\r"
expect "*#"

send "cd install_zk_kafka\r"
expect "*#"

send "./gen_rsa_pub.sh\r"
expect "*#"

send "cd ~\r"
expect "*#"

send "rm -rf install_zk_kafka*\r"
expect "*#"

send "exit\r"
expect eof
EOF

cat > scp_rsa_pub.exp << EOF
#!/usr/bin/expect -f

set ip [lindex \$argv 0]
set password [lindex \$argv 1]
set timeout 30

spawn scp root@\$ip:~/.ssh/id_rsa.pub .
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

send "exit\r"
expect eof
EOF

cat > write_rsa_pubs.exp << EOF
#!/usr/bin/expect -f

set ip [lindex \$argv 0]
set password [lindex \$argv 1]
set timeout 30

spawn scp zk_id_rsa.pub root@\$ip:~
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

send "exit\r"
expect eof

spawn ssh root@\$ip
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

expect "*#"
send "cat ~/zk_id_rsa.pub >> ~/.ssh/authorized_keys\r"

expect "*#"
send "rm -rf ~/zk_id_rsa.pub\r"

expect "*#"
send "exit\r"

expect eof
EOF

if [ $zookeeper_num -gt 1 ]; then
    cat /dev/null > zk_id_rsa.pub
    chmod +x gen_rsa_pub.exp
    chmod +x scp_rsa_pub.exp
    chmod +x write_rsa_pubs.exp

    for zk in $zookeepers
    do
        ./gen_rsa_pub.exp $zk $password
        ./scp_rsa_pub.exp $zk $password
        cat id_rsa.pub >> zk_id_rsa.pub
        rm -rf id_rsa.pub
    done

    for zk in $zookeepers
    do
        ./write_rsa_pubs.exp $zk $password
    done

    rm -rf zk_id_rsa.pub
fi

    rm -rf gen_rsa_pub.exp
    rm -rf scp_rsa_pub.exp
    rm -rf write_rsa_pubs.exp

cat > install_zookeeper.exp << EOF
#!/usr/bin/expect -f

set ip [lindex \$argv 0]
set password [lindex \$argv 1]
set zookeepers [lindex \$argv 2]
set id [lindex \$argv 3]
set timeout 600

spawn ssh root@\$ip
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

expect "*#"

send "curl -O ftp://192.168.2.2/pub/install_zk_kafka.tar.gz\r"
expect "*#"

send "tar -xzvf install_zk_kafka.tar.gz\r"
expect "*#"

send "cd install_zk_kafka\r"
expect "*#"

send "./install_zookeeper.sh \$zookeepers \$id\r"
expect "*#"

send "cd ~\r"
expect "*#"

send "rm -rf install_zk_kafka*\r"
expect "*#"

send "exit\r"
expect eof
EOF

chmod +x install_zookeeper.exp

id=0
for zk in $zookeepers
do
    # in order to avoid info expired when the machine is rebuild
    sed -i "/$ip/d" ~/.ssh/known_hosts >/dev/null 2>&1

    ./install_zookeeper.exp $zk $password "'$zookeepers'" $id
    id=`expr $id + 1`
done

rm -rf install_zookeeper.exp

zookeeper_connect=""
for zk in $zookeepers
do
    zookeeper_connect=${zookeeper_connect}${zk}":2181,"
done
zookeeper_connect=${zookeeper_connect%,*}

cat > install_kafka.exp << EOF
#!/usr/bin/expect -f

set ip [lindex \$argv 0]
set password [lindex \$argv 1]
set broker_id [lindex \$argv 2]
set zookeeper_connect [lindex \$argv 3]
set timeout 600

spawn ssh root@\$ip
expect {
  "*yes/no" {
    send "yes\r";
    exp_continue
  }

  "*password:" {
    send "\$password\r"
  }
}

expect "*#"

send "curl -O ftp://192.168.2.2/pub/install_zk_kafka.tar.gz\r"
expect "*#"

send "tar -xzvf install_zk_kafka.tar.gz\r"
expect "*#"

send "cd install_zk_kafka\r"
expect "*#"

send "./install_kafka.sh \$broker_id \$ip \$zookeeper_connect\r"
expect "*#"

send "cd ~\r"
expect "*#"

send "rm -rf install_zk_kafka*\r"
expect "*#"

send "exit\r"
expect eof
EOF

chmod +x install_kafka.exp

id=0
for kafka in $kafkas
do
    # in order to avoid info expired when the machine is rebuild
    sed -i "/$ip/d" ~/.ssh/known_hosts >/dev/null 2>&1

    ./install_kafka.exp $kafka $password $id $zookeeper_connect
    id=`expr $id + 1`
done

rm -rf install_kafka.exp

echo $?
```

### 集群配置信息

```bash
# 此文件只能修改 value，不能修改 key
# 即，只能修改等号右边的值，根据实际集群信息修改
zookeeper=192.168.2.3 192.168.2.4 192.168.2.5
kafka=192.168.2.3 192.168.2.4 192.168.2.5
cluster_common_passwd=123456
```