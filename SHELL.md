# 统计网络状态及数目
netstat -n|awk '/^tcp/ {++state[$NF]} END {for(i in state) print i, state[i]}'

# 统计进程打开的文件句柄数目
lsof -p PID
lsof -p PID|wc -l
