[TOC]

------

##  Git 客户端基本配置项

```bash
# 执行方式：命令行执行即可
# 提交/检出 不转换
git config --global core.autocrlf false
# 拒绝提交包含混合换行符的文件
git config --global core.safecrlf true
git config --global core.autocrlf false
git config --global core.safecrlf true
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.ct commit
git config --global alias.df diff
git config --global alias.br branch
git config --global color.ui true
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset %C(bold blue)<%an>%Creset ---%C(yellow)%d%Creset %s %Cgreen(%cr)' --abbrev-commit"
# 指定 vim 作为默认的编辑器
git config core.editor vim --global
git config --global user.name xx
git config --global user.email xx@xxx.cn
```

## VIM 基础配置

> VIM 配置文件位置：~/.vimrc

```bash
set incsearch
set number
set hlsearch
set ignorecase
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
set fileencodings=utf-8,gbk
set relativenumber " show relative line number
set ruler          " show the current line number and column number
set showcmd        " show the current typing command
set scrolloff=7    " Set 7 lines to the cursor - when moving vertically using j/k
set encoding=utf-8
set fileencodings=utf-8,ucs-bom,cp936,gb18030,big5,euc-jp,euc-kr,latin1
set helplang=en
set termencoding=utf-8
set laststatus=2
set cursorline

set guifont=Courier_New:h14:cANSI
set history=2222
set selection=exclusive
set selectmode=mouse,key
set fillchars=vert:\ ,stl:\ ,stlnc:\
set showmatch
set matchtime=1
set linebreak
set colorcolumn=80
set wrap
set tw=80

let mapleader = "\<Space>"
nmap <Leader><Leader> V
nnoremap <Leader>w :wq!<CR> "save file"
nmap <leader><Space><Space> :%s/\s\+$//<CR> "连续三个空格去掉行末空白（包括tab/space）"
```



## 基于 vsftpd 的 ftp 服务器

### 授权用户访问模式
```bash
0. 运行环境：Cent OS 6.8/vsftpd 2.2.2

1. 安装配置vsftpd
yum install vsftpd ftp -y
chkconfig vsftpd on

2. 添加用户
> useradd -d /home/ftp -g ftp -s /sbin/nologin XXXftp -p XXX123!
> passwd XXXftp

3. 修改配置 /etc/vsftpd/vsftpd.conf
anonymous_enable=NO
local_enable=YES
write_enable=YES
local_umask=022
dirmessage_enable=YES
xferlog_enable=YES
connect_from_port_20=YES
xferlog_std_format=YES
ftpd_banner=Welcome to FTP service.
listen=YES

pam_service_name=vsftpd
userlist_enable=YES
userlist_deny=NO
tcp_wrappers=YES
download_enable=YES
# 限速 500KByte
local_max_rate=500000

4. 修改配置文件 /etc/vsftpd/user_list
# vsftpd userlist
# If userlist_deny=NO, only allow users in this file
# If userlist_deny=YES (default), never allow users in this file, and
# do not even prompt for a password.
# Note that the default vsftpd pam config also checks /etc/vsftpd/ftpusers
# for users that are denied.
#root
#bin
#daemon
#adm
#lp
#sync
#shutdown
#halt
#mail
#news
#uucp
#operator
#games
#nobody
XXXftp

5. 防火墙开放 21 端口
6. 启动服务 service vsftpd start
7. 验证
> ftp ftp.xxx.cn
Connected to ftp.xxx.cn (xxx.xxx.xxx.xxx).
220 (vsFTPd 2.2.2)
Name (ftp.xxx.cn:kevin): XXXftp
331 Please specify the password.
Password:
230 Login successful.
Remote system type is UNIX.
Using binary mode to transfer files.
```
### 匿名用户访问模式
```bash
0. 运行环境：Cent OS 6.8/vsftpd 2.2.2

1. 安装配置vsftpd
yum install vsftpd ftp -y
chkconfig vsftpd on

2. 修改配置文件
anonymous_enable=YES
local_enable=YES
local_umask=022
write_enable=YES
dirmessage_enable=YES
xferlog_enable=YES
chown_uploads=NO
xferlog_std_format=YES
chroot_local_user=NO
listen=YES

userlist_enable=YES
anon_umask=022
anon_upload_enable=YES
anon_mkdir_write_enable=YES
anon_other_write_enable=YES

pam_service_name=vsftpd

connect_from_port_20=YES
tcp_wrappers=YES

pasv_enable=YES
pasv_min_port=30000
pasv_max_port=31000

3. 开启防火墙 /etc/sysconfig/iptables
-A INPUT -p tcp -m multiport --dport 20,21  -m state --state NEW -j ACCEPT
-A INPUT -p tcp -m state --state NEW -m tcp --dport 21 -j ACCEPT
-A INPUT -p tcp --dport 30000:31000 -j ACCEPT
```

