[TOC]

------

## 内存泄露排查

### 较为明显的内存泄漏

> 通过系统自带的命令持续地观察进程内存的占用情况，即可发现有明显内存泄漏的进程；更进一步，当进程运行一段时间导致系统内存耗尽，将会被操作系统杀掉。

- 利用 free 查看系统内存

- 利用 top 查看进程占用内存

  ```bash
  top -d 1 -p pid
  ```

- 利用 ps 查看进程占用内存

  ```bash
  watch -n1 'ps -aux|grep -v grep|grep pid'
  ```

### 不太明显的内存泄漏

- 利用 valgrind 工具查看内存分配、释放、泄漏

  ```bash
  valgrind --log-file=valgrind.log --tool=memcheck --leak-check=full --show-reachable=no --workaround-gcc296-bugs=yes ./a.out
  ```

## 进程异常排查

### 查看系统级别是否运行异常

- 利用 top 查看全局资源使用
- 利用 free 查看系统内存使用
- 利用 iostat 查看磁盘 I/O 是否异常
- 利用 df -i 查看系统 inode 使用是否异常；df -h 查看系统磁盘使用是否异常
- 利用 ss/netstat 查看系统网络连接是否异常
- 利用 ifstat 查看系统网络流量是否异常

### 查看进程级别是否运行异常

- top 查看进程资源使用是否正常（特别注意，内存是否一致在增加）

- lsof 查看进程打开的文件句柄数

- 查看进程堆栈信息（2388 为进程号）

  ```bash
  [root@www ~]# cat /proc/2388/stack
  [<ffffffff811f2bb5>] poll_schedule_timeout+0x55/0xb0
  [<ffffffff811f413d>] do_sys_poll+0x4cd/0x580
  [<ffffffff811f42f4>] SyS_poll+0x74/0x110
  [<ffffffff81645909>] system_call_fastpath+0x16/0x1b
  [<ffffffffffffffff>] 0xffffffffffffffff
  ```

- strace 查看系统调用和信号

  ```bash
  [root@www ~]#  strace -s 99 -ffp 3363
  Process 3363 attached with 2 threads
  [pid  3365] restart_syscall(<... resuming interrupted call ...> <unfinished ...>
  [pid  3363] select(18, [13 16 17], NULL, NULL, {29, 702368}) = 1 (in [16], left {23, 709762})
  [pid  3363] fcntl(16, F_GETFL)          = 0x802 (flags O_RDWR|O_NONBLOCK)
  [pid  3363] accept4(16, 0, NULL, SOCK_CLOEXEC) = -1 EAGAIN (Resource temporarily unavailable)
  Process 3365 detached
  ```

- gdb attach 进程并获取堆栈信息

  ```bash
  [root@www ~]# gdb attach 2388
  GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-80.el7
  Copyright (C) 2013 Free Software Foundation, Inc.
  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
  This is free software: you are free to change and redistribute it.
  There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
  and "show warranty" for details.
  This GDB was configured as "x86_64-redhat-linux-gnu".
  For bug reporting instructions, please see:
  <http://www.gnu.org/software/gdb/bugs/>...
  Attaching to process 2388
  Reading symbols from /home/mysql/bin/mysqld...
  done.
  Reading symbols from /usr/lib64/libpthread.so.0...Reading symbols from /usr/lib/debug/usr/lib64/libpthread-2.17.so.debug...done.
  done.
  
  (gdb) 
  (gdb) bt
  #0  0x00007f88e3f4669d in poll () at ../sysdeps/unix/syscall-template.S:81
  #1  0x0000000000d2ae9d in Mysqld_socket_listener::listen_for_connection_event (this=0x5933700)
      at /root/lnmp1.3-full/src/mysql-5.7.11/sql/conn_handler/socket_connection.cc:848
  #2  0x000000000077e069 in connection_event_loop (this=0x59a6050) at /root/lnmp1.3-full/src/mysql-5.7.11/sql/conn_handler/connection_acceptor.h:66
  #3  mysqld_main (argc=45, argv=0x3b56bd8) at /root/lnmp1.3-full/src/mysql-5.7.11/sql/mysqld.cc:4941
  #4  0x00007f88e3e7bb15 in __libc_start_main (main=0x756100 <main(int, char**)>, argc=10, ubp_av=0x7ffe5ab6c418, init=<optimized out>, fini=<optimized out>, 
      rtld_fini=<optimized out>, stack_end=0x7ffe5ab6c408) at libc-start.c:274
  #5  0x00000000007734dd in _start ()
  ```

