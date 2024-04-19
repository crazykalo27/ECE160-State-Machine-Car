float readLight() {
  float light = analogRead(g_photoresistorPin);
  return light;
}
