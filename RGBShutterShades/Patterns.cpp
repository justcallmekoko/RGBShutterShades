#include "Patterns.h"

void Patterns::bitRace()
{
  if (this->show_led)
  {

    this->current_itter++;
    if (this->current_itter >= this->ring_speed * this->fade_delay)
    {   
      this->current_itter = 0;
      this->current_pixel++;
      if (this->current_pixel >= STS)
        this->current_pixel = 0;



      // XY Test
      //current_x++;
  
      //if (this->current_x >= matrix_x)
      //{
      //current_x = 0;
      int temp_y = random(0, 5);

      // Don't choose the same Y as last time
      while (temp_y == current_y)
        temp_y = random(0, 5);
        
      current_y = temp_y;
      //Serial.println(current_y);
      //}

      for (int y = 0; y < matrix_y; y++)
      {
        for (int x = 0; x < matrix_x; x++)
        {
          if (mapObj.XYtable[y][x] == 1)
          {
            //strip.setPixelColor(mapObj.XY(x, y), this->Wheel((256 / 50 + this->wheel_pos) % 256));
            //strip.setPixelColor(mapObj.XY(x, y), this->Wheel((this->wheel_pos) & 255));
            //strip.setPixelColor(mapObj.XY(x, y), this->Wheel((x * 256 / 50 + this->wheel_pos) % 256));
            strip.setPixelColor(mapObj.XY(x, y), this->Wheel((x * 256 / 100 + this->wheel_pos) % 256));
          }
          else
            strip.setPixelColor(mapObj.XY(x, y), 0, 0, 0);

          
          //uint16_t i = this->current_pixel;
          //uint16_t i = mapObj.XY(current_x, current_y);
          
          //strip.setPixelColor(i, Wheel(((strip.numPixels() / i)+current_itter) & 255));
          //strip.setPixelColor(i, Wheel((i+current_itter) & 255));
          //strip.setPixelColor(i, this->Wheel((256 / 50 + this->wheel_pos) % 256));
          //if (current_x != 0)
          //  strip.setPixelColor(mapObj.XY(current_x - 1, current_y), 0, 0, 0);
        }
      }

      for (int y = 0; y < matrix_y; y++)
      {
        for (int x = 0; x < matrix_x; x++)
        {
          if (mapObj.XYtable[y][x] == 1)
          {
            mapObj.XYtable[y][x] = 0;
            if (x < matrix_x - 1){
              mapObj.XYtable[y][x + 1] = 1;
              x++;
            }
          }
        }
      }

      uint16_t i = mapObj.XY(0, current_y);
      //strip.setPixelColor(i, this->Wheel((256 / 50 + this->wheel_pos) % 256));
      mapObj.XYtable[current_y][0] = 1;
    }

    
    //strip.setPixelColor(0, 0, 255, 0);
    //strip.setPixelColor(11, 255, 0, 0);
    strip.show();
    
    this->current_fade_itter++;

    this->wheel_pos = this->wheel_pos - this->wheel_speed;
    if (this->wheel_pos < 0)
      this->wheel_pos = 255;
    
    delay(ring_speed);
  }
}

/*
// Fill the dots one after the other with a color
void Patterns::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
*/

