[TOC]

------

## 解决 root 分区空间不足的问题

**系统环境**

​	CentOS release 6.8 (Final)

**问题描述**

​	在安装操作系统时采取默认分区策略或者当初分配的策略与后面实际使用差异，导致某些分区仍然有大量的可用空间，但是 root 分区空间不够。

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

## Host SMbus controller not enabled

**系统环境**

​	CentOS/VMware® Workstation 12 Pro

**问题描述**

​	在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

​	在 /etc/modprobe.d/blacklist.conf 文件里添加如下内容：
blacklist i2c_piix4

## intel_rapl: no valid rapl domains found in package 0

**系统环境**

CentOS/VMware® Workstation 12 Pro

**问题描述**

在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

在 /etc/modprobe.d/blacklist.conf 文件里添加如下内容：
blacklist intel_rapl

## sd 0:0:0:0: [sda] Assuming drive cache: write through

**系统环境**

CentOS/VMware® Workstation 12 Pro

**问题描述**

在 VMWare 虚拟机启动 CentOS 时，出现如上警告信息

**解决方式**

1. 在 /etc/default/grub 文件里去掉 rhgb 参数

2. 执行 grub2-mkconfig -o /boot/grub2/grub.cfg

   > "rhgb" 表示 "redhat graphics boot"，就是图形进度条模式



3. 最后reboot

## MySQL 插入关键字导致 SQL 执行失败

**系统环境**

​	MySQL 5.6.x

**问题描述**

​	在 MySQL 表中某字段包含关键字 key，导致 SQL 语句执行报错，数据无法正常插入表中。错误信息大致如下：

​	*You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ...*

**解决方式**

​	执行如下 SQL  报错：INSERT into tb_map(key, value) VALUES('a',' 123');

> key 是 MySQL 关键字之一

