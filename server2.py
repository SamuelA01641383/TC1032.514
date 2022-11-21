from http.server import BaseHTTPRequestHandler, HTTPServer

class MyServer(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
    
    def do_GET(self):
        print("Hola desde el get")
        if "/sensor1_temp" in self.path:
            sensor1_temp = slef.path.split("=")[1] 
            #........................................
            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%H')
            collectionName = u'sensor_Samuel_${0}'.format(date)
            
            encendido = bool(random.getrandbits(1))
            
            totals_ref = db.collection(collectionName).document('totals')
            totals_doc = totals_ref.get()
            totals_data = totals_doc.to_dict()
    
            if totals_data == None:
                totals_ref.set({
                    u'total_minutos_encendido': 1 if encendido else 0,
                })
            else:
                if encendido:
                    totals_ref.update({
                        u'total.minutos_encendido': totals_data[u'total_minutos_encendido'] + 1,
                    })  
            #........................................
 
            print("La temperatura es {}".format(sensor1_temp))
        self._set_response()
        self.wfile.write("Hola este es mi super server. GET request for {}".format(self.path).encode('utf-8'))

port = 8080
server_address = ('', port)
httpd = HTTPServer(server_address, MyServer)
httpd.serve_forever()
