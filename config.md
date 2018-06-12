[TOC]

------

##  Git 客户端基本配置项

```bash
# 执行方式：命令行执行即可
# 提交/检出 不转换
git config --global core.autocrlf false
# 拒绝提交包含混合换行符的文件
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

## Git .gitignore

```basic
# From https://github.com/github/gitignore

# Prerequisites
*.d

# Compiled Object files
*.slo
*.lo
*.o
*.obj

# Precompiled Headers
*.gch
*.pch

# Compiled Dynamic libraries
*.so
*.dylib
*.dll

# Fortran module files
*.mod
*.smod

# Compiled Static libraries
*.lai
*.la
*.a
*.lib

# Executables
*.exe
*.out
*.app

# CMake
CMakeCache.txt
CMakeFiles
CMakeScripts
Testing
Makefile
cmake_install.cmake
install_manifest.txt
compile_commands.json
CTestTestfile.cmake

# Config
*.conf

# Log
log/
*.log

# Generated binary file/directory
debug/
release/
bin/
debug
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
set history=161202
set selection=exclusive
set selectmode=mouse,key
set fillchars=vert:\ ,stl:\ ,stlnc:\
set showmatch
set matchtime=1
set linebreak
set colorcolumn=100
set wrap
set tw=100

let mapleader = "\<Space>"
nmap <Leader><Leader> V
nnoremap <Leader>w :wq!<CR> "save file"
nmap <leader><Space><Space> :%s/\s\+$//<CR> "trimTrailingWhitespace"

" 自动补全 "
" inoremap ( ()<ESC>i<CR><CR><ESC>k
" inoremap [ []<ESC>i<CR><CR><ESC>k
" inoremap { {}<ESC>i<CR><CR><ESC>k
" inoremap " ""<ESC>i
" inoremap ' ''<ESC>i
" inoremap /* /* */<ESC>i

imap jj <ESC>
```

## VS Code 基础配置

> **入口：**文件 -> 首选项 -> 配置
>
> **备注：**前两个配置项根据实际情况设置

```json
{
    "go.gopath": "d:\\go",
    "terminal.integrated.shell.windows": "C:\\Program Files\\Git\\bin\\bash.exe",
    "editor.wordWrapColumn": 100,
    "files.eol": "\n",
    "editor.insertSpaces": true,
    "editor.tabSize": 4,
    "files.trimTrailingWhitespace": true,
    "files.autoSave": "afterDelay",
    "editor.formatOnSave": true,
    "editor.formatOnPaste": true,
    "window.zoomLevel": 2,
    "explorer.confirmDelete": true,
    "editor.detectIndentation": true,
    "team.showWelcomeMessage": false,
    "python.linting.flake8Enabled": true
}
```

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


## CentOS 安装 Python 3.5

```bash
1. CentOS 6.8 安装 Python 的依赖包

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

## CentOS 配置 MySQL

> - 主要包括**配置防火墙**、**修改初始密码**、**允许远程访问**三部分
> - MySQL 配置文件位置： /etc/my.cnf

1. 开启 3306 端口
```bash
/sbin/iptables -I INPUT -p tcp --dport 3306 -j ACCEPT
/etc/rc.d/init.d/iptables save
```

2. 修改初始密码

```bash
mysql -uroot -p123456（初始密码为空）
> use mysql;
> update user set password=password('123456') where user='root';
> flush privileges;
```
3. 允许远程访问

```bash
> grant all privileges on *.* to 'root'@'%' identified by '123456' with grant option;
```
## CentOS 安装 Redis 4.0.9

1. 运行环境：Cent OS 6.8
2. 安装

```bash
wget http://download.redis.io/releases/redis-4.0.9.tar.gz
tar -xzvf redis-4.0.9.tar.gz
cd redis-4.0.9
make -j4
# 测试，可跳过
make test
make install

# 拷贝默认配置文件
mkdir -p /etc/redis
cp sentinel.conf redis.conf /etc/redis/
```
3. 配置 redis.conf

> Redis server/cluster 对应的配置文件 redis.conf
>
> Redis Sentinel 对应的配置文件 sentinel.conf

