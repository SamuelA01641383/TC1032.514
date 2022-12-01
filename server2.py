from http.server import BaseHTTPRequestHandler, HTTPServer
import firebase_admin
from firebase_admin import firestore
from firebase_admin import credentials
import time
from datetime import datetime
import random
#Application Default credentials are automatically created.
cred = credentials.Certificate('credentials.json')
app = firebase_admin.initialize_app(cred)
db = firestore.client()

class MyServer(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
    
    def do_GET(self):
        print("Hola desde el get")
        if "/sensor1_temp" in self.path:
            sensor1_temp = self.path.split("=")[1]
            print("La temperatura es {}".format(sensor1_temp))
            self._set_response()
            self.wfile.write("Hola este es mi super server. GET request for {}".format(self.path).encode('utf-8'))
            #........................................
            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%Hh%Mm%Ss')
            collectionName = u'sensores_Samuel_${0}'.format(date)
            variable = u'temperatura{0}'.format(hour)
            
            temperatura_ref = db.collection(collectionName).document('temperaturas')
            temperatura_doc = temperatura_ref.get()
            temperatura_data = temperatura_doc.to_dict()
    
            if temperatura_data == None:
                temperatura_ref.set({
                    variable : sensor1_temp 
                })
            else:
                temperatura_ref.update({
                    variable : sensor1_temp
                })
        
        elif "/sensor2_lvl" in self.path:
            sensor2_lvl = self.path.split("=")[1]
            print("La profundidad es {}".format(sensor2_lvl))
            self._set_response()
            self.wfile.write("Hola este es mi super server. GET request for {}".format(self.path).encode('utf-8'))
            #........................................
            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%Hh%Mm%Ss')
            collectionName = u'sensores_Samuel_${0}'.format(date)
            variable2 = u'profundidad{0}'.format(hour)
            
            profundidad_ref = db.collection(collectionName).document('profundidades')
            profundidad_doc = profundidad_ref.get()
            profundidad_data = profundidad_doc.to_dict()
    
            if profundidad_data == None:
                profundidad_ref.set({
                    variable2 : sensor2_lvl 
                })
            else:
                profundidad_ref.update({
                    variable2 : sensor2_lvl
                }) 
            #........................................
port = 8080
server_address = ('', port)
httpd = HTTPServer(server_address, MyServer)
httpd.serve_forever()