void Patterns::Dash(int r, int g, int b)
{  
  if (this->show_led)
  {
    
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      
      for(uint16_t l = 0; l < STS; l++) {
        if (this->redStates2[l] > 1 || this->greenStates2[l] > 1 || this->blueStates2[l] > 1) {
          strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
          
          if (this->redStates2[l] > 1) {
            this->redStates2[l] = this->redStates2[l] * this->fadeRate;
          } else {
            this->redStates2[l] = 0;
          }
          
          if (this->greenStates2[l] > 1) {
            this->greenStates2[l] = this->greenStates2[l] * this->fadeRate;
          } else {
            this->greenStates2[l] = 0;
          }
          
          if (this->blueStates2[l] > 1) {
            this->blueStates2[l] = this->blueStates2[l] * this->fadeRate;
          } else {
            this->blueStates2[l] = 0;
          }
          
        } else {
          strip.setPixelColor(l, 0, 0, 0);
        }
      }
    }

    this->current_itter++;
    if (this->current_itter >= this->ring_speed * this->fade_delay)
    {   
      this->current_itter = 0;
      this->current_pixel++;
      if (this->current_pixel >= STS)
        this->current_pixel = 0;



      // XY Test
      current_x++;
  
      if (this->current_x >= matrix_x)
      {
        current_x = 0;
        int temp_y = random(0, 5);

        // Don't choose the same Y as last time
        while (temp_y == current_y)
          temp_y = random(0, 5);
          
        current_y = temp_y;
        //Serial.print(" Y: ");
        //Serial.println(current_y);
      }
    
    
      //Serial.print("X: ");
      //Serial.print(current_x);
      //Serial.print(" Y: ");
      //Serial.println(current_y);

      // End XY Test
        
      //uint16_t i = this->current_pixel;
      uint16_t i = mapObj.XY(current_x, current_y);
      if (this->redStates2[i] < 1 && this->greenStates2[i] < 1 && this->blueStates2[i] < 1) {
        this->redStates2[i] = r;
        this->greenStates2[i] = g;
        this->blueStates2[i] = b;
      }
    }
    //strip.setPixelColor(0, 0, 255, 0);
    //strip.setPixelColor(11, 255, 0, 0);
    strip.show();
    
    this->current_fade_itter++;
    
    //delay(10);
  }
}

// Adjust values specific for a certain pattern
void Patterns::initPattern(uint8_t pattern)
{
  /*if (pattern == PULSE)
  {
    this->fade_delay = 20;
    this->fadeRate = 0.90;
    //this->Pulse(255, 255, 0);
  }*/
  if (pattern == TWINKLE)
  {
    this->fade_delay = 20;
    this->fadeRate = 0.80;
    this->Twinkle();
  }
  else if (pattern == TRACER)
  {
    this->ring_speed = 3;
    this->fade_delay = 2;
    this->fadeRate = 0.95;
    this->Tracer2(255, 0, 255);
  }
  else if (pattern == DASH)
  {
    this->ring_speed = 3;
    this->fade_delay = 2;
    this->fadeRate = 0.92;
    this->Dash(0, 170, 255);
  }
  else if (pattern == FALLING_RAINBOW)
  {
    this->ring_speed = 10;
    this->fade_delay = 2;
    this->fadeRate = 0.90;
    this->wheel_speed = 1;
    this->Rainbow2();
  }
  else if (pattern == RADIATE_RAINBOW)
  {
    this->ring_speed = 10;
    this->fade_delay = 2;
    this->fadeRate = 0.90;
    this->wheel_speed = 1;
    this->Rainbow3();
  }
  else if (pattern == BIT_RACE)
  {
    this->ring_speed = 4;
    this->fade_delay = 2;
    this->fadeRate = 0.90;
    this->bitRace();
  }
  else if (pattern == XS)
  {
    this->Xs();
  }
  else if (pattern == HEARTS)
  {
    this->Hearts();
  }
}

