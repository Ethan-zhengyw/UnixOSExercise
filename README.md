# 《UNIX操作系统设计》

## 目录

### Chapter 1. 系统概览

### Chapter 2. 内核介绍

### Chapter 3. 缓冲缓存

### Chapter 4. 文件的内部呈现形式

### Chapter 5. 文件相关的系统调用

### Chapter 6. 进程的结构

### Chapter 7. 进程控制

### Chapter 8. 进程调度和时间

### Chapter 9. 内存管理策略

### Chapter 10. I/O子系统

### Chapter 11. 进程间通信

### Chapter 12. 多处理器系统

### Chapter 13. 分布式UNIX系统

## Chapter 1. 系统概览

### 1.1 历史

#### 1969年Unix系统诞生，能够在微处理器或主机上运行。该系统可以划分为两大部分：用户可见的程序、服务；支撑程序、服务运行的操作系统。

##### Ken Thompson, Dennis Ritchie

##### 16K bytes for the system, 8K bytes for user programs, a disk of 512K bytes, and a limit of 64K bytes per file.

#### 1972～1973年，贝尔实验室的Dennis Ritchie发明了C语言

#### 1973年 Unix系统第二版，使用C重写，流行程度：25，较使用汇编语言编写的系统大大约20%～40%，并且运行速度也更慢，但可读性得到提升，是值得的

#### 1977年 Unix系统流行程度：500个Unix系统站点，其中125个在大学

#### 1978年 Dennis Ritchie与Brian W. Kernighan一起出版了第一版的《The C Programming Language》

#### 1977～1982 Unix系统第三版、第五版（AT&T正式支持），流行程度100,000

#### 系统特点总结

##### 使用高级语言C编写，更容易读、理解、修改和移植。较使用汇编语言编写的系统大大约20%～40%，并且运行速度也更慢，但可读性得到提升，是值得的

##### 有简单的用户界面，通过该界面为用户提供服务

##### 能够在该系统中通过简单的程序编译功能更复杂的程序

##### 它是一个多用户、多进程的系统，用户可以同时运行多个程序

##### 它对用户屏蔽了底层机器架构，让用户能够容易地编写支持不同机器架构的应用程序

##### 提供高效的分层文件系统实现，管理文件变得更容易

##### 文件采用一致的格式——字节流，程序读写文件变得简单

##### 提供外围设备一致的简单的接口

#### Unix系统哲学——提供简单的一致的接口、功能、模块（模块化的思想），通过这些简单模块的组合完成复杂的功能

##### 在第五版的Unix系统中，内核提供60个系统调用，其中比较常被调用的不到32个

### 1.2 系统结构

#### 分层结构

##### 1. 硬件

##### 2. 内核

##### 3. 应用程序

###### 系统预置命令

####### who、date、vi、grep、sh、wc

####### ed（简单的编辑器）、nroff（文本格式化）、comp（文本比较）

###### C程序编译相关命令

####### cc、ld（链接，二阶段编译中最后一步使用）、cpp、as（汇编相关）

###### 其它用户自定义应用程序

##### 在第五版的Unix系统中，内核提供60个系统调用，其中比较常被调用的不到32个

### 1.3 用户视角

#### 1.3.1 文件系统

##### 特点

###### 分层结构

###### 对文件数据一致的处理方式

###### 能够创建和删除文件

###### 文件能够动态增长

###### 文件数据得到保护

###### 能够以文件的方式对待外围设备

##### 分层结构

###### 文件目录树，根节点“/”，非叶子结点为目录，叶子节点为目录、普通文件、或设备文件

##### 程序对文件数据一致的处理方式

###### 程序不知道内核是怎么存储文件的，内核负责处理文件存储读取，程序只能获取到字节流，程序读取到字节流后需要自己进行解析，发现格式不对，自己要处理异常

##### 权限控制

###### 读、写、执行 & 用户/组/其它

##### 拷贝文件的执行流程

###### 命令行输入命令“copy oldfile newfile”

###### 系统调用main函数，传入参数argc、argv（argc为3，argv为列表["copy"，"oldfile"，"newfile"]）

###### 参数数目校验通过后，调用系统调用open，以read-only的方式打开oldfile，调用系统调用create创建newfile，默认权限为0666

####### 系统调用若成功，获得file descriptor（fd）

####### 系统调用若失败，则返回-1

####### main函数如果调用系统调用失败，则打印错误信息，并调用系统调用exit返回1，结束程序