## 安装配置 Apache Tomcat 9，支持 http2
```bash
#!/bin/sh

PWD=`pwd`
ROOT=$PWD

echo "install gcc"
yum install gcc -y

echo "install expect"
yum install expect -y

echo "yum install curl"
yum install curl -y

echo "install jdk"
tar -zxvf jdk-8u111-linux-x64.tar.gz
mv jdk1.8.0_111/ /usr/local

cat >> /etc/profile << EOF
#add jdk related environment variables
JAVA_HOME=/usr/local/jdk1.8.0_111
CLASSPATH=.:\$JAVA_HOME/jre/lib/rt.jar:\$JAVA_HOME/lib/dt.jar:\$JAVA_HOME/lib/tools.jar
JRE_HOME=\$JAVA_HOME/jre

export JAVA_HOME=\$JAVA_HOME
export CLASSPATH=\$CLASSPATH
export JRE_HOME=\$JRE_HOME
export PATH=\$PATH:\$JAVA_HOME/bin
EOF

echo "set env temporary"
JAVA_HOME=/usr/local/jdk1.8.0_111
CLASSPATH=.:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
JRE_HOME=$JAVA_HOME/jre
export JAVA_HOME=$JAVA_HOME
export CLASSPATH=$CLASSPATH
export JRE_HOME=$JRE_HOME
export PATH=$PATH:$JAVA_HOME/bin

echo "install apr"
tar -xzvf apr-1.5.2.tar.gz
cd apr-1.5.2
./configure --prefix=/usr/local/apr
make -j4
make install
cd -
rm -rf apr-1.5.2

echo "install apr-util"
tar -xzvf apr-util-1.5.4.tar.gz
cd apr-util-1.5.4
./configure --prefix=/usr/local/apr-util --with-apr=/usr/local/apr
make -j4
make install
cd -
rm -rf apr-util-1.5.4

echo "install openssl"
tar -xzvf openssl-1.0.2h.tar.gz
cd openssl-1.0.2h
./config shared --prefix=/usr/local/openssl
make depend
make -j4
make install
cd -
rm -rf openssl-1.0.2h

echo "install apache tomcat"
tar -xzvf apache-tomcat-9.0.0.M17.tar.gz
mv apache-tomcat-9.0.0.M17 /usr/local
cd /usr/local/apache-tomcat-9.0.0.M17/bin
tar -xzvf tomcat-native.tar.gz
cd tomcat-native-1.2.10-src/native
./configure --prefix=/usr/local/native --with-apr=/usr/local/apr --with-ssl=/usr/local/openssl
make -j4
make install

cat >> /etc/profile << EOF
#add native related environment variables
NATIVE_HOME=/usr/local/native

export NATIVE_HOME=\$NATIVE_HOME
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$NATIVE_HOME/lib
EOF

NATIVE_HOME=/usr/local/native
export NATIVE_HOME=$NATIVE_HOME
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$NATIVE_HOME/lib

echo "gen cert related"
mkdir $ROOT/cert
cd $ROOT/cert
openssl genrsa -out server.key 2048
openssl rsa -in server.key -out server.key

cat > gen_cert.sh << EOF
#!/usr/bin/expect -f

set timeout 30

spawn openssl req -new -x509 -key server.key -out ca.crt -days 3650
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
        send "xxx.com\r";
        exp_continue
    }

    "Organizational Unit Name (eg, section)" {
        send "Dev\r";
        exp_continue
    }

    "Common Name (eg, your name or your server's hostname)" {
        send "stream service\r";
        exp_continue
    }

    "Email Address" {
        send "dev@xxx.com\r";
        exp_continue
    }
}
EOF

chmod +x gen_cert.sh
./gen_cert.sh
cd $ROOT
cp -r $ROOT/cert/* /usr/local/apache-tomcat-9.0.0.M17/conf
rm -rf $ROOT/cert

echo "modify tomcat conf"
cat > /usr/local/apache-tomcat-9.0.0.M17/conf/server.xml << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!--
  Licensed to the Apache Software Foundation (ASF) under one or more
  contributor license agreements.  See the NOTICE file distributed with
  this work for additional information regarding copyright ownership.
  The ASF licenses this file to You under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with
  the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
-->
<!-- Note:  A "Server" is not itself a "Container", so you may not
     define subcomponents such as "Valves" at this level.
     Documentation at /docs/config/server.html
 -->
<Server port="8005" shutdown="SHUTDOWN">
  <Listener className="org.apache.catalina.startup.VersionLoggerListener" />
  <!-- Security listener. Documentation at /docs/config/listeners.html
  <Listener className="org.apache.catalina.security.SecurityListener" />
  -->
  <!--APR library loader. Documentation at /docs/apr.html -->
  <Listener className="org.apache.catalina.core.AprLifecycleListener" SSLEngine="on" />
  <!-- Prevent memory leaks due to use of particular java/javax APIs-->
  <Listener className="org.apache.catalina.core.JreMemoryLeakPreventionListener" />
  <Listener className="org.apache.catalina.mbeans.GlobalResourcesLifecycleListener" />
  <Listener className="org.apache.catalina.core.ThreadLocalLeakPreventionListener" />

  <!-- Global JNDI resources
       Documentation at /docs/jndi-resources-howto.html
  -->
  <GlobalNamingResources>
    <!-- Editable user database that can also be used by
         UserDatabaseRealm to authenticate users
    -->
    <Resource name="UserDatabase" auth="Container"
              type="org.apache.catalina.UserDatabase"
              description="User database that can be updated and saved"
              factory="org.apache.catalina.users.MemoryUserDatabaseFactory"
              pathname="conf/tomcat-users.xml" />
  </GlobalNamingResources>

  <!-- A "Service" is a collection of one or more "Connectors" that share
       a single "Container" Note:  A "Service" is not itself a "Container",
       so you may not define subcomponents such as "Valves" at this level.
       Documentation at /docs/config/service.html
   -->
  <Service name="Catalina">

    <!--The connectors can use a shared executor, you can define one or more named thread pools-->
    <!--
    <Executor name="tomcatThreadPool" namePrefix="catalina-exec-"
        maxThreads="150" minSpareThreads="4"/>
    -->


    <!-- A "Connector" represents an endpoint by which requests are received
         and responses are returned. Documentation at :
         Java HTTP Connector: /docs/config/http.html
         Java AJP  Connector: /docs/config/ajp.html
         APR (HTTP/AJP) Connector: /docs/apr.html
         Define a non-SSL/TLS HTTP/1.1 Connector on port 8080
    -->
    <Connector port="8080" protocol="HTTP/1.1"
               connectionTimeout="20000"
               redirectPort="8443" />
    <!-- A "Connector" using the shared thread pool-->
    <!--
    <Connector executor="tomcatThreadPool"
               port="8080" protocol="HTTP/1.1"
               connectionTimeout="20000"
               redirectPort="8443" />
    -->
    <!-- Define a SSL/TLS HTTP/1.1 Connector on port 8443
         This connector uses the NIO implementation. The default
         SSLImplementation will depend on the presence of the APR/native
         library and the useOpenSSL attribute of the
         AprLifecycleListener.
         Either JSSE or OpenSSL style configuration may be used regardless of
         the SSLImplementation selected. JSSE style configuration is used below.
    -->
    <!--
    <Connector port="8443" protocol="org.apache.coyote.http11.Http11NioProtocol"
               maxThreads="150" SSLEnabled="true">
        <SSLHostConfig>
            <Certificate certificateKeystoreFile="conf/localhost-rsa.jks"
                         type="RSA" />
        </SSLHostConfig>
    </Connector>
    -->
    <!-- Define a SSL/TLS HTTP/1.1 Connector on port 8443 with HTTP/2
         This connector uses the APR/native implementation which always uses
         OpenSSL for TLS.
         Either JSSE or OpenSSL style configuration may be used. OpenSSL style
         configuration is used below.
    -->
    <!--
    <Connector port="8443" protocol="org.apache.coyote.http11.Http11AprProtocol"
               maxThreads="150" SSLEnabled="true" >
        <UpgradeProtocol className="org.apache.coyote.http2.Http2Protocol" />
        <SSLHostConfig>
            <Certificate certificateKeyFile="conf/localhost-rsa-key.pem"
                         certificateFile="conf/localhost-rsa-cert.pem"
                         certificateChainFile="conf/localhost-rsa-chain.pem"
                         type="RSA" />
        </SSLHostConfig>
    </Connector>
    -->

    <Connector port="8443" protocol="org.apache.coyote.http11.Http11AprProtocol"
               maxThreads="150" SSLEnabled="true" >
        <UpgradeProtocol className="org.apache.coyote.http2.Http2Protocol" />
        <SSLHostConfig>
            <Certificate certificateKeyFile="conf/server.key"
                certificateFile="conf/ca.crt"
                         type="RSA" />
        </SSLHostConfig>
    </Connector>

    <!-- Define an AJP 1.3 Connector on port 8009 -->
    <Connector port="8009" protocol="AJP/1.3" redirectPort="8443" />


    <!-- An Engine represents the entry point (within Catalina) that processes
         every request.  The Engine implementation for Tomcat stand alone
         analyzes the HTTP headers included with the request, and passes them
         on to the appropriate Host (virtual host).
         Documentation at /docs/config/engine.html -->

    <!-- You should set jvmRoute to support load-balancing via AJP ie :
    <Engine name="Catalina" defaultHost="localhost" jvmRoute="jvm1">
    -->
    <Engine name="Catalina" defaultHost="localhost">

      <!--For clustering, please take a look at documentation at:
          /docs/cluster-howto.html  (simple how to)
          /docs/config/cluster.html (reference documentation) -->
      <!--
      <Cluster className="org.apache.catalina.ha.tcp.SimpleTcpCluster"/>
      -->

      <!-- Use the LockOutRealm to prevent attempts to guess user passwords
           via a brute-force attack -->
      <Realm className="org.apache.catalina.realm.LockOutRealm">
        <!-- This Realm uses the UserDatabase configured in the global JNDI
             resources under the key "UserDatabase".  Any edits
             that are performed against this UserDatabase are immediately
             available for use by the Realm.  -->
        <Realm className="org.apache.catalina.realm.UserDatabaseRealm"
               resourceName="UserDatabase"/>
      </Realm>

      <Host name="localhost"  appBase="webapps"
            unpackWARs="true" autoDeploy="true">

        <!-- SingleSignOn valve, share authentication between web applications
             Documentation at: /docs/config/valve.html -->
        <!--
        <Valve className="org.apache.catalina.authenticator.SingleSignOn" />
        -->

        <!-- Access log processes all example.
             Documentation at: /docs/config/valve.html
             Note: The pattern used is equivalent to using pattern="common" -->
        <Valve className="org.apache.catalina.valves.AccessLogValve" directory="logs"
               prefix="localhost_access_log" suffix=".txt"
               pattern="%h %l %u %t &quot;%r&quot; %s %b" />

      </Host>
    </Engine>
  </Service>
</Server>
EOF

echo "start tomcat"
cd /usr/local/apache-tomcat-9.0.0.M17/bin
./startup.sh

sleep 5

echo "test tomcat"
curl -k -I https://localhost:8443

echo "stop tomcat"
cd /usr/local/apache-tomcat-9.0.0.M17/bin
./shutdown.sh

echo ""
echo "ATTENTION: RUN 'source /etc/profile'"
echo ""
```

