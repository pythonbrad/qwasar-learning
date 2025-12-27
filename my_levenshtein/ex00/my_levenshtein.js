function my_levenshtein(s1, s2) {
	var x = 0;
	var score = 0;

	if (s1.length != s2.length) {
		return -1;
	}

	while (x < s1.length) {
		if (s1[x] != s2[x]) {
			score = score + 1;
		}

		x++;
	}

	return score;
}

// console.log(my_levenshtein("GGACTGA", "GGACTGA"));
// console.log(my_levenshtein("ACCAGGG", "ACTATGG"));
// console.log(my_levenshtein("GGACGGATTCTG", "AGG"));
// console.log(my_levenshtein("", ""));
