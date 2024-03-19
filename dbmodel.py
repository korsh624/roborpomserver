import math
import  time
from mysql.connector import connect, Error
class DBmanager:
    def __init__(self,host, user, passwd, name):
        self.host=host
        self.user=user
        self.passwd=passwd
        self.name=name

    def query(self, arg, values=None):
        try:
            with connect(
                    host=self.host,
                    user=self.user,
                    password=self.passwd,
                    database=self.name,
                    ssl_disabled=True,
            ) as connection:
                with connection.cursor() as cursor:
                    if values==None:
                        cursor.execute(arg)
                    else:
                        cursor.execute(arg, values)
                    connection.commit()
                    cursor.close()
                    connection.close()
        except Error as e:
            print(e)

    def fetchone(self, arg, values=None):
        try:
            with connect(
                    host=self.host,
                    user=self.user,
                    password=self.passwd,
                    database=self.name,
                    ssl_disabled=True,
            ) as connection:
                with connection.cursor() as cursor:
                    if values==None:
                        cursor.execute(arg)
                    else:
                        cursor.execute(arg, values)
                    return cursor.fetchone()
        except Error as e:
            print(e)
            return None


    def fetchall(self, arg, values=None):
        try:
            with connect(
                    host=self.host,
                    user=self.user,
                    password=self.passwd,
                    database=self.name,
                    ssl_disabled=True,
            ) as connection:
                with connection.cursor() as cursor:
                    if values==None:
                        cursor.execute(arg)
                    else:
                        cursor.execute(arg, values)
                    return cursor.fetchall()
        except Error as e:
            print(e)
            return None

    def addUser(self, name, email, hpsw):
        try:
            print(name)
            print(email)
            print(hpsw)
            user=(name, email, hpsw)
            self.query("""CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name text, email text, psw text)""")
            self.query("INSERT INTO users(name, email, psw) VALUES(%s, %s, %s)",user )
        except:
            print("Ошибка добавления пользователя в БД ")
            return False
        return True

    def getUser(self, user_id):
        try:
            res=self.fetchone(f"SELECT * FROM users WHERE id = {user_id}")
            if not res:
                print("Пользователь не найден")
                return False
            return res
        except:
            print("Ошибка получения данных из БД ")

        return False

    def getUserByEmail(self, email):
        try:
            res=self.fetchone(f"SELECT * FROM users WHERE email = '{email}'")
            if not res:
                print("Пользователь не найден")
                return False
            print(res)
            return res
        except:
            print("Ошибка получения данных из БД ")

        return False