void Patterns::Hearts()
{
  strip.setPixelColor(60, 255, 0, 100);
  strip.setPixelColor(55, 255, 0, 100);
  strip.setPixelColor(54, 255, 0, 100);
  strip.setPixelColor(53, 255, 0, 100);
  strip.setPixelColor(31, 255, 0, 100);
  strip.setPixelColor(32, 255, 0, 100);
  strip.setPixelColor(33, 255, 0, 100);
  strip.setPixelColor(34, 255, 0, 100);
  strip.setPixelColor(35, 255, 0, 100);
  strip.setPixelColor(24, 255, 0, 100);
  strip.setPixelColor(25, 255, 0, 100);
  strip.setPixelColor(26, 255, 0, 100);
  strip.setPixelColor(27, 255, 0, 100);
  strip.setPixelColor(28, 255, 0, 100);
  strip.setPixelColor(1, 255, 0, 100);
  strip.setPixelColor(3, 255, 0, 100);
  strip.setPixelColor(65, 255, 0, 100);
  strip.setPixelColor(48, 255, 0, 100);
  strip.setPixelColor(47, 255, 0, 100);
  strip.setPixelColor(46, 255, 0, 100);
  strip.setPixelColor(42, 255, 0, 100);
  strip.setPixelColor(41, 255, 0, 100);
  strip.setPixelColor(40, 255, 0, 100);
  strip.setPixelColor(39, 255, 0, 100);
  strip.setPixelColor(38, 255, 0, 100);
  strip.setPixelColor(19, 255, 0, 100);
  strip.setPixelColor(18, 255, 0, 100);
  strip.setPixelColor(17, 255, 0, 100);
  strip.setPixelColor(16, 255, 0, 100);
  strip.setPixelColor(15, 255, 0, 100);
  strip.setPixelColor(10, 255, 0, 100);
  strip.setPixelColor(12, 255, 0, 100);
  strip.show();
}

/*
// Pulse a color on and off
void Patterns::Pulse(int r, int g, int b)
{
  if (this->show_led)
  {
    float modifier = 0;
    
    if (this->current_fade_itter > this->fade_delay)
    {
      if (this->increasing)
        modifier = 2 - this->fadeRate;
      else
        modifier = this->fadeRate;
  
      for(uint16_t l = 0; l < Pixels; l++)
      {
        this->redStates[l] = this->redStates[l] * modifier;
        
  
        this->greenStates[l] = this->greenStates[l] * modifier;
  
        
        this->blueStates[l] = this->blueStates[l] * modifier;
  
        if (this->redStates[l] < 1 && this->greenStates[l] < 1 && this->blueStates[l] < 1)
        {
          this->increasing = true;
          this->redStates[l] = r * 0.0037;
          this->greenStates[l] = g * 0.0037;
          this->blueStates[l] = b * 0.0037;
        }
        else if (this->redStates[l] >= 255 || this->greenStates[l] >= 255 || this->blueStates[l] >= 255)
        {
          this->increasing = false;
          this->redStates[l] = r;
          this->greenStates[l] = g;
          this->blueStates[l] = b;
        }
        
        strip.setPixelColor(l, this->redStates[l], this->greenStates[l], this->blueStates[l]);
      }
      
      this->current_fade_itter = 0;
  
      /*
      Serial.print(redStates[0]);
      Serial.print(" ");
      Serial.print(greenStates[0]);
      Serial.print(" ");
      Serial.println(blueStates[0]); 
      */  
      /* 
    }
    
    this->current_fade_itter++;
    
    strip.show();
  }
}*/


// idefk rainbow
/*
void Patterns::Rainbow1()
{
  uint16_t i, j;
  this->current_itter++;
  if (current_itter >= 256)
    current_itter = 0;
    
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i+current_itter) & 255));
  }
  strip.show();
  delay(ring_speed);
}
*/

// Falling rainbow
void Patterns::Rainbow2()
{
  this->current_itter++;
  if (current_itter >= 256)
    current_itter = 0;
    
  for(uint16_t i = 0; i < matrix_y; i++) {
    for (int x = 0; x < matrix_x; x++)
      strip.setPixelColor(mapObj.XY(x, i), Wheel(((strip.numPixels() / (i + 1))+current_itter) & 255));
  }
  strip.show();
  delay(ring_speed);
}

