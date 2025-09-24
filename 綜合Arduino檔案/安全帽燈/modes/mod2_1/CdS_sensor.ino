uint8_t CDS() {
  T_cds = millis();
  SUN1 = analogRead(CDSPIN);
  if (T_cds + 1500 > millis() > T_cds + 2000) {
    SUN2 = analogRead(CDSPIN);
  }
  if (T_cds + 3500 > millis() > T_cds + 4000) {
    SUN3 = analogRead(CDSPIN);
  }
  SUN = ( SUN1 + SUN2 + SUN3) / 3;

  if (SUN < DARK) {
    return 1;
  }
  if (DARK < SUN < BRIGHT) {
    return 2;
  }
  if (BRIGHT < SUN) {
    return 3;
  }

}