```bash
# 默认只监听 127.0.0.1:6379，一般情况下，需要添加外网监听
bind 127.0.0.1 192.168.2.99
protected-mode yes
port 6379
tcp-backlog 511
timeout 0
tcp-keepalive 300
daemonize yes
supervised no
pidfile /var/run/redis.pid
loglevel notice
logfile /var/log/redis.log
databases 16
always-show-logo yes
save 900 1
save 300 10
save 60 10000
stop-writes-on-bgsave-error yes
rdbcompression yes
rdbchecksum yes
dbfilename dump.rdb
dir /var/lib/redis
slave-serve-stale-data yes
slave-read-only yes
repl-diskless-sync no
repl-diskless-sync-delay 5
repl-disable-tcp-nodelay no
slave-priority 100
lazyfree-lazy-eviction no
lazyfree-lazy-expire no
lazyfree-lazy-server-del no
slave-lazy-flush no
appendonly no
appendfilename "appendonly.aof"
appendfsync everysec
no-appendfsync-on-rewrite no
auto-aof-rewrite-percentage 100
auto-aof-rewrite-min-size 64mb
aof-load-truncated yes
aof-use-rdb-preamble no
lua-time-limit 5000
slowlog-log-slower-than 10000
slowlog-max-len 128
latency-monitor-threshold 0
notify-keyspace-events ""
hash-max-ziplist-entries 512
hash-max-ziplist-value 64
list-max-ziplist-size -2
list-compress-depth 0
set-max-intset-entries 512
zset-max-ziplist-entries 128
zset-max-ziplist-value 64
hll-sparse-max-bytes 3000
activerehashing yes
client-output-buffer-limit normal 0 0 0
client-output-buffer-limit slave 256mb 64mb 60
client-output-buffer-limit pubsub 32mb 8mb 60
hz 10
aof-rewrite-incremental-fsync yes
```
4. 运行与测试

```bash
redis_server /etc/redis/redis.conf
```

```bash
[root@localhost ~]# redis-cli 
127.0.0.1:6379> ping
PONG
127.0.0.1:6379> set name kevin
OK
127.0.0.1:6379> get name
"kevin"
127.0.0.1:6379> exit
```
## CentOS 安装 Siege

> **Siege** 是 linux 下的一个 web 系统的压力测试工具，支持多链接，支持 get 和 post 请求，可以对 web 系统进行多并发下持续请求的压力测试。

1. 运行环境：Cent OS 6.8
2. 安装
```bash
wget http://download.joedog.org/siege/siege-latest.tar.gz
tar -xzvf siege-latest.tar.gz
# 根据实际情况切换目录
cd siege-4.0.4/
./configure
make -j4
make install
```

3. 使用 siege -h 查看简要使用说明；使用 man siege 查看详细使用说明，包括示例。

## CentOS 安装 pip

```bash
# 安装 Python 2.7.4

# 安装 setuptools
wget --no-check-certificate https://pypi.python.org/packages/source/s/setuptools/setuptools-1.4.2.tar.gz
# 解压:
tar -xvf setuptools-1.4.2.tar.gz
cd setuptools-1.4.2
# 使用 Python 2.7.4 安装 setuptools
python setup.py install

# 安装 pip
curl  https://bootstrap.pypa.io/get-pip.py | python2.7 -

# 确认安装
[root@localhost~]# pip -V
pip 10.0.1 from /usr/local/lib/python2.7/site-packages/pip (python 2.7)
```

## CentOS 安装 protobuf 3.5.1

```bash
# 墙内需要找其他下载源
wget https://github.com/google/protobuf/releases/download/v3.5.1/protobuf-cpp-3.5.1.tar.gz
tar -xzvf protobuf-cpp-3.5.1.tar.gz
cd protobuf-3.5.1/
./configure
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

## Nginx 用户认证配置

1. 利用 htpasswd 生成密码文件

```basic
htpasswd -cb push4.passwd.20180531 push4 lucky2018
```

2. 配置 Nginx

```bash
server {
        listen       80;
        server_name  push4.vnay.vn;
        auth_basic "Restricted";
        auth_basic_user_file /usr/local/nginx/conf/push4.passwd.20180531;
        root /usr/local/vntop/server/push_server/static;
        index index.html;
        location /pushserver
        {
           proxy_set_header X-Real-IP $remote_addr;
           proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
           proxy_set_header Host $http_host;
           proxy_pass http://10.99.0.4:42290;
        }
}
```

3. reload nginx

```bash
/usr/local/nginx/sbin/nginx -t
/usr/local/nginx/sbin/nginx -s reload
```

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

    server_name             api.danbay.cn;
    root         		    /usr/share/nginx/html;
    ssl             		on;
    error_page 497          https://$host:443$uri; 
    #error_page 497         https://$host:443$request_uri?$args;

    ssl_certificate         /etc/letsencrypt/live/dev3.danbay.cn/fullchain.pem;
    ssl_certificate_key     /etc/letsencrypt/live/dev3.danbay.cn/privkey.pem;

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

    server_name             api.danbay.cn;
    root         		    /usr/share/nginx/html;
    ssl             		on;

    #error_page 497         https://$host:443$uri?$args;
    error_page 497          https://$host:443$request_uri; 

    ssl_certificate         /etc/letsencrypt/live/api.danbay.cn/fullchain.pem;
    ssl_certificate_key     /etc/letsencrypt/live/api.danbay.cn/privkey.pem;

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

## 安装配置 CURL 支持 http2

###基础环境

- CentOS 6.8
- Python 2.6.6
- CURL 7.19.7

### 安装依赖库

```bash
yum install -y readline-devel sqlite-devel lz4 lz4-devel gdbm gdbm-devel bzip2 openssl openssl-devel libdbi-devel ncurses-libs zlib-devel _bsddb bz2 dl
```

### 安装 Python 2.7.3

> nghttp2 依赖 Python 2.7.x

```bash
# 下载、安装 Python 2.7.3
wget http://python.org/ftp/python/2.7.3/Python-2.7.3.tar.bz2 
tar -jxvf Python-2.7.3.tar.bz2
cd Python-2.7.3
./configure
make -j4 all
make install

