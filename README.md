# Dyson_Library
A library to interface with the Dyson shortwave and longwave modules 


## Variables

Header Name | Units | Description |
----------- | ----  | ----------- |
`R_x` | Degrees | Roll angle of unit |
`P_x` | Degrees | Pitch angle of unit |
`UVA_x` | [1] | Intensity of UVA light |
`UVB_x` | [1] | Intensity of UVB light |
`White_x` | [2] | Intensity of broad spectrum white light |
`Vis_x` | lux | Intensity of visible light |
`IR_S_x` | mV [3] | Intensity of short wave IR Light |
`IR_M_x` | mV [4] | Intensity of mid wave IR Light |
`PyroT_x` |&deg;C | Temperature of Dyson module |

Notes:

For encapsulated models, all values will be attenuated by the PTFE coating. However, the transmittance should be approximately flat across the transmission range (slightly lower in the UV range), so if a mid point value is calibrated, along with a UV point, this should be sufficient to compensate for the absorption of the PTFE encapsulation.

[1] Further information about conversion to UV intensity can be found in the accompanying [App Note](http://www.vishay.com/docs/84339/designingveml6075.pdf) 

[2] 

[3] The shortwave IR measurement has a peak wavelength of ~800nm, and has an output gain of 10,000 A/V, and the sensor has a responsivity of ~1.804 uA/mW/cm^2. 0.018 V/mW/cm^2 = 0.18 V/W/m^2. Calculation can be made more accurate by pulling further information from the data sheet of the [photodiode](http://www.vishay.com/docs/84295/vemd1060x01.pdf)

[4] The shortwave IR measurement has a mean wavelength of ~1300nm, and has an output gain of 100,000 A/V, and the sensor has a responsivity of 0.9A/W, with an active area of 4.417e-9 m^2. 0.0039 V/W/m^2. Calculation can be made more accurate by pulling further information from the data sheet of the [photodiode](https://media.digikey.com/pdf/Data%20Sheets/Photonic%20Detetectors%20Inc%20PDFs/SD003-151-001.pdf)
