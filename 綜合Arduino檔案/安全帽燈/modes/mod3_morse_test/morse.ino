#define FREQ 3000

void MORSE(int  NUM) {
  for (int i = 0; i < 5; i++) { 
  switch (NUM) {

    case 0:
      
        if (ms[0][i]==0){
        tone(TONEPIN, FREQ,50);
        delay(500);
        }
        if (ms[0][i]==1){
        tone(TONEPIN, FREQ,300);
        
        }

           case 1:
             case 2:

          }



  }
