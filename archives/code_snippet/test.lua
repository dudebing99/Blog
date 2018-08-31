mylib = require "mylib"

--日志类型
LOG_TYPE =
{
   ENUM_STRING = 0, --字符串类型
   ENUM_NUMBER = 1, --数字类型
};

--系统账户操作定义
OPER_TYPE =
{
    ENUM_ADD_FREE = 1,   --系统账户加
    ENUM_MINUS_FREE = 2  --系统账户减
}

--脚本应用账户操作类型定义
APP_OPERATOR_TYPE =
{
    ENUM_ADD_FREE_OP = 1,      --自由账户加
    ENUM_SUB_FREE_OP = 2,      --自由账户减
    ENUM_ADD_FREEZED_OP = 3,   --冻结账户加
    ENUM_SUB_FREEZED_OP = 4    --冻结账户减
}

--账户类型
ADDR_TYPE =
{
    ENUM_REGID = 1,        -- REG_ID
    ENUM_BASE58 = 2,    -- BASE58 ADDR
}

--交易类型
TX_TYPE =
{
    TX_WITHDRAW = 1,    --提现
    TX_RECHARGE= 2,     --充值
}

FREEZE_MONTH_NUM = 20       -- 冻结次数
FREEZE_PERIOD = 5    -- 冻结周期

MAX_MONEY = 100000000000000000 -- 总金额限制
FREE_MONEY = 10000000000000000 -- 自由金额限制

gCheckAccount = true -- 平衡检查 true 打开，false 关闭

gSendAccountTbl =             -- 发币地址
{
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00
}

--判断表是否为空
function TableIsEmpty(t)
    return _G.next(t) == nil
end

--判断表非空
function TableIsNotEmpty(t)
    return false == TableIsEmpty(t)
end

--[[
  功能:日志输出
  参数：
    aKey:日志类型
    bLength:日志长度
    cValue：日志
--]]
function LogPrint(aKey,bLength,cValue)
    assert(bLength >= 1,"LogPrint bLength invlaid")
    if(aKey == LOG_TYPE.ENUM_STRING) then
      assert(type(cValue) == "string","LogPrint cValue invlaid0")
    elseif(aKey == LOG_TYPE.ENUM_NUMBER)     then
        assert(TableIsNotEmpty(cValue),"LogPrint cValue invlaid1")
    else
        error("LogPrint aKey invlaid")
    end

    local logTable = {
        key = LOG_TYPE.ENUM_STRING,
        length = 0,
        value = nil
    }
    logTable.key = aKey
    logTable.length = bLength
    logTable.value = cValue
    mylib.LogPrint(logTable)
end

--[[
  功能:遍历表元素
  参数：
    t:表
    i:开始索引
--]]
function Unpack(t,i)
   i = i or 1
   if t[i] then
     return t[i],Unpack(t,i+1)
   end
end

--[[
  功能:比较两表元素是否相同
  参数：
    tDest:表1
    tSrc:表2
    start1:开始索引
  返回值：
    0:相等
    1:表1>表2
    2:表1<表2
--]]
function MemCmp(tDest,tSrc,start1)
    assert(TableIsNotEmpty(tDest),"tDest is empty")
    assert(TableIsNotEmpty(tSrc),"tSrc is empty")
    local i
    for i = #tDest,1,-1 do
        if tDest[i] > tSrc[i + start1 - 1] then
            return 1
        elseif tDest[i] < tSrc[i + start1 - 1] then
            return -1
        end
    end
    return 0
end

--[[
  功能:获取表从开始索引指定长度的元素集合
  参数：
    tbl:表
    start:开始索引
    length:长度
  返回值：
    一个新表
--]]
function GetValueFromContract(tbl,start,length)
  assert(start > 0,"GetValueFromContract start err")
  assert(length > 0,"GetValueFromContract length err")
  local newTab = {}
    local i
    for i = 0,length -1 do
        newTab[1 + i] = tbl[start + i]
    end
    return newTab
end