## CentOS 配置 VNC

1. 安装软件包

   yum install tigervnc* -y

2. 修改 /root/.vnc/xstartup 文件，包括注释、新增，如下所示

   \# xterm -geometry 80x24+10+10 -ls -title "VNCDESKTOP Desktop" &

   \# twm &

   gnome-session &

3. 修改 /etc/sysconfig/vncservers，修改如下行

   VNCSERVERARGS[1]="-geometry 1360x768"

4. 配置防火墙，允许默认端口 5901（或者，关闭防火墙）

5. 启动服务

   service vncserver start

6. 安装客户端，并连接

   客户端连接服务器信息 VNC Server: xxx.xxx.xxx.xxx:5901

   > xxx.xxx.xxx.xxx 为 VNC Server 的 IP 地址

7. 其他命令

   - vncpasswd *修改 VNC 连接密码*
   - vncserver --list *查看启动的会话实例（session）*
   - vncserver :2 *启动第二个实例*，默认监听 5902 端口，具体可通过 netstat 命令查看
   - vncserver -kill :2 *停止第二个实例*

## Makefile 模板

```bash
INCLUDES := -I. -I./include -I/opt/Ice-3.5.1/include
LIBS := -Wl,--enable-new-dtags -Wl,-rpath,/opt/Ice-3.5/lib64
LIBS += -Wl,-Bstatic  -L./lib -lcpp_redis -ltacopie
LIBS += -Wl,-Bdynamic -L/opt/Ice-3.5.1/lib64 -lIce -lIceUtil

CXX := g++ -std=c++11
CXXFLAGS := -rdynamic -m64 -Wall -Wextra -pthread -fPIC -g $(INCLUDES)
# 把所有警告当做错误：-Werror，支持 C++ 11：-std=c++11
#CXXFLAGS +=  -Werror -std=c++11

TARGETS := server
TARGETS += client

all: $(TARGETS)

db.cpp db.h: db.ice
	slice2cpp $^

server: db.o dbi.o server.o
	$(CXX) -o $@ $^ $(LIBS)

client: db.o dbi.o client.o
	$(CXX) -o $@ $^ $(LIBS)

clean:
	rm -f *.o $(TARGETS)
```

