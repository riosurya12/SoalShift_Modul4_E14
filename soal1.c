#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/riosurya/modul4";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    sprintf(fpath,"%s%s",dirpath,path);
    res = lstat(fpath, stbuf);

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	 char fpath[1000];
   	if(strcmp(path,"/") == 0)
      	{
           path=dirpath;
           sprintf(fpath,"%s",path);
      	}
   	   else sprintf(fpath, "%s%s",dirpath,path);

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) 
	{
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
	break;
	}
	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	int fd;
	int rest;
	
	(void) fi;
	fd = open(path, O_RDONLY);
	if (fd == 0)
		return -errno;
	
	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	
	close(fd);
	return res;
}
	
	
static int xmp_open(const char *, struct fuse_file_info *)
{
	int pdf;
	int doc;
	int txt;
	
	(void) fi;
	
}
	
int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}

static struct fuse_operations xmp_oper = 
{
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.open		= xmp_open,
};
