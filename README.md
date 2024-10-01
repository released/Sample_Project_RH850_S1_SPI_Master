# Sample_Project_RH850_S1_SPI_Master
 Sample_Project_RH850_S1_SPI_Master

update @ 2024/10/01

1. base on EVM : Y-ASK-RH850F1KM-S1-V3 , initial below function

- TAUJ0_0 : timer interval for 1ms interrupt

- CSIH1 : 

		- SC/CLK:P0_6
		
		- SI/MISO:P0_4
		
		- SO/MOSI:P0_5
		
		- SS0:P10_11
		
		- SS1:P10_12
		
		- SS2:P0_11 , default output HIGH

2. scenario : 

- change SPI chip select port and transmit data per 100 ms

- SS0 port , len is 16 , idx 0/1:0x5A , last byte/last byte -1:0xA5 , for indicator , hardware control SS0

- SS1 port , len is 8 , idx 0/1:0x5B , last byte/last byte -1:0xB5 , for indicator , hardware control SS1

- SS2 port , len is 6 , idx 0/1:0x5C , last byte/last byte -1:0xC5 , for indicator , use GPIO to control SS2


3. below is smart configurator CSIH1 setting

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/smc_CSIH1_cfg.jpg)

4. below is smart configurator CSIH1 , about SS0 setting

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/smc_CSIH1_cfg_SS0.jpg)

- SS0 port , len is 16 , idx 0/1:0x5A , last byte/last byte -1:0xA5 , for indicator , hardware control SS0

below is LA capture (CH12:SS0,CH13:CLK,CH14:MOSI,CH15:MISO)

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS0_DATA1.jpg)

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS0_DATA2.jpg)


5. below is smart configurator CSIH1 , about SS1 setting

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/smc_CSIH1_cfg_SS1.jpg)

- SS1 port , len is 8 , idx 0/1:0x5B , last byte/last byte -1:0xB5 , for indicator , hardware control SS1

below is LA capture (CH11:SS1,CH13:CLK,CH14:MOSI,CH15:MISO) 

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS1_DATA1.jpg)

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS1_DATA2.jpg)


6. below is smart configurator CSIH1 , about SS2 setting

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/smc_CSIH1_cfg_SS2.jpg)

- SS2 port , len is 6 , idx 0/1:0x5C , last byte/last byte -1:0xC5 , for indicator , use GPIO to control SS2

below is LA capture (CH10:SS2,CH13:CLK,CH14:MOSI,CH15:MISO)  

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS2_DATA1.jpg)

![image](https://github.com/released/Sample_Project_RH850_S1_SPI_Master/blob/main/SS2_DATA2.jpg)


