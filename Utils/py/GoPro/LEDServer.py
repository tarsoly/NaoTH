import RPi.GPIO as GPIO
import socket
import time
import json

class StatusMonitor():
  def __init__(self):
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
  def sendMessage(self, msg):
    self.sock.sendto(msg.encode(), ("localhost", 8000))
    
  def setConnectingToGoPro(self, delay = 1):
    self.sendMessage('{{"yellow":"blink", "time":"{}"}}'.format(delay))
    
  def setConnectedToGoPro(self, delay = 1):
    self.sendMessage('{{"yellow":"on", "time":"{}"}}'.format(delay))
    
  def setReceivedMessageFromGC(self, delay = 1):
    self.sendMessage('{{"green":"on", "delay":"{}"}}'.format(delay))
    
  def setDidntReceivedMessageFromGC(self, delay = 1):
    self.sendMessage('{{"green":"off", "delay":"{}"}}'.format(delay))
    
  def setReceivedMessageFromGC(self, delay = 1):
    self.sendMessage('{{"green":"on", "delay":"{}"}}'.format(delay))
  
  def setRecordingStart(self, delay = 1):
    self.sendMessage('{{"red":"on", "delay":"{}"}}'.format(delay))
    
  def setRecordingStop(self, delay = 0):
    self.sendMessage('{{"red":"off", "delay":"{}"}}'.format(delay))
  
    
class LED():
  def __init__(self, PIN):
    self.PIN = PIN

    GPIO.setup(self.PIN, GPIO.OUT)
    
    self.set(False)
    self.blink_delay = 0
    
  def set(self, state):
    self.state = state
    self.time = time.time()
    
    if self.state:
      GPIO.output(self.PIN,GPIO.HIGH)
    else:
      GPIO.output(self.PIN,GPIO.LOW)
      
  def blink(self, delay = 1.0):
    self.blink_delay = delay
    if self.blink_delay <= 0:
      self.blink_delay = 0
    else:
      self.set(self.state)

  def update(self):
    print ('update: ', self.time, self.blink_delay)
    if self.blink_delay > 0 and time.time() > self.time + self.blink_delay:
      self.set(not self.state)
      
    
class LEDServer():
  def __init__(self):
  
    GPIO.setmode(GPIO.BCM)
    
    self.leds = {
      "red": LED(8),
      "yellow": LED(7),
      "green": LED(24)
    }
    
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    self.sock.bind(("localhost", 8000))
    self.sock.settimeout(1.0)
    
    self.message_validity_time = 0

  def reset(self):
    for name in self.leds:
      self.leds[name].set(False)
    
  def update(self):
    for name in self.leds:
      self.leds[name].update()
    
  def run(self):
    while True:
      print ('\nwaiting to receive message')
      try:
        data, address = self.sock.recvfrom(4096)
        
        print ('received %s bytes from %s' % (len(data), address))
        print (data.decode('utf-8'))
        
        # parse the message
        msg = json.loads(data.decode('utf-8'))
        
        for name in msg:
          if name in self.leds:
            if msg[name] == 'on':
              self.leds[name].set(True)
            elif msg[name] == 'off':
              self.leds[name].set(False)
            elif msg[name] == 'blink':
              self.leds[name].blink()
        
        if 'time' in msg and float(msg['time']) > 0:
          self.message_validity_time = time.time() + float(msg['time'])
        else:
          self.message_validity_time = 0
          
      except socket.timeout:
        if self.message_validity_time > 0 and time.time() > self.message_validity_time:
          self.reset()
        else:
          self.update()

statusMonitor = StatusMonitor()

if __name__ == "__main__":
  server = LEDServer()
  server.run()