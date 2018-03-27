# 统计网络状态及数目
netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'

# 统计进程打开的文件句柄数目
lsof -p PID
lsof -p PID|wc -l

# awk getline: 过滤行、改变奇数偶数行
### 打印出从 1 到 10 之间的偶数
seq 10|awk '{getline; print $0}'

### 打印出从 1 到 10 之前的奇数
seq 10|awk '{print $0; getline}'

### 交换奇数、偶数行
seq 10|awk '{getline tmp; print tmp; print $0}'

# for 循环的常用写法
### 数值类型
```bash
// i = i*3+1
for((i=1; i<=10; i++))
do
    echo $(expr $i \*3 + 1)
done
```

```bash
for i in $(seq 1 10)
do
    echo $(expr $i \* 3 + 1);
done
```

```bash
for i in {1..10}
do
    echo $(expr $i \* 3 + 1);
done
```

```bash
awk 'BEGIN {for(i=1; i<=10; i++) print i}'
```

### 字符串类型
```bash
for i in `ls`
do
    echo $i
done
```

```bash
for i in $*
do
    echo $i
done
```

```bash
for i in f1 f2 f3
do
    echo $i
done
```

```bash
list="rootfs usr data"
for i in $list
do
    echo $i
done
```
