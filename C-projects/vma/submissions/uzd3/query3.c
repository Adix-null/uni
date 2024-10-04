#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Student {
	char name[30];
	char surname[30];
	int course;					// year of study
	double average; 			// average grade

	int load; 					// number of courses
	char courses[10][30]; 		// course names
	int grades[10]; 			// course grades

	char languages[100];		// spoken languages

} Student;




int main(int argc, char *argv[]) {
	FILE *db = NULL;
	// open database file for reading, provide a parameter or use default "db.bin"
	if (argc > 1)
		db = fopen(argv[1], "rb");
	else
		db = fopen("db.bin", "rb");

    //int ef;("%d", &ef);

	if (db){
		Student students[1000];			// all the data goes here
		int size = 0;					// how many students in database

		// reading data from file
		fread(&size, sizeof(int), 1, db);

		for (int i = 0; i < size; i++){
			fread(&students[i], sizeof(Student), 1, db);
		}
        //printf("%d records loaded succesfully\n", size);


		// MODIFY CODE BELOW


        char otp[999];
        char total[999000];

		int counterDemo = 0; // for counting students

		for (int i = 0; i < size; ++i){ // process all the student records in database
			Student s = students[i]; // store data for each student in s

            char vowels[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
            bool start_vowel = false;
            for(int i = 0; i < sizeof(vowels) / sizeof(char); i++)
            {
                if(s.name[0] == vowels[i])
                {
                    start_vowel = true;
                    break;
                }
            }

			if(!start_vowel){ // *** first filter, conditions on the student
				sprintf(otp, "%15s %15s %3d %10f %3d ", s.name, s.surname, s.course, s.average, s.load); // print student data
				strcat(total, otp);
				int anotherDemo = 0; // for counting courses/grades
				for (int i = 0; i < s.load; ++i){ // process each course taken by the student
					if(1){ // *** second filter, conditions on the course/grade
						++anotherDemo; // counting courses
						sprintf(otp, "%25s %3d ", s.courses[i], s.grades[i]);
						strcat(total, otp);
					}
				}
				sprintf(otp, "%s\n", s.languages);
				strcat(total, otp);

				if (anotherDemo == s.load) // *** third filter, various other conditions
					++counterDemo; // counting studfents
			}
		}
		printf("%d\n%s", counterDemo, total); // how many passed the filters
		fclose(db);
	} else {
		printf("File db.bin not found, check current folder\n");
	}

	return 0;
}
