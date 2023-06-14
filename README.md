# ch55xduino_uc1701_lcd9648  
based on ch55xduino(https://github.com/DeqingSun/ch55xduino)  
drive lcd9648(uc1701) at ch55xduino with ch552  
![IMG_20230614_220541](https://github.com/coinight/ch55xduino_uc1701_lcd9648/assets/32589807/fb3fba39-7ddd-47a2-96c2-3046b09a2cd4)  
test on ch552 board  
PIN_RST -> P11  
PIN_RS  -> P34  
PIN_CS  -> P33  
    
## functions:  
&ensp;oled_pixelat(x,y,color);  
&ensp;oled_pageat(x, page, data_u8);  
&ensp;oled_characterat(x, page, character);  
&ensp;oled_charactersat(x, page, arr,characters);  
  
## !!!caution!!!  
characters is {0,1,2,3,4,5,6,7,8,9,:,-,.,T,A,°C,U}  
if oled_characterat(1,1,12)  
then '.' will be drawn from (1,8) to (9,24)  
Because of the low memory, ch552 can't use framebuf to memory which page is drawn,so oled_pixelat will change a whole page,  
e.g.   
&ensp;&ensp;oled_pixelat(0,0,1);  
&ensp;&ensp;oled_pixelat(0,1,1);  
the oled will only show pixel at (0,1) not both (0,0) and (0,1)  
