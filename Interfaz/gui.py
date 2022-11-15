# -*- coding: utf-8 -*-
"""
Created on Mon Oct 17 21:06:30 2022

@author: UnseR
"""

from PyQt5.QtWidgets import *
import numpy as np
import matplotlib.pyplot as plt
import csv

class Widgets(QWidget):
	def __init__(self,**kwargs):
		super(Widgets,self).__init__()
		self.vlayout=QVBoxLayout()

		self.hlayout_1=QHBoxLayout()

		self.l1=QLabel()
		self.l1.setText("Presionar boton para descripcion")
		self.hlayout_1.addWidget(self.l1)
		self.t1=QPushButton("Descripcion")
		self.t1.clicked.connect(self.descr)
		self.hlayout_1.addWidget(self.t1)

		self.vlayout.addLayout(self.hlayout_1)
		self.hlayout_2=QHBoxLayout()

		self.l2=QLabel()
		self.l2.setText("Primer Compartimiento")
		self.hlayout_2.addWidget(self.l2)

		self.t3=QPushButton("Grafica")
		self.t3.clicked.connect(self.graf_sup)
		self.hlayout_2.addWidget(self.t3)

		self.lc1max=QPushButton("Maximo")
		self.lc1max.clicked.connect(lambda: self.max_v(0))
		self.hlayout_2.addWidget(self.lc1max)

		self.lc1min=QPushButton("Minimo")
		self.lc1min.clicked.connect(lambda: self.min_v(0))
		self.hlayout_2.addWidget(self.lc1min)

		self.vlayout.addLayout(self.hlayout_2)

		self.hlayout_3=QHBoxLayout()
		self.l3=QLabel()
		self.l3.setText("Segundo Compartimiento")
		self.hlayout_3.addWidget(self.l3)

		self.btn_3=QPushButton("Grafica")
		self.btn_3.clicked.connect(self.graf_inf)
		self.hlayout_3.addWidget(self.btn_3)

		self.lc2max=QPushButton("Maximo")
		self.lc2max.clicked.connect(lambda: self.max_v(2))
		self.hlayout_3.addWidget(self.lc2max)

		self.lc2min=QPushButton("Minimo")
		self.lc2min.clicked.connect(lambda: self.min_v(2))
		self.hlayout_3.addWidget(self.lc2min)

		self.vlayout.addLayout(self.hlayout_3)

		self.setLayout(self.vlayout)

	def graf_inf(self):
		dat=self.abrir()
		plt.plot(np.linspace(0,len(dat[2]),len(dat[2])),np.array(dat[2]), label="Temperatura")
		plt.plot(np.linspace(0,len(dat[3]),len(dat[3])),np.array(dat[3]), label="Humedad")
		plt.legend()
		plt.grid(True)
		plt.title("Bloque inferior")
		plt.show()
	def descr(self):
		print("El proyecto se basa en la estimacion del valor de pi \n Por el metodo de lanzamientos aleatorios en un circulo cricusncrito en un cuadrado \n")
		print("La barra y boton del medio realizan la estimacion \n La barra selecciona el numero de lanzamientos y el boton es la orden apra hacerlo")
		print("La ultima barra y boton realizan la demostracion grafica en un cuarto de circulo \n nuevamente la barra es la cantidad de lanzamientos que se haran")

	def graf_sup(self):
		dat=self.abrir()
		plt.plot(np.linspace(0,len(dat[0]),len(dat[0])),np.array(dat[0]), label="Temp1")
		plt.plot(np.linspace(0,len(dat[1]),len(dat[1])),np.array(dat[1]),label="Hum1")
		plt.legend()
		plt.title("Bloque Superior")
		plt.grid(True)
		plt.show()
	def abrir(self):
		t1,t2,h1,h2=[],[],[],[]
		with open("TEMPLOG.TXT", 'r') as f:
			csv_input=csv.reader(f,delimiter=',',skipinitialspace=True)
			for cols in csv_input:
				t1.append(float(cols[0]))
				h1.append(float(cols[1]))
				t2.append(float(cols[2]))
				h2.append(float(cols[3]))
		return [t1,h2,t2,h2]
	def max_v(self,n):
		dat=self.abrir()
		print("Temperatura maxima: ", np.max(np.array(dat[n])), " Humedad relativa maxima: ", np.max(np.array(dat[n+1])))
	def min_v(self,n):
		dat=self.abrir()
		print("Temperatura minima: ", np.min(np.array(dat[n])), " Humedad relativa minima: ", np.min(np.array(dat[n+1])))
def window():
    app=QApplication([])
    wig=Widgets()

    wig.show()
    app.exec()
if __name__=="__main__":
    window()
