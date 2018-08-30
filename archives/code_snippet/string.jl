# Julia 1.0.0
# 字符、字符串的使用

ch = 'k'
println(ch)
# 转换为数值
println(Int(ch))

str = "THIS a test str"
# 换行、不换行输出
println(str)
print(str)
print(str, "\n")
# 大小写转换
println("uppercase: ", uppercase(str))
println("lowercase: ", lowercase(str))
# 子串
show(str[1:4]); println()
println(str[6:7])
println(str[end-3:end])

# julia 支持字符串插值用法
a = "sb"
b = "jiakong"
println("$a $b")
# 插值用法可以扩展到数学计算
println("2 + 22 = $(2 + 22)")

# 字符串拼接
c = string(a, " ", b)
println(c)
# 可以用 *（非 +）实现字符串拼接
d = a * " + " * b
print(d)