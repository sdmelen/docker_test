#include <fcgi_stdio.h>
#include <stdio.h>

int main() {
  while (FCGI_Accept() >= 0) {
    printf("Content-type: text/html\r\n"
           "\r\n"
           "<html>\n"
           "<head>\n"
           "<title>Hello World!</title>\n"
           "</head>\n"
           "<body>\n"
           "<h1>Hello World!</h1>\n"
           "</body>\n"
           "</html>\n");
  }
  return 0;
}