## CentOS 安装 Python 3.5

```bash
1. CentOS 6.5 安装 Python 的依赖包

yum groupinstall "Development tools"
yum install zlib-devel bzip2-devel openssl-devel ncurses-devel sqlite-devel readline-devel tk-devel gdbm-devel db4-devel libpcap-devel xz-devel

2. 下载 Python3.5 的源码包并编译

wget https://www.python.org/ftp/python/3.5.0/Python-3.5.0.tgz
tar xf Python-3.5.0.tgz
cd Python-3.5.0
./configure --prefix=/usr/local --enable-shared
make
make install
ln –s /usr/local/bin/python3 /usr/bin/python3

3. 在运行 Python 之前需要配置库

echo /usr/local/lib >> /etc/ld.so.conf.d/local.conf
ldconfig

4. 运行演示
python3 --version
Python 3.5.0

5. 删除编译 Python 时所需要的库（可不删除）
yum groupremove "Development tools" --remove-leaveas
yum remove zlib-devel bzip2-devel openssl-devel ncurses-devel sqlite-devel readline-devel tk-devel gdbm-devel db4-devel libpcap-devel xz-devel --remove-leaves

6. 设置别名方便使用
alias py=python3
```

## CentOS 安装 ICE

```bash
1.下载 Ice 源码
cd /opt
wget http://www.zeroc.com/download/Ice/3.5/Ice-3.5.1.tar.gz
wget http://www.zeroc.com/download/Ice/3.5/ThirdParty-Sources-3.5.1.tar.gz

2. 安装依赖库
yum -y install gcc gcc-c++ expat-devel bzip2 bzip2-devel
yum -y install openssl*

2.1 安装第三方资源
tar xvf ThirdParty-Sources-3.5.1.tar.gz
cd ThirdParty-Sources-3.5.1
tar xvf mcpp-2.7.2.tar.gz
cd mcpp-2.7.2
patch -p0 < ../mcpp/patch.mcpp.2.7.2
./configure CFLAGS=-fPIC --enable-mcpplib --disable-shared
make && make install
cd ../

2.2 安装 BerkeleyDB
tar zxf db-5.3.21.NC.tar.gz
cd db-5.3.21.NC
patch -p0 < ../db/patch.db.5.3.21
cd build_unix
../dist/configure --prefix=/usr --enable-cxx
make && make install

（说明：db 的默认安装 prefix 路径是：/usr/local/BerkeleyDB.5.3，需要改为 /usr，否则 make Ice 时会找不到路径）

3. 安装 ICE
cd /opt
tar xvf Ice-3.5.1.tar.gz
cd Ice-3.5.1/cpp
make && make install

4. 环境变量设置（vim /etc/profile）
#add ice install dir to path for all users
ICE_HOME=/opt/Ice-3.5.1

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ICE_HOME/lib:$ICE_HOME/lib64
export PATH=$PATH:$ICE_HOME/bin
```

