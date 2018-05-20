[TOC]

##  [CPP] 读取文件

```c++
static bool ReadFile(const char *file, std::string &out)
{
    std::ifstream fin(file);
    if (!fin.is_open())
    {
        return false;
    }

    std::stringstream buffer;
    buffer << fin.rdbuf();
    out.assign(buffer.str());
    fin.close();

    return true;
}
```

## [CPP] 处理信号，服务优雅退出

```c++
#include <chrono>

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static bool g_done = false;

static void SignalHandler(int)
{
    std::cout << "[WARN] try to stop and exit" << std::endl;
    g_done = true;
}

static void RegisterSignalHandler(void)
{
    struct sigaction action;

    action.sa_handler = SignalHandler;
    sigemptyset(&action.sa_mask);

    // Handle signals properly before shutting down the server.
    // Ctrl + C
    sigaction(SIGINT, &action, (struct sigaction *)nullptr);
    // kill PID
    sigaction(SIGTERM, &action, (struct sigaction *)nullptr);
}

int main(int argc, char **argv)
{
    RegisterSignalHandler();

    // start service

    while (!g_done)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // stop service

    return 0;
}
```

## [CPP] 自定义服务运行参数

```c++
static void ShowHelp()
{
    const char *help =
        "=============================================\n"
        " Desc: Danbay's Access Service\n"
        "\n"
        " Usage:\n"
        "  -c/--conf <file>     default 'default.conf'\n"
        "  -d/--daemon          run in daemon mode\n"
        "  -w/--watchdog        run with watchdog\n"
        "  -h/--help            show help and exit\n"
        "=============================================\n";

    std::cout << help << std::endl;
}

int main(int argc, char **argv)
{
    const char *conf = "default.conf";
    bool daemon_alias = false;
    bool watchdog = false;

    const struct option options[] = {
        {"conf", 1, nullptr, 'c'},
        {"daemon", 0, nullptr, 'd'},
        {"watchdog", 0, nullptr, 'w'},
        {"help", 0, nullptr, 'h'}
    };

    int opt = -1;
    while ((opt = getopt_long(argc, argv, "c:dwh", options, nullptr)) != -1)
    {
        switch (opt)
        {
            case 'c':
                conf = optarg;
                break;
            case 'd':
                daemon_alias = true;
                break;
            case 'w':
                watchdog = true;
                break;
            case 'h':
            default:
                ShowHelp();
                return -1;
        }
    }

    // RegisterSignalHandler();

    std::string config;
    if (!ReadFile(conf, config))
    {
        std::cerr << "[ERROR] open conf file failed" << std::endl;
        return -1;
    }

    std::cout << "[INFO] here is all configuration information" <<
        std::endl << config << std::endl;

    int ret = 0;
    if (daemon_alias)
    {
        int nochdir = 1;
        int noclose = 0;
        ret = daemon(nochdir, noclose);
        if (ret == -1)
        {
            std::cerr << "[ERROR] run in daemon mode failed" << std::endl;
            return -1;
        }
    }

    while (watchdog)
    {
        ret = fork();
        if (ret == -1)
        {
            std::cerr << "[ERROR] run with watchdog failed" << std::endl;
            return -1;
        }
        else if (ret == 0)
        {
            break;
        }

        if (wait(&ret) == -1)
        {
            std::cerr << "[ERROR] run with watchdog failed" << std::endl;
            return -1;
        }
    }
    
    // ...
}
```

## [CPP] SSL/TLS 客户端

