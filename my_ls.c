#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct s_string_array {
	int size;
	char **array;
} string_array;

typedef struct s_option {
	bool incl_dot_file;
	bool time_sort;
} option;

typedef struct s_path_linkedlist {
	char *path;
	struct timespec st_mtim;
	mode_t st_mode;
	struct s_path_linkedlist *next;
} path_linkedlist;

// Compare two strings based on the lexicographical order.
int my_strcmp(char *haystack, char *needle) {
	while (*haystack == *needle && *haystack != '\0' && *needle != '\0') {
		haystack++;
		needle++;
	}

	if (*haystack == *needle) {
		return 0;
	} else if (*haystack < *needle) {
		return 1;
	}
	
	return -1;
}

//
string_array* my_string_array_sort(string_array *data) {
	char *temp = NULL;

	for (int i = 0; i < data->size; i++) {
		for (int j = i+1; j < data->size; j++) {
			if (my_strcmp(data->array[i], data->array[j]) == 1) continue;

			// swap
			temp = data->array[i];
			data->array[i] = data->array[j];
			data->array[j] = temp;
		}
	}

	return data;
}

/*
 * Insert a path node based on his time order on the list.
 * Note that the new node will be freed if the root is empty.
 *
 * The argument `opt` can be null.
 */
void sort_path_insert(path_linkedlist *node, path_linkedlist *new_node, option *opt) {
	path_linkedlist *parent = NULL;
	path_linkedlist temp = {0};

	while (node != NULL && node->path != NULL) {
		// Time sort.
		if (opt != NULL && opt->time_sort && (
			new_node->st_mtim.tv_sec > node->st_mtim.tv_sec
			|| (new_node->st_mtim.tv_sec == node->st_mtim.tv_sec
				&& new_node->st_mtim.tv_nsec > node->st_mtim.tv_nsec)
		)) break;

		// Lexicographical sort.
		if (opt != NULL && !opt->time_sort && my_strcmp(new_node->path, node->path) == 1) break;

		parent = node;
		node = node->next;
	}

	// Empty root node.
	if (parent == NULL && node->path == NULL) {
		*node = *new_node;

		free(new_node);
	}
	// Insert at root node.
	else if (parent == NULL) {
		temp = *node;
		*node = *new_node;
		*new_node = temp;

		node->next = new_node;
	}
	// Insert in the middle / end.
	else {
		parent->next = new_node;
		new_node->next = node;
	}
}

// Create a path node based on the provided string path.
path_linkedlist* new_path_linkedlist(char *path) {
	struct stat path_stat;
	path_linkedlist *node;

	if (stat(path, &path_stat) == -1) return NULL;

	node = malloc(sizeof(path_linkedlist));
	node->path = path;
	node->st_mtim = path_stat.st_mtim;
	node->st_mode = path_stat.st_mode;
	node->next = NULL;

	return node;
}

//
int my_strlen(char *str) {
	int length = 0;;

	while (*str++ != '\0') length++;

	return length;
}

// Concat two strings.
char* my_pathcat(char *a, char *b) {
	// a + '/' + b + '\0'
	int size = my_strlen(a) + my_strlen(b) + 2;
	char *temp = malloc(size * sizeof(char));
	char *ptr = temp;

	while (*a != '\0') {
		*ptr++ = *a++;
	}

	// Add the slash if missing.
	*ptr++ = '/';

	while (*b != '\0') {
		*ptr++ = *b++;
	}

	*ptr = '\0';

	return temp;
}

// Free the memory used by a path linkedlist.
void free_path_linkedlist(path_linkedlist *node) {
	path_linkedlist *temp_node = node;

	while (node != NULL) {
		temp_node = node;
		node = node->next;

		free(temp_node);
	}
}

//
char* my_basename(char *path) {
	char *out = path;

	while (*path != '\0') {
		if (*path == '/') {
			out = path + 1;
		}

		path++;
	}

	return out;
}

// Display the items of a directory.
void glob(char *path, option *opt) {
	path_linkedlist root_dirent_node = {0};
	path_linkedlist *node = NULL;

	DIR *dirp = NULL;
	struct dirent *dirent = NULL;
	char *dirent_path = NULL;

	dirp = opendir(path);

	while ((dirent = readdir(dirp)) != NULL) {
		if (!opt->incl_dot_file && *dirent->d_name == '.') continue;

		// Prepare the new node.
		dirent_path = my_pathcat(path, dirent->d_name);
		if ((node = new_path_linkedlist(dirent_path)) == NULL) continue;

		sort_path_insert(&root_dirent_node, node, opt);
	}

	for (node = &root_dirent_node; node != NULL; node = node->next) {
		printf("%s\n", my_basename(node->path));

		free(node->path);
	}

	free_path_linkedlist(root_dirent_node.next);

	closedir(dirp);
}

// Contains the main logic of the program.
void _my_ls(string_array *paths, option *opt) {
	path_linkedlist root_filenode = {0};
	path_linkedlist root_dirnode = {0};
	path_linkedlist *node = NULL;

	my_string_array_sort(paths);

	if (paths->size == 0) {
		// Prepare the new node.
		if ((node = new_path_linkedlist(".")) != NULL) {
			sort_path_insert(&root_dirnode, node, NULL);
		}
	}
	// else
	for (int i = 0; i < paths->size; i++) {
		// Prepare the new node.
		if ((node = new_path_linkedlist(paths->array[i])) == NULL) continue;

		switch (node->st_mode & S_IFMT) {
		case S_IFREG:
			sort_path_insert(&root_filenode, node, opt);
			break;
		case S_IFDIR:
			sort_path_insert(&root_dirnode, node, NULL);
			break;
		default:
			// TODO: Handle it.
			break;
		}
	}

	// Display
	for (node = &root_filenode; node != NULL && node->path != NULL; node = node->next) {
		printf("%s\n", node->path);
	}

	if (root_filenode.path != NULL) {
		printf("\n");
	}

	for (node = &root_dirnode; node != NULL && node->path != NULL; node = node->next) {
		// Only if there is many directories to display.
		if (root_dirnode.next != NULL) {
			printf("%s:\n", node->path);
		}

		glob(node->path, opt);

		if (node->next != NULL) {
			printf("\n");
		}
	}

	// Clean from the dynamic allocated memory
	free_path_linkedlist(root_filenode.next);
	free_path_linkedlist(root_dirnode.next);
}

void print_help() {
	printf("my_ls -- list directory contents.\n");
	printf("Usage: my_ls [-at] [file ...]\n");
	printf("-a Include directory entries whose names begin with a dot (.).\n");
	printf("-t Sort by time modified (most recently modified first)\n");
	printf("\tif not specified, the sorting will be in a lexicographical order.");
}

int main(int argc, char **argv) {
	string_array args = {0};

	option opt = {false};

	// Parse arguments.
	// Skip the first argument.
	for (int argi = 1; argi < argc; argi++) {
		if (argv[argi][0] != '-') {
			args.size = argc - argi;
			args.array = argv + argi;

			break;
		}

		if (my_strcmp(argv[argi], "--help") == 0) {
			print_help();

			return 0;
		}

		for (int i = 1; argv[argi][i] != '\0'; i++) {
			switch (argv[argi][i]) {
			case 'a':
				opt.incl_dot_file = true;
				break;
			case 't':
				opt.time_sort = true;
				break;
			default:
				printf("Unknow option `-%c`.\n", argv[argi][i]);
				return 1;
			}
		}
	}

	// Start the logic.
	_my_ls(&args, &opt);

	return 0;
}
