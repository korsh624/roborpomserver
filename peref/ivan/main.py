from peewee import MySQLDatabase, Model, AutoField, IntegerField, CharField, SQL
from socket import socket, AF_INET, SOCK_DGRAM

db = MySQLDatabase('my_database', user='root', password='P@ssw0rd')


class Data(Model):
    id = AutoField()
    cell_id = IntegerField(column_name='cell_id')
    param_name = CharField(column_name='param_name')
    param_value = IntegerField(column_name='param_value')
    time = IntegerField(column_name='time')
    is_last = IntegerField(column_name='is_last', default=1)

    class Meta:
        database = db
        table_name = 'data'


if __name__ == '__main__':
    UDPServerSocket = socket(family=AF_INET, type=SOCK_DGRAM)
    UDPServerSocket.bind(("192.168.42.2", 8888))
    while True:
        bytesAddressPair = UDPServerSocket.recvfrom(1024)
        data = bytesAddressPair[0].decode("utf-8").split(':')
        if last := Data.get_or_none(
                Data.cell_id == data[0],
                Data.param_name == data[1],
                Data.is_last == 1
        ):
            last.is_last = 0
            last.save()
        Data.create(
            cell_id=data[0],
            param_name=data[1],
            param_value=data[2],
            time=SQL('UNIX_TIMESTAMP()')
        )