正确写法：INSERT into tb_map(\`key\`, value) VALUES('a',' 123');

> 使用 转义符号：\`关键字\`

## MySQL 字段包含单引号、双引号导致 SQL 语法错误

**系统环境**

​	CentOS 6.8 x64/MySQL 5.6.35

**问题描述**

​	略

**解决方式**

​	SQL 中利用 `\` 转义即可，如下两种方式均可

```sql
-- 单引号转义
insert into blog_info_tbl (title, url) values ('kevin\'s blog', 'https://dudebing99.github.io/blog/');

-- 双引号转义
insert into blog_info_tbl (title, url) values ('\"kevin\" blog', 'https://dudebing99.github.io/blog/');
```

## MySQL 重置密码

**系统环境**

​	CentOS 6.8 x64/MySQL 5.6.35

**问题描述**

​	MySQL 用户密码丢失，重置用户密码

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

​	CentOS 6.8 x64/5.7.18 MySQL Community Server

**问题描述**

```sql
mysql> select org_user_id, uniq_user_id from (select * from multi_app_user_tbl) as tmp group by uniq_user_id;
ERROR 1055 (42000): Expression #1 of SELECT list is not in GROUP BY clause and contains nonaggregated column 'tmp.org_user_id' which is not functionally dependent on columns in GROUP BY clause; this is incompatible with sql_mode=only_full_group_by
```

**解决方式**

 	**原因：**Select 语句选择的列与 Group by 包含的列不一致，MySQL 默认有此限制。因此，一方面，可以修改业务的 SQL，遵循此限制；另一方面，可以取消 MySQL 此限制，如下所示

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

## SecureFX 中文文件名乱码

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

## SecureCRT 冻结终端/解除冻结/全屏/清屏

**系统环境**

​	SecureCRT Version 7.0.3 (build 480)

**问题描述**

​	略。

**解决方式**

- Ctrl + s：冻结终端
- Ctrl + q：解除冻结
- Alt + Enter：全屏/退出全屏
- Ctrl + L：清屏 clear

## SourceInSight 支持 .cc 文件

**系统环境**

Windows 7 Ultimate/SourceInSight 4.0

**问题描述**

略。

**解决方式**

Options -> Document Options，Document Type 下拉选 C++ Source File, File Filter 中加入 *.cc

## 设置网卡自启动

**系统环境**

CentOS

**问题描述**

略。

**解决方式**

将 /etc/sysconfig/network-scripts/ifctg-xxx 中如下内容修改

ONBOOT=no 修改为 ONBOOT=yes

> 备注：重启网卡或系统生效。

## CentOS 图形、多用户（命令行）模式切换

**系统环境**

​	CentOS 7.x

**问题描述**

​	CentOS 7.x 不在使用 init 托管服务，systemd 取而代之。

**解决方式**

1. 命令（多用户）模式

   systemctl set-default multi-user.target

2. 图形模式

   systemctl set-default graphical.target

## Ubuntu 图形、命令行模式切换

**系统环境**

​	Ubuntu 14.04

**问题描述**

​	略。

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

## IceGrid 应用进程权限

**系统环境**

​	CentOS 7.x/Ice 3.6.1

**问题描述**

​	IceGrid Node 节点部署的应用进程无法创建日志目录

**原因分析**

​	IceGrid Node 节点应用进程默认以 everyone 用户启动，进程需要在运行目录写日志文件，而 everyone 用户不具备该目录的写权限，导致无法创建日志目录。

**解决方式**

​	**方法 1：**将应用写日志文件的目录赋予 everyone 用户权限。

​	**方法 2：**IceGrid 机制允许修改用户进程启动默认启动的用户，详见 ICE 官方文档。

## Failed to continue: "Cannot find Delve debugger. Ensure it is in your \`GOPATH/bin\` or \`PATH\`."

**系统环境**

​	Windows 7 x64 Ultimate/VS Code v1.23.0

**问题描述**

​	略

**解决方式**

​	1. 确认已经正确设置 GOPATH 环境变量，并将  %GOPATH%\bin 追加到 PATH 环境变量

​	2. 打开 Git Bash，运行 go get github.com/derekparker/delve/cmd/dlv

## [Django] Signal only works in main thread

**系统环境**

​	CentOS 7.x/Python 2.7.x/django 1.11.7

**问题描述**

​	运行报错

**解决方式**

​	运行时加入追加如下参数 --nothreading --noreload

## Django memory leak with gunicorn

**系统环境**

​	CentOS 7.x/Python 2.7.x/django 1.11.7

**问题描述**

​	Django 项目运行时内存泄漏，正常情况下，应当找出内存泄漏的地方并且修复，但是如果是引入的第三方库引入的（或者团队的其他成员的代码引入），无法迅速地正面解决（find it and fix it）

**解决方式**

​	运行时添加如下参数 --max-requests 1000，该参数指定当工作线程（gunicorn workers）在处理完 1000 个请求时，主进程将其杀掉并释放这些工作线程占用（存在内存泄漏）的内存，然后重新分配新的工作线程。

> 实际上，主进程杀掉并重新拉起新的子进程时，不会影响对客户端的请求的处理。例如，nginx 代理 Django 后端服务，客户端的请求不会受到影响。

## Python MySQL 结果集返回字典格式

**系统环境**

 	CentOS 7.x/Python 2.7.4

**问题描述**

​	Python 的 MySQLdb 模块访问 MySQL 的一个模块，默认查询结果是 tuple 类型，使用只能根据字段的位置作为下标去访问，使用不方便且容易出错

**解决方式**

​	初始化 MySQL 连接时，显示指定结果集为字典类型 cursorclass=MySQLdb.cursors.DictCursor，如下所示

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

## Python module not found error 可能原因

**系统环境**

 	CentOS 7.x/Python 2.7.4

**问题描述**

​	导入 Python 模块，提示找不到模块

**解决方式**

 1. 如果引用的模块包含多级目录，需要在每一级目录添加一个  `__init__.py` 文件（内容为空即可）

 2. 子目录中的文件引用父目录的模块，可将父目录的路径添加进来，举例如下

    ```python
    sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
    ```

## str(c.version) for c in all_candidates SyntaxError: invalid syntax

**系统环境**

 	CentOS 6.x/Python 2.6.6

**问题描述**

​	执行 pip install --upgrade pip 报错，如上所示

**解决方式**

​	python 版本过低，安装 python 2.7.x 或以上版本

## [Ubuntu] libssl-dev : Depends: libssl1.0.0 (= 1.0.1f-1ubuntu2) but 1.0.1f-1ubuntu2.19 is to be installed

> **类似问题：**software-properties-common : Depends: python3-software-properties (= 0.92.37.8) but it is not going to be installed

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	执行 `apt-get install libssl-dev` 安装 libssl-dev 出错，具体信息如下所示

```bash
The following packages have unmet dependencies:
 software-properties-common : Depends: python3-software-properties (= 0.92.37.8) but it is not going to be installed
E: Unable to correct problems, you have held broken packages.
```

**解决方式**

```basic
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

​	执行 shell 脚本，报错 [: 1: unexpected operator

**原因分析**

​	Ubuntu shell 下默认的脚本解析器是 dash，会使一些 bash 脚本执行失败。

**解决方式**

​	通过如下方式改回 bash:
	sudo dpkg-reconfigure dash
	选择 NO

## [Ubuntu] lua.c:80:31: fatal error: readline/readline.h: No such file or directory

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	源码编译 lua 5.3 时，报错 lua.c:80:31: fatal error: readline/readline.h: No such file or directory

**原因分析**

​	缺少 libreadline-dev 依赖包

**解决方式**

​	执行  apt-get install libreadline-dev

## [Ubuntu] ssh root 登陆 Permission denied

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	安装 ssh 服务之后，root 账户无法 ssh 登陆，提示权限不足

**解决方式**

1. 修改 /etc/ssh/sshd_config

```bash
#PermitRootLogin without-password                                                               PermitRootLogin yes
```

2. 重启服务生效

```bash
service ssh restart
```

## [Ubuntu] 重置 root 密码

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	忘记 root 登陆密码

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

​	Ubuntu 系统自带 protobuf，项目中使用高版本 protobuf（由源码编译），与系统自带的产生冲突，导致项目编译、链接失败

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

​	Ubuntu 源码编译 protobuf，执行 ./configure 配置时检查出错，原因是缺少必要的 C++ 库

**解决方式**

```bash
apt-get install build-essential g++ -y
```

> 如果是 CentOS，运行如下命令即可
>
> ```bash
> yum install glibc-headers gcc-c++ -y
> ```

## [Ubuntu] Package libdb4.8++-dev is not available, but is referred to by another package.

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	Ubuntu 无法安装 libdb4.8++-dev

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

​	运行 go get 下载出错，错误信息如上，提示未设置 GOPATH 环境变量

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

​	运行 go get 下载出错，提示 i/o 超时

```basic
Fetching <https://golang.org/x/net/html?go-get=1> https fetch failed: Get <https://golang.org/x/net/html?go-get=1>: dial tcp 216.239.37.1:443: i/o timeout package golang.org/x/net/html: unrecognized import path "golang.org/x/net/html" (https fetch: Get <https://golang.org/x/net/html?go-get=1>: dial tcp 216.239.37.1:443: i/o timeout)
```

**原因分析**

​	因为 the fucking gfw，导致无法直接通过 go get 下载，需要 git clone 对应仓库到本地并放到对应的目录，即，完成 go get 做的工作。缺少其他包，可采用同样的方式解决。

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

​	安装 golang 之后，在系统变量设置 GOPATH=D:\go，但是未生效

```basic
$ echo $GOPATH
C:\Users\Administrator\go
```

**原因分析**

​	安装 golang 之后，默认给用户变量添加 GOPATH=%USERPROFILE%\go，导致覆盖了系统变量 GOPATH，如下所示：

![](pic/golang/gopath.png)

**解决方式**

​	删除用户变量 GOPATH 即可（当然，删除系统变量，然后修改用户变量 GOPATH 为目标目录也可）

## [geth] unexpected directory layout

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	源码编译以太坊，运行 go install ./cmd/geth 报错，详细错误如下

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

​	安装缺失的库

```bash
go get -u -v github.com/elastic/gosigar
```

## [geth] Block sealing failed err="waiting for transactions"

> **参考资料：**https://github.com/ethereum/go-ethereum/issues/15646

**系统环境**

 	Ubuntu 14.04/geth 1.8.13

**问题描述**

​	以太坊以开发者模式运行，启动挖矿时报错，如下所示：

```bash
> miner.start()
INFO [07-24|20:13:55.983] Transaction pool price threshold updated price=1
INFO [07-24|20:13:55.983] Starting mining operation 
null
> INFO [07-24|20:13:55.983] Commit new mining work                   number=1 txs=0 uncles=0 elapsed=148.484µs
WARN [07-24|20:13:55.984] Block sealing failed                     err="waiting for transactions"
```

**解决方式**

​	开发者模式运行，当有交易时节点才启动挖矿，因此，创建一个交易即可触发节点的挖矿。

## [geth] Please enable network time synchronisation in system settings

**系统环境**

 	Ubuntu 14.04/geth 1.8.13

**问题描述**

​	以太坊 Testnet 运行 `./geth --datadir="./testnet" --testnet console`，错误信息如上所示

**原因分析**

​	节点所在机器时间未同步

**解决方式**

> 参考资料：https://github.com/ethereum/go-ethereum/issues/14717

​	同步节点所在机器时间，参考方式如下

```bash
sudo apt-get update
sudo apt-get install ntp
sudo service ntp start
```

## [NPM] sh: 1: node: not found npm WARN This failure might be due to the use of legacy binary 

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	npm install 安装包的时候报错，如上所示。

**原因分析**

​	新版本的 nodejs，已经将原来 /usr/bin/node 改成 /usr/bin/nodejs，所以报如上错误。 

**解决方式**

```bash
apt-get install nodejs-legacy
```

## [NPM] npm WARN enoent ENOENT: no such file or directory

**系统环境**

 	Ubuntu 14.04

**问题描述**

​	npm install 安装包的时候报错，npm WARN enoent ENOENT: no such file or directory, open '\<root>/node_modules/supertest/package.json'

**解决方式**

​	运行 npm init 进行初始化即可

## [web3.js] Error: Error: Method eth_compileSolidity not supported.

**系统环境**

 	Ubuntu 14.04/Solc 0.20.1/node 8.11.3/npm 5.6.0

**问题描述**

​	调用 web3.js 编译合约接口时，报错，对应代码如下所示：

```javascript
let calc = web3.eth.compile.solidity(source);
```

**原因分析**

> the developers decided that making a node compile a contract like this to be out of scope. So this functionality has been [deprecated](https://github.com/ethereum/EIPs/issues/209). There were many reasons behind this, but the main ones are that RPC calls are beyond the responsibilities of the eth API, and node compilation like this is not sufficient. You can use an on-line compiler like Remix, or a compiler like solc to get the bytecode and go from there. 

​	新版本 web3.js 废弃了该接口

**解决方式**

​	利用 Solc 提前编译好合约，js 代码中不依赖该接口即可

## [web3.js] 监听合约事件失败

**系统环境**

 	Ubuntu 14.04/Solc 0.20.1/node 8.11.3/npm 5.6.0

**问题描述**

​	监听合约事件，但是无法捕获事件，代码如下所示

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

​	由于事件监听属于回调，执行合约交易之后，立即调用 process.exit(0) 退出程序，导致监听合约事件失败。

**解决方式**

​	去掉 process.exit(0) 即可，如下所示

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

