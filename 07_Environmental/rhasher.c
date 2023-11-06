#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <strings.h>
#include <ctype.h>
#include <sys/types.h>
#include <rhash.h>
#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif /* ifdef USE_READLINE */

int make_file_hash(char *file_path, unsigned int hash_algo, unsigned char *digest)
{
	int res = rhash_file(hash_algo, file_path, digest);
	if (res < 0) {
		fprintf(stderr, "LibRHash error: %s: %s\n", file_path, strerror(errno));
		return -1;
	}
	return 0;
}

int make_string_hash(char *msg, unsigned int hash_algo, unsigned char *digest)
{
	int res = rhash_msg(hash_algo, msg, strlen(msg), digest);
	if (res < 0) {
		fprintf(stderr, "LibRHash error: message digest calculation error\n");
		return -1;
	}
	return 0;
}

unsigned int extract_hash_algo_type(char *hash_algo_str)
{
	if (!strcasecmp(hash_algo_str, "MD5")) {
		return RHASH_MD5;
	} else if (!strcasecmp(hash_algo_str, "SHA1")) {
		return RHASH_SHA1;
	} else if (!strcasecmp(hash_algo_str, "TTH")) {
		return RHASH_TTH;
	} else {
		fprintf(stdout, "Invalid hash algo type, backing on SHA256\n");
		return RHASH_SHA256;
	}
}

ssize_t getline_wrapper(char **lineptr, size_t *n, FILE *stream)
{
	const char *prompt = "> ";
#ifdef USE_READLINE
	*lineptr = readline(prompt);
	if (*lineptr == NULL)
		return -1;
	return strlen(*lineptr);
#else
	fprintf(stdout, "%s", prompt);
	return getline(lineptr, n, stream);
#endif /* ifdef USE_READLINE */
}

int main(int argc, char *argv[])
{
	char *cur_line = NULL;
	FILE *stream = stdin;
	size_t cur_len;
	ssize_t nread;

	rhash_library_init();

	while ((nread = getline_wrapper(&cur_line, &cur_len, stream)) != -1) {
		unsigned char digest[64];
		unsigned int hash_algo;
		char *hash_algo_str;
		char *arg_to_hash;
		char output[130];

		if ((hash_algo_str = strtok(cur_line, " ")) == NULL) {
			fprintf(stderr, "hash_algo not specified\n");
			goto loop_exit;
		}
		hash_algo = extract_hash_algo_type(hash_algo_str);

		if ((arg_to_hash = strtok(NULL, " ")) == NULL) {
			fprintf(stderr, "filename/string not specified\n");
			goto loop_exit;
		}

		if (arg_to_hash[0] == '"') {
			arg_to_hash = arg_to_hash + 1;
			if (make_string_hash(arg_to_hash, hash_algo, digest) < 0)
				goto loop_exit;
		} else {
			if (make_file_hash(arg_to_hash, hash_algo, digest) < 0)
				goto loop_exit;
		}

		if (islower(hash_algo_str[0]))
			rhash_print_bytes(output, digest, rhash_get_digest_size(hash_algo), RHPR_BASE64);
		else
			rhash_print_bytes(output, digest, rhash_get_digest_size(hash_algo), RHPR_HEX);

		fprintf(stdout, "%s (%s) = %s\n", rhash_get_name(hash_algo), arg_to_hash, output);
loop_exit:
		free(cur_line);
		cur_line = NULL;
	}

	free(cur_line);
	return 0;
}
