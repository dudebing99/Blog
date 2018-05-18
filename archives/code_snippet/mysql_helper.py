# coding=utf-8
import sys
import time
import datetime
import random
import json
import traceback
import hashlib
import logging
import MySQLdb
import MySQLdb.cursors
import getopt
import traceback
import requests

logger = logging.getLogger("multi_app_with_single_user")
logger.setLevel(logging.INFO)

vntopnews_user = {
    "host": "101.99.0.102",
    "port": 3306,
    "user": "dev",
    "passwd": "123456",
    "db": "vntopnews_user"
}

def init_logger(log_module):
    handler = logging.FileHandler(filename="multi_app_with_single_user.log", mode='w')
    # handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
    handler.setFormatter(formatter)
    log_module.addHandler(handler)

def get_db_conn(mysql_config):
    db = MySQLdb.connect(host=mysql_config['host'],
                         port=mysql_config['port'],
                         user=mysql_config['user'],
                         passwd=mysql_config['passwd'],
                         db=mysql_config['db'],
                         cursorclass=MySQLdb.cursors.DictCursor)
    db.set_character_set('utf8mb4')
    cursor = db.cursor()
    cursor.execute('SET NAMES utf8mb4;')

    return db, cursor

def truncate_table_helper():
    sql = "truncate table `vntopnews_user`.`multi_app_user_tbl`"
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()

def fetch_helper(start, limit):
    sql = """
    select id, user_flavor_unique_id
    from `vntopnews_user`.`user_tbl`
    where id < {}
    order by id desc
    limit {}
    """.format(start, limit)
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret

def find_max_id_helper():
    sql = "select max(org_user_id) as max_id from `vntopnews_user`.`multi_app_user_tbl` order by id asc"
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret

def insert_helper(org_user_id, uniq_user_id):
    sql = """
    INSERT INTO `vntopnews_user`.`multi_app_user_tbl`
    (org_user_id, uniq_user_id)
    VALUES ({}, '{}')
    """.format(org_user_id, uniq_user_id)
    logger.debug("database: %s, sql: %s", vntopnews_user, sql)
    db, cursor = get_db_conn(vntopnews_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()

def batch_insert_helper(multi_app_user_dict):
    if len(multi_app_user_dict) == 0:
        return
    total = 0
    try:

        db, cursor = get_db_conn(vntopnews_user)
        batch = 10000
        values = []

        for i in multi_app_user_dict:
            if len(multi_app_user_dict[i]) > 1:
                for j in multi_app_user_dict[i]:
                    values.append((j, i))
                    # 批量插入
                    if len(values) == batch:
                        total += batch
                        logger.info("batch insert, count: %d", len(values))
                        cursor.executemany('INSERT INTO `vntopnews_user`.`multi_app_user_tbl` (org_user_id, uniq_user_id) VALUES (%s, %s)', values)
                        db.commit()
                        values = []

        if len(values) > 0:
            total += len(values)
            logger.info("final batch insert, count: %d", len(values))
            cursor.executemany('INSERT INTO `vntopnews_user`.`multi_app_user_tbl` (org_user_id, uniq_user_id) VALUES (%s, %s)', values)
            db.commit()
            values = []

        cursor.close()
        db.close()
    except MySQLdb.Error as ex:
        logger.error("MySQL Error %d: %s", ex.args[0], ex.args[1])

    return total

if __name__ == '__main__':
    init_logger(logger)

    logger.info("begin task")

    truncate_table_helper()

    start = 99999999999
    limit = 500000
    multi_app_user_dict = {}
    while (1):
        logger.debug("begin to fetch from user table, start:%d, limit:%d", start, limit)
        multi_app_users = fetch_helper(start, limit)
        if not multi_app_users:
            logger.info("fetch from user table, no record")
            break

        for row in multi_app_users:
            start = row['id']
            if not row['user_flavor_unique_id']:
                continue

            try:
                # logger.debug("id:%d, user_flavor_unique_id:%s", row['id'], row['user_flavor_unique_id'])
                index = row['user_flavor_unique_id'].index("_") + 1

                org_user_id = row['id']
                uniq_user_id = row['user_flavor_unique_id'][index:]
                # 多个 org_user_id 对应 一个 uniq_user_id
                if uniq_user_id in multi_app_user_dict:
                    logger.debug("old uniq_user_id, add org_user_id:%d, uniq_user_id:%s", org_user_id, uniq_user_id)
                    user_id_set = multi_app_user_dict[uniq_user_id]
                    if len(user_id_set) == 1:
                        multi_app_user_dict[uniq_user_id].add(org_user_id)
                        logger.debug("need insert twice, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                    elif len(user_id_set) == 2:
                        multi_app_user_dict[uniq_user_id].add(org_user_id)
                        logger.debug("need insert once, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                    else:
                        # 超过三条，过滤
                        logger.debug("filter, org_user_id:%d, uniq_user_id:%s, %s", org_user_id, uniq_user_id, user_id_set)
                else:
                    logger.debug("new uniq_user_id, add org_user_id:%d, uniq_user_id:%s", org_user_id, uniq_user_id)
                    multi_app_user_dict[uniq_user_id] = {org_user_id}
            except Exception as ex:
                logger.error("caught exception: %s, traceback: %s", ex, traceback.format_exc())

    total = batch_insert_helper(multi_app_user_dict)
    logger.info("Total:%d record(s)", total)

    logger.info("end task")
