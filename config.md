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
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset %C(bold blue)\
<%an>%Creset ---%C(yellow)%d%Creset %s %Cgreen(%cr)' --abbrev-commit"
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
>useradd -d /home/ftp -g ftp -s /sbin/nologin XXXftp -p XXX123!
>passwd XXXftp

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

3. 开启防火墙
```
