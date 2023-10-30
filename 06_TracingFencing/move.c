#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 64

int main(int argc, char **argv)
{
	char *infile, *outfile;
	int infd, outfd;
	int read_bytes;
	int err = 1;
	char *buf;

	if (argc != 3) {
		fprintf(stderr, "Usage: ./move infile outfile\n");
		return err;
	}

	infile = argv[1];
	outfile = argv[2];

	if (!strcmp(infile, outfile)) {
		fprintf(stdout, "./move is no-op: infile and outfile are the same file\n");
		return 0;
	}

	infd = open(infile, O_RDONLY);
	if (infd == -1) {
		perror("Failed to open infile");
		err = 2;
		goto err_open_infd;
	}

	outfd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	if (outfd == -1) {
		perror("Failed to open outfile");
		err = 3;
		goto err_open_outfd;
	}

	buf = malloc(BUF_SIZE * sizeof(*buf));
	if (!buf) {
		perror("Failed to allocate buffer");
		err = 4;
		goto err_alloc_buf;
	}

	while ((read_bytes = read(infd, buf, BUF_SIZE * sizeof(*buf))) > 0) {
		int ret_write = write(outfd, buf, read_bytes);
		if (ret_write == -1) {
			perror("Failed to write data to outfile");
			err = 5;
			goto err_write_outfd;
		} else if (ret_write < read_bytes) {
			if (lseek(infd, ret_write - read_bytes, SEEK_CUR) == -1) {
				perror("Failed to execute lseek inside infile");
				err = 6;
				goto err_lseek;
			}
		}
	}

	if (read_bytes == -1) {
		perror("Failed to read from infile");
		err = 7;
		goto err_read;
	}

	err = 0;
err_read:
err_lseek:
err_write_outfd:
	if (err && remove(outfile) == -1) {
		perror("Failed to remove outfile");
		err = 8;
	}
	free(buf);
err_alloc_buf:
	if (close(outfd) == -1) {
		perror("Failed to close outfile");
		err = 9;
	}
err_open_outfd:
	if (close(infd) == -1) {
		perror("Failed to close infile");
		err = 10;
	}

	if (!err && remove(infile) == -1) {
		perror("Failed to remove infile");
		err = 11;
	}
err_open_infd:
	if (err)
		return err;
	return 0;
}