- java 程序，可以借助 jstack、jstat、jmap、jinfo 等查看进程的运行信息

## TCP 协议

### TCP 连接建立

在 TCP/IP 协议中，TCP 协议提供可靠的连接服务，采用三次握手建立一个连接。

- 第一次握手：建立连接时，客户端发送 `SYN` 到服务器，并进入 `SYN_SEND` 状态，等待服务器确认
- 第二次握手：服务器收到 `SYN`，必须确认客户的 `SYN`，同时自己也发送一个 `SYN`，即 `SYN + ACK`，此时服务器 进入 `SYN_RECV` 状态
- 第三次握手：客户端收到服务器的 `SYN＋ACK`，向服务器发送确认包 `ACK`，此包发送完毕，客户端和服务器进入 `ESTABLISHED` 状态，完成三次握手。 完成三次握手，客户端与服务器开始传送数据。

![](pic/tcp/connect.png)

> **为什么要三次握手？**
>
> 防止失效的连接请求突然传到服务器端，让服务器端误认为要建立连接。

### TCP 连接释放

在 TCP/IP 协议中，TCP 协议提供可靠的连接服务，采用四次挥手释放一个连接。

![](pic/tcp/disconnect.png)

> **为什么 Client 进入 TIME-WAIT 后必须等待 2 MSL？**
>
> - 保证 Client 发送的最后一个 ACK 报文段能达到 Server
> - 防止失效的报文段出现在连接中

## HTTP 压力测试

### wrk

