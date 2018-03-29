# git 客户端基本配置项
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
git config --global alias.lg "log --color --graph --pretty=format:
'%Cred%h%Creset %C(bold blue)<%an>%Creset ---%C(yellow)%d%Creset %s %Cgreen(%cr)'
 --abbrev-commit"
git config --global user.name xx
git config --global user.email xx@xxx.cn
```
