#include <stdio.h>

/*Ввести строку и слово. Вывести количество слов в строке,
имеющих длину, равную длине введенного слова.*/

int count_match_words(char * line, int size, char * word, int word_size) {
	int len = 0, i = 0, count = 0, ip = 0;
	char n;
	while (ip < word_size) {
		n = word[ip];
		ip++;
		if (n == '\n' || n == ' ') break;
		if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z')) {
			len++;
		}
	}
	ip = 0;
	while (ip < size) {
		n = line[ip];
		ip++;
		if (n == '\n' || n == ' ') {
			if (i == len) {
				count++;
			}
			i = 0;
			if (n == '\n') break;
		}
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) {
			i++;
		}
	}
	return count;
}

int main() {
	char * line = (char *)malloc(sizeof(char) * 1024);
	char * word = (char *)malloc(sizeof(char) * 4096);
	char len = 0, word_size = 0, i = 0, n;
	int count = 0;
	printf("Enter the word: ");
	while (1) {
		if (i > 1021) break;
		scanf_s("%c", &n, 1);
		if (n == '\n' || n == ' ') break;
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) {
			word[i] = n;
			i++;
		}
	}
	word[word_size = i] = '\n';
	word[++word_size] = 0;
	i = 0;
	printf("Enter the line: ");
	while (1) {
		if (i > 4093) break;
		scanf_s("%c", &n, 1);
		if (n == '\n') break;
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122) || n == ' ') {
			line[i] = n;
			i++;
		}
	}
	line[len = i] = '\n';
	line[++len] = 0;
	count = count_match_words(line, len, word, word_size);
	printf("Result: %d", count);
	getchar();
	//getchar();
	return 0;
}