# 修复其他服务（如，YUM）对旧版本 Python 2.6.6 的依赖
mv /usr/bin/python /usr/bin/python-2.6.6
ln -sf /usr/local/bin/python2.7 /usr/bin/python
sed -i "s/#\!\/usr\/bin\/python/#\!\/usr\/bin\/python-2.6.6/" /usr/bin/yum
```

### 安装 nghttp2 v1.14.x

> CURL 依赖 nghttp2 提供对 http2 的支持，因此，需要先安装 nghttp2

```bash
git clone https://github.com/tatsuhiro-t/nghttp2.git
cd nghttp2

# 默认 master 分支，切换到特定的分支，例如 v1.14.x
git checkout -b v1.14.x origin/v1.14.x

autoreconf -i
automake
autoconf
./configure
make -j4
make install
echo '/usr/local/lib' > /etc/ld.so.conf.d/local.conf
ldconfig

# 查看 nghttp2
[root@localhost curl-7.46.0]# whereis libnghttp2
libnghttp2: /usr/local/lib/libnghttp2.a /usr/local/lib/libnghttp2.la /usr/local/lib/libnghttp2.so
```

### 安装 CURL 7.46.0

```bash
# 安装 CURL 7.46.0
wget http://curl.haxx.se/download/curl-7.46.0.tar.bz2
tar -xvjf curl-7.46.0.tar.bz2
cd curl-7.46.0
./configure --with-nghttp2=/usr/local --with-ssl
make -j4
make install

# 替换旧版本
ln -sf /usr/local/bin/curl /usr/bin/curl
```

### 确认 CURL 版本以及是否支持 http2

```bash
# 查看 CURL 版本以及所有支持的协议、特性
[root@localhost curl-7.46.0]# curl --version
curl 7.46.0 (x86_64-pc-linux-gnu) libcurl/7.46.0 OpenSSL/1.0.1e zlib/1.2.3 nghttp2/1.14.1
Protocols: dict file ftp ftps gopher http https imap imaps pop3 pop3s rtsp smb smbs smtp smtps telnet tftp 
Features: IPv6 Largefile NTLM NTLM_WB SSL libz HTTP2 UnixSockets 

# 如下提示则表明此版本 CURL 支持 http2
[root@localhost curl-7.46.0]# curl --http2 -I https://nghttp2.org/
HTTP/2.0 200
date:Thu, 12 Apr 2018 16:31:22 GMT
content-type:text/html
last-modified:Thu, 12 Apr 2018 15:17:17 GMT
etag:"5acf787d-19d8"
accept-ranges:bytes
content-length:6616
x-backend-header-rtt:0.001775
strict-transport-security:max-age=31536000
server:nghttpx
via:2 nghttpx
x-frame-options:SAMEORIGIN
x-xss-protection:1; mode=block
x-content-type-options:nosniff
```

## Mail 发送邮件

1. 配置 /etc/mail.rc
```bash
set from=xuchao@bigsillybear.com smtp="smtp.bigsillybear.com"
set smtp-auth-user="xuchao@bigsillybear.com" smtp-auth-password="HiBigsillybear"
set smtp-auth=login
```

2. 发送邮件

```bash
# 发送主题为 test，邮件正文为 ca.pem 文件内容，包含附件 ca.pem 的邮件到 cloud_dev@bigsillybear.com
mail -s "test" -a ca.pem cloud_dev@bigsillybear.com < ca.pem

