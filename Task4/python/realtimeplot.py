import serial
import matplotlib.pyplot as plt
import numpy as np

arduino = serial.Serial('COM3', 9600)
plt.close('all')
plt.figure()
plt.ion()
plt.show()

count = 0
tempF = np.array([])
humF = np.array([])
lightF = np.array([])

def drawplot():
    plt.title('Realtime data plot')
    plt.grid(True)
    plt.ylim(0,50)
    plt.plot(tempF, 'ro-', label="Temperature C")
    plt.plot(humF, 'b^-', label='Humidity %')
    plt.legend(loc='upper left')
    plt2 = plt.twinx()
    plt.ylim(0, 1000)
    plt2.plot(lightF, 'g*-', label='Light intensity')
    plt2.legend(loc='upper right')

while True:
    while (arduino.inWaiting()==0):
        pass
    arduino_data = arduino.readline()
    data_decoded=arduino_data.decode()
    dataArray = data_decoded.split(' ')
    temp = float(dataArray[0])
    hum = float(dataArray[1])
    light = float(dataArray[2])
    tempF = np.append(tempF, temp)
    humF = np.append(humF, hum)
    lightF = np.append(lightF, light)
    plt.cla()
    drawplot()
    #print(tempF)
    #print(humF)
    #print(light)
    print(data_decoded)
    plt.pause(0.01)
    count=count+1

arduino.close()