## CentOS 安装 GCC 4.9.2

> 注意：GCC 4.8.1 支持 C++11 全部特性

```bash
1. 下载 GCC 的源码包 gcc-4.9.2.tar.gz，以及三个依赖的安装包，依赖包的版本及其下载地址在 GCC 源码包目录 gcc-4.9.2/contrib/download_prerequisites 脚本文件中有指明。
	ftp://ftp.gnu.org/gnu/gmp/gmp-4.3.2.tar.bz2
	http://www.mpfr.org/mpfr-2.4.2/mpfr-2.4.2.tar.bz2
	http://www.multiprecision.org/mpc/download/mpc-0.8.1.tar.gz
	
	备用下载地址：http://ftp.vim.org/languages/gcc/infrastructure/

2. 编译、安装依赖包
2.1 安装 gmp-4.3.2
	cd gmp-4.3.2
	mkdir build && cd build
	../configure --prefix=/usr/local/gmp-4.3.2
	make -j4
	make install

2.2 安装 mpfr
	cd mpfr-2.4.2
	mkdir build && cd build
	../configure --prefix=/usr/local/mpfr-2.4.2 --with-gmp=/usr/local/gmp-4.3.2
	make -j4
	make install

2.3 安装 mpc
	cd mpc-0.8.1
	mkdir build && cd build
	../configure --prefix=/usr/local/mpc-0.8.1 --with-gmp=/usr/local/gmp-4.3.2 --with-mpfr=/usr/local/mpfr-2.4.2
	make -j4
	make install

2.4 在 /etc/profile 添加环境变量
	GCC_RELATED_LIBS=/usr/local/gmp-4.3.2/lib:/usr/local/mpfr-2.4.2/lib:/usr/local/mpc-0.8.1/lib
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GCC_RELATED_LIBS

3. 安装 GCC
	cd gcc-4.9.2
	mkdir build && cd build
	../configure --prefix=/usr/local/gcc-4.9.2 --enable-threads=posix --disable-checking --disable-multilib --enable-languages=c,c++ --with-gmp=/usr/local/gmp-4.3.2 --with-mpfr=/usr/local/mpfr-2.4.2 --with-mpc=/usr/local/mpc-0.8.1
	make -j4
	make install
```

