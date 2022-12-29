#!/usr/bin/python3
#This is the REAL ONE

#==========================================
# Firebase setup

import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import threading

# Use a service account 在本機用Key.json驗證
cred = credentials.Certificate('/NTUT/專題 - IoT/raspberry-app-connection-firebase-adminsdk-7gexa-4cd7905330.json')
firebase_admin.initialize_app(cred)
db = firestore.client()

#==========================================



import serial
import time

ser = serial.Serial('/COM3', 115200, timeout=1)
ser.flush()


        
callback_done = threading.Event()

# Create a callback on_snapshot function to capture changes
def on_snapshot(doc_snapshot, changes, read_time):
    
    docs = db.collection(u'Requests')

    for doc in doc_snapshot:
        #print(f'{doc.id}')
        #print(f'{doc.to_dict()}')
        #print("")
        
        if (f'{doc.to_dict()}'.find('False') >= 0):
            
            if (f'{doc.to_dict()}'.find('書房') >= 0):
                
                doc_id = f'{doc.id}'
                Requests_doc = f'{doc.to_dict()}'
                print(Requests_doc)
                print("")
                
                #=============================================
                # IRRawData
                
                I_location = Requests_doc.find('I')
                I_deal = Requests_doc[I_location+13:]
                
                athing = "'"
                athing_location = I_deal.index(athing)
                button_raw_data = I_deal[:athing_location]
                
                print(button_raw_data)
                print("")
                
                #=============================================
                
                #=============================================
                # path
                
                path_location = Requests_doc.find('path')
                path_deal = Requests_doc[path_location+8:]
                
                athing = "'"
                athing_location = path_deal.index(athing)
                path_no_athing = path_deal[:athing_location]
                
                path = str( "'" + path_no_athing + "'" )
                
                print(path)
                print("")
                
                #=============================================
                

                ser.write(button_raw_data.encode())
                ser.write('\n'.encode())
                print("yes")
                
                
                doc_ref = db.document(path)
                doc_ref.update({u'isCompleted': True})
                
                doc_ref = db.collection(u'Requests').document(doc_id)
                doc_ref.update({u'isCompleted': True})
                
                
                #db.collection(u'Requests').document(doc_id).delete()
                            
                print("Completed")
    
    

    print("-----")
    callback_done.set()




doc_ref = db.collection(u'Requests')

# Watch the document
doc_watch = doc_ref.on_snapshot(on_snapshot)



if __name__ == '__main__':
    
    while True:
        line = ser.readline().decode('utf-8').rstrip()
        
        if line.find('h') >= 0:
            humudity_float = float(line[10:])
            doc_ref = db.collection(u'CheatSheets').document(u'書房')
            doc_ref.update({u'humidity': humudity_float})
            print("humidity: "+str(humudity_float))
            
        if line.find('p') >= 0:
            temp_float = float(line[6:])
            doc_ref = db.collection(u'CheatSheets').document(u'書房')
            doc_ref.update({u'temperature': temp_float})
            print("temp: "+str(temp_float))
        