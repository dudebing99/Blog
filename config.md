[TOC]

------

## git 客户端基本配置项

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
git config --global user.name xx
git config --global user.email xx@xxx.cn
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