[TOC]

------

##  读取文件

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

## 处理信号，服务优雅退出

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

## 自定义服务运行参数

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

## OpenSSL 客户端

> **源码路径：**[openssl_client.c](https://github.com/dudebing99/blog/blob/master/archives/code_snippet/openssl_client.c)

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



