#include "Patterns.h"

// Fill the dots one after the other with a color
void Patterns::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void Patterns::Dash(int r, int g, int b)
{  
  if (this->show_led)
  {
    
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      
      for(uint16_t l = 0; l < SHADES_TABLE_SIZE; l++) {
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
      if (this->current_pixel >= SHADES_TABLE_SIZE)
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

void Patterns::initPattern(uint8_t pattern)
{
  if (pattern == COLOR_WIPE)
  {
    this->fade_delay = 20;
    this->fadeRate = 0.90;
  }
  else if (pattern == PULSE)
  {
    this->fade_delay = 20;
    this->fadeRate = 0.90;
    this->Pulse(this->clicon[0], this->clicon[1], this->clicon[2]);
  }
  else if (pattern == TWINKLE)
  {
    this->fade_delay = 20;
    this->fadeRate = 0.80;
    this->Twinkle();
  }
  else if (pattern == TRACER)
  {
    this->ring_speed = 6;
    this->fade_delay = 2;
    this->fadeRate = 0.985;
    this->Tracer2(this->purple[0], this->purple[1], this->purple[2]);
  }
  else if (pattern == DASH)
  {
    this->ring_speed = 3;
    this->fade_delay = 2;
    this->fadeRate = 0.92;
    this->Dash(this->serving[0], this->serving[1], this->serving[2]);
  }
}

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
    }
    
    this->current_fade_itter++;
    
    strip.show();
  }
}

void Patterns::resetWheel()
{
  for(uint16_t l = 0; l < Pixels; l++) {
    this->redStates[l] = 0;
    this->greenStates[l] = 0;
    this->blueStates[l] = 0;
    strip.setPixelColor(l, this->redStates[l], this->greenStates[l], this->blueStates[l]);
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
        uint16_t i = random(Pixels);
        if (this->redStates[i] < 1 && this->greenStates[i] < 1 && this->blueStates[i] < 1) {
          this->redStates[i] = random(256);
          this->greenStates[i] = random(256);
          this->blueStates[i] = random(256);
        }
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
    this->current_fade_itter++;
    strip.show();
  }
}

// mapObj.ShadesTable

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


void Patterns::Tracer2(int r, int g, int b)
{  
  if (this->show_led)
  {
    this->current_itter++;
    if (this->current_itter >= this->ring_speed * this->fade_delay)
    {   
      this->current_itter = 0;
      this->current_pixel++;
      if (this->current_pixel >= SHADES_TABLE_SIZE)
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
      
      for(uint16_t l = 0; l < SHADES_TABLE_SIZE; l++) {
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
