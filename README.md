# BEng-Project- 
Completed as a requisite of Biomedical Engineering degree at King's College London.

Dissertation titled "Development and Evaluation of Therapy Phantoms and their Robotic Delivery".

# Abstract

Age-related macular degeneration (AMD) is a disease of the eye which leads to blurring of vision. It is the leading cause of vision loss in adults in the UK and affects 11 million people in the US. AMD can be categorised as either dry AMD or wet AMD,
with dry AMD being more prevalent. Current treatments for wet AMD include anti-VEGF injections and engineered RPE patches made of hESCs. The project aimed to design and create a motorised syringe pump that can distribute fluids for vitreoretinal
surgery. The syringe pump housing will be created via 3D printing with a NEMA 17 stepper motor acting as the actuation machine. This prototype aims to be used to treat AMD. Developing this prototype will eliminate the need for the surgeon to
manually inject the treatment into the patient’s eye, thus reducing the limitations of the surgeon, i.e. physiological tremors. Experiments calibrating the system for different fluids, volumes, and different stepper motor settings were conducted. The distributed system was completed successfully, allowing the user to dictate and manipulate the delivery of fluids from the system. Furthermore, a prototype of a dual delivery system was developed, with which future experiments should be conducted.

![CNC](https://github.com/remytr/BEng-Project-/blob/main/Images/CNC.png?raw=true)
![Dual Syringe Pump](https://github.com/remytr/BEng-Project-/blob/main/Images/Dual%20syringe%20pump.png?raw=true)

# SensirionFlowSensor.ino
This code  has been provided by Sensirion and the code allows the Sensirion SLF3S-1300F Liquid Flow Sensor to take measurements of temperature and flow rate.

# accelStepper22.ino
This code is used to control the NEMA 17 stepper motor. It allows the user to enter a command that controls the stepper motor direction, speed, and the number of steps the motor rotates for.
