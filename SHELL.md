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
