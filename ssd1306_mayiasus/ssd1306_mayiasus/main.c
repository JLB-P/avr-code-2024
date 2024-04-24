/*
*/

#include "ssd1306.h"
#include <util/delay.h>

int main(void)
{
  init_ssd1306();
  SSD1306_ClearScreen ();
  SSD1306_SetPosition (2, 0);//col,row
  SSD1306_DrawString ("jlb", BOLD);
  int count = 0;
  for (count = 0; count <= 122; count++)
  {
	SSD1306_SetPosition (count, 4);
	SSD1306_DrawString ("-", NORMAL);
	_delay_ms(20);
  }
  SSD1306_SetPosition (10, 8) ;
  SSD1306_DrawString ("FEIC", NORMAL);
  SSD1306_SetPosition (10, 10) ;
  SSD1306_DrawString ("2024", NORMAL | UNDERLINE);
  // return value
  return 0;
}