> - wrk 是一款现代化的 http 压测工具，提供 lua 脚本的功能可以满足每个请求或部分请求的差异化
> - wrk 中执行 http 请求的时候，调用 lua 分为3个阶段，setup，running，done，每个 wrk 线程中都有独立的脚本环境
> - 可以参考 [wrk benchmark](https://github.com/wg/wrk) 项目包含的样例（目录 scripts）以及说明（SCRIPTING）

![](pic/wrk/wrk.png)

#### wrk的全局属性

```lua
wrk = {
  scheme  = "http",
  host    = "localhost",
  port    = nil,
  method  = "GET",
  path    = "/",
  headers = {},
  body    = nil,
  thread  = <userdata>,
}
```

#### wrk 的全局方法

```lua
-- 生成整个 request 的 string，与全局属性 wrk table 配合使用
function wrk.format(method, path, headers, body)
-- 获取域名的 IP 和端口，返回 table
function wrk.lookup(host, service)
-- 判断 addr 是否能连接，例如：`127.0.0.1:80`，返回 true 或 false
function wrk.connect(addr)
```

#### 启动阶段

> 在脚本文件中实现 setup 方法，wrk 就会在测试线程已经初始化但还没有启动的时候调用该方法。wrk 会为每一个测试线程调用一次 setup 方法，并传入代表测试线程的对象 thread 作为参数。setup 方法中可操作该thread 对象，获取信息、存储信息、甚至关闭该线程。 

thread提供了 1 个属性，3 个方法 

- thread.addr 设置请求需要打到的 ip
- thread:get(name) 获取线程全局变量
- thread:set(name, value) 设置线程全局变量
- thread:stop() 终止线程

#### 运行阶段

> init 由测试线程调用，只会在进入运行阶段时，调用一次。支持从启动 wrk 的命令中，获取命令行参数； delay 在每次发送 request 之前调用，如果需要 delay，那么 delay 相应时间； request 用来生成请求；每一次请求都会调用该方法，所以注意不要在该方法中做耗时的操作； reponse 在每次收到一个响应时调用；为提升性能，如果没有定义该方法，那么 wrk 不会解析 headers 和 body。

- function init(args)  每个线程仅调用 1 次，args 用于获取命令行中传入的参数, 例如 --env=pre
- function delay()  每次请求调用 1 次，发送下一个请求之前的延迟, 单位为 ms 
- function request()  每次请求调用 1 次，返回 http 请求  
- function response(status, headers, body)  每次请求调用 1 次，返回 http 响应

#### 结束阶段

> 该方法在整个测试过程中只会调用一次，可从参数给定的对象中，获取压测结果，生成定制化的测试报告。 

```lua
function done(summary, latency, requests)


latency.min              -- minimum value seen
latency.max              -- maximum value seen
latency.mean             -- average value seen
latency.stdev            -- standard deviation
latency:percentile(99.0) -- 99th percentile value
latency(i)               -- raw value and count

summary = {
  duration = N,  -- run duration in microseconds
  requests = N,  -- total completed requests
  bytes    = N,  -- total bytes received
  errors   = {
    connect = N, -- total socket connection errors
    read    = N, -- total socket read errors
    write   = N, -- total socket write errors
    status  = N, -- total HTTP status codes > 399
    timeout = N  -- total request timeouts
  }
}
```

#### wrk 使用手册

```basic
使用方法: wrk <选项> <被测 HTTP 服务的 URL>                            
  Options:                                            
	-c, --connections <N>  跟服务器建立并保持的 TCP 连接数量  
    -d, --duration    <T>  压测时间           
    -t, --threads     <N>  使用多少个线程进行压测   
                                                      
	-s, --script      <S>  指定 Lua 脚本路径       
	-H, --header      <H>  为每一个 HTTP 请求添加 HTTP 头      
        --latency          在压测结束后，打印延迟统计信息   
        --timeout     <T>  超时时间     
	-v, --version          打印正在使用的 wrk 的详细版本信息
                                                      
  <N>代表数字参数，支持国际单位 (1k, 1M, 1G)
  <T>代表时间参数，支持时间单位 (2s, 2m, 2h)
```

#### 示例 1

> 启动 4 个线程，创建 100 个连接，持续 10s，请求百度主页（**支持 HTTP/HTTPS**）

```bash
root@ubuntu:~/wrk# wrk -t4 -c100 -d10s https://www.baidu.com
Running 10s test @ https://www.baidu.com
  4 threads and 100 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    77.65ms  122.51ms   1.88s    88.42%
    Req/Sec   618.40    200.60     1.25k    77.58%
  24500 requests in 10.04s, 360.47MB read
  Socket errors: connect 0, read 130, write 0, timeout 0
Requests/sec:   2439.09
Transfer/sec:     35.89MB
```

**结果分析：**

- avg/stddev/max 平均值/标准差/最大值
- +/- stddev 正负一个标准差，落在正负一个标准差的次数所占比重，值越大数据越稳定
- latency 时延，对应响应时间
- request/sec 每秒钟请求数，值越大性能越高

#### 示例 2

> 每个线程要先进行认证，认证之后获取 token 以进行压测。在没有token的情况下，先访问 /authenticate 认证。认证成功后，读取 token 并替换 path 为 /resource。

```lua
token = nil
path  = "/authenticate"

request = function()
   return wrk.format("GET", path)
end

response = function(status, headers, body)
   if not token and status == 200 then
      token = headers["X-Token"]
      path  = "/resource"
      wrk.headers["X-Token"] = token
   end
end
```

#### 示例 3

> 启动 4 个线程，创建 100 个连接，持续 10s，每个请求发送不同的数据

脚本内容如下所示

```lua
wrk.method = "POST"  
wrk.body   = ""
-- 可以根据实际接口请求路径修改
wrk.path   = "/"
wrk.headers["Content-Type"] = "text/plain" 

-- 每次修改充值积分值，保证每次交易都能成功提交，否则，可能因为交易仍在内存池中，
-- 判定为同一笔交易导致提交失败。当然，也可在脚本中每次选用不同的目标账户进行充值。
local value = 1
local a = '{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"creditrechargetx\", \"params\": [\"wWPAztEx3m5hArykWaH3qQZ13NtxaZXJts\", \"82908-1\", 0, 10000, 0, \"wNYc86E6JVvQfmgzQDESR81J7UuLtt9WDx\", '
local b = '] }'

request = function()

    local data = string.format("%s%d%s", a, value, b)
    value = value + 1

    return wrk.format(nil, nil, nil, data)
end

-- 请求之间设置 30~40 ms 的随机延迟
--function delay()
--   return math.random(30, 40)
--end

-- 可打印响应内容
--response = function(status, headers, body)
--    print(string.format("status: %d", status))
--    print(body)
--end
```

执行压测用例

```bash
root@ubuntu:~/wrk# wrk -t4 -c100 -d10s -s creditrecharge.lua http://192.168.1.213:6901
Running 10s test @ http://192.168.1.213:6901
  4 threads and 100 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   688.24ms  363.88ms   2.00s    84.39%
    Req/Sec    52.32     50.44   242.00     83.33%
  1435 requests in 10.09s, 667.72KB read
  Socket errors: connect 0, read 0, write 0, timeout 15
Requests/sec:    142.25
Transfer/sec:     66.19KB
```

## GDB 小技巧

### 基本操作

```bash
# 列出源码的一部分
list

# 单步调试，不进入函数
next
# 单步调试，进入函数
step

# 运行加载了的程序
run
# 继续执行程序
continue
# 退出调试
quit

# 输出特定变量的值
print
# 设置断点
break
#查看所有断点信息
info break
# 删除断点
delete
# 监视一个变量的值，一旦发生变化，程序将会被暂停
watch

# 打印所有线程堆栈
thread apply all bt
```

### 调试 coredump

- 生成 coredump 文件

  ```bash
  # 方式一
  gcore -o xxx.core pid
  
  # 方式二
  gdb attach pid
  gcore
  ```

- 调试 coredump 文件

  ```bash
  gdb xxx -c xxx.core
  ```

## VIM 小技巧

```bash
# VIM 替换时带确认，即，对于任何一个匹配项，需要确认是否替换
:%s/a/b/gc

# 上下(垂直）分割当前打开的文件
Ctrl+w s

# 左右（水平）分割当前打开的文件
Ctrl+w v

# 关闭当前窗口，对应 :close 
# 注意：最后一个窗口不能使用 close 关闭，使用 close 只是暂时关闭窗口，其内容还在缓存中。
Ctrl+w c
# 关闭当前窗口，对应 :q
Ctrl+w q

# 横向切割窗口
:new 文件名
:split 文件名 或简写为 :sp 文件名

# 纵向切割窗口
:vsplit 文件名 或简写为 :vsp 文件名

# 关闭当前窗口，对应 :close，使用 close 只是暂时关闭窗口，其内容还在缓存中。
Ctrl+w c
# 关闭当前窗口，对应 :q，与 close 不同之处在于永久关闭窗口，因此可关闭最后一个打开的窗口。
Ctrl+w q

# 切换窗口：连续两次 Ctrl+w 依次切换打开的窗口
Ctrl+w Ctrl+w
# 切换窗口：Ctrl+w 配合h/j/k/l 或者 上下左右方向键
Ctrl+w h/j/k/l

# 显示空格、TAB
# TAB 键显示为 ^I，$ 显示在每行的结尾，表示换行；空格仍然显示为空格。
:set list		进入 List Mode
:set nolist		退出 List Mode
```

## Git 小技巧

### 基本操作

```bash
# 克隆远程仓库到本地
git clone ssh://kevin@192.168.5.32:29418/dummy.git

# 查看本地变更信息
git status
# 查看本地当前目录变更信息
git status .

# 添加提交信息（交互式编辑）
git commit
# 添加提交信息（非交互式）
git commit -m "fix(module): free memory"
# 追加新的变更到上次提交（即，commit id 不变，多次修改的内容合并到一次提交）
git commit --amend

# 修改本次提交的作者信息
git commit --amend --author="kevin <dudebing99@gmail.com>" -C HEAD

# 查看当前所在分支
git branch
# 查看远程分支
git branch -r
```

### git stash

> - [x] 默认情况下，git stash 缓存文件的策略如下：
>
>
> 1. **会缓存下列文件**
>
> - 添加到暂存区的修改（staged changes）
> - Git 跟踪的但并未添加到暂存区的修改（unstaged changes）
> 2. **不会缓存以下文件**
> - 在工作目录中新的文件（untracked files）
> - 被忽略的文件（ignored files）
>
> - [x] 使用 -u 或者 --include-untracked 可以 stash untracked 的文件
> - [x] 使用 -a 或者 --all 命令可以  stash 当前目录下的所有修改

```bash
# 保存未提交的变更(建议通过 sava "fix(xxx): xxx)" 备注变更说明）
git stash save "fix(xxx): xxx"
# 可在 git stash 之后拉取远程最新代码
git pull
# 然后，pop 之前保存的未提交的更新，做修改、合并，最后再提交
git stash pop

# pop 指定栈层次， git stash pop stash@{0} 命令等同于 git stash pop
git stash pop stash@{id}

# 查看所有的 stash
git stash list

# 移除某个 stash
git stash drop stash@{id}
# 移除所有的 stash
git stash clear
```

### 合并分支到主干

```bash
# 假设在 dev 分支开发完
git add .
git commit -m "feat: ..."
git push -u origin dev

# 切换到（本地）master
git checkout master
# 拉取最新
git pull

# 将 dev 合并到（本地）master
git merge dev

# 可能需要解决冲突，然后 add，commit

# 推送到远程 master
git push origin master
```

### 查看历史提交信息

```bash
# 查看所有提交日志
git log

# 查看某次 commit 的修改内容
git show <commit-id>

# 查看某个文件的所有的修改内容
git log -p <filename>

# 查看某个文件的最近 2 次的更新内容
git log -p -2 <filename>

# 查看最近一次所有的更新内容（如下两种方法）
git log -p -1
git diff HEAD^

# 查看某个文件的最后一次更新内容由谁提交（对应到每一行）
git blame <filename>
```

### 仓库迁移

```bash
# 1. 本地有仓库 project1
# 2. 在 github 新建仓库 project2
# 3. 以镜像推送到 project2 上，可以保留 project1 的所有提交记录
git push --mirror git@github.com:dudebing99/project2.git
```

## 同步机器时间、硬件时钟

```bash
yum install rdate -y
# 设置时区
timedatectl set-timezone Asia/Shanghai
# 同步机器时间、硬件时钟
rdate -t 30 -s time.nist.gov && hwclock -w 
```

## SSH 机器互信（免密登陆）

**目标：**client 被 server 信任，即，client 可以通过免密 ssh 登陆 server。

1. client 产生公钥

   ```bash
   ssh-keygen -t rsa
   # 后续回车即可
   ```

2. 将步骤 1 中产生的 id_rsa.pub 拷贝并追加到 server 已授权 key 文件中

   ```bash
   cat id_rsa.pub >> root/.ssh/authorized_keys
   ```

3. 重启 server 端 ssh 服务

   ```bash
   # Ubuntu，service ssh restart 即可
   service sshd restart
   ```

## SSH 禁用超时

**目标：**SSH 空闲之后，默认断掉，每次需要重连太过麻烦，可以修改 SSH 服务端设置禁用超时

1. 在 /etc/ssh/sshd_config 添加/修改 如下配置项

   ```bash
   TCPKeepAlive yes
   ClientAliveInterval 30
   ClientAliveCountMax 999999
   ```

2. 重启 server 端 ssh 服务

   ```bash
   # Ubuntu，service ssh restart 即可
   service sshd restart
   ```

## 跳板机 Jumpserver 上传/下载文件

> **需求：**linux 服务器大多是通过 ssh 客户端来进行远程的登陆和管理，使用跳板机 Jumpserver，传输文件是个基础需求，可以借助 rz/sz 实现
>
> **限制：**rz/sz 只支持对文件（不支持文件夹）操作

### 上传文件 rz

```bash
rz -bye
```

### 下载文件 sz

```basic
[xbuser@push4 push_server]$ sz ce.sh
rz
Starting zmodem transfer.  Press Ctrl+C to cancel.
  100%       1 KB    0 KB/s 00:00:25       0 Errors
```

## MySQL 小技巧

### MySQL 清理控制台

```sql
system clear
```

### MySQL 查看表结构

```sql
show create table multi_app_user_tbl;
```

**输出**

```basic
mysql> show create table multi_app_user_tbl\G
*************************** 1. row ***************************
       Table: multi_app_user_tbl
Create Table: CREATE TABLE `multi_app_user_tbl` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增 ID',
  `uniq_user_id` varchar(64) NOT NULL COMMENT '用户唯一 ID',
  `org_user_id` int(11) NOT NULL COMMENT '用户 ID',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_org_user_id` (`org_user_id`),
  KEY `idx_uniq_user_id_user_id` (`uniq_user_id`)
) ENGINE=MyISAM AUTO_INCREMENT=4662 DEFAULT CHARSET=utf8
1 row in set (0.00 sec)
```

### MySQL 随机排序

```sql
select * from multi_app_user_tbl order by rand() limit 3;
```

**输出**

```basic
mysql> select * from multi_app_user_tbl order by rand() limit 3;
+------+--------------------------------------------+-------------+
| id   | uniq_user_id                               | org_user_id |
+------+--------------------------------------------+-------------+
| 1576 | advid:2b3f4008-9d2c-4410-8ff0-fb1a37021831 |      309614 |
| 2545 | advid:629e3632-83fc-41f6-b7a7-507d07da323a |      220043 |
| 2984 | advid:5a21e37d-8472-4b4b-aaad-c3828ab3a6fa |      190268 |
+------+--------------------------------------------+-------------+
3 rows in set (0.01 sec)