## zookeeper/kafka 安装配置

```bash
zookeeper-3.4.6 安装配置
0. 设置机器名
    hostname XXX

1. 修改 /etc/hosts
    192.168.2.2 master
    192.168.2.3 node1
    192.168.2.4 node2

2. 做 三台主机 master/node1/node2 之间的机器互信
    2.1    每台机器执行 ssh-keygen -t rsa -P ''  #产生密钥对
    2.2    将2.1中三个公钥写入authorized_keys #~/.ssh/id_rsa.pub >> authorized_keys
    2.3    将2.2中authorized_keys拷贝到每台机器~/.ssh

3. 下载 zookeeper-3.4.6
    wget http://mirrors.hust.edu.cn/apache/zookeeper/zookeeper-3.4.6/zookeeper-3.4.6.tar.gz 

4. 解压，添加环境变量 /etc/profile
    export ZOOKEEPER_HOME=/app/zookeeper-3.4.6
    export PATH=$PATH:$ZOOKEEPER_HOME

5. 配置/app/zookeeper-3.4.6/zoo.cfg
# The number of milliseconds of each tick
tickTime=2000
# The number of ticks that the initial 
# synchronization phase can take
initLimit=10
# The number of ticks that can pass between 
# sending a request and getting an acknowledgement
syncLimit=5
# the directory where the snapshot is stored.
# do not use /tmp for storage, /tmp here is just 
# example sakes.
dataDir=/app/zookeeper-3.4.6/snapshot
dataLogDir=/app/zookeeper-3.4.6/log
# the port at which the clients will connect
clientPort=2181
# the maximum number of client connections.
# increase this if you need to handle more clients
#maxClientCnxns=60
#
# Be sure to read the maintenance section of the 
# administrator guide before turning on autopurge.
#
# http://zookeeper.apache.org/doc/current/zookeeperAdmin.html#sc_maintenance
#
# The number of snapshots to retain in dataDir
#autopurge.snapRetainCount=3
# Purge task interval in hours
# Set to "0" to disable auto purge feature
#autopurge.purgeInterval=1
server.1=master:2888:3888
server.2=node1:2888:3888
server.3=node2:2888:3888
   
6. 配置 /app/zookeeper-3.4.6/snapshot/myid
（备注：创建myid：在zoo.cfg配置文件中的 dataDir 的目录下面创建 myid，每个节点myid要求不一样）
master：echo 1 > /app/zookeeper-3.4.6/snapshot/myid
node1:  echo 2> /app/zookeeper-3.4.6/snapshot/myid
node2:  echo 3 > /app/zookeeper-3.4.6/snapshot/myid

7. 启动 ./bin/zkServer.sh start
JMX enabled by default
Using config: /app/zookeeper-3.4.6/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED

8. 查看 zookeeper 节点状态
[root@localhost bin]# ./zkServer.sh status
JMX enabled by default
Using config: /app/zookeeper-3.4.6/bin/../conf/zoo.cfg
Mode: leader

kafka 安装配置

1. 下载 wget http://mirrors.cnnic.cn/apache/kafka/0.10.0.0/kafka_2.11-0.10.0.0.tgz

2. 配置config/server.properties
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# see kafka.server.KafkaConfig for additional details and defaults

############################# Server Basics #############################

# The id of the broker. This must be set to a unique integer for each broker.
broker.id=0

############################# Socket Server Settings #############################

# The address the socket server listens on. It will get the value returned from 
# java.net.InetAddress.getCanonicalHostName() if not configured.
#   FORMAT:
#     listeners = security_protocol://host_name:port
#   EXAMPLE:
#     listeners = PLAINTEXT://your.host.name:9092
listeners=PLAINTEXT://master:9092

# Hostname and port the broker will advertise to producers and consumers. If not set, 
# it uses the value for "listeners" if configured.  Otherwise, it will use the value
# returned from java.net.InetAddress.getCanonicalHostName().
#advertised.listeners=PLAINTEXT://your.host.name:9092

# The number of threads handling network requests
num.network.threads=3

# The number of threads doing disk I/O
num.io.threads=8

# The send buffer (SO_SNDBUF) used by the socket server
socket.send.buffer.bytes=102400

# The receive buffer (SO_RCVBUF) used by the socket server
socket.receive.buffer.bytes=102400

# The maximum size of a request that the socket server will accept (protection against OOM)
socket.request.max.bytes=104857600


############################# Log Basics #############################

# A comma seperated list of directories under which to store log files
log.dirs=/app/kafka_2.11-0.10.0.0/kafka-logs

# The default number of log partitions per topic. More partitions allow greater
# parallelism for consumption, but this will also result in more files across
# the brokers.
num.partitions=1

# The number of threads per data directory to be used for log recovery at startup and flushing at shutdown.
# This value is recommended to be increased for installations with data dirs located in RAID array.
num.recovery.threads.per.data.dir=1

############################# Log Flush Policy #############################

# Messages are immediately written to the filesystem but by default we only fsync() to sync
# the OS cache lazily. The following configurations control the flush of data to disk.
# There are a few important trade-offs here:
#    1. Durability: Unflushed data may be lost if you are not using replication.
#    2. Latency: Very large flush intervals may lead to latency spikes when the flush does occur as there will be a lot of data to flush.
#    3. Throughput: The flush is generally the most expensive operation, and a small flush interval may lead to exceessive seeks.
# The settings below allow one to configure the flush policy to flush data after a period of time or
# every N messages (or both). This can be done globally and overridden on a per-topic basis.

# The number of messages to accept before forcing a flush of data to disk
#log.flush.interval.messages=10000

# The maximum amount of time a message can sit in a log before we force a flush
#log.flush.interval.ms=1000

############################# Log Retention Policy #############################

# The following configurations control the disposal of log segments. The policy can
# be set to delete segments after a period of time, or after a given size has accumulated.
# A segment will be deleted whenever *either* of these criteria are met. Deletion always happens
# from the end of the log.

# The minimum age of a log file to be eligible for deletion
log.retention.hours=168

# A size-based retention policy for logs. Segments are pruned from the log as long as the remaining
# segments don't drop below log.retention.bytes.
#log.retention.bytes=1073741824

# The maximum size of a log segment file. When this size is reached a new log segment will be created.
log.segment.bytes=1073741824

# The interval at which log segments are checked to see if they can be deleted according
# to the retention policies
log.retention.check.interval.ms=300000

############################# Zookeeper #############################

# Zookeeper connection string (see zookeeper docs for details).
# This is a comma separated host:port pairs, each corresponding to a zk
# server. e.g. "127.0.0.1:3000,127.0.0.1:3001,127.0.0.1:3002".
# You can also append an optional chroot string to the urls to specify the
# root directory for all kafka znodes.
zookeeper.connect=master:2181,node1:2181,node2:2181

# Timeout in ms for connecting to zookeeper
zookeeper.connection.timeout.ms=6000

delete.topic.enable=true
auto.leader.rebalance.enable=true

3. 启动 nohup ./kafka-server-start.sh ../config/server.properties &
```

