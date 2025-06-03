#ifndef  NOTEPAD_H
#define  NOTEPAD_H

#define MAX_NOTE_LENGTH     256
#define FILENAME            "notes.txt"
#define CATEGORY_COUNT      3

extern const char *categories[];

void addNote(void);
void viewNotes(void);
void searchNotes(void);
void deleteNote(void);
void viewNotesByCategory(void);

#endif
