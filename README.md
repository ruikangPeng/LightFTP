[![Build status](https://ci.appveyor.com/api/projects/status/0mvll9a7emrqo0a7?svg=true)](https://ci.appveyor.com/project/hfiref0x/lightftp)

# LightFTP
* Small x86-32/x64 FTP Server

# 系统要求

* x86-32/x64 POSIX 兼容操作系统，例如 Linux。
* x86-32/x64 Windows 7/8/8.1/10 和 Cygwin（请参阅 readme 的"build"部分）。
* 不需要管理员 /root 权限。防火墙中必须允许 FTP 服务器。

# 配置

保存在 fftp.conf 文件中，包含 ftpconfig 的配置部分和以及描述 User 的部分。 

#### [ftpconfig]

      port

要将服务器绑定到的端口号。
默认值: 21

      maxusers

可以同时建立的到服务器的最大连接数。
默认值: 1

      interface

要绑定到的接口IP。使用0.0.0.0可以侦听任何可用的接口。
默认值: 127.0.0.1

      external_ip

如果你在 NAT 后面运行服务器，那么把你的真实IP放在这里。
这将帮助客户端建立数据连接。
默认值: 0.0.0.0

      local_mask

本地网络的 IP 掩码。
有助于服务器区分本地客户端和Internet客户端。
默认值: 255.255.255.0

      minport
      maxport

数据连接的端口范围。你可以使用它在网关设备上配置端口转发。
默认值: 1024..65535

      logfilepath

日志文件的带有文件名的完整路径。注释或删除它以禁用日志记录。
默认值: disabled

      CATrustFile

建议保留此选项（/etc/ssl/certs/ca-certs.crt）

      ServerCertificate

SSL证书的路径。接受的格式为 x509 ASCII PEM。

      Keyfile

证书的PEM私钥文件的路径。

      KeyfilePassword

用于解密私钥的密码。

      keepalive

发送 keepalive 数据包（某些NAT可能需要这样做）。
默认值: 0 (已禁用)


# User sections

“accs”字段注释：

      banned

不允许登录

      readonly

只允许读取目录和下载文件

      upload

创建新目录，存储新文件。Append、rename and delete已禁用。
      
      admin

所有已启用的功能。

注意"pswd"字段：pswd=* 表示"任何密码都匹配"

配置文件的示例可以在源目录中以 fftp.conf 的形式找到。

# Build 

* LightFTP 提供了完整的源代码，用 C 编写；
* 为了在Windows中从源代码构建，您需要 Cygwin 环境 (https://www.cygwin.com/) 安装了 GNU make、gnutls 和 pthreads 包。还要确保 Cygwin-bin 文件夹设置在系统范围的PATH 变量中（例如PATH=SomeOfYourOtherValues；C:\Cygwin\bin；C:\Cygwin/usr/bin）。要构建可执行文件，请在 Release 目录中运行 make 命令；
* 为了在 Linux 中从源代码构建，您需要 GCC C编译器，请在 elease 目录中运行 make 命令。LigthFTP 使用 GnuTLS，请确保安装了头文件（libgnutls-dev或GnuTLS-dev）。

### Example for Linux Mint 19.3/Ubuntu 18.04

您需要安装 GCC 和 Make。如果没有安装它们，您可以将它们作为构建基本包的一部分进行安装：

      sudo apt install build-essential
      
LightFTP 使用 GnuTLS 库。在编译 LightFTP 之前需要安装它。要安装它，请打开终端并使用：

      sudo apt install gnutls-dev
	  
或者，如果不起作用，请尝试：

      sudo apt install libgnutls28-dev  
      
您可以从下载源 https://github.com/hfiref0x/LightFTP/releases 或者使用 git。

如果您想使用 git，但没有安装 git，请先安装：

      sudo apt install git
      
接下来使用以下内容:

      git clone https://github.com/hfilef0x/lightftp
      cd lightftp/Source/Release
      make
      
在此目录下你可以得到可运行二进制文件 fftp。下一步设置 ftp 配置，配置文件为 Bin/fftp.conf。设置端口、帐户、日志文件路径（如果需要，可以选择）、证书路径（如果要使用）等。

# Old Windows version

由于2.2旧的 Windows 未维护版本移到了单独的归档存储库，https://github.com/hfiref0x/LightFTP_win.

# Changelog

Changelog available at Bin/changelog.txt

# Authors

(c) 2007 - 2022 LightFTP Project