--[[
  功能:充值
  参数：
    无
  返回值：
    true:成功
    false:失败
  流程：
    1）获取当前交易账户，并判断是否与发币地址一致
    2）获取合约相应内容，并判断合法性
    3）将自由金额提现到系统账户下
    4）冻结相应的冻结部分
    5）扣除相应的脚本账户下的金额
--]]
function Recharge()
    -- 1）
    -- local accountTbl = {0, 0, 0, 0, 0, 0}
    -- accountTbl = {mylib.GetCurTxAccount()}
    -- assert(TableIsNotEmpty(accountTbl),"GetCurTxAccount error")

    -- assert(MemCmp(gSendAccountTbl, accountTbl,1) == 0,"Recharge address err")

    -- 2）
    local toAddrTbl = {}
    toAddrTbl = GetValueFromContract(contract, 3, 34)

    local moneyTbl = {}
    moneyTbl = GetValueFromContract(contract, 37, 8)
    local money = mylib.ByteToInteger(Unpack(moneyTbl))
    assert(money > 0,"money <= 0")

    local freeMoneyTbl = {}
    freeMoneyTbl = GetValueFromContract(contract, 45, 8)
    local freeMoney = mylib.ByteToInteger(Unpack(freeMoneyTbl))
    assert(freeMoney > 0,"freeMoney <= 0")

    local freeMonthMoneyTbl = {}
    freeMonthMoneyTbl = GetValueFromContract(contract, 53, 8)
    local freeMonthMoney = mylib.ByteToInteger(Unpack(freeMonthMoneyTbl))
    assert(freeMonthMoney > 0,"freeMonthMoney <= 0")

    local payMoneyTbl = {}
    payMoneyTbl = {mylib.GetCurTxPayAmount()}
    assert(TableIsNotEmpty(payMoneyTbl),"GetCurTxPayAmount error")
    local payMoney = mylib.ByteToInteger(Unpack(payMoneyTbl))
    assert(payMoney > 0,"payMoney <= 0")

    -- 总金额与充值金额要相等
    assert(money == payMoney, "充值金额不正确1")

    -- 总金额不能小于1,不能小于自由金额或月冻结金额
    if money < 1
        or money < freeMoney
        or money < freeMonthMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确2"), "充值金额不正确2");
        error("充值金额不正确2")
    end

    -- 三个金额，上限值检测
    if money >= MAX_MONEY
        or freeMoney >= FREE_MONEY
        or freeMonthMoney >= FREE_MONEY then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确3"), "充值金额不正确3");
        error("充值金额不正确3")
    end

    local freezeNum = FREEZE_MONTH_NUM - 1
    assert(freezeNum > 0, "月冻结总数不正确")

    -- 总金额不能小于总的月冻结金额
    local freezeMoney = freeMonthMoney * freezeNum
    if  freezeMoney < freezeNum
        or freezeMoney < freeMoney
        or money < freezeMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确4"), "充值金额不正确4");
        error("充值金额不正确4")
    end

    -- 检查充值总金额和自由金额加上冻结金额是否相等
    freezeMoney = freezeMoney + freeMoney
    if money ~= freezeMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确5"), "充值金额不正确5");
        error("充值金额不正确5")
    end

    -- 3）
    --操作系统账户的结构
    local writeOutputTbl =
    {
        addrType = 1,       --账户类型 REG_ID = 0x01,BASE_58_ADDR = 0x02,
        accountIdTbl = {},  --account id
        operatorType = 0,   --操作类型
        outHeight = 0,      --超时高度
        moneyTbl = {}       --金额
    }

    writeOutputTbl.addrType = ADDR_TYPE.ENUM_BASE58
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_ADD_FREE
    writeOutputTbl.accountIdTbl = {Unpack(toAddrTbl)}
    writeOutputTbl.moneyTbl = {Unpack(freeMoneyTbl)}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteOutput err1")

    local curHeight = 0
    curHeight = mylib.GetCurRunEnvHeight()

    -- 4）
    local appOperateTbl = {
        operatorType = 0, -- 操作类型
        outHeight = 0,    -- 超时高度
        moneyTbl = {},
        userIdLen = 0,    -- 地址长度
        userIdTbl = {},   -- 地址
        fundTagLen = 0,   -- fund tag len
        fundTagTbl = {}   -- fund tag
    }

    appOperateTbl.operatorType = APP_OPERATOR_TYPE.ENUM_ADD_FREEZED_OP
    appOperateTbl.userIdLen = 34
    appOperateTbl.userIdTbl = toAddrTbl
    appOperateTbl.moneyTbl = freeMonthMoneyTbl

    for i = 1, freezeNum do
      appOperateTbl.outHeight = curHeight + FREEZE_PERIOD * i
      assert(mylib.WriteOutAppOperate(appOperateTbl),"WriteOutAppOperate err1")
    end

    -- 5）
    writeOutputTbl.addrType = ADDR_TYPE.ENUM_REGID
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_MINUS_FREE
    writeOutputTbl.accountIdTbl = {mylib.GetScriptID()}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteOutput err2")

    return true
end