###### 进入读写循环——调用系统调用read从oldfile中读取一定数目的字节，调用系统调用write将读取的字节写入newfile

####### read系统调用执行成功则返回读取的字节数目，已经读取到文件的末尾则返回0，执行失败则返回-1

####### write系统调用执行成功则返回写入的字节数目，没有内容写入则返回0，执行失败则返回-1

####### read发生异常或读取到文件末尾则循环终止

#### 1.3.2 进程环境

##### 进程相关系统调用

###### Various system calls allow processes to create new processes, terminate processes, synchronize stages of process execution, and control reaction to various events. 

###### 创建新进程（子进程与父进程具有相同的代码段、数据段）：fork

####### 三种返回情况

######## 返回-1：新进程创建失败

######## 返回0（未初始化）：新进程创建成功，程序在子进程中执行

######## 返回大于0的整数：返回子进程的进程号，程序在父进程中继续执行

####### 父进程通过系统调用fork创建子进程后，父进程与子进程的执行次序

####### 子进程从哪一行代码开始执行——fork语句的下一语句开始

###### 执行程序（切换进程的执行程序内容，用其它shell命令或shell脚本或可执行文件替换）：execl

####### execl执行成功，则不会返回，进程在新的地址空间内执行，不会继续执行原始进程的后续代码段

####### execl vs fork

######## fork是创建一个子进程，子进程与父进程所执行的代码是一致的，不同的是子进程从fork语句的下一语句开始执行

######## execl是切换正在执行的进程的执行程序，把执行代码给替换了

####### exec系统调用家族

######## int execve(const char *filename, char *const argv[], char *const envp[]);（执行程序，被以下系统调用）（执行成功则不返回）

######### execl

######### execlp

######### execle

######### execv

######### execvp

######### execvpe

######## l vs v

######### l - 参数一个一个分开（提前知道参数个数时使用）

######### v - 参数在一个数组内

######## e - 最后一个参数为环境变量数组

######## p - 在环境变量中的PATH目录中搜索目标文件，没有的话如果目标文件不在当前执行目录，必须指定绝对路径

###### 响应事件

###### 同步状态

###### wait

###### 结束进程：exit

#### 1.3.3 构建原语

##### 进程的标准输入输出（I/O重定向）

###### 标准输入

###### 标准输出

###### 标准错误输出

##### 管道

###### 进程间通信

###### 避免了临时文件的创建

### 1.4 操作系统服务

#### 进程管理

##### 进程生命周期管理

##### 进程调度

#### 内存管理

##### 进程独立内存、共享内存、交换空间

##### 分页系统 vs 交换系统

#### 文件管理

##### 文件创建、删除、修改

##### 权限控制

##### 设备以文件的形式暴露给用户

#### 允许进程访问外围设备（网卡、磁带、终端、磁盘驱动等）

### 1.5 关于硬件的假设

#### 用户态和内核态

##### 运行中的进程可分为两种模式——用户态和内核态，当用户态的进程调用系统调用时，进程进入内核态。

#### 1.5.1 中断与异常

##### 中断

###### 中断事件能够触发内核将进程的执行状态（上下文）临时保存下来，中断进程的执行，转而执行中断服务，中断服务执行完后再恢复之前被中断的进程的执行

###### 中断事件例子：外围I/O设备，系统时钟

###### 高优先级的中断可以中断低优先级的中断

##### 异常

###### 程序运行过程中发生的异常

###### 异常事件例子：非法内存访问、执行特权指令、除数为0

##### 中断 vs 异常

###### 触发：中断由进程之外的事件触发；异常是进程本身执行过程中触发

###### 处理机制相同

#### 1.5.2 处理器执行等级

##### 机器错误 > 时钟 > Disk > 网络设备 > 终端 > 软件中断

#### 1.5.3 内存管理

##### 编译程序时，编译器会为程序生成一段虚拟地址，用于存储变量、数据结构、或者函数指令，真正运行时，内核负责完成编译器生成的虚拟内存到物理内存的映射

### 1.6 小结

#### 这一章

##### 先概述了unix系统的发展历史和系统特点

##### 介绍了unix系统的整体结构

##### 从用户视角和系统的角度介绍了unix系统提供的进程管理、文件管理、内存管理服务，以及构建原语（I/O和管道）

##### 最后介绍了与硬件的假设，包括：进程的用户态和内核态、中断与异常、处理器的执行等级、虚拟内存与物理内存的映射关系
