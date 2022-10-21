#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
 mkdir("dir1", 0700);
 mkdir("dir1/subdir", 0700);
 mkdir("dir2", 0600);
 mkdir("dir2/subdir", 0700);
 mkdir("dir3", 0500);
 mkdir("dir3/subdir", 0700);
 symlink("dir1/subdir","quick1");
 symlink("dir2/subdir","quick2");
 symlink("dir3/subdir","quick3");
return 0;
}

