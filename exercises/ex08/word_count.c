/** Script to count words in a text file.
Utilizes glib and hashtables.
Big thanks to the glib documentation and the fact you can just add g_ to anything.
**/

/** Answers to the questions.
1. GLib is a compilation of three low-level C system libraries developed by
GNOME. It provides data structures. memory management, standard macros, warnings
and assertions, dynamic loading of modules, and thread functionality. Originally
it was a part of GTK so it can be used by software other then GNOME.
2. The pros of using Glib is that it seems very useful in providing data structures,
in particular advanced ones, for which implementation would be arduous. The con is
figuring out all of the various GLib calls, which seems to boil down to putting a 
'g' or a 'g_' in front of everything.
3. gcc ex_compile.c -Wall -o ex_compile `pkg-config --cflags --libs glib-2.0`
**/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

/**
Function to split the input text into words.
Returns an array of type gchar (aka the words)
**/
gchar ** split_input () {
	gchar *filename = "tos.txt";
	gchar *input_text;
	gsize length;
	GError *error = NULL;

	// if there is an error getting contents
	if (! g_file_get_contents(filename, &input_text, &length, &error)) {
		g_error ("g_file_get_contents() failed: %s", error->message);
	}

	return (g_strsplit(input_text, " ", -1));
}

/**
Function to count the words. Done via hashtable.
Takes in the words and the hashtable to store.
**/
void count_words (gchar ** splitin, GHashTable *table) {
	gchar **ptr;
	gchar *key;

	// goes through everything in the gchar array
	for (ptr = splitin; *ptr; ptr++) {
		key = *ptr;

		// it exists? then update the value
		if (g_hash_table_lookup (table, g_strdup(key)) != NULL) {
			g_hash_table_insert(table, g_strdup(key), g_hash_table_lookup(table, g_strdup(key)) + 1);
		}
		// doesn't exist? then initialize the value to 1
		else {
			g_hash_table_insert(table, g_strdup(key), GINT_TO_POINTER(1));
		}

	}
}


/**
Function to print out the values of the hashtable
**/
void print_hash(gpointer key, gpointer value, gpointer user_data){
	char * pkey = (char *) key;
	int pvalue = GPOINTER_TO_INT(value);

	printf("%s - %d\n", pkey, pvalue);


}

/**
Main function - it splits the text, counts them, and prints out the counts
**/
int main() {
	gchar ** contents;
	GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
	contents = split_input();
	count_words(contents, table);
	g_hash_table_foreach(table, print_hash, NULL);

	return 0;
}

