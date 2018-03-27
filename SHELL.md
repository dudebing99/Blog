# 统计网络状态及数目
netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'

# 统计进程打开的文件句柄数目
lsof -p PID
lsof -p PID|wc -l

# awk getline: 过滤行、改变奇数偶数行
## 打印出从 1 到 10 之间的偶数
seq 10|awk '{getline; print $0}'

## 打印出从 1 到 10 之前的奇数
seq 10|awk '{print $0; getline}'

## 交换奇数、偶数行
seq 10|awk '{getline tmp; print tmp; print $0}'
