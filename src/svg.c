#include <stdio.h>
#include "svg.h"

void svg_begin(FILE *fp){
    if (!fp) return;

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp,
        "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
        "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
    );
}

void svg_end(FILE *fp){
    if (!fp) return;
    
    fprintf(fp, "</svg>\n");
}