mysql> select * from multi_app_user_tbl order by rand() limit 3;
+------+--------------------------------------------+-------------+
| id   | uniq_user_id                               | org_user_id |
+------+--------------------------------------------+-------------+
| 1615 | advid:eca90566-6048-4ff5-a1e3-c979d467221f |      307227 |
| 2646 | advid:a383d2fc-22e5-4ccc-b5d7-de80cc8f8eed |      283161 |
| 1913 | advid:fb082377-24a0-4936-a189-50563515c5cd |      281130 |
+------+--------------------------------------------+-------------+
3 rows in set (0.00 sec)
```

### 快捷选择 MySQL 实例

1. 创建脚本 xdb.sh

```bash
#!/bin/bash

db=""
case $1 in
"log")
    db="mysql -uroot -p123456 -h log.topnews.com -Dlog"
    ;;
"reclog")
    db="mysql -uroot -p123456 -h 10.99.0.133 -Dreclog"
    ;;
"push")
    db="mysql -uroot -p123456 -h 10.99.0.56 -Dpush"
    ;;
*)
    echo "no param set"
esac

echo "Attention: connect to database: $1"
$db
```

2. chmod +x xdb.sh

3. 使用

   ./xdb.sh log 即可快捷登陆 log.topnews.com 的数据库 log

### 条件插入

**场景：**先根据条件判断某条记录是否存在，不存在则插入；存在即跳过。

**语法：**insert into table(column1, column2, ..., columnN) select value1, value2, value3, ..., valueN from dual where not exists (condition clause)

   ```sql
 insert into push_log_tbl(guid, origin_url, new_url, beg_ts) select '1111', '', '', sysdate() from dual where not exists (select guid from push_log_tbl where guid='1111');
   ```

### timestamp 字段查询

**场景一：**查询某个时间范围的数据

```sql
 SELECT `id`, `create_time` FROM `record` WHERE (create_time >= '2011-05-27 11:27:00') ORDER BY id DESC LIMIT 0, 20
