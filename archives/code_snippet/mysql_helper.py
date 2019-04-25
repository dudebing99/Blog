# coding=utf-8
import sys
import time
import datetime
import logging
import MySQLdb
import MySQLdb.cursors

logger = logging.getLogger("latest_active_user")
logger.setLevel(logging.DEBUG)

# user_tbl
user_tbl = {
    "host": "10.10.10.10",
    "port": 3306,
    "user": "lsb",
    "passwd": "lsb",
    "db": "db"
}

latest_active_user = {
    "host": "10.10.10.10",
    "port": 3306,
    "user": "lsb",
    "passwd": "lsb",
    "db": "db"
}

# push_stat_{}
push_stat = {
    "host": "10.10.10.10",
    "port": 4000,
    "user": "lsb",
    "passwd": "lsb",
    "db": "db"
}

# user_register_{}
user_register = {
    "host": "10.10.10.10",
    "port": 3306,
    "user": "lsb",
    "passwd": "lsb",
    "db": "db"
}

# user_action_log_{}
user_action_log = {
    "host": "10.10.10.10",
    "port": 3306,
    "user": "lsb",
    "passwd": "lsb",
    "db": "db"
}

user_id_set = set()


def format_date(diff_days):
    date_time = datetime.datetime.utcnow() + datetime.timedelta(hours=7)
    return (date_time + datetime.timedelta(days=diff_days)).strftime("%Y%m%d")


def init_logger(log_module):
    handler = logging.FileHandler(filename="latest_active_user.log", mode='w')
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
    sql = "truncate table `db`.`latest_active_user_tbl`"
    logger.debug("database: %s, sql: %s", latest_active_user_tbl, sql)
    db, cursor = get_db_conn(latest_active_user)
    cursor.execute(sql)
    db.commit()
    cursor.close()
    db.close()


def fetch_helper(conn, sql):
    logger.debug("database: %s, sql: %s", conn, sql)
    db, cursor = get_db_conn(conn)
    cursor.execute(sql)
    ret = cursor.fetchall()
    cursor.close()
    db.close()
    if not ret:
        logger.warn("sql not ret")
    return ret


def batch_insert_helper(user_id_set):
    if len(user_id_set) == 0:
        return
    total = 0
    try:

        db, cursor = get_db_conn(latest_active_user)
        batch = 100000
        values = []

        for i in user_id_set:
            values.append((i,))
            # 批量插入
            if len(values) == batch:
                total += batch
                logger.info("batch insert, count: %d", len(values))
                cursor.executemany(
                    'INSERT INTO `db`.`latest_active_user_tbl` (user_id) VALUES (%s)', values)
                db.commit()
                values = []

        if len(values) > 0:
            total += len(values)
            logger.info("final batch insert, count: %d", len(values))
            cursor.executemany(
                'INSERT INTO `db`.`latest_active_user_tbl` (user_id) VALUES (%s)', values)
            db.commit()
            values = []

        cursor.close()
        db.close()
    except MySQLdb.Error as ex:
        logger.error("MySQL Error %d: %s", ex.args[0], ex.args[1])

    return total


def from_push_stat():
    sql = """
    select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    union select distinct(user_id) from `db`.`push_stat_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3), format_date(-4),
               format_date(-5), format_date(-6), format_date(-7))
    users = fetch_helper(push_stat, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


def from_user():
    sql = """
    select id from `db`.`user_tbl`
    where create_time > date_add(now(), interval - 7 day)
    """
    users = fetch_helper(user, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['id'])


def from_user_register():
    sql = """
    select distinct(user_id) from `db`.`user_register_{}`
    union select distinct(user_id) from `db`.`user_register_{}`
    union select distinct(user_id) from `db`.`user_register_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3))
    users = fetch_helper(user_register, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


def from_user_action_log():
    sql = """
    select distinct(user_id) from `db`.`user_action_log_{}`
    union select distinct(user_id) from `db`.`user_action_log_{}`
    union select distinct(user_id) from `db`.`user_action_log_{}`
    """.format(format_date(-1), format_date(-2), format_date(-3))
    users = fetch_helper(user_action_log, sql)
    if not users:
        logger.info("call fetch_helper(), no record")
    else:
        logger.info("call fetch_helper(), got %d record(s)", len(users))
        for row in users:
            user_id_set.add(row['user_id'])


if __name__ == '__main__':
    init_logger(logger)

    logger.info("begin task")

    # 清空表
    truncate_table_helper()

    # 清洗数据
    from_push_stat()
    logger.info("after from_push_stat(), size: %d", len(user_id_set))
    from_user()
    logger.info("after from_user(), size: %d", len(user_id_set))
    from_user_register()
    logger.info("after from_user_register(), size: %d", len(user_id_set))
    from_user_action_log()
    logger.info("after from_user_action_log(), size: %d", len(user_id_set))

    # 批量插入数据
    batch_insert_helper(user_id_set)

    logger.info("end task")