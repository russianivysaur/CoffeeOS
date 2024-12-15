void main() {
    char* welcome = "Kernel loaded";
    char* video_memory = (char*) 0xb8000;
    while(*welcome!='\0'){
      *video_memory = *welcome;
      welcome++;
    }
}

