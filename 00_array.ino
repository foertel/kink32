bool int_in_array(int item, int data[]) {
  int sizeOfData = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeOfData; i++) {
    if (data[i] == item) return true;
  }
  return false;
}

bool chr_in_array(char* item,  data[]) {
  int sizeOfData = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeOfData; i++) {
    if (data[i] == item) return true;
  }
  return false;
}