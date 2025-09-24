void SOS_beep() {
 if (start_say == 1) {
    Serial.println(ring);
    between_ring = 270;
    if (T < millis() - between_ring) {
      switch (ring) {
        case 1: tone(11, 2500, 80); Serial.println("wwwwww");     break;
        case 2: tone(11, 2500, 80);                     break;
        case 3: tone(11, 2500, 80);                     break;
        case 4: tone(11, 2500, 250);                     break;
        case 5: tone(11, 2500, 250);                     break;
        case 6: tone(11, 2500, 250);                     break;
        case 7: tone(11, 2500, 80);                     break;
        case 8: tone(11, 2500, 80);                     break;
        case 9: tone(11, 2500, 80);                     break;
  
        case 14: ring = 0;             break;
      }
      T = millis();
      if (ring < 14) {
        ring += 1;
      }
    }
  }

}
