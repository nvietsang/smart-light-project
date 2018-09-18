import serial #Serial imported for Serial communication
import time #Required to use delay functions

def send_email():
    import smtplib
    server = smtplib.SMTP('smtp.gmail.com', 587)

    server.ehlo()

    server.starttls()

    #Next, log in to the server
    server.login("nvietsang@gmail.com", "4119978418")

    #Send the mail
    msg = "WARNING!" # The /n separates the message from the headers
    server.sendmail("nvietsang@gmail.com", "nvietsang@icloud.com", msg)

if __name__ == '__main__':
    ArduinoSerial = serial.Serial('/dev/cu.usbmodem1411',9600) #Create Serial port object called arduinoSerialData
    time.sleep(2) #wait for 2 secounds for the communication to get established
    
    print ('Waiting for Arduino...')
    while 1:
        msg_from_arduino = ArduinoSerial.read()
        #print ('Message: ', msg_from_arduino)
        if msg_from_arduino == ';'.encode():
            send_email() 
            print('Sent email!')
            print ('Waiting for Arduino...')
  