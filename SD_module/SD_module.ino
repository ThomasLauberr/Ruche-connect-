#include <SPI.h>
#include <SD.h>

File root, file;

void setup() {
  Serial.begin(9600);
  const int pin_CS = 53;
  Serial.println(SD.begin(pin_CS));
  root = SD.open("/");
  print_directory(root, 0);
} 

void loop() {
}

void print_directory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      print_directory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void write_file(String filename, String content) {
  file = SD.open(filename, FILE_WRITE);
  if (file) {
    file.println(content);
    file.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void read_file(String filename) {
  file = SD.open(filename, FILE_READ);
  if (file) {
    // read from the file until there's nothing else in it:
    while (file.available()) {
      Serial.write(file.read());
    }
    // close the file:
    file.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void delete_file(String filename) {
  SD.remove(filename);
}