// Radiating rainbow
void Patterns::Rainbow3()
{
  for(uint16_t i = 0; i < matrix_y; i++) {
    for (int x = 0; x < matrix_x; x++)
      strip.setPixelColor(mapObj.XY(x, i), this->Wheel(((i * x) * 256 / 50 + this->wheel_pos) % 256));
  }
      
  strip.show();
  delay(ring_speed);

  this->wheel_pos = this->wheel_pos + this->wheel_speed;
  if (this->wheel_pos >= 256)
    this->wheel_pos = 0;
}

void Patterns::resetWheel()
{
  for(uint16_t l = 0; l < Pixels; l++) {
    this->redStates2[l] = 0;
    this->greenStates2[l] = 0;
    this->blueStates2[l] = 0;
    //this->redStates[l] = 0;
    //this->greenStates[l] = 0;
    //this->blueStates[l] = 0;
    strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
    //strip.setPixelColor(l, this->redStates[l], this->greenStates[l], this->blueStates[l]);
  }
  strip.show();
}


void Patterns::Twinkle()
{
  if (this->show_led)
  {
    this->current_itter++;
    if (this->current_itter >= this->ring_speed)
    {
      this->current_itter = 0;
  
      if (random(this->max_interval) != -1) {
        uint16_t x = random(matrix_x);
        uint16_t y = random(matrix_y);
        uint8_t i = mapObj.XY(x, y);
        if (this->redStates2[i] < 1 && this->greenStates2[i] < 1 && this->blueStates2[i] < 1) {
          this->redStates2[i] = random(256);
          this->greenStates2[i] = random(256);
          this->blueStates2[i] = random(256);
        }
      }
    }
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      for(uint16_t l = 0; l < Pixels; l++) {
        if (this->redStates2[l] > 1 || this->greenStates2[l] > 1 || this->blueStates2[l] > 1) {
          strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
          
          if (this->redStates2[l] > 1) {
            this->redStates2[l] = this->redStates2[l] * this->fadeRate;
          } else {
            this->redStates2[l] = 0;
          }
          
          if (this->greenStates2[l] > 1) {
            this->greenStates2[l] = this->greenStates2[l] * this->fadeRate;
          } else {
            this->greenStates2[l] = 0;
          }
          
          if (this->blueStates2[l] > 1) {
            this->blueStates2[l] = this->blueStates2[l] * this->fadeRate;
          } else {
            this->blueStates2[l] = 0;
          }
          
        } else {
          strip.setPixelColor(l, 0, 0, 0);
        }
      }
    }
    this->current_fade_itter++;
    strip.show();
  }
}


// mapObj.ShadesTable
/*
void Patterns::Tracer(int r, int g, int b)
{  
  if (this->show_led)
  {
    this->current_itter++;
    if (this->current_itter >= this->ring_speed * this->fade_delay)
    {   
      this->current_itter = 0;
      this->current_pixel++;
      if (this->current_pixel >= Pixels)
        this->current_pixel = 0;



      // XY Test
      current_x++;
  
      if (this->current_x >= matrix_x)
      {
        current_x = 0;
        current_y++;
      }
    
      if (this->current_y >= matrix_y)
        current_y = 0;
    
      //Serial.print("X: ");
      //Serial.print(current_x);
      //Serial.print(" Y: ");
      //Serial.println(current_y);

      // End XY Test
        
      uint16_t i = this->current_pixel;
      if (this->redStates[i] < 1 && this->greenStates[i] < 1 && this->blueStates[i] < 1) {
        this->redStates[i] = r;
        this->greenStates[i] = g;
        this->blueStates[i] = b;
      }
    }
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      
      for(uint16_t l = 0; l < Pixels; l++) {
        if (this->redStates[l] > 1 || this->greenStates[l] > 1 || this->blueStates[l] > 1) {
          strip.setPixelColor(l, this->redStates[l], this->greenStates[l], this->blueStates[l]);
          
          if (this->redStates[l] > 1) {
            this->redStates[l] = this->redStates[l] * this->fadeRate;
          } else {
            this->redStates[l] = 0;
          }
          
          if (this->greenStates[l] > 1) {
            this->greenStates[l] = this->greenStates[l] * this->fadeRate;
          } else {
            this->greenStates[l] = 0;
          }
          
          if (this->blueStates[l] > 1) {
            this->blueStates[l] = this->blueStates[l] * this->fadeRate;
          } else {
            this->blueStates[l] = 0;
          }
          
        } else {
          strip.setPixelColor(l, 0, 0, 0);
        }
      }
    }
    //strip.setPixelColor(0, 0, 255, 0);
    //strip.setPixelColor(11, 255, 0, 0);
    strip.show();
    
    this->current_fade_itter++;
    
    //delay(10);
  }
}
*/