> **源码路径：**
>
> 1. [openssl_client.c](https://dudebing99.github.io/blog/archives/code_snippet/openssl_client.c)
> 2. [boost_ssl_client.cpp](https://dudebing99.github.io/blog/archives/code_snippet/boost_ssl_client.cpp)

```c
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXBUF 1024

#define CA_FILE             "ca.pem"
#define CLIENT_KEY          "client.pem"
#define CLIENT_CERT         "client.pem"

void ShowCerts(SSL * ssl)
{
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl);
    if (cert != NULL)
    {
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("证书: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("颁发者: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
    {
        printf("无证书信息！\n");
    }
}

int main(int argc, char **argv)
{
    int sockfd, len;
    struct sockaddr_in dest;
    char buffer[MAXBUF + 1];
    SSL_CTX *ctx;
    SSL *ssl;
    const SSL_METHOD *method;

    if (argc != 3)
    {
        printf("%s <ip> <port>\n", argv[0]);
        exit(0);
    }

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    method = TLSv1_2_client_method();
    ctx = SSL_CTX_new(method);

    if (!ctx)
    {
        printf("create ctx is failed.\n");
    }

    /* 设置会话的握手方式 */
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, 0);

    /* 加载 CA FILE */
    if (SSL_CTX_load_verify_locations(ctx, CA_FILE, 0) != 1)
    {
        SSL_CTX_free(ctx);
        printf("Failed to load CA file %s", CA_FILE);
    }

    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
    {
        SSL_CTX_free(ctx);
        printf("Call to SSL_CTX_set_default_verify_paths failed");
    }

    /* 加载客户端证书 */
    if (SSL_CTX_use_certificate_file(ctx, CLIENT_CERT, SSL_FILETYPE_PEM) != 1)
    {
        SSL_CTX_free(ctx);
        printf("Failed to load client certificate from %s", CLIENT_KEY);
    }

    /* 加载客户端私钥 */
    if (SSL_CTX_use_PrivateKey_file(ctx, CLIENT_KEY, SSL_FILETYPE_PEM) != 1)
    {
        SSL_CTX_free(ctx);
        printf("Failed to load client private key from %s", CLIENT_KEY);
    }

    /* 验证私钥 */
    if (SSL_CTX_check_private_key(ctx) != 1)
    {
        SSL_CTX_free(ctx);
        printf("SSL_CTX_check_private_key failed");
    }

    /* 处理握手多次 */
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Create socket error.\n");
        exit(errno);
    }

    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], (struct in_addr *)&dest.sin_addr.s_addr) == 0)
    {
        perror(argv[1]);
        exit(errno);
    }

    if (connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0)
    {
        perror("Connect error.\n");
        exit(errno);
    }

    /* 创建 SSL */
    ssl = SSL_new(ctx);
    if (ssl == NULL)
    {
        printf("SSL_new error.\n");
    }

    /* 将 fd 添加到 ssl 层 */
    SSL_set_fd(ssl, sockfd);
    if (SSL_connect(ssl) == -1)
    {
        printf("SSL_connect fail.\n");
        ERR_print_errors_fp(stderr);
    }
    else
    {
        printf("SSL 最终协商的算法：%s\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);
    }

    bzero(buffer, MAXBUF + 1);
    strcpy(buffer, "Hello World!");
    len = SSL_write(ssl, buffer, strlen(buffer));
    if (len < 0)
    {
        printf("消息'%s'发送失败，错误码：%d，错误信息：'%s'\n",
            buffer, errno, strerror(errno));
        goto finish;
    }
    else
    {
        printf("消息'%s'发送成功，长度：%d 字节\n", buffer, len);
    }

    bzero(buffer, MAXBUF + 1);
    len = SSL_read(ssl, buffer, MAXBUF);
    if (len > 0)
    {
        printf("接收消息成功: '%s'，长度：%d\n", buffer, len);
    }
    else
    {
        printf("接收消息失败，错误码：%d，错误信息：'%s'\n",
            errno, strerror(errno));
    }

finish:

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);

    return 0;
}
```

```cpp
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

enum { max_length = 1024 };

class client
{
public:
  client(boost::asio::io_service& io_service,
      boost::asio::ssl::context& context,
      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : socket_(io_service, context)
  {
    socket_.set_verify_mode(boost::asio::ssl::verify_peer);
    socket_.set_verify_callback(
        boost::bind(&client::verify_certificate, this, _1, _2));

    boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
        boost::bind(&client::handle_connect, this,
          boost::asio::placeholders::error));
  }

  bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
  {
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    return preverified;
  }

  void handle_connect(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_handshake(boost::asio::ssl::stream_base::client,
          boost::bind(&client::handle_handshake, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Connect failed: " << error.message() << "\n";
    }
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if (!error)
    {
      std::cout << "Enter message: ";
      std::cin.getline(request_, max_length);
      size_t request_length = strlen(request_);

      boost::asio::async_write(socket_,
          boost::asio::buffer(request_, request_length),
          boost::bind(&client::handle_write, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Handshake failed: " << error.message() << "\n";
    }
  }

  void handle_write(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_read(socket_,
          boost::asio::buffer(reply_, bytes_transferred),
          boost::bind(&client::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Write failed: " << error.message() << "\n";
    }
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      std::cout << "Reply: ";
      std::cout.write(reply_, bytes_transferred);
      std::cout << "\n";
    }
    else
    {
      std::cout << "Read failed: " << error.message() << "\n";
    }
  }

private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  char request_[max_length];
  char reply_[max_length];
};

std::string get_password()
{
    return "Danbay666!";
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
    ctx.set_password_callback(boost::bind(&get_password));
    ctx.use_certificate_chain_file("client.pem");
    ctx.use_private_key_file("client.pem", boost::asio::ssl::context::pem);
    ctx.load_verify_file("ca.pem");

    client c(io_service, ctx, iterator);

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
```

## [CPP] SSL/TLS 服务器端

> **源码路径：**[boost_ssl_server.cpp](https://dudebing99.github.io/blog/archives/code_snippet/boost_ssl_server.cpp)

```cpp
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class session
{
public:
  session(boost::asio::io_service& io_service,
      boost::asio::ssl::context& context)
    : socket_(io_service, context)
  {
  }

  ssl_socket::lowest_layer_type& socket()
  {
    return socket_.lowest_layer();
  }

  void start()
  {
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&session::handle_handshake, this,
          boost::asio::placeholders::error));
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

private:
  ssl_socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_service, unsigned short port)
    : io_service_(io_service),
      acceptor_(io_service,
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      context_(boost::asio::ssl::context::sslv23)
  {
    context_.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    context_.set_password_callback(boost::bind(&server::get_password, this));
    context_.set_verify_callback(boost::bind(&server::verify_certificate, this, _1, _2));
    context_.use_certificate_chain_file("server.pem");
    context_.use_private_key_file("server.pem", boost::asio::ssl::context::pem);
    context_.load_verify_file("ca.pem");
    context_.set_verify_mode(boost::asio::ssl::verify_peer);

    start_accept();
  }

  bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
  {
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    return preverified;
  }

  std::string get_password() const
  {
    return "Danbay666!";
  }

  void start_accept()
  {
    session* new_session = new session(io_service_, context_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

private:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ssl::context context_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    using namespace std; // For atoi.
    server s(io_service, atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
```
## [Python 2.x] 输出不换行

```python
# -*- coding:utf-8 -*-

if __name__ == '__main__':
    print("hello")
    print("world")
    
    print("hello"),
    print("world")
```

**输出**

```basic
hello
world
hello world
```

## [Python] 获取 unixstamp

```python
import time
import datetime
import calendar

original_seconds = time.time()
print original_seconds

seconds = int(time.time())
print seconds

millis = int(round(time.time() * 1000))
print millis

now = datetime.datetime.utcnow()
tt = long(calendar.timegm(now.utctimetuple()))
print tt
```

**输出**

```basic
1527122035.76
1527122035
1527122035756
1527122035
```

## [Python] 日期时间格式化

```python
# -*- coding:utf-8 -*-

import datetime
import time

if __name__ == '__main__':

    date = datetime.datetime.now().strftime("%Y-%m-%d")
    print(date)

    now = datetime.datetime.strptime("2018-04-25 18:00:34.123456", "%Y-%m-%d %H:%M:%S.%f")
    print(now)

    now = datetime.datetime.utcnow()
    vn_now = now + datetime.timedelta(hours=7)
    vn_date = vn_now.strftime("%Y-%m-%d")
    print(vn_date)
```

**输出**

```basic
2018-05-24
2018-04-25 18:00:34.123456
2018-05-24
```

## [Python] Redis 使用

> **环境：**Python 2.7.14 
>
> **安装 redis：**pip install redis *redis*-py-cluster
>
> **源码：**[点此下载](https://dudebing99.github.io/blog/archives/code_snippet/redis_helper.py)

```python
# -*- coding:utf-8 -*-
import datetime
import time


class RedisHelper(object):
    def __init__(self, redis_type=None, **args):
        if redis_type == "cluster":
            import rediscluster
            self.r_conn = rediscluster.StrictRedisCluster(**args)
        else:
            import redis
            self.r_conn = redis.StrictRedis(**args)

    def GetValue(self, name):
        return self.r_conn.get(name)

    def IncrValue(self, name):
        return self.r_conn.incr(name)

    def SetValue(self, name, value):
        self.r_conn.set(name, value)

    def GetSetValue(self, name, value):
        return self.r_conn.getset(name, value)


if __name__ == '__main__':

    # 单点
    conn_dict = {'host': '127.0.0.1', 'port': 6379}
    redis_type = 'single'

    # 集群
    # conn_dict={"startup_nodes":[
    #    {'host':'192.168.0.3', 'port':4000},
    #    {'host':'192.168.0.3', 'port':5000},
    #    {'host':'192.168.0.4', 'port':6000},
    #    {'host':'192.168.0.5', 'port':7000}]}
    # redis_type='cluster'

    myredis = RedisHelper(redis_type, **conn_dict)
    print(myredis.SetValue('name', 'kevin'))
    print(myredis.GetValue('name'))
    print(myredis.GetSetValue('nickname', 0))
    print(myredis.GetValue('nickname'))

```

**输出**

```basic
None
kevin
0
0
```

## [Python] MySQL 使用

> **环境：**Python 2.7.14 
>
> **源码：**[点此下载](https://dudebing99.github.io/blog/archives/code_snippet/mysql_helper.py)
>
> **Tag：**查询、插入、批量插入、truncate

```python
# coding=utf-8
import sys
import time
import datetime
import random
import json
import traceback
import hashlib
import logging
import MySQLdb
import MySQLdb.cursors
import getopt
import traceback
import requests

logger = logging.getLogger("multi_app_with_single_user")
logger.setLevel(logging.INFO)

vntopnews_user = {
    "host": "101.99.0.102",
    "port": 3306,
    "user": "dev",
    "passwd": "123456",
    "db": "vntopnews_user"
}

def init_logger(log_module):
    handler = logging.FileHandler(filename="multi_app_with_single_user.log", mode='w')
    # handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
    handler.setFormatter(formatter)
    log_module.addHandler(handler)

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

def truncate_table_helper():
    sql = "truncate table `vntopnews_user`.`multi_app_user_tbl`"
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()

def fetch_helper(start, limit):
    sql = """
    select id, user_flavor_unique_id
    from `vntopnews_user`.`user_tbl`
    where id < {}
    order by id desc
    limit {}
    """.format(start, limit)
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret

def find_max_id_helper():
    sql = "select max(org_user_id) as max_id from `vntopnews_user`.`multi_app_user_tbl` order by id asc"
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret

def insert_helper(org_user_id, uniq_user_id):
    sql = """
    INSERT INTO `vntopnews_user`.`multi_app_user_tbl`
    (org_user_id, uniq_user_id)
    VALUES ({}, '{}')
    """.format(org_user_id, uniq_user_id)
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()

def batch_insert_helper(multi_app_user_dict):
    if len(multi_app_user_dict) == 0:
        return
    total = 0
    try:

        db, cursor = get_db_conn(vntopnews_user)
        batch = 10000
        values = []

        for i in multi_app_user_dict:
            if len(multi_app_user_dict[i]) > 1:
                for j in multi_app_user_dict[i]:
                    values.append((j, i))
                    # 批量插入
                    if len(values) == batch:
                        total += batch
                        logger.info("batch insert, count: %d", len(values))
                        cursor.executemany('INSERT INTO `vntopnews_user`.`multi_app_user_tbl` (org_user_id, uniq_user_id) VALUES (%s, %s)', values)
                        db.commit()
                        values = []

        if len(values) > 0:
            total += len(values)
            logger.info("final batch insert, count: %d", len(values))
            cursor.executemany('INSERT INTO `vntopnews_user`.`multi_app_user_tbl` (org_user_id, uniq_user_id) VALUES (%s, %s)', values)
            db.commit()
            values = []

        cursor.close()
        db.close()
    except MySQLdb.Error as ex:
        logger.error("MySQL Error %d: %s", ex.args[0], ex.args[1])

    return total

if __name__ == '__main__':
    init_logger(logger)

    logger.info("begin task")

    truncate_table_helper()

    start = 99999999999
    limit = 500000
    multi_app_user_dict = {}
    while (1):
        logger.debug("begin to fetch from user table, start:%d, limit:%d", start, limit)
        multi_app_users = fetch_helper(start, limit)
        if not multi_app_users:
            logger.info("fetch from user table, no record")
            break

        for row in multi_app_users:
            start = row['id']
            if not row['user_flavor_unique_id']:
                continue

            try:
                # logger.debug("id:%d, user_flavor_unique_id:%s", row['id'], row['user_flavor_unique_id'])
                index = row['user_flavor_unique_id'].index("_") + 1

                org_user_id = row['id']
                uniq_user_id = row['user_flavor_unique_id'][index:]
                # 多个 org_user_id 对应 一个 uniq_user_id
                if uniq_user_id in multi_app_user_dict:
                    logger.debug("old uniq_user_id, add org_user_id:%d, uniq_user_id:%s", org_user_id, uniq_user_id)
                    user_id_set = multi_app_user_dict[uniq_user_id]
                    if len(user_id_set) == 1:
                        multi_app_user_dict[uniq_user_id].add(org_user_id)
                        logger.debug("need insert twice, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                    elif len(user_id_set) == 2:
                        multi_app_user_dict[uniq_user_id].add(org_user_id)
                        logger.debug("need insert once, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                    else:
                        # 超过三条，过滤
                        logger.debug("filter, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                else:
                    logger.debug("new uniq_user_id, add org_user_id:%d, uniq_user_id:%s", org_user_id, uniq_user_id)
                    multi_app_user_dict[uniq_user_id] = {org_user_id}
            except Exception as ex:
                logger.error("caught exception: %s, traceback: %s", ex, traceback.format_exc())

    total = batch_insert_helper(multi_app_user_dict)
    logger.info("Total:%d record(s)", total)

    logger.info("end task")
```

