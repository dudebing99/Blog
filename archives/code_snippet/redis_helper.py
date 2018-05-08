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