## Gerrit 使用者初始配置

> **Tips:** 公司启用 Gerrit 代码审查，作为使用者，例如开发人员，须完成初始配置之后才能使用 Gerrit。

1. 使用 CM 分配的 Gerrit 账号登陆 gerrit WEB 服务器

2. 进入设置（Setting），填写个人邮箱，点击注册邮箱（Register New Mail）

3. 登陆个人邮箱，找到 Gerrit 发送的验证邮件，点击邮件链接进行确认激活

4. 安装 Git 客户端

5. 生成 SSH 公钥（ssh-kengen -t rsa）

   **备注：**如果客户端使用的 openssl 库版本较高而服务器端版本较低，openssl 高版本禁用某些安全性较低的算法，这种情形下，需要在客户端的 .ssh 目录（即，id_rsa.pub所在目录）新建一个文件 config（Windows 下注意去掉后缀），内容如下

   ```bash
   Host 172.13.31.14
       KexAlgorithms +diffie-hellman-group1-sha1
   ```

6. 登陆 Gerrit，进入个人中心，将上一步产生的公钥 id_rsa.pub 添加到 SSH 公钥（SSH Public Keys）

## gSOAP 2.8.18 安装

1. 安装 gSOAP 2.8.18

```bash
unzip gsoap_2.8.18.zip
cd gsoap_2.8.18
./configure --prefix=/usr/local
make -j4 && make install
```

