from kafka import KafkaConsumer

def consume():
    # To consume latest messages and auto-commit offsets
    consumer = KafkaConsumer('test',
                             group_id='test-group',
                             bootstrap_servers=['192.168.2.99:9092'],
                             api_version=(0, 10))
    for message in consumer:
        # message value and key are raw bytes -- decode if necessary!
        # e.g., for unicode: `message.value.decode('utf-8')`
        print("%s:%d:%d: key=%s value=%s" % (message.topic, message.partition,
                                              message.offset, message.key,
                                              message.value))


if __name__ == '__main__':
    consume()