[TOC]

------

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
## [CPP] 代理模式

![](pic/designpattern/proxy.jpg)

> **源码路径：**[proxy.cpp](https://dudebing99.github.io/blog/archives/code_snippet/proxy.cpp)

```cpp
#include <string>
#include <iostream>

class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

public:
    virtual void Request() = 0;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject() {}
    ~ConcreteSubject() {}

public:
    void Request()
    {
        std::cout << "Done in ConcreteSubject" << std::endl;
    }
};

class Proxy : public Subject
{
public:
    Proxy(Subject *subject) 
    :m_subject(subject)
    {}
    ~Proxy() {}

public:
    void Request()
    {
        std::cout << "Call ConcreteSubject::Request() to do the job" << std::endl;
        m_subject->Request();
    }

private:
    Subject * m_subject;
};


int main()
{
    Subject *subject = new ConcreteSubject();
    Proxy *proxy = new Proxy(subject);

    proxy->Request();

    delete proxy;
    proxy = nullptr;
    delete subject;
    subject = nullptr;

    return 0;
}
```

**输出**

```bash
[root@localhost design_pattern]# g++ proxy.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Call ConcreteSubject::Request() to do the job
Done in ConcreteSubject
```

## [CPP] 单例模式

![img](pic/designpattern/singleton.jpg) 

### 饿汉式

> **源码路径：**[hungry_singleton.cpp](https://dudebing99.github.io/blog/archives/code_snippet/hungry_singleton.cpp)

```cpp
#include <iostream>

class Singleton {
public:
    static Singleton* Instance()
    {
        return &m_instance;
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static Singleton m_instance;
};

Singleton Singleton::m_instance;

int main()
{
    Singleton *singleton1 = Singleton::Instance();
    Singleton *singleton2 = Singleton::Instance();

    if (singleton1 == singleton2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ hungry_singleton.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Got the same instance
```

### 饱汉式

> **源码路径：**[full_singleton.cpp](https://dudebing99.github.io/blog/archives/code_snippet/full_singleton.cpp)

```cpp
#include <iostream>

class Singleton {
public:
    static Singleton* Instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Singleton();
        }

        return m_instance;
    }

    static void Release()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static Singleton *m_instance;
};

Singleton *Singleton::m_instance = nullptr;

int main()
{
    Singleton *singleton1 = Singleton::Instance();
    Singleton *singleton2 = Singleton::Instance();

    if (singleton1 == singleton2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    singleton1->Release();

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ full_singleton.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Got the same instance
```

### 双重检测（线程安全）

> **源码路径：**[double_check_singleton.cpp](https://dudebing99.github.io/blog/archives/code_snippet/double_check_singleton.cpp)

```cpp
#include <iostream>
#include <mutex>

class Singleton {
public:
    static Singleton* Instance()
    {
        if (m_instance == nullptr)
        {
            m_mtx.lock();
            if (m_instance == nullptr)
            {
                m_instance = new Singleton();
            }
            m_mtx.unlock();
        }

        return m_instance;
    }

    static void Release()
    {
        if (m_instance != nullptr)
        {
            m_mtx.lock();
            if (m_instance != nullptr)
            {
                delete m_instance;
                m_instance = nullptr;
            }
            m_mtx.unlock();
        }
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static Singleton *m_instance;
    static std::mutex m_mtx;
};

Singleton *Singleton::m_instance = nullptr;
std::mutex Singleton::m_mtx;

int main()
{
    Singleton *singleton1 = Singleton::Instance();
    Singleton *singleton2 = Singleton::Instance();

    if (singleton1 == singleton2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    singleton1->Release();

    return 0;
}
```

**输出**

```bash
[root@localhost design_pattern]# g++ double_check_singleton.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Got the same instance
```

### 模板

> **源码路径：**[template_singleton.cpp](https://dudebing99.github.io/blog/archives/code_snippet/template_singleton.cpp)

```cpp
#include <iostream>
#include <mutex>

template<typename T>
class Singleton {
public:
    static T* Instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new T();
        }

        return m_instance;
    }

    static void Release()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static T *m_instance;
};

template<typename T>
T *Singleton<T>::m_instance = nullptr;

class A
{
public:
    void SayHello()
    {
        std::cout << "hello world" << std::endl;
    }
};

int main()
{
    A *a1 = Singleton<A>::Instance();
    A *a2 = Singleton<A>::Instance();
    if (a1 == a2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    a1->SayHello();

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ template_singleton.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Got the same instance
hello world
```

## [CPP] 适配器模式

### 类适配器

![img](pic/designpattern/class_adapter.jpg) 

> **源码路径：**[class_adapter.cpp](https://dudebing99.github.io/blog/archives/code_snippet/class_adapter.cpp)

```cpp
#include <iostream>

class Target
{
public:
    Target() {}
    virtual ~Target() {}

public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    Adaptee(){}
    virtual ~Adaptee() {}

public:
    virtual void SpecificRequest() = 0;
};

class Adapter : public Target, public Adaptee
{
public:
    Adapter() {}
    ~Adapter() {}

public:
    void Request()
    {
        std::cout << "Transfer Specific Request to Reuest" << std::endl;
        SpecificRequest();
        std::cout << "Finally, Request" << std::endl;
    }

    void SpecificRequest()
    {
        std::cout << "Specific Request" << std::endl;
    }
};

int main()
{
    Target *target = new Adapter();
    target->Request();

    delete target;
    target = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ class_adapter.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Transfer Specific Request to Reuest
Specific Request
Finally, Request
```

### 对象适配器

![](pic/designpattern/object_adapter.jpg)

> **源码路径：**[object_adapter.cpp](https://dudebing99.github.io/blog/archives/code_snippet/object_adapter.cpp)

```cpp
#include <iostream>

class Target
{
public:
    Target() {}
    virtual ~Target() {}

public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    Adaptee(){}
    virtual ~Adaptee() {}

public:
    void SpecificRequest()
    {
        std::cout << "Specific Request" << std::endl;
    }
};

class Adapter : public Target
{
public:
    Adapter(Adaptee *adaptee) {}
    ~Adapter() {}

public:
    void Request()
    {
        std::cout << "Transfer Specific Request to Reuest" << std::endl;
        m_adaptee->SpecificRequest();
        std::cout << "Finally, Request" << std::endl;
    }

private:
    Adaptee * m_adaptee;
};

int main()
{
    Adaptee *adaptee = new Adaptee();
    Target *target = new Adapter(adaptee);
    target->Request();

    delete target;
    target = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ object_adapter.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Transfer Specific Request to Reuest
Specific Request
Finally, Request
```

## [CPP] 桥接模式

![img](pic/designpattern/bridge.jpg) 

> **源码路径：**[bridge.cpp](https://dudebing99.github.io/blog/archives/code_snippet/bridge.cpp)

```cpp
#include <iostream>
#include <string>

class USB
{
public:
    USB() {}
    virtual ~USB() {}

public:
    virtual void Transfer() = 0;
};

// USB 2.0
class USB20 : public USB
{
public:
    USB20() {}
    ~USB20() {}

public:
    void Transfer()
    {
        std::cout << "Transfer by USB 2.0" << std::endl;
    }
};

// USB 3.0
class USB30 : public USB
{
public:
    USB30() {}
    ~USB30() {}

public:
    void Transfer()
    {
        std::cout << "Transfer by USB 3.0, faster" << std::endl;
    }
};

class PC
{
public:
    PC() {}
    virtual ~PC() {}

public:
    virtual void Transfer(USB *usb) = 0;
};

class DellPC : public PC
{
public:
    DellPC() {}
    ~DellPC() {}

public:
    void Transfer(USB *usb)
    {
        std::cout << "Dell PC, try to transfer data by USB device" << std::endl;
        usb->Transfer();
    }
};


int main()
{
    USB *usb20 = new USB20();
    USB *usb30 = new USB30();

    PC *pc = new DellPC();

    pc->Transfer(usb20);
    pc->Transfer(usb30);

    delete usb20;
    usb20 = nullptr;
    delete usb30;
    usb30 = nullptr;
    delete pc;
    pc = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ bridge.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Dell PC, try to transfer data by USB device
Transfer by USB 2.0
Dell PC, try to transfer data by USB device
Transfer by USB 3.0, faster
```

## [CPP] 观察者模式

![img](pic/designpattern/observer.jpg) 

> **源码路径：**[observer.cpp](https://dudebing99.github.io/blog/archives/code_snippet/observer.cpp)

```cpp
#include <iostream>
#include <list>
#include <string>

class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}

public:
    virtual void Update(int status) = 0;
};

class ConcreteObserver : public Observer
{
public:
    ConcreteObserver() {}
    ~ConcreteObserver() {}

public:
    void Update(int status)
    {
        std::cout << "The target subject is changing status: " << status << std::endl;
    }
};

class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

public:
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
    virtual void SetStatus(int status) = 0;
    virtual int GetStatus() = 0;

private:
    int status;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject() {}
    virtual ~ConcreteSubject() {}

    void Attach(Observer *observer)
    {
        m_observers.push_back(observer);
    }

    void Detach(Observer* observer)
    {
        m_observers.remove(observer);
    }

    void Notify()
    {
        for (auto itor = m_observers.begin(); itor != m_observers.end(); itor++)
        {
            (*itor)->Update(m_status);
        }
    }

    void SetStatus(int status)
    {
        m_status = status;
    }

    int GetStatus()
    {
        return m_status;
    }

private:
    std::list<Observer*> m_observers;
    int m_status;
};

int main()
{
    Observer *observer = new ConcreteObserver();
    Subject *subject = new ConcreteSubject();
        
    subject->Attach(observer);
    subject->SetStatus(99);
    std::cout << "Subject's status: " << subject->GetStatus() << std::endl;
    subject->Notify();

    subject->Detach(observer);

    delete observer;
    observer = nullptr;
    delete subject;
    subject = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ observer.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
Subject's status: 99
The target subject is changing status: 99
```

## [CPP] 装饰器模式

![img](pic/designpattern/decorator.jpg) 

> **源码路径：**[decorator.cpp](https://dudebing99.github.io/blog/archives/code_snippet/decorator.cpp)

```c++
#include <iostream>
#include <string>

class Phone
{
public:
    Phone() {}
    virtual ~Phone() {}
    virtual void ShowDecorate() = 0;
};

class iPhone : public Phone
{
public:
    iPhone(std::string name)
        : m_name(name) {}
    ~iPhone() {}
    void ShowDecorate()
    {
        std::cout << "Name: " << m_name << std::endl;
    }

private:
    std::string m_name;

};

class NokiaPhone : public Phone
{
public:
    NokiaPhone(std::string name)
        : m_name(name)
    {
    }
    ~NokiaPhone()
    {
    }
    void ShowDecorate()
    {
        std::cout << "Name: " << m_name << std::endl;
    }

private:
    std::string m_name;
};

class DecoratorPhone : public Phone
{
public:
    DecoratorPhone(Phone *phone)
        : m_phone(phone)
    {
    }
    virtual void ShowDecorate()
    {
        m_phone->ShowDecorate();
    }

private:
    Phone *m_phone;
};

class DecoratePhoneA : public DecoratorPhone
{
public:
    DecoratePhoneA(Phone *ph)
        : DecoratorPhone(ph)
    {
    }
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }

private:
    void AddDecorate()
    {
        std::cout << "Decorator: HiFi Audio System" << std::endl;
    }
};

class DecoratePhoneB : public DecoratorPhone
{
public:
    DecoratePhoneB(Phone *ph)
        : DecoratorPhone(ph)
    {
    }
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }

private:
    void AddDecorate()
    {
        std::cout << "Decorator: Duel Camera" << std::endl;
    }
};

int main()
{
    Phone *nokia = new NokiaPhone("Nokia N8");
    Phone *iphone = new iPhone("iPhone 4");
    Phone *dpa = new DecoratePhoneA(nokia);
    Phone *dpb = new DecoratePhoneB(iphone);

    nokia->ShowDecorate();
    dpa->ShowDecorate();
    dpb->ShowDecorate();

    delete nokia;
    nokia = nullptr;
    delete iphone;
    iphone = nullptr;
    delete dpa;
    dpa = nullptr;
    delete dpb;
    dpb = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ decorator.cpp -std=c++11
[root@localhost design_pattern]# ./a.out                     
Name: Nokia N8
Name: Nokia N8
Decorator: HiFi Audio System
Name: iPhone 4
Decorator: Duel Camera
```

## [CPP] 职责链模式

![img](pic/designpattern/chain_of_responsibility.jpg) 

> **源码路径：**[chain_of_responsibility.cpp](https://dudebing99.github.io/blog/archives/code_snippet/chain_of_responsibility.cpp)

```cpp
#include <iostream>

class Handler
{
public:
    Handler() {}
    virtual ~Handler() {}

public:
    virtual void HandleRequest(int count) = 0;
    void SetSuccessor(Handler *successor)
    {
        m_successor = successor;
    }
    Handler *GetSuccessor()
    {
        return m_successor;
    }

protected:
    Handler *m_successor;
};

class ConcreteHandlerA : public Handler
{
public:
    ConcreteHandlerA() {}
    ~ConcreteHandlerA() {}

public:
    void HandleRequest(int count)
    {
        if (count < 100)
        {
            std::cout << "A: I can do it, done" << std::endl;
        }
        else
        {
            std::cout << "A: I can not do it, next" << std::endl;
            if (GetSuccessor() != nullptr)
            {
                GetSuccessor()->HandleRequest(count);
            }
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    ConcreteHandlerB() {}
    ~ConcreteHandlerB() {}

public:
    void HandleRequest(int count)
    {
        if (count >= 100)
        {
            std::cout << "B: I can do it, done" << std::endl;
        }
    }
};

int main()
{
    Handler *a = new ConcreteHandlerA();
    Handler *b = new ConcreteHandlerB();
    a->SetSuccessor(b);

    a->HandleRequest(50);
    a->HandleRequest(150);

    a->SetSuccessor(nullptr);
    delete b;
    b = nullptr;
    delete a;
    a = nullptr;

    return 0;
}
```

**输出**

```basic
[root@localhost design_pattern]# g++ chain_of_responsibility.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
A: I can do it, done
A: I can not do it, next
B: I can do it, done
```

## [CPP] 模板方法模式

![](pic/designpattern/template_function.jpg)

> **源码路径：**[template_function.cpp](https://dudebing99.github.io/blog/archives/code_snippet/template_function.cpp)

```cpp
#include <iostream>
#include <string>

class AbstractClass 
{
public:
    AbstractClass() {}
    virtual ~AbstractClass() {}

public:
    void TemplateMethod() 
    {
        this->Primitive1();
        this->Primitive2();
    }

protected:
    virtual void Primitive1() = 0;
    virtual void Primitive2() = 0;
};

class ConcreteClass1 : public AbstractClass 
{
public:
    ConcreteClass1() {}
    ~ConcreteClass1() {}
protected:
    void Primitive1()
    {
        std::cout << "ConcreteClass1::Primitive1()" << std::endl;
    }
    void Primitive2()
    {
        std::cout << "ConcreteClass1::Primitive2()" << std::endl;
    }
};

class ConcreteClass2 : public AbstractClass
{
public:
    ConcreteClass2() {}
    ~ConcreteClass2() {}
protected:
    void Primitive1()
    {
        std::cout << "ConcreteClass2::Primitive1()" << std::endl;
    }
    void Primitive2()
    {
        std::cout << "ConcreteClass2::Primitive2()" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    AbstractClass* p1 = new ConcreteClass1();
    AbstractClass* p2 = new ConcreteClass2();

    p1->TemplateMethod();
    p2->TemplateMethod();

    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;

    return 0;
}
```

**输出**

```bash
[root@localhost design_pattern]# g++ template_function.cpp -std=c++11
[root@localhost design_pattern]# ./a.out 
ConcreteClass1::Primitive1()
ConcreteClass1::Primitive2()
ConcreteClass2::Primitive1()
ConcreteClass2::Primitive2()
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

## [Python] 计算比特币发行总量

```python
# -*- coding: utf-8 -*-

# 初始的块奖励为 50 BTC
start_block_reward = 50
# 以10分钟为一个区块的间隔，210000 个块共约 4 年时间
reward_interval = 210000

def max_money():
    # 50 BTC = 50 0000 0000 Satoshis
    current_reward = 50 * 10**8
    total = 0
    while current_reward > 0:
        total += reward_interval * current_reward
        current_reward /= 2
    return total

print "Total BTC to ever be created:", max_money(), "Satoshis"
```

**输出**

```basic
Total BTC to ever be created: 2099999997690000 Satoshis
```

## [Python] 简化的工作量证明算法

> 可以任意调整难度值（按二进制 bit 数来设定，即哈希值开头多少个 bit 必须是 0）

```python
# -*- coding: utf-8 -*-
# example of proof-of-work algorithm

import hashlib
import time

max_nonce = 2 ** 32 # 4 billion

def proof_of_work(header, difficulty_bits):

    # calculate the difficulty target
    target = 2 ** (256-difficulty_bits) 

    for nonce in xrange(max_nonce):
        hash_result = hashlib.sha256(str(header)+str(nonce)).hexdigest() 

        # check if this is a valid result, below the target

        if long(hash_result, 16) < target:
            print "Success with nonce %d" % nonce 
            print "Hash is %s" % hash_result 
            return (hash_result,nonce)

    print "Failed after %d (max_nonce) tries" % nonce 
    return nonce

if __name__ == '__main__': 

    nonce = 0
    hash_result = ''

    # difficulty from 0 to 31 bits
    for difficulty_bits in xrange(32): 

        difficulty = 2 ** difficulty_bits
        print "Difficulty: %ld (%d bits)" % (difficulty, difficulty_bits) 

        print "Starting search..."

        # checkpoint the current time
        start_time = time.time()

        # make a new block which includes the hash from the previous block 
        # we fake a block of transactions - just a string
        new_block = 'test block with transactions' + hash_result

        # find a valid nonce for the new block
        (hash_result, nonce) = proof_of_work(new_block, difficulty_bits) 

        # checkpoint how long it took to find a result
        end_time = time.time()

        elapsed_time = end_time - start_time
        print "Elapsed Time: %.4f seconds" % elapsed_time 

        if elapsed_time > 0:

            # estimate the hashes per second
            hash_power = float(long(nonce)/elapsed_time)
            print "Hashing Power: %ld hashes per second" % hash_power
```

**输出**

> 输出较多，仅列出一小部分

```basic
Difficulty: 1 (0 bits)
Starting search...
Success with nonce 0
Hash is ff8253ed10b5f719d52a709a66af8cd5e2054f702e675af4ca0cae70f0988634
Elapsed Time: 0.0001 seconds
Hashing Power: 0 hashes per second
Difficulty: 2 (1 bits)
Starting search...
Success with nonce 0
Hash is 22c608547e239faf5c353e7ebd204042760b93891d1d0be9ab488d36c73c077b
Elapsed Time: 0.0000 seconds
Hashing Power: 0 hashes per second
Difficulty: 4 (2 bits)
Starting search...
Success with nonce 2
Hash is 0635f41cdb98c6e73516f84fc88da19a13a3bac6298dbfc0df5170bac93ba4dd
Elapsed Time: 0.0000 seconds
Hashing Power: 55553 hashes per second
Difficulty: 8 (3 bits)
Starting search...
Success with nonce 9
Hash is 1c1c105e65b47142f028a8f93ddf3dabb9260491bc64474738133ce5256cb3c1
Elapsed Time: 0.0001 seconds
Hashing Power: 140329 hashes per second
Difficulty: 16 (4 bits)
Starting search...
Success with nonce 25
Hash is 0f7becfd3bcd1a82e06663c97176add89e7cae0268de46f94e7e11bc3863e148
Elapsed Time: 0.0001 seconds
Hashing Power: 227456 hashes per second
Difficulty: 32 (5 bits)
Starting search...
Success with nonce 36
Hash is 029ae6e5004302a120630adcbb808452346ab1cf0b94c5189ba8bac1d47e7903
Elapsed Time: 0.0003 seconds
Hashing Power: 108085 hashes per second
Difficulty: 64 (6 bits)
Starting search...
Success with nonce 0
Hash is 0083214fa878cea749bd07bd77e92b311be876dd72f3d4924d5ae4ead54febe5
Elapsed Time: 0.0001 seconds
Hashing Power: 0 hashes per second
Difficulty: 128 (7 bits)
Starting search...
Success with nonce 26
Hash is 00f7abab177613afc42270e3f5f79ffddd694093030663b32fe26ce2a377a993
Elapsed Time: 0.0008 seconds
Hashing Power: 32956 hashes per second
Difficulty: 256 (8 bits)
```

## [Python] 列表

### 列表的遍历

```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-

if __name__ == '__main__':
    my_list = ['html', 'js', 'css', 'python']

    for i in my_list:
        print("index:%d, value:%s" % (my_list.index(i), i))

    for i in range(len(my_list)):
        print("index:%d, value:%s" % (i, my_list[i]))

    for i, val in enumerate(my_list):
        print("index:%d, value:%s" % (i, val))

    # 只是改变索引的输出，默认从 0 开始，如下设置从 2 开始
    for i, val in enumerate(my_list, 2):
        print("index:%d, value:%s" % (i, val))
```

**输出**

```basic
index:0, value:html
index:1, value:js
index:2, value:css
index:3, value:python
index:0, value:html
index:1, value:js
index:2, value:css
index:3, value:python
index:0, value:html
index:1, value:js
index:2, value:css
index:3, value:python
index:2, value:html
index:3, value:js
index:4, value:css
index:5, value:python
```

### 列表的去重

```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-

if __name__ == '__main__':
    my_list = ['html', 'js', 'css', 'python', 'cpp', 'css']
    print my_list

    my_set = set(my_list)
    my_list = [x for x in my_set]
    print my_list
```

**输出**

```basic
['html', 'js', 'css', 'python', 'cpp', 'css']
['python', 'cpp', 'html', 'css', 'js']
```

## [Python] 集合

```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import traceback

if __name__ == '__main__':
    set1 = set([1, 3, 5, 6, 7])
    set2 = set([2, 3, 4, 5, 8])

    print "set1:", set1
    print "set2:", set2

    if 4 in set1:
        print "4 in set1"
    else:
        print "4 not in set1"

    # 添加元素
    set1.add(9)
    print "set1:", set1
    set1.update([9, 10, 11])
    print "set1:", set1

    # 删除元素
    try:
        set1.remove(99)
    except Exception as ex:
        print traceback.format_exc()
    print "after remove 99, set1:", set1
    set1.discard(99)
    print "after discard 99, set1:", set1
    set1.remove(10)
    print "after remove 10, set1:", set1
    set1.discard(9)
    print "after discard 9, set1:", set1

    # 测试是否 set1 中每一个元素都在 set2 中
    if set1.issubset(set2):
        print "set1 is subset of set2"
    else:
        print "set1 is not subset of set2"

    # 测试是否 set2 中每一个元素都在 set1 中
    if set1.issuperset(set2):
        print "set1 is superset of set2"
    else:
        print "set1 is not superset of set2"

    print "set1:", set1
    print "set2:", set2
    # x ∈ set1 || x ∈ set2
    print set1.union(set2)
    # (x ∈ set1 && x ∉ set2) || (x ∈ set2 && x ∉ set1)
    print set1.symmetric_difference(set2)
    # x ∈ set1 && x ∈ set2
    print set1.intersection(set2)
    # x ∈ set1 && x ∉ set2
    print set1.difference(set2)
    print set2.difference(set1)
```

**输出**

```basic
set1: set([1, 3, 5, 6, 7])
set2: set([8, 2, 3, 4, 5])
4 not in set1
set1: set([1, 3, 5, 6, 7, 9])
set1: set([1, 3, 5, 6, 7, 9, 10, 11])
Traceback (most recent call last):
  File "d:\blog\archives\debug\debug.py", line 26, in <module>
    set1.remove(99)
KeyError: 99

after remove 99, set1: set([1, 3, 5, 6, 7, 9, 10, 11])
after discard 99, set1: set([1, 3, 5, 6, 7, 9, 10, 11])
after remove 10, set1: set([1, 3, 5, 6, 7, 9, 11])
after discard 9, set1: set([1, 3, 5, 6, 7, 11])
set1 is not subset of set2
set1 is not superset of set2
set1: set([1, 3, 5, 6, 7, 11])
set2: set([8, 2, 3, 4, 5])
set([1, 2, 3, 4, 5, 6, 7, 8, 11])
set([1, 2, 4, 6, 7, 8, 11])
set([3, 5])
set([1, 11, 6, 7])
set([8, 2, 4])
```

## [Python] range 与 xrange

```python

# -*- coding: utf-8 -*-

for i in range(2, 10, 3):
    print i

for i in range(3):
    print i

print range(2, 10, 2)


for j in xrange(2, 10, 3):
    print j

for j in xrange(3):
    print j

print xrange(2, 10, 2)
print list(xrange(2, 10, 2))
```

**输出**

```basic
2
5
8
0
1
2
[2, 4, 6, 8]
2
5
8
0
1
2
xrange(2, 10,
[2, 4, 6, 8]
```

## [Python] 字典的遍历

> **效率：**由高到低，性能要求高的地方需要注意

```python
from time import clock

l = [(x, x) for x in xrange(1000000)]
d = dict(l)

t0 = clock()
for i in d:
    t = i + d[i]
t1 = clock()

for k, v in d.iteritems():
    t = k + v
t2 = clock()

for k, v in zip(d.iterkeys(), d.itervalues()):
    t = k + v
t3 = clock()

for k, v in d.items():
    t = k + v
t4 = clock()

print t1-t0, t2-t1, t3-t2, t4-t3
```

**输出**

```basic
0.147005027863 0.151357206668 0.273842580021 0.696996068627
```

## [Python] 构造、析构

```python
class X(object):
    def __init__(self, a, b, range):
        self.a = a
        self.b = b
        self.range = range
        print('__init__ with {}, {}, {}'.format(self.a, self.b, self.range))

    def __call__(self, a, b):
        self.a = a
        self.b = b
        print('__call__ with {}, {}'.format(self.a, self.b))

    def __del__(self):
        del self.a
        del self.b
        del self.range
        print('__del__')


if __name__ == '__main__':
    x = X(1, 2, 3)
    x(3, 4)
```

**输出**

```basic
__init__ with 1, 2, 3
__call__ with 3, 4
__del__
```

## [Python] 全局变量

> - 全局变量可在函数中直接使用
> - 函数中存在同名变量，局部变量覆盖全局变量作用域
> - 函数中显示声明 global var，实现对全局变量的修改；对于列表、字典等全局变量，不需要额外的 global 声明

```python
#! /usr/bin/python

a = 1
b = [2, 3]


def func1():
    a = 11
    print "in func1 a:", a
    b[0] = 22
    print "in func1 b:", b


def func2():
    global a
    a = 11
    print "in func a:", a
    b[1] = 33
    print "in func b:", b


if __name__ == '__main__':
    print "init, a:", a
    print "init, b:", b

    func1()

    print "after func1 a:", a
    print "after func1 b:", b

    func2()

    print "after func2 a:", a
    print "after func2 b:", b
```

**输出**

```basic
init, a: 1
init, b: [2, 3]
in func1 a: 11
in func1 b: [22, 3]
after func1 a: 1
after func1 b: [22, 3]
in func a: 11
in func b: [22, 33]
after func2 a: 11
after func2 b: [22, 33]
```

## [Python] lambda 表达式

```python
# -*- coding: utf-8 -*-

# 常规使用
f = lambda x : x + 1
print f(99)

# 映射
print map(lambda x : x + 1, [1, 2, 3])
print map(lambda x: x*x, [y for y in range(10)])

# 过滤
foo = [2, 18, 9, 22, 17, 24, 8, 12, 27]
print filter(lambda x : x % 3 == 0, foo)

# 归纳
print reduce(lambda x, y : x + y, foo)

# 闭包
def add(n):
    return lambda x : x + n

print add(3)(5)
# 等价于
add_3 = add(3)
print add_3(5)
```

**输出**

```basic
100
[2, 3, 4]
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
[18, 9, 24, 12, 27]
139
8
8
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
> **Tag：**查询、批量插入、truncate

```python
# coding=utf-8
import sys
import time
import datetime
import logging
import MySQLdb
import MySQLdb.cursors

logger = logging.getLogger("latest_active_user")
logger.setLevel(logging.DEBUG)

# user_tbl
vntopnews_user = {
    "host": "10.99.0.120",
    "port": 3306,
    "user": "topnews",
    "passwd": "topnews2016",
    "db": "vntopnews_user"
}

vntopnews_latest_active_user = {
    "host": "10.99.0.120",
    "port": 3306,
    "user": "topnews",
    "passwd": "topnews2016",
    "db": "vntopnews_user"
}

# push_stat_{}
vntopnews_push_stat = {
    "host": "10.99.0.166",
    "port": 4000,
    "user": "root",
    "passwd": "",
    "db": "vntopnews_log"
}

# user_register_{}
vntopnews_user_register = {
    "host": "10.99.0.112",
    "port": 3306,
    "user": "topnews",
    "passwd": "topnews2016",
    "db": "vntopnews_ureg"
}

# user_action_log_{}
vntopnews_user_action_log = {
    "host": "10.99.0.26",
    "port": 3306,
    "user": "topnews",
    "passwd": "topnews2016",
    "db": "vntopnews_uact"
}

user_id_set = set()


def format_date(diff_days):
    date_time = datetime.datetime.utcnow() + datetime.timedelta(hours=7)
    return (date_time + datetime.timedelta(days=diff_days)).strftime("%Y%m%d")


def init_logger(log_module):
    handler = logging.FileHandler(filename="latest_active_user.log", mode='w')
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
    sql = "truncate table `vntopnews_user`.`latest_active_user_tbl`"
    logger.debug("database: %s, sql: %s", vntopnews_latest_active_user, sql)
    db, cursor = get_db_conn(vntopnews_latest_active_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()


def fetch_helper(conn, sql):
    logger.debug("database: %s, sql: %s", conn, sql)
    db, cursor = get_db_conn(conn)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret


def batch_insert_helper(user_id_set):
    if len(user_id_set) == 0:
        return
    total = 0
    try:

        db, cursor = get_db_conn(vntopnews_latest_active_user)
        batch = 100000
        values = []

        for i in user_id_set:
            values.append((i,))
            # 批量插入
            if len(values) == batch:
                total += batch
                logger.info("batch insert, count: %d", len(values))
                cursor.executemany(
                    'INSERT INTO `vntopnews_user`.`latest_active_user_tbl` (user_id) VALUES (%s)', values)
                db.commit()
                values = []

        if len(values) > 0:
            total += len(values)
            logger.info("final batch insert, count: %d", len(values))
            cursor.executemany(
                'INSERT INTO `vntopnews_user`.`latest_active_user_tbl` (user_id) VALUES (%s)', values)
            db.commit()
            values = []

        cursor.close()
        db.close()
    except MySQLdb.Error as ex:
        logger.error("MySQL Error %d: %s", ex.args[0], ex.args[1])

    return total


def from_push_stat():
    sql = """
    select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    union select distinct(user_id) from `vntopnews_log`.`push_stat_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3), format_date(-4),
               format_date(-5), format_date(-6), format_date(-7))
    users = fetch_helper(vntopnews_push_stat, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


def from_user():
    sql = """
    select id from `vntopnews_user`.`user_tbl`
    where create_time > date_add(now(), interval - 7 day)
    """
    users = fetch_helper(vntopnews_user, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['id'])


def from_user_register():
    sql = """
    select distinct(user_id) from `vntopnews_ureg`.`user_register_{}`
    union select distinct(user_id) from `vntopnews_ureg`.`user_register_{}`
    union select distinct(user_id) from `vntopnews_ureg`.`user_register_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3))
    users = fetch_helper(vntopnews_user_register, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


def from_user_action_log():
    sql = """
    select distinct(user_id) from `vntopnews_uact`.`user_action_log_{}`
    union select distinct(user_id) from `vntopnews_uact`.`user_action_log_{}`
    union select distinct(user_id) from `vntopnews_uact`.`user_action_log_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3))
    users = fetch_helper(vntopnews_user_action_log, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


if __name__ == '__main__':
    init_logger(logger)

    logger.info("begin task")

    # 清空表
    truncate_table_helper()

    # 清洗数据
    from_push_stat()
    logger.info("after from_push_stat(), size: %d", len(user_id_set))
    from_user()
    logger.info("after from_user(), size: %d", len(user_id_set))
    from_user_register()
    logger.info("after from_user_register(), size: %d", len(user_id_set))
    from_user_action_log()
    logger.info("after from_user_action_log(), size: %d", len(user_id_set))

    # 批量插入数据
    batch_insert_helper(user_id_set)

    logger.info("end task")
```

## [Python] kafka 使用

> **环境：**Python 2.7.14/kafka-python 1.4.2
>
> **源码：**
>
> - [kafka_consumer.py](https://dudebing99.github.io/blog/archives/code_snippet/kafka_consumer.py)
> - [kafka_producer.py](https://dudebing99.github.io/blog/archives/code_snippet/kafka_producer.py)
>
> **Tag：**kafka 生产者、消费者
>
> **参考：**http://kafka-python.readthedocs.io/en/master/usage.html

### 消费者

```python
from kafka import KafkaConsumer

def consume():
    # To consume latest messages and auto-commit offsets
    consumer = KafkaConsumer('test',
                             group_id='test-group',
                             bootstrap_servers=['192.168.2.99:9092'],
                             api_version=(0, 10))
    for message in consumer:
        # message value and key are raw bytes -- decode if necessary!
        # e.g., for unicode: `message.value.decode('utf-8')`
        print("%s:%d:%d: key=%s value=%s" % (message.topic, message.partition,
                                              message.offset, message.key,
                                              message.value))


if __name__ == '__main__':
    consume()
```

### 生产者

```python
from kafka import KafkaProducer
from kafka.errors import KafkaError
import json
import sys

def on_send_success(record_metadata):
    print(record_metadata.topic, record_metadata.partition, record_metadata.offset)

def on_send_error(excp):
    print('I am an errback', str(exc_info=excp))
    # handle exception

producer = KafkaProducer(bootstrap_servers=['192.168.2.99:9092'],
                         api_version=(0, 10),
                         max_block_ms=10000,
                         retries=2)

def produce():
    for i in range(3):
        message = {
            'id': i,
            'msg': 'hello world',
        }
        # produce asynchronously with callbacks
        # produce keyed messages to enable hashed partitioning
        producer.send('test', key='bingo', value=json.dumps(message)).add_callback(
            on_send_success).add_errback(on_send_error)
        # un-keyed messages
        producer.send('test', json.dumps(message)).add_callback(on_send_success).add_errback(
            on_send_error)

    # block until all async messages are sent
    producer.flush()

if __name__ == '__main__':
    produce()
```

**输出**

```basic
$ python kafka_producer.py
('test', 0, 132)
('test', 0, 133)
('test', 0, 134)
('test', 0, 135)
('test', 0, 136)
('test', 0, 137)
```

```basic
$ python kafka_consumer.py
test:0:132: key=bingo value={"msg": "hello world", "id": 0}
test:0:133: key=None value={"msg": "hello world", "id": 0}
test:0:134: key=bingo value={"msg": "hello world", "id": 1}
test:0:135: key=None value={"msg": "hello world", "id": 1}
test:0:136: key=bingo value={"msg": "hello world", "id": 2}
test:0:137: key=None value={"msg": "hello world", "id": 2}
```

## [Python] YAML 配置文件

> **环境：**Python 2.7.14/PyYAML 3.12
>
> **依赖库：**pip install pyyaml

```python
# coding: utf8

import os
import yaml
import time
from os import path


class DynFileLoader(object):
    def __init__(self, file_path, detect_interval=10):
        if not path.exists(file_path):
            raise IOError('{} not existed'.format(file_path))

        self._detect_interval = detect_interval
        self._file_path = file_path
        self._file_last_mtime = None
        self._file_content = None
        self._file_last_load_time = None

        self._reload()

    def _reload(self):
        with open(self._file_path) as f:
            now = int(time.time())
            self._file_content = f.read()
            self._file_last_mtime = now
            self._file_last_load_time = now

    def _is_file_modified(self):
        return path.getmtime(self._file_path) > self._file_last_mtime

    def _should_reload(self):
        now = int(time.time())
        if now - self._file_last_load_time > self._detect_interval:
            return self._is_file_modified()
        else:
            return False

    def get_content(self):
        if self._should_reload():
            self._reload()

        return self._file_content


class DynYamlConfig(DynFileLoader):
    def __init__(self, file_path, detect_interval=10):
        self._yaml_map = {}
        DynFileLoader.__init__(self, file_path, detect_interval)

    def _reload(self):
        with open(self._file_path) as f:
            now = int(time.time())
            self._yaml_map = yaml.safe_load(f)
            self._file_last_mtime = now
            self._file_last_load_time = now

    def get_content(self):
        if self._should_reload():
            self._reload()
        return self._yaml_map

    def get_value(self, key, default=None):
        config = self.get_content()

        if not config:
            return default

        return config.get(key, default)

if __name__ == '__main__':
    conf = DynYamlConfig('dummy.yml')

    content = conf.get_content()
    print(content)

    item = conf.get_value("product")['item']
    print(item)

    numbers = conf.get_value("numbers")
    print(numbers)

    item = conf.get_value("food")['fruit']['item']
    print(item)
```

**输出**

```basic
{'food': {'fruit': {'item': 'apple'}}, 'product': {'item': 'hello'}, 'numbers': [1, 2, 3, 4]}
hello
[1, 2, 3, 4]
apple
```

## [Python] HTTP GET/POST 请求

### urllib2

```python
# coding = utf-8
import urllib2
import json
import sys
reload(sys)
sys.setdefaultencoding('utf-8')


def get(url):
    resp = urllib2.urlopen(url=url, timeout=10)
    return resp.read()


def post(url, data):
    resp = urllib2.urlopen(url=url, data=data, timeout=10)
    return resp.read()


if __name__ == '__main__':
    data1 = get('http://45.77.40.154:9999/admin_stat/product')
    print(data1)

    payload = {
        'product': 'ahihi'
    }
    data2 = post('http://45.77.40.154:9999/admin_stat/category',
                 json.dumps(payload))
    print(data2)
```

**输出**

```basic
{"message": "success", "data": [{"name": "\u5934\u6761\u4ea7\u54c1", "value": "topnews"}, {"name": "\u5c0f\u8bf4\u6f2b\u753b", "value": "ahihi"}]}

{"message": "success", "data": [{"description": "total product data", "children": [], "name": "\u4ea7\u54c1\u603b\u4f53\u6570\u636e",
"data_cat": "total_product_data,"}]}
```

### requests

```python
# coding = utf-8
import requests
import sys
import json
reload(sys)
sys.setdefaultencoding('utf-8')

RETRY_TIMES = 1
REQUEST_TIMEOUT = 3

http_session = requests.Session()


def common_request(url, payload):
    retry_times = 0
    resp = None
    while retry_times < RETRY_TIMES:
        try:
            resp = http_session.post(
                url, data=json.dumps(payload), timeout=REQUEST_TIMEOUT)
            break
        except Exception as ex:
            print("common_request post error: %s, url=%s" % (ex, url))
            retry_times += 1

    if (resp is not None) and (resp.status_code == 200):
        r = resp.json()
        result = r.get('data', {})
        print("return resp result_len=%d" % (len(result)))
        return result
    else:
        print("common_request post error! url=%s, payload=%s" % (url, payload))
        return None


if __name__ == '__main__':
    r = requests.get('http://45.77.40.154:9999/admin_stat/product')
    print(r.content)

    payload = {'product': 'ahihi'}
    r = requests.post('http://45.77.40.154:9999/admin_stat/category',
                      json.dumps(payload))
    print('URL: ', r.url)
    print('HEADERS: ', r.headers)
    print('Content-Type: ', r.headers.get('content-type'))
    print('CODE: ', r.status_code)
    print(r.content)

    result = common_request('http://45.77.40.154:9999/admin_stat/category',
                            payload)
    print(result)
```

**输出**

```basic
{"message": "success", "data": [{"name": "\u5934\u6761\u53f7\u4f5c\u8005", "value": "top_author"}, {"name": "\u5934\u6761\u4ea7\u54c1", "value": "topnews"}, {"name": "\u5c0f\u8bf4\u6f2b\u753b", "value": "novel&comic"}]}

('URL: ', u'http://45.77.40.154:9999/admin_stat/category')
('HEADERS: ', {'Date': 'Tue, 29 May 2018 03:29:47 GMT', 'Content-Length': '171', 'Content-Type': 'application/json', 'Server': 'Werkzeug/0.12.2 Python/2.7.5'})
('Content-Type: ', 'application/json')
('CODE: ', 200)
{"message": "success", "data": [{"description": "total product data", "children": [], "name": "\u4ea7\u54c1\u603b\u4f53\u6570\u636e",
"data_cat": "total_product_data,"}]}

return resp result_len=1
[{u'data_cat': u'total_product_data,', u'description': u'total product data', u'name': u'\u4ea7\u54c1\u603b\u4f53\u6570\u636e', u'children': []}]
```

## [Python] Flask RESTful

> **环境：**Python 2.7.14/Flask 0.11.1/Flask-RESTful 0.3.5/Flask-SQLAlchemy 2.2

```python
# -*- coding:utf-8 -*-
from flask import Flask
from flask_restful import Api
from flask_restful import Resource

import os
import sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
reload(sys)
sys.setdefaultencoding('utf-8')

class IndexView(Resource):
    def post(self):
        return {'message': 'error! please use http get'}

    def get(self):
        return {'message': 'hello world'}

if __name__ == '__main__':
    app = Flask(__name__)
    api = Api(app)
    api.add_resource(IndexView, '/index')

    app.run(host='0.0.0.0', port=12345, debug=True)
```

**输出**

```basic
[root@~]# python app.py
 * Running on http://0.0.0.0:12345/ (Press CTRL+C to quit)
 * Restarting with stat
 * Debugger is active!
 * Debugger PIN: 293-571-458
127.0.0.1 - - [25/May/2018 09:34:49] "GET /index HTTP/1.1" 200 -
```

```basic
[root@~]# curl http://0.0.0.0:12345/index
{
    "message": "hello world"
}
```

## [Python] WSGI 服务器以及中间件

> **环境：**Python 2.7.4
>
> **源码：**[点此下载](https://dudebing99.github.io/blog/archives/code_snippet/wsgi_server.py)

```python
from wsgiref.simple_server import make_server

URL_PATTERNS = (
    ('hi/', 'say_hi'),
    ('hello/', 'say_hello'),
)


# 自定义中间件
class Dispatcher(object):
    def _match(self, path):
        path = path.split('/')[1]
        for url, app in URL_PATTERNS:
            if path in url:
                return app

    def __call__(self, environ, start_response):
        path = environ.get('PATH_INFO', '/')
        app = self._match(path)
        if app:
            app = globals()[app]
            return app(environ, start_response)
        else:
            start_response("404 NOT FOUND", [('Content-type', 'text/plain')])
            return ["Not Found!"]


def say_hi(environ, start_response):
    start_response("200 OK", [('Content-type', 'text/html')])
    return ["Hi!"]


def say_hello(environ, start_response):
    start_response("200 OK", [('Content-type', 'text/html')])
    return ["Hello!"]


app = Dispatcher()

httpd = make_server('', 8000, app)
print "Serving on port 8000..."
httpd.serve_forever()
```

**输出**

```basic
Serving on port 8000...
('middleware, uri: ', '/hi')
127.0.0.1 - - [28/May/2018 00:06:03] "GET /hi HTTP/1.1" 200 3
('middleware, uri: ', '/hello')
127.0.0.1 - - [28/May/2018 00:06:07] "GET /hello HTTP/1.1" 200 6
('middleware, uri: ', '/haha')
127.0.0.1 - - [28/May/2018 00:06:15] "GET /haha HTTP/1.1" 404 10
```

```basic
$ curl http://127.0.0.1:8000/hi -s
Hi!
$ curl http://127.0.0.1:8000/hello -s
Hello!
$ curl http://127.0.0.1:8000/haha -s
Not Found!
```

## [Python] 微信报警

> **环境：**Python 2.7.14
>
> **源码：**[点此下载](https://dudebing99.github.io/blog/archives/code_snippet/wechat_alarm.py)
>
> **功能：**将服务异常信息通过微信企业号 api 发送给运维员工企业微信

```python
# coding = utf-8
import urllib2
import copy
import time
import json
import sys
import getopt

ACCESS_TOKEN_URL = "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=wx290fabd94076dd5f&corpsecret=aHg0UnTDcnkQKw8sqqejxrBLPksuvauedrvOoaF0l2Q"
SEND_MESSAGE_URL = "https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token="
MSG_TEMPLATE = {
    "msgtype": "text",
    "agentid": 1,
    "text": {
        "content": "no message set"
    },
    "safe": 0
}


class Wechat(object):

    def __init__(self):
        self.last_get_token_time = 0
        self.token_expire = 0
        self.token = None

    def _get(self, url):
        resp = urllib2.urlopen(url=url, timeout=10)
        return resp.read()

    def _post(self, url, data):
        resp = urllib2.urlopen(url=url, data=data, timeout=10)
        return resp.read()

    def _get_access_token(self):
        data = self._get(ACCESS_TOKEN_URL)
        if data == None:
            print("request wechat server falied")
            return

        resp = json.loads(data)
        if resp == None:
            print("request wechat server falied")
        if resp["errcode"] == 0:
            self.token = resp["access_token"]
            self.last_get_token_time = int(time.time())
            self.token_expire = resp["expires_in"]
        else:
            print("get wechat access token error, msg: %s", resp["errmsg"])

    def send_message(self, toparty=None, touser=None, msg="no msg set"):
        if not self.is_token_valid():
            self._get_access_token()
        body = copy.deepcopy(MSG_TEMPLATE)
        text = body.setdefault("text", {})
        text["content"] = msg

        if toparty != None:
            body["toparty"] = toparty

        if touser != None:
            body["touser"] = touser

        url = SEND_MESSAGE_URL + self.token
        data = self._post(url, json.dumps(body))
        if data == None:
            print("request wechat server falied")
            return
        resp = json.loads(data)
        if resp == None:
            print("request wechat server falied")
        elif resp["errcode"] != 0:
            print("get wechat access token error, msg: %s", resp["errmsg"])
        else:
            pass

    def is_token_valid(self):
        if self.token == None:
            return False
        elif (int(time.time()) - self.last_get_token_time) > (self.token_expire - 100):
            return False
        else:
            return True


wechat = Wechat()


def notify(userids, message):
    if userids is None:
        notify_all(message)
    else:
        notify_user(userids, message)


def notify_all(message):
    wechat.send_message(toparty="2", msg=message)


def notify_user(userids, message):
    users = "|".join(userids)
    wechat.send_message(touser=users, msg=message)


def send_message(msg):
    wechat.send_message(msg)


def usage(e):
    print "python wechat_alter.py -m \"test message\" -u \"lvfei,XieJianHe\""
    if e != None:
        print str(e)


if __name__ == '__main__':

    try:
        opts, args = getopt.getopt(sys.argv[1:], "m:u:")
        message = None
        users = None
        for op, value in opts:
            if op == "-m":
                message = value
            elif op == "-u":
                users = value.split(",")
            else:
                usage(None)
                sys.exit()
        if message == None:
            raise Exception("-m must be setted")
        if users != None:
            notify_user(users, message)
        else:
            notify_all(message)
        print "Message send success"
    except Exception, e:
        usage(e)
        sys.exit()
```