void Patterns::Tracer2(int r, int g, int b)
{  
  if (this->show_led)
  {
    this->current_itter++;
    if (this->current_itter >= this->ring_speed * this->fade_delay)
    {   
      this->current_itter = 0;
      this->current_pixel++;
      if (this->current_pixel >= STS)
        this->current_pixel = 0;



      // XY Test
      current_x++;
  
      if (this->current_x >= matrix_x)
      {
        current_x = 0;
        current_y++;
      }
    
      if (this->current_y >= matrix_y)
        current_y = 0;
    
      //Serial.print("X: ");
      //Serial.print(current_x);
      //Serial.print(" Y: ");
      //Serial.println(current_y);

      // End XY Test
        
      //uint16_t i = this->current_pixel;
      uint16_t i = mapObj.XY(current_x, current_y);
      if (this->redStates2[i] < 1 && this->greenStates2[i] < 1 && this->blueStates2[i] < 1) {
        this->redStates2[i] = r;
        this->greenStates2[i] = g;
        this->blueStates2[i] = b;
      }
    }
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      
      for(uint16_t l = 0; l < STS; l++) {
        if (this->redStates2[l] > 1 || this->greenStates2[l] > 1 || this->blueStates2[l] > 1) {
          strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
          
          if (this->redStates2[l] > 1) {
            this->redStates2[l] = this->redStates2[l] * this->fadeRate;
          } else {
            this->redStates2[l] = 0;
          }
          
          if (this->greenStates2[l] > 1) {
            this->greenStates2[l] = this->greenStates2[l] * this->fadeRate;
          } else {
            this->greenStates2[l] = 0;
          }
          
          if (this->blueStates2[l] > 1) {
            this->blueStates2[l] = this->blueStates2[l] * this->fadeRate;
          } else {
            this->blueStates2[l] = 0;
          }
          
        } else {
          strip.setPixelColor(l, 0, 0, 0);
        }
      }
    }
    //strip.setPixelColor(0, 0, 255, 0);
    //strip.setPixelColor(11, 255, 0, 0);
    strip.show();
    
    this->current_fade_itter++;
    
    //delay(10);
  }
}

void Patterns::Xs()
{
  strip.setPixelColor(0, 255, 0, 0);
  strip.setPixelColor(27, 255, 0, 0);
  strip.setPixelColor(33, 255, 0, 0);
  strip.setPixelColor(53, 255, 0, 0);
  strip.setPixelColor(62, 255, 0, 0);
  strip.setPixelColor(58, 255, 0, 0);
  strip.setPixelColor(55, 255, 0, 0);
  strip.setPixelColor(25, 255, 0, 0);
  strip.setPixelColor(4, 255, 0, 0);
  strip.setPixelColor(63, 255, 0, 0);
  strip.setPixelColor(48, 255, 0, 0);
  strip.setPixelColor(40, 255, 0, 0);
  strip.setPixelColor(16, 255, 0, 0);
  strip.setPixelColor(13, 255, 0, 0);
  strip.setPixelColor(9, 255, 0, 0);
  strip.setPixelColor(18, 255, 0, 0);
  strip.setPixelColor(46, 255, 0, 0);
  strip.setPixelColor(67, 255, 0, 0);
  strip.show();
}

uint32_t Patterns::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
