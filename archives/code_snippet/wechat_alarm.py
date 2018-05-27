# coding = utf-8
import urllib2
import copy
import time
import json
import sys
import getopt

ACCESS_TOKEN_URL = "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=wx290fabd94076dd5f&corpsecret=aHg0UnTDcnkQKw8sqqejxrBLPksuvauedrvOoaF0l2Q"
SEND_MESSAGE_URL = "https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token="
MSG_TEMPLATE = {
    "msgtype": "text",
    "agentid": 1,
    "text": {
        "content": "no message set"
    },
    "safe": 0
}


class Wechat(object):

    def __init__(self):
        self.last_get_token_time = 0
        self.token_expire = 0
        self.token = None

    def _get(self, url):
        resp = urllib2.urlopen(url=url, timeout=10)
        return resp.read()

    def _post(self, url, data):
        resp = urllib2.urlopen(url=url, data=data, timeout=10)
        return resp.read()

    def _get_access_token(self):
        data = self._get(ACCESS_TOKEN_URL)
        if data == None:
            print("request wechat server falied")
            return

        resp = json.loads(data)
        if resp == None:
            print("request wechat server falied")
        if resp["errcode"] == 0:
            self.token = resp["access_token"]
            self.last_get_token_time = int(time.time())
            self.token_expire = resp["expires_in"]
        else:
            print("get wechat access token error, msg: %s", resp["errmsg"])

    def send_message(self, toparty=None, touser=None, msg="no msg set"):
        if not self.is_token_valid():
            self._get_access_token()
        body = copy.deepcopy(MSG_TEMPLATE)
        text = body.setdefault("text", {})
        text["content"] = msg

        if toparty != None:
            body["toparty"] = toparty

        if touser != None:
            body["touser"] = touser

        url = SEND_MESSAGE_URL + self.token
        data = self._post(url, json.dumps(body))
        if data == None:
            print("request wechat server falied")
            return
        resp = json.loads(data)
        if resp == None:
            print("request wechat server falied")
        elif resp["errcode"] != 0:
            print("get wechat access token error, msg: %s", resp["errmsg"])
        else:
            pass

    def is_token_valid(self):
        if self.token == None:
            return False
        elif (int(time.time()) - self.last_get_token_time) > (self.token_expire - 100):
            return False
        else:
            return True


wechat = Wechat()


def notify(userids, message):
    if userids is None:
        notify_all(message)
    else:
        notify_user(userids, message)


def notify_all(message):
    wechat.send_message(toparty="2", msg=message)


def notify_user(userids, message):
    users = "|".join(userids)
    wechat.send_message(touser=users, msg=message)


def send_message(msg):
    wechat.send_message(msg)


def usage(e):
    print "python wechat_alter.py -m \"test message\" -u \"lvfei,XieJianHe\""
    if e != None:
        print str(e)


if __name__ == '__main__':

    try:
        opts, args = getopt.getopt(sys.argv[1:], "m:u:")
        message = None
        users = None
        for op, value in opts:
            if op == "-m":
                message = value
            elif op == "-u":
                users = value.split(",")
            else:
                usage(None)
                sys.exit()
        if message == None:
            raise Exception("-m must be setted")
        if users != None:
            notify_user(users, message)
        else:
            notify_all(message)
        print "Message send success"
    except Exception, e:
        usage(e)
        sys.exit()