```

**场景二：**查询某一天数据

```sql
select guid, content_id, title, long_text, new_url, ttl, icon, picture, push_enum from vntopnews_push.push_content_tbl where date_format(create_time,'%Y-%m-%d')='2011-05-27' order by create_time asc
```

### 时间相关函数

#### 查询 utc 时间戳、utc 日期、utc 时间、now()

```sql
mysql> select utc_timestamp(), utc_date(), utc_time(), now();
+---------------------+------------+------------+---------------------+
| utc_timestamp()     | utc_date() | utc_time() | now()               |
+---------------------+------------+------------+---------------------+
| 2018-05-26 08:27:00 | 2018-05-26 | 08:27:00   | 2018-05-26 16:27:00 |
+---------------------+------------+------------+---------------------+
```

#### now() 与 sysdate() 异同

```sql
mysql> select now(), sleep(3), now();
+---------------------+----------+---------------------+
| now()               | sleep(3) | now()               |
+---------------------+----------+---------------------+
| 2018-05-26 16:25:29 |        0 | 2018-05-26 16:25:29 |
+---------------------+----------+---------------------+
```

```sql
mysql> select sysdate(), sleep(3), sysdate();
+---------------------+----------+---------------------+
| sysdate()           | sleep(3) | sysdate()           |
+---------------------+----------+---------------------+
| 2018-05-26 16:24:56 |        0 | 2018-05-26 16:24:59 |
+---------------------+----------+---------------------+
```

#### date_add 函数

```sql
mysql> select date_add(now(), interval -1 day) as t1, date_add(now(), interval 8 hour) as t2, now();
+---------------------+---------------------+---------------------+
| t1                  | t2                  | now()               |
+---------------------+---------------------+---------------------+
| 2018-05-25 16:39:34 | 2018-05-27 00:39:34 | 2018-05-26 16:39:34 |
+---------------------+---------------------+---------------------+
```

### INSERT INTO SELECT 语句

```sql
INSERT INTO table2 SELECT * FROM table1;
```

```sql
INSERT INTO table2 (column_name(s))
SELECT column_name(s) FROM table1;
```

### 查看表创建时间

```sql
show table status
```

```sql
mysql> select CREATE_TIME from INFORMATION_SCHEMA.TABLES where TABLE_NAME='latest_active_user_tbl';
+---------------------+
| CREATE_TIME         |
+---------------------+
| 2018-05-30 10:36:31 |
+---------------------+
```



 