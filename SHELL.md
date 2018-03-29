# 统计网络连接状态及数目
```bash
netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'
```

# 统计进程打开的文件句柄数目
```bash
lsof -p PID
lsof -p PID|wc -l
```

# awk getline: 过滤行、改变奇数偶数行
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

# for 循环的常用写法
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

# 分割、合并大文件
```bash
# 按照指定行数分割
split -l 500 large_file.log new_file_prefix

# 按照文件大小分割
split -b 100m large_file.log new_file_prefix

# 使用 cat 进行文件合并
cat new_file_prefix* > large_file.log
```

# 检查 IPv4 地址合法性
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

# 替换文件中所有 \r
```bash
sed -i 's/\r//g' FILE
```

# 检查进程是否重启
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

# nohup 后台启动 java 进程
```bash
nohup java -classpath xxx_service_1.0.jar xxx_entry > xxx_service.log 2>&1 &
```

# 获取进程号、杀进程
```bash
ps afx|grep 进程名|grep -v grep|awk '{print $1}'|xargs kill -9
pgrep 进程名|xargs kill -9
pidof 进程名|xargs kill -9
pkill -9 进程名
killall -9 进程名
```

# 查询、启动、停止服务
```bash
# 新管理方式，如 Cent OS >= 7.x
systemctl start/status/enable/disable/stop/restart xxx_service

# 旧管理方式，如 Cent OS < 7.x
service xxx_service start/status/stop/restart
```

# 显示已经登录的用户、执行的命令
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

# 添加定时任务
```bash
### at 定时任务
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

# watch 持续监视命令的执行情况
```bash
# 每隔 3s，打印一次指定端口 9999 处于连接已建立的连接数目
watch -n 3 'netstat -anp|grep 9999|wc -l'
```

# TCP/UDP 收发数据、探测端口是否打开
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

# 逐行读取文件
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

# 如何解决 Linux Error: No space left on device
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

# 查找指定范围内的日志信息
```bash
# 查找时间范围 2018/03/28 05:00:00 ~ 2018/03/28 07:59:59 的所有日志
sed -n '#2018/03/28 05:[0-9][0-9]:[0-9][0-9]#,#2018/03/28 07:[0-9][0-9]:[0-9][0-9]#p' log
```

# tr 字符进行替换、压缩和删除
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
> echo aa.,a 1 b#$bb 2 c*/cc 3 ddd 4 | tr -d -c '0-9 \n'
1 2 3 4

# 去掉重复的字符
> echo "hell   oooo wwwworld"|tr -d ' ow'
hello world

# 数字相加操作
> seq 100| xargs -n1 | echo $[ $(tr '\n' '+')0]
5050
```