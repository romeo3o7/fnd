#include <stdio.h>

int packageGudie() {
        fprintf(stderr, "  Structure: Package <option> <package/file>\n");
        fprintf(stderr, "  Options:\n");
        fprintf(stderr, "  < -i for installed >:   the files this package has installed.\n");
        fprintf(stderr, "  < -m for metadata>:     the metadata of the package \n");
        fprintf(stderr, "  < -d for depndency:     what this package requires to run\n");
        fprintf(stderr, "  < -r for required:      packages that require it\n");
        fprintf(stderr, "  < -o for own>:          packages who owns this file\n");
        return 1;
}