2. 添加环境变量 /etc/profile

   GSOAP=/usr/local/gsoap_2.8.18

   PATH=\$GSOAP/bin:$ATH

   export PATH

3. source /etc/profile

## Lets Encrypt 证书制作、部署

> **References:**
>
> [Lets Encrypt](https://community.letsencrypt.org/t/trying-to-renew-got-message-cert-not-yet-due-for-renewal/36303)
>
> [Nginx 与 Apache Tomcat 组合的简单使用]([Nginx与tomcat组合的简单使用](http://www.cnblogs.com/naaoveGIS/p/5478208.html))

### 基础环境

- CentOS 6.8
- Nginx 1.10.2
- Apache Tomcat 8.0.47
- 配置域名解析 api.danbay.cn xxx.xxx.xxx.xxx

### 证书制作

1. 获取 certbot 客户端

   ```bash
   wget https://dl.eff.org/certbot-auto
   chmod a+x certbot-auto
   ```

   ​

2. 生成证书

   ```bash
   /opt/certbot-auto certonly --webroot -w /usr/share/nginx/html --agree-tos --email xuchao@danbay.cn -d api.danbay.cn
   ```

   ![生成证书](pic/certbot/certbot.jpg)

3. 查看证书文件

   ```bash
   tree /etc/letsencrypt/live/
   ```

   ![证书文件](pic/certbot/cert.jpg)
### 部署

#### Nginx 同时支持 http/https

   ```bash
   server {
           listen	80;
           listen  443;

           ssl_certificate      /etc/letsencrypt/live/api.danbay.cn/fullchain.pem;
           ssl_certificate_key  /etc/letsencrypt/live/api.danbay.cn/privkey.pem;

           ssl_session_timeout 1d;
           ssl_session_cache shared:SSL:32m;
           ssl_session_tickets off;

           # modern configuration. tweak to your needs.
           ssl_protocols TLSv1.2;
           ssl_ciphers 'ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256';
           ssl_prefer_server_ciphers on;

           server_name          api.danbay.cn;
           root         		/usr/share/nginx/html;

           # Load configuration files for the default server block.
           include /etc/nginx/default.d/*.conf;

           location / {
           }

           error_page 404 /404.html;
           location = /40x.html {
           }

           error_page 500 502 503 504 /50x.html;
           location = /50x.html {
           }
   }
   ```

#### Nginx 强制启用 https

```bash
server {
        listen  80;
        listen  443;

        server_name          api.danbay.cn;
        root         		/usr/share/nginx/html;
        ssl             		on;
        error_page 497   https://$host:7443$uri; 
        #error_page 497  https://$host:7443$request_uri?$args;

        ssl_certificate      /etc/letsencrypt/live/dev3.danbay.cn/fullchain.pem;
        ssl_certificate_key  /etc/letsencrypt/live/dev3.danbay.cn/privkey.pem;

        ssl_session_timeout 1d;
        ssl_session_cache shared:SSL:32m;
        ssl_session_tickets off;

        # modern configuration. tweak to your needs.
        ssl_protocols TLSv1.2;
        ssl_ciphers 'ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256';
        ssl_prefer_server_ciphers on;

        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;

        location / {
        }

        error_page 404 /404.html;
        location = /40x.html {
        }

        error_page 500 502 503 504 /50x.html;
        location = /50x.html {
        }
}
```

#### Nginx 代理 Apache Tomcat

```bash
upstream tomcat {
        server 127.0.0.1:7080;
}

server {
        listen  80;
        listen  443;

        server_name          api.danbay.cn;
        root         		/usr/share/nginx/html;
        ssl             		on;

        #error_page 497  https://$host$uri?$args;
        error_page 497  https://$host:7443$request_uri; 

        ssl_certificate      /etc/letsencrypt/live/api.danbay.cn/fullchain.pem;
        ssl_certificate_key  /etc/letsencrypt/live/api.danbay.cn/privkey.pem;

        ssl_session_timeout 1d;
        ssl_session_cache shared:SSL:32m;
        ssl_session_tickets off;

        # modern configuration. tweak to your needs.
        ssl_protocols TLSv1.2;
        ssl_ciphers 'ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256';
        ssl_prefer_server_ciphers on;

        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;

        location / {
                proxy_pass http://tomcat;
        }

        error_page 404 /404.html;
        location = /40x.html {
        }

        error_page 500 502 503 504 /50x.html;
        location = /50x.html {
        }
}
```

### 更新证书

```bash
# 证书默认 90 有效，更新不能太频繁，同一域名一周之内最多只能更新5次
/opt/certbot-auto renew
```