# 发送主题为 test，邮件正文为 hello world 的邮件到 cloud_dev@bigsillybear.com
echo "hello world"|mail -s "test" cloud_dev@bigsillybear.com
```
## Windows 下 nodejs /npm 安装配置

> **说明：**使用 Node.js 的 npm 命令需要访问国外的站点，但由于国内网络的问题，可能安装 react-native-cli 的速度会比较慢，甚至完全无法安装，淘宝为国内开发者提供了 npm 镜像服务。
>
> **环境：**node-v8.11.1-x64/Windows 7 64位旗舰版

1. 下载 nodejs（已包含 npm），官网 https://nodejs.org/en/
2. 使用淘宝 npm 镜像安装 react-native-cli

```bash
# 安装 nrm 模块，方便我们切换 npm 下载源
npm install -g nrm
# 安装 npm2
npm install -g npm@2
# 创建一个名为 cnpm 的安装点，后面我们可以使用这个安装点从淘宝提供的 npm 镜像站点安装 React Native
npm install -g cnpm --registry=https://registry.npm.taobao.org
# npm 后接参数的命令都可以把 npm 换为 cnpm 来加快速度，比如安装 react-native-cli
cnpm install -g react-native-cli
```
## Windows 下 Git Bash 支持 wget/make/protoc

> **参考资料：**[How to add more to Git Bash on Windows](https://gist.github.com/evanwill/0207876c3243bbb6863e65ec5dc3f058)

### wget

1. 下载 [wget.exe](https://eternallybored.org/misc/wget/1.19.4/64/wget.exe)

2. 拷贝 wget.exe 到 Git 安装目录，默认路径 C:\Program Files\Git\mingw64\bin\（需根据 Git 实际安装路径调整）

### make

1. 下载 [make-4.2.1-without-guile-w32-bin.zip](https://sourceforge.net/projects/ezwinports/files/make-4.2.1-without-guile-w32-bin.zip/download)（适用于 Windows 64 位系统）

2. 解压

3. 将解压后的所有文件拷贝到 Git 安装目录，默认路径 C:\Program Files\Git\mingw64\（需根据 Git 实际安装路径调整，**另外，如果某些文件原来此目录已存在，切记不要覆盖，选择跳过即可**）

### protoc

1. 下载 [exe](https://github.com/google/protobuf/releases)

2. 解压

3. 将解压后的所有文件拷贝到 Git 安装目录，默认路径 C:\Program Files\Git\mingw64\（需根据 Git 实际安装路径调整，**另外，如果某些文件原来此目录已存在，切记不要覆盖，选择跳过即可**）

4. 确认配置成功

   打开 Git Bash，输入 protoc --version

```bash
$ protoc --version
libprotoc 3.5.1
```
## Visual Studio Code 配置 GoLang 开发环境

1. 官网下载 GoLang 安装包，安装之后 go version 查看版本

```bash
$ go version
go version go1.10.1 windows/amd64	
```

> **安装时勾选添加环境变量，不需要单独添加环境变量；否则，需要新添加环境变量，如下：**
>
> ​	计算机（右键）-> 属性 -> 高级系统设置 -> 高级 -> 环境变量 -> 系统变量 
>
> - 添加 变量名 GOROOT，值为安装目录，如  C:\app\Go\
> - 变量名 Path，追加值  C:\app\Go\bin;

2. 设置环境变量 GOPATH，具体操作如步骤 1 所示，值为后续你存放源码的目录，如 D:\go
3. 打开 Git Bash，依次安装如下依赖项

```bash
go get -u -v github.com/nsf/gocode
go get -u -v github.com/rogpeppe/godef
go get -u -v github.com/golang/lint/golint
go get -u -v github.com/lukehoban/go-outline
go get -u -v sourcegraph.com/sqs/goreturns
go get -u -v golang.org/x/tools/cmd/gorename
go get -u -v github.com/tpng/gopkgs
go get -u -v github.com/newhook/go-symbols
go get -u -v golang.org/x/tools/cmd/guru

# 可选择性下载
# protobuf 相关，需要安装 protoc
go get -u -v github.com/golang/protobuf/protoc-gen-go
go get -u -v github.com/golang/protobuf/proto
# grpc
go get -u -v google.golang.org/grpc
```

> **请注意大坑：**步骤  3 需要墙外操作，F**K

4. 安装 VS Code
5. 安装 VS Code 各种插件，打开 VS Code，按 Ctrl+Shift+P，输入 install ext，输入 go，选中安装即可

> VS Code 支持各种语法，同理，安装对应的插件即可，如，需要支持 C++，安装 C++ 插件即可

## Ubuntu 替换源

> **环境：**Ubuntu 14.04.5 LTS

1. 备份

```bash
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak
```

2. 替换阿里云的源

```bash
su -

cat > /etc/apt/sources.list << EOF
deb http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
EOF

apt-get update
```

