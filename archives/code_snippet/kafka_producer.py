from kafka import KafkaProducer
from kafka.errors import KafkaError
import json
import sys

def on_send_success(record_metadata):
    print(record_metadata.topic, record_metadata.partition, record_metadata.offset)

def on_send_error(excp):
    print('I am an errback', str(exc_info=excp))
    # handle exception

producer = KafkaProducer(bootstrap_servers=['192.168.2.99:9092'],
                         api_version=(0, 10),
                         max_block_ms=10000,
                         retries=2)

def produce():
    for i in range(3):
        message = {
            'id': i,
            'msg': 'hello world',
        }
        # produce asynchronously with callbacks
        # produce keyed messages to enable hashed partitioning
        producer.send('test', key='bingo', value=json.dumps(message)).add_callback(
            on_send_success).add_errback(on_send_error)
        # un-keyed messages
        producer.send('test', json.dumps(message)).add_callback(on_send_success).add_errback(
            on_send_error)

    # block until all async messages are sent
    producer.flush()

if __name__ == '__main__':
    produce()