--[[
  功能:操作系统账户
  参数：
    accTbl:账户
    moneyTbl:操作金额
  返回值：
    true:成功
    false:失败
  流程：
    1）增加该系统账户金额
    2）相应地减少脚本账户金额
--]]
function WriteWithdrawal(accTbl,moneyTbl)
    --操作系统账户的结构
    local writeOutputTbl =
    {
        addrType = 1,       --账户类型 REG_ID = 0x01,BASE_58_ADDR = 0x02,
        accountIdTbl = {},  --account id
        operatorType = 0,   --操作类型
        outHeight = 0,      --超时高度
        moneyTbl = {}       --金额
    }
    --执行系统账户提现操作
    assert(TableIsNotEmpty(accTbl),"WriteWithDrawal accTbl invlaid1")
    assert(TableIsNotEmpty(moneyTbl),"WriteWithDrawal moneyTbl invlaid1")

    -- 1）
    writeOutputTbl.addrType = ADDR_TYPE.ENUM_REGID
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_ADD_FREE
    writeOutputTbl.accountIdTbl = {Unpack(accTbl)}
    writeOutputTbl.moneyTbl = {Unpack(moneyTbl)}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteWithDrawal WriteOutput err0")

    -- 2）
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_MINUS_FREE
    writeOutputTbl.accountIdTbl = {mylib.GetScriptID()}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteWithDrawal WriteOutput err1")

    return true
end

--[[
  功能:提现
  参数：
    addrType:账户类型，BASE58或REGID
  返回值：
    true:成功
    false:失败
  流程：
    1）判断账户类型
    2）获取当前交易账户
    3）获取该账户下的自由金额
    4）减掉该账户下的自由金额
    5）相应的操作系统账户
--]]
function Withdraw(addrType)
    -- 1）
    if addrType ~= ADDR_TYPE.ENUM_REGID and addrType ~= ADDR_TYPE.ENUM_BASE58 then
        error("In function Withdraw, addr type err")
    end

    -- 2）
    local accountTbl = {0, 0, 0, 0, 0, 0}
    accountTbl = {mylib.GetCurTxAccount()}
    assert(TableIsNotEmpty(accountTbl),"GetCurTxAccount error")

    local idTbl =
    {
        idLen = 0,
        idValueTbl = {}
    }
    if addrType == ADDR_TYPE.ENUM_REGID then
        idTbl.idLen = 6
        idTbl.idValueTbl = accountTbl
    else
        local base58Addr = {}
        base58Addr = {mylib.GetBase58Addr(Unpack(accountTbl))}
        assert(TableIsNotEmpty(base58Addr),"GetBase58Addr error")
        idTbl.idLen = 34
        idTbl.idValueTbl = base58Addr
    end

    -- 3）
    local freeMoneyTbl = {mylib.GetUserAppAccValue(idTbl)}
    assert(TableIsNotEmpty(freeMoneyTbl),"GetUserAppAccValue error")
    local freeMoney = mylib.ByteToInteger(Unpack(freeMoneyTbl))

    assert(freeMoney > 0,"Account balance is 0.")

    -- 4）
    local appOperateTbl = {
        operatorType = 0, -- 操作类型
        outHeight = 0,    -- 超时高度
        moneyTbl = {},
        userIdLen = 0,    -- 地址长度
        userIdTbl = {},   -- 地址
        fundTagLen = 0,   -- fund tag len
        fundTagTbl = {}   -- fund tag
    }

    appOperateTbl.operatorType = APP_OPERATOR_TYPE.ENUM_SUB_FREE_OP
    appOperateTbl.userIdLen = idTbl.idLen
    appOperateTbl.userIdTbl = idTbl.idValueTbl
    appOperateTbl.moneyTbl = freeMoneyTbl

    assert(mylib.WriteOutAppOperate(appOperateTbl),"WriteOutAppOperate err1")

    -- 5）
    assert(WriteWithdrawal(accountTbl, freeMoneyTbl), "WriteWithdrawal err")
    return true
end


function Main()
  --[[
  local i = 1

  for i = 1,#contract do
    print("contract")
    print("  ",i,(contract[i]))
  end
  --]]

  assert(#contract >= 2,"contract length err.")
  assert(contract[1] == 0xff,"Contract identification error.")

  if contract[2] == TX_TYPE.TX_RECHARGE then
    assert(#contract == 60,"recharge contract length err.")
    Recharge()
  elseif contract[2] ==  TX_TYPE.TX_WITHDRAW then
    assert(#contract == 11,"withdraw contract length err.")
    Withdraw(contract[3])
  else
    error("RUN_SCRIPT_DATA_ERR")
  end

end